#!/usr/bin/env bash


set -o errexit
set -o nounset

: ${CMSSW_BASE:?"CMSSW_BASE is not set!  Run cmsenv before recipe.sh"}

install=$CMSSW_BASE/src/URAnalysis/install
v_CMSSW=$(echo $CMSSW_VERSION | awk -F_ '{print $2 $3}')

#add recipe to include pseudoTop code
if [ "$v_CMSSW" -ge 74 ]; then 
    $install/install_pseudoTop.sh
else
    $install/install_pseudoTop_manually.sh
fi

#install RooUnfold
$install/install_roounfold.sh

#installing python
$install/install_python.sh

#installing rake
$install/install_rake.sh
