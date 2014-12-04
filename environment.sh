#!/bin/bash 

# Setup the environment for the framework

echo "Setting up CMSSW runtime environment"
eval `scramv1 runtime -sh`

export URA=$CMSSW_BASE/src/URAnalysis/
echo "Setting variable \$URA=$URA"

export URA_BASE=$CMSSW_BASE/src

vpython=$base/URAnalysis/external/virtualenv
echo "Activating python virtualenv from $vpython"

if [ -d "$vpython" ]; then
  echo "Activating python virtual environment"
  export VIRTUAL_ENV_DISABLE_PROMPT=1
  pushd $vpython
  # See https://github.com/pypa/virtualenv/issues/150
  source bin/activate
  popd
fi

#source site-dependent configuration
source $URA/Configuration/site/site_configuration.sh

# Put the PWD into the PYTHONPATH
export PYTHONPATH=.:$PYTHONPATH
# Make sure we prefer our virtualenv packages
export PYTHONPATH=$vpython/lib/python2.7/site-packages/:$PYTHONPATH

# Don't require a scram build to get updated scripts
export PATH=$URA/Utilities/scripts:$PATH
export PATH=$URA/PlotTools/scripts:$PATH

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
