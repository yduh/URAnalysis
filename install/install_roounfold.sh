#! /bin/env bash

echo "Installing RooUnfold..."
pushd ../external/src/

svn co https://svnsrv.desy.de/public/unfolding/RooUnfold/trunk RooUnfold
pushd RooUnfold
svn up -r349
make
popd
popd

echo "Installing TUnfold..."
pushd ../external/src/TUnfold
tar -xf TUnfold.tgz
make lib
popd
