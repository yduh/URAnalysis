#! /bin/env python

'''
holds the process until all condor jobs are done
'''

import subprocess, time, os
from pdb import set_trace

escape = False
while not escape:
   proc = subprocess.Popen(["condor_q", os.environ['USER']], stderr=subprocess.PIPE, stdout=subprocess.PIPE)
   stdout, stderr = proc.communicate()
   last = stdout.split('\n')[-2]
   njobs = int(last.split()[0])
   if njobs == 0:
      print "Jobs completed! exiting..."
      escape = True
   else:
      print "%i jobs are still running, checking again in 30 seconds" % njobs
      time.sleep( 30 )
