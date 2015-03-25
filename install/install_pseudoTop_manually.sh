#!/bin/bash

pushd $CMSSW_BASE/src
git fetch official-cmssw
git checkout CMSSW_7_5_X_2015-03-23-1200 -- TopQuarkAnalysis
popd
