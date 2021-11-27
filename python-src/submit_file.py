import platform
import time
import sys
import os

from selenium import webdriver
from selenium.webdriver.chrome.options import Options

import creds

PYTHON_VENV_DIR = os.path.dirname(os.path.realpath(__file__))
PYTHON_VERSION = f'{sys.version_info[0]}.{sys.version_info[1]}'
CHROME_DRIVER_RELATIVE_ROOT = f'{PYTHON_VENV_DIR}/env/lib/python{PYTHON_VERSION}/site-packages/chromedriver_py'
CHROME_DRIVER_BIN_NAMES = {
    'Darwin': 'chromedriver_mac64',
    'Windows': 'chromedriver_win32.exe',
    'Linux': 'chromedriver_linux64'
}

CSS_SELECTORS = {
    'login_id': '#nick',
    'login_password': 'body > div.skeleton > div.content-wrapper > div > form > fieldset > p:nth-child(2) > input[type=password]',
    'login_submit': 'body > div.skeleton > div.content-wrapper > div > form > p > input[type=submit]',
    'task_submit_tab': 'body > div.skeleton > div.navigation > div.title-block > ul > li:nth-child(2) > a',
    'task_file_selector': 'body > div.skeleton > div.content-wrapper > div.content > form > p:nth-child(4) > input[type=file]',
    'task_submit_button': 'body > div.skeleton > div.content-wrapper > div.content > form > p:nth-child(6) > input[type=submit]',
    'status': '#status', # READY | COMPILE ERROR
    'result': 'body > div.skeleton > div.content-wrapper > div.content > table.summary-table.left-align.narrow > tbody > tr:nth-child(6) > td:nth-child(2) > span' # ACCEPTED | TIME LIMIT EXCEEDED | WRONG ANSWER
}

WEBSITE_ROOT = 'https://cses.fi'


def init_driver():
    chrome_options = Options()
    chrome_options.add_argument('--headless')  # ['--disable-extensions', '--disable-gpu', '--no-sandbox'] # linux only
    driver = webdriver.Chrome(
            f'{CHROME_DRIVER_RELATIVE_ROOT}/{CHROME_DRIVER_BIN_NAMES[platform.system()]}',
            options=chrome_options)
    return driver


def login(driver: webdriver, username: str, password: str):
    driver.get(f'{WEBSITE_ROOT}/login')
    driver.find_element_by_css_selector(CSS_SELECTORS['login_id']).send_keys(username)
    driver.find_element_by_css_selector(CSS_SELECTORS['login_password']).send_keys(password)
    driver.find_element_by_css_selector(CSS_SELECTORS['login_submit']).click()


def go_to_problem_page(driver: webdriver, problem_name: str):
    driver.get(f'{WEBSITE_ROOT}/problemset')
    driver.find_element_by_link_text(problem_name).click()
    print('go_to_problem_page:', driver.current_url)


def cses_problem_name_of(source_file_path: str):
    def capitalize(word: str):
        if word.count('i') == len(word):
            return word.upper()
        if word in {'in', 'of', 'on', 'and'}:
            return word
        return word.capitalize()

    local_filename = source_file_path.split('/')[-1]
    problem_name = local_filename.split('.')[0]
    return ' '.join([capitalize(word) for word in  problem_name.split('_')])


def submit_solution(driver: webdriver, local_file_path: str):
    driver.find_element_by_css_selector(CSS_SELECTORS['task_submit_tab']).click()
    driver.find_element_by_css_selector(CSS_SELECTORS['task_file_selector']).send_keys(local_file_path)
    driver.find_element_by_css_selector(CSS_SELECTORS['task_submit_button']).click()


def await_status(driver: webdriver):
    num_times = 10
    status = driver.find_element_by_css_selector(CSS_SELECTORS['status'])
    while (status.text == 'PENDING' or status.text.startswith('TESTING')) and num_times:
        time.sleep(1)
        num_times -= 1
        status = driver.find_element_by_css_selector(CSS_SELECTORS['status'])
    return status


def get_result(driver: webdriver):
    status = await_status(driver)
    if status.text != 'READY':
        return (driver.current_url, status.text)
    result = driver.find_element_by_css_selector(CSS_SELECTORS['result'])
    if result.text != 'ACCEPTED':
        return (driver.current_url, result.text)
    return ("OK", "VERDIK AGZINA")


def main(source_file_path: str, file_to_upload_path: str):
    driver = init_driver()
    login(driver, creds.username, creds.password)
    go_to_problem_page(driver, cses_problem_name_of(source_file_path))
    submit_solution(driver, file_to_upload_path)
    results = get_result(driver)
    print(results)
    driver.quit()

main(sys.argv[1], sys.argv[2])
