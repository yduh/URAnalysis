#! /bin/env bash

pushd ../external/src/

svn co https://svnsrv.desy.de/public/unfolding/RooUnfold/trunk RooUnfold
pushd RooUnfold
svn up -r349
make
popd
popd