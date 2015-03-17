#! /bin/env python

'''
holds the process until all condor jobs are done
'''

import subprocess, time, os
from pdb import set_trace

escape = False
start = time.time()
totjobs = -1
while not escape:
   proc = subprocess.Popen(["condor_q", os.environ['USER']], stderr=subprocess.PIPE, stdout=subprocess.PIPE)
   stdout, stderr = proc.communicate()
   last = stdout.split('\n')[-2]
   njobs = int(last.split()[0])
   eta = 'UNKNOWN'
   if totjobs <> -1:
      elapsed = time.time() - start
      completed = totjobs - njobs
      if completed != 0:
         eta_time = njobs*(elapsed/completed)
         m, s = divmod(eta_time, 60)
         h, m = divmod(m, 60)
         eta = "%d:%02d:%02d" % (h, m, s)
   else:
      totjobs = njobs
   if njobs == 0:
      print "Jobs completed! exiting..."
      escape = True
   else:
      print "%i jobs are still running, checking again in 30 seconds. ETA: %s" % (njobs, eta)
      time.sleep( 30 )
