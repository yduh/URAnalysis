#! /bin/env python

'''
holds the process until all condor jobs are done
'''

import subprocess, time, os, glob, re
from argparse import ArgumentParser
from pdb import set_trace

parser = ArgumentParser(__doc__)
parser.add_argument(
   '--check_correctness', type=str, help='check that every stdout '
   'has exit code 0, marking proper ending. Provide root submission directory', 
   default=''
   )
parser.add_argument(
   '--maxResubmission', type=int, help='resubmit the jobs a maximum of times',
   default=3
   )

args = parser.parse_args()

escape = False
start = time.time()
totjobs = -1
regex = re.compile('exit code: (?P<exitcode>\d+)')
submission = 0

while not escape:
   proc = subprocess.Popen(
      ["condor_q", os.environ['USER']], 
      stderr=subprocess.PIPE, stdout=subprocess.PIPE
      )
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
      print "Jobs completed!",
      if args.check_correctness:
         stdouts = glob.glob(os.path.join(args.check_correctness, '*/*.stdout'))
         failed_samples = set()
         for log in stdouts:
            last_line = open(log).readlines()[-1]
            match = regex.match(last_line)
            if match:
               exitcode = int(match.group('exitcode'))
               if exitcode != 0 :
                  failed_samples.add(os.path.dirname(log))
            else:
               raise ValueError("cannot match %s with exit code regex!" % last_line)
         if len(failed_samples) == 0:
            print " exiting..."
            escape = True
         else:
            if submission <= args.maxResubmission:
               submission += 1
               print " %i samples failed to complete properly! Resubmitting them..." % len(failed_samples)
               cwd = os.getcwd()
               for condor_dir in failed_samples:
                  os.chdir(condor_dir)
                  os.system("rm *.root *.stdout *.stderr")
                  os.system("condor_submit condor.jdl")
               os.chdir(cwd)
            else:
               print (" There are still some failing samples, bet the maximum numbers"
                      "of resubmission was reached, exiting...")
               escape = True
      else:        
         print " exiting..."
         escape = True
   else:
      print "%i jobs are still running, checking again in 30 seconds. ETA: %s" % (njobs, eta)
      time.sleep( 30 )
