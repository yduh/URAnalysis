#!/usr/bin/env python2
#run this script in the job collection directory to add all output files in the subdirectories
import sys, os, time

allfiles = os.listdir('.')

jobdirs = [d for d in allfiles if os.path.isdir(d)]

for dir in jobdirs:
  print dir
  if dir + '.root' in allfiles:
    continue
  confile = open(dir+'/condor.jdl', 'r')
  info = confile.read().split('\n')
  confile.close()
  info = [l.strip() for l in info if 'Queue' in l]
  num =  int(info[0].split('Queue')[1].strip())
  files = os.listdir(dir)
  files = [f for f in files if ('%s_out_' % dir) in f]
  print num, len(files)
  if num == len(files):
    files = [dir + '/' + f for f in files]
    command = 'hadd ' + dir + '.root ' + ' '.join(files)
    print command
    os.system(command)
  else:
    raise IOError('You asked to merge %i files, but only %i were found.'
                  ' Something must have gone wrong in the batch jobs.' % (num, len(files)))

