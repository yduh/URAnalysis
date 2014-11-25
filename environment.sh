#!/bin/bash 

# Setup the environment for the framework

echo "Setting up CMSSW runtime environment"
eval `scramv1 runtime -sh`

export fwk=$CMSSW_BASE/src/placeholder/
echo "Setting variable \$fwk=$fwk"

export base=$CMSSW_BASE/src

vpython=$base/placeholder/external/virtualenv
echo "Activating python virtualenv from $vpython"

# Define some shortcuts to HDFS and scratch areas
export hdfs=/hdfs/store/user/$LOGNAME/
export scratch=/scratch/$LOGNAME/

if [ -d "$vpython" ]; then
  echo "Activating python virtual environment"
  export VIRTUAL_ENV_DISABLE_PROMPT=1
  pushd $vpython
  # See https://github.com/pypa/virtualenv/issues/150
  source bin/activate
  popd
fi

# Put the PWD into the PYTHONPATH
export PYTHONPATH=.:$PYTHONPATH
# Make sure we prefer our virtualenv packages
export PYTHONPATH=$vpython/lib/python2.7/site-packages/:$PYTHONPATH

# Don't require a scram build to get updated scripts
export PATH=$fwk/Utilities/scripts:$PATH
export PATH=$fwk/PlotTools/scripts:$PATH

#activate local rake
if which ruby >/dev/null && which gem >/dev/null; then
    gemsdir=$(ruby -rubygems -e 'puts Gem.user_dir')/bin
    if $(echo "$PATH"|grep -q $gemsdir) >/dev/null; then
	echo "custom ruby already sourced"
    else
	echo "activating ruby"
	PATH="$gemsdir:$PATH"
    fi
fi
