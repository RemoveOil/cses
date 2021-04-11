die() { echo "$*" 1>&2 ; exit 1; }

CPP_FILE_PATH="$PWD/${1}"
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
PYTHON_SRC_DIR="$SCRIPT_DIR/python-src"

if [[ -z "$1" ]] || [[ ! -f $CPP_FILE_PATH ]]
then
    die "You need to supply a path to the root cpp file."
fi


if [ ! -d "$PYTHON_SRC_DIR/env" ]
then
    echo "No virtual env found in $PYTHON_SRC_DIR. Instantiating a virtual env."
    cd $PYTHON_SRC_DIR
    python3 -m venv env && . "./env/bin/activate" && pip install -r "./requirements.txt" && deactivate
    cd -
fi

. "$PYTHON_SRC_DIR/env/bin/activate" &&
python "$PYTHON_SRC_DIR/shipit.py" "$CPP_FILE_PATH" > "$SCRIPT_DIR/sendit.cpp" &&
deactivate &&
echo "Donezie."
