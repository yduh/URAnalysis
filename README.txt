============================================
 University of Rochester analysis framework
============================================

Installation
============

Current CMSSW version supported is CMSSW_7_2_3_patch1

```
scram pro -n MyWorkingAreaName CMSSW CMSSW_7_2_3_patch1
cd MyWorkingAreaName/src
# Setup your CMSSW environment
cmsenv
# Run this before doing ANYTHING else in src because REASONS
git cms-init

# Now get the analysis package
# Clone the git repository...
git clone --recursive https://git.cern.ch/ldap/ur-gitmaster URAnalysis

#...and install the dependencies
cd URAnalysis/install
./install.sh

#compile
cd ../..
# Avoid the new strict version of the compiler by relaxing some flags
#export USER_CXXFLAGS="-Wno-delete-non-virtual-dtor -Wno-error=unused-but-set-variable -Wno-error=unused-variable -Wno-error=sign-compare -Wno-error=reorder"
scram b -j 8
```

    Usage
============

Whenever using the package in a new shell you need to source the 
CMSSW+Framework environment by doing

cd MyWorkingAreaName/src/placeholder
source environment.sh

And you are set to go!

