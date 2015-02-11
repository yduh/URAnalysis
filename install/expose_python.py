#! /usr/bin/env python

'''
Expose local packages to python when running on your laptop
'''

import os
import sys
import logging
from glob import glob
logging.basicConfig(level=logging.WARNING, stream=sys.stderr)

def subdirs(path):
   for obj in os.listdir(path):
      subpath = os.path.join(path, obj)
      if os.path.isdir(subpath):
         yield subpath
         continue
      elif os.path.islink(subpath):
         yield os.path.realpath(subpath)
         continue

def make_visible(path):
   init_file = os.path.join(path, '__init__.py')
   if not os.path.isfile(init_file):
      logging.debug('creating %s' % init_file)
      with open(init_file, 'w') as i:
         i.write("#automatically created")
   for sub in subdirs(path):
      logging.debug('descending into %s' % sub)
      make_visible(sub)

def make_link(pypath):
   name = pypath.split('/')[-2]
   lpath = os.path.join(ura, 'external/URAnalysis', name)
   if not os.path.islink(lpath):
      logging.debug('symlinking %s to %s' % (pypath, lpath))
      os.symlink(pypath, lpath)
   else:
      logging.debug('symlink %s already exists, skipping..' % lpath)

ura = os.environ['URA']
urpy = os.path.join(ura, 'external/URAnalysis')
if not os.path.isdir(urpy):
   os.makedirs(urpy)

pydirs = glob(os.path.join(ura,'*/python'))
for pydir in pydirs:
   make_link(pydir)

make_visible(urpy)
