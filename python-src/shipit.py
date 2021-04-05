import argparse

from utility_objects import MakeBelievePreprocessor

def path_to_entry_file():
    parser = argparse.ArgumentParser()
    parser.add_argument('src_path', type=str, help='Relative? path of cpp file.')
    return parser.parse_args().src_path


# TODO: do some sanity checks on given path?
# TODO: take output file path as cmd arg?
entry_path = path_to_entry_file()
preprocessor = MakeBelievePreprocessor(entry_path)
preprocessor.read_files_and_create_dependency_graph()
preprocessor.merge_files_and_print()
