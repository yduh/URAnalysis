#! /bin/bash

function testcmd {
    if which $1 >/dev/null; then
	echo "$1 found";
    else
	echo "please install $1";
    fi;
}

function testpkg {
    if  python -c "import $1" >&/dev/null; then
	echo "$1 found";
    else
	echo "please install $1";
    fi;
}

testcmd 'pip'
testpkg 'uncertainties'
testpkg 'progressbar'
testpkg 'argparse'
testpkg 'rootpy'

echo "---------------------------------------------------------"
echo "OPTIONALS (you do not need them, but are very convenient)"
echo "---------------------------------------------------------"

testpkg pudb
testcmd yolk
testcmd ipython

