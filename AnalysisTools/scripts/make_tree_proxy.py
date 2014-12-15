#! /bin/env python

'''
Takes as input a root file name and the path for the TTree
to use as sample. Builds in place a C++ code to read it
named URStreamer.C
'''

import os, sys
from argparse import ArgumentParser
from pdb import set_trace
import URAnalysis.AnalysisTools.autocode.types as cpp_types
parser = ArgumentParser(__doc__)
parser.add_argument('tfile_name', type=str)
parser.add_argument('tree_path', type=str)

args = parser.parse_args()

if not os.path.isfile(args.tfile_name):
   raise ValueError('%s does not exist!' % args.tfile_name)

import ROOT
tfile = ROOT.TFile.Open(args.tfile_name)
tree  = tfile.Get(args.tree_path)
if not tree:
   raise ValueError('%s does not exist!' % args.tree_path)

branches = [cpp_types.BranchMeta(i) for i in tree.GetListOfBranches()]
objects  = set(i.name.split('_')[0] for i in branches if i.is_object)
objects  = [cpp_types.ObjectMeta(
      i, 
      [j for j in branches if j.name.startswith(i)]
      ) for i in objects]

streamer = cpp_types.StreamerMeta(branches, objects)

with open('URStreamer.h', 'w') as output:
   output.write(streamer.cpp_dump())

ldef = cpp_types.LinkDefMeta(objects)
with open('LinkDef.h', 'w') as output:
   output.write(ldef.cpp_dump())

#Compile macro
#ROOT.gROOT.ProcessLine('.L URStreamer.C+')
os.system('rootcint -f Dict.cxx -c ./URStreamer.h LinkDef.h')
os.system('g++ -Wall -shared -fPIC -o Dict.so Dict.cxx `root-config --cflags --glibs`')
