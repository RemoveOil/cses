from typing import Dict, List, Set
import re
import networkx as nx

from pathlib import Path

class IncludeDirectives:
    ANGLE_PATTERN = re.compile(r'^\s*#\s*include\s*<(\w+)>\s*$')  # no spaces between angles and text?
    QUOTE_PATTERN = re.compile(r'^\s*#\s*include\s*"(.+)"\s*$')  # .+ too naive?
    def __init__(self) -> None:
        self.angles: List[str] = []
        self.quotes: List[str] = []

    # return True iff `line` is an include directive.
    def add_include_directive(self, line: str) -> bool:
        angle_match = IncludeDirectives.ANGLE_PATTERN.match(line)
        quote_match = IncludeDirectives.QUOTE_PATTERN.match(line)
        if not (angle_match or quote_match):
            return False
        if angle_match:
            self.angles.append(angle_match.group(1))
        if quote_match:
            self.quotes.append(quote_match.group(1))
        return True


class CppFile:
    def __init__(self, absolute_path) -> None:
        self.includes: IncludeDirectives = IncludeDirectives()
        self.body_lines: List[str] = []
        self.__path: Path = Path(absolute_path)  # throw if path not absolute?
        with self.__path.open() as physical_file:
            physical_lines = physical_file.read().splitlines()
        for line in physical_lines:
            if not self.includes.add_include_directive(line):
                self.body_lines.append(line)

    @property
    def path(self) -> str:
        '''Returns the absolute path of file as str.'''
        return str(self.__path.absolute())

    # extracts lib name.
    def std_dependencies(self) -> Set[str]:
        return set(self.includes.angles)

    def local_dependencies(self) -> Set[str]:
        '''Returns a set of absolute paths of upstream dependencies.'''
        parent_dir = self.__path.parent
        return {str(parent_dir.joinpath(q).resolve()) for q in self.includes.quotes}


class MakeBelievePreprocessor:
    def __init__(self, entry_path: str) -> None:
        self.main_file_path = entry_path
        self.entry = CppFile(entry_path)
        self.local_files: Dict[str, CppFile] = {entry_path: self.entry}
        self.dependency_graph = nx.DiGraph()

    def read_files_and_create_dependency_graph(self):
        file_stack = [self.entry]
        while file_stack:
            current_file = file_stack.pop()
            for dependency_path in current_file.local_dependencies():
                self.dependency_graph.add_edge(current_file.path, dependency_path)
                if dependency_path not in self.local_files:
                    dependency_file = CppFile(dependency_path)
                    self.local_files[dependency_path] = dependency_file
                    file_stack.append(dependency_file)

        if not nx.is_directed_acyclic_graph(self.dependency_graph):
            raise SystemError('fucked up dependency tree at hand.')

    def merge_files_and_print(self):
        merged_lines = []
        merged_lines.extend(self.__create_std_lib_lines(self.local_files.values()))
        files_in_reverse_order = list(nx.topological_sort(self.dependency_graph))
        for file_path in reversed(files_in_reverse_order):
            merged_lines.extend(self.local_files[file_path].body_lines)

        # TODO: remove comments?
        # TODO: optimise namespace lines?  -> i.e skip lines of using namespace xxx if namespace is already xxx
        # TODO: wrap this bit in a function? if you do, also wrap above merging bits in another one?
        # TODO: write tests for regex
        file_content = '\n'.join(merged_lines)
        file_content = re.sub(r'\s*//.*?$', '', file_content, flags=re.MULTILINE)  # truncate line after //
        file_content = re.sub(r'/\*.*\*/', '', file_content, flags=re.DOTALL)  # remove /* ... */
        file_content = re.sub(r'\n\n\n+', '\n\n', file_content)  # at most 1 empty line?
        print(file_content)


    # TODO: sort these for style points ^_^?
    def __create_std_lib_lines(self, files: List[CppFile]):
        std_lib_names = list(set().union(*[file.std_dependencies() for file in files]))
        return [f'#include <{lib_name}>' for lib_name in std_lib_names]
