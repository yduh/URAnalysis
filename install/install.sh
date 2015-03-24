#!/usr/bin/env bash


set -o errexit
set -o nounset

: ${CMSSW_BASE:?"CMSSW_BASE is not set!  Run cmsenv before recipe.sh"}

install=$CMSSW_BASE/src/URAnalysis/install

#add recipe to include pseudoTop code

#install RooUnfold
$install/install_roounfold.sh

#installing python
$install/install_python.sh

#installing rake
$install/install_rake.sh