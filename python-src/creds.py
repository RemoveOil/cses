from getpass import getpass


f = {
    'username': input,
    'password': getpass        
}


username = None
password = None


def input_creds(cred: str, prompt: str):
    if cred is None:
        cred = f[prompt](f'Input {prompt} : ')
    return cred


username = input_creds(username, 'username')
password = input_creds(password, 'password')
