#!/bin/bash

pushd $CMSSW_BASE/src
git cms-addpkg TopQuarkAnalysis/TopEventProducers
popd
