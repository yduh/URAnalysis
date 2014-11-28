#! /bin/env python

'''
Threaded script to extract meta data from NTuple root
files.

Author: Mauro Verzetti UR
'''

from Queue import Queue
import threading
import placeholder.Utilities.prettyjson as prettyjson
from placeholder.Utilities.threadtools import LockedObject
import ROOT
import sys
import logging
log = logging.getLogger("fit_efficiency")
logging.basicConfig(level=logging.WARNING, stream=sys.stderr)
from argparse import ArgumentParser
import os
from pdb import set_trace

class LumiJson():
   '''Json information'''
   def __init__(self):
      # {run: lumis}
      #lumis are collapsed
      self.run_map = {}
      self.evts = 0
      
   def append(self, run, lumi, evts, filename):
      self.evts += evts
      if run not in self.run_map:
         self.run_map[run] = set([lumi])
      else:
         #check if lumi already present
         if lumi in self.run_map[run]:
            log.warning(
               "run: %i lumi: %i already present " 
               "in other files other than %s, are "
               "you sure there are no duplicates?",
               run, lumi, filename)
         else:
            self.run_map[run].add(lumi)

   @staticmethod
   def collapse(lumiset):
      '''Collapse a set of lumis into a more 
      compact format which include ranges'''
      lumilst = list(lumiset)
      lumilst.sort(reverse=True)
      collapsed = []
      lumi  = lumilst.pop()
      block = [lumi]
      prev  = lumi
      #consume all input
      for _ in xrange(len(lumilst)):
         lumi = lumilst.pop()
         if prev+1 == lumi:
            prev = lumi
         else:
            #end block here and create a new one
            block.append(prev)
            collapsed.append(block)
            block = [lumi]
            prev = lumi
      if block[0] != lumi:
         block.append(lumi)
      collapsed.append(block)
      return collapsed

   def dump(self, fname):
      json = {
         'events' : self.evts,
         'lumimap' : {}
         }

      for run, lumis in self.run_map.iteritems():
         json['lumimap'][str(run)] = self.collapse(lumis)

      with open(fname, 'w') as output:
         output.write(prettyjson.dumps(json))

class Extractor(threading.Thread):
   def __init__(self, name, queue, pu_histo, out_json):
      super(Extractor, self).__init__()
      self.name = name
      self.queue = queue
      self.histo = pu_histo
      self.json = out_json
   
   def run(self):
      #infinite loop!
      while True:
         fname = ''
         log.debug('%s: getting new file' % self.name)
         with self.queue as q:
            if q.empty():
               log.debug('%s: the file queue is empty, exiting...' % self.name)
               return
            fname = q.get()
         
         log.debug('%s: opening root file' % self.name)
         tfile = ROOT.TFile.Open(fname)
         #set_trace()
         if self.histo:
            log.debug('%s: getting pu distribution' % self.name)
            pu_histo = tfile.Get('PUDistribution')
            with self.histo as h:
               if not h:
                  self.histo.object = pu_histo.Clone('pu_distribution')
                  self.histo.object.SetDirectory(0) #get ownership of the object
               else:
                  h.Add(pu_histo)

         log.debug('%s: getting meta information' % self.name)
         meta_tree = tfile.Get('metaTree/meta')
         with self.json as json:
            for entry in meta_tree:
               json.append(
                  entry.run,
                  entry.lumi,
                  entry.processed,
                  fname
                  )
         tfile.Close()

if __name__=='__main__':
   parser = ArgumentParser(description=__doc__)
   parser.add_argument('flist', metavar='files.txt', type=str,
                       help='.txt file containing the location of'
                       ' root files to be processed')
   parser.add_argument('output', metavar='file.json', type=str,
                       help='Json output file name')
   parser.add_argument('--mc-mode', dest='isMc', action='store_true',
                       default=False, help='Computes the true PU distribution')
   parser.add_argument('--threads', dest='threads', type=int, default=4,
                       help='Number of threads used')

   args = parser.parse_args()
   if not os.path.isfile(args.flist):
      raise IOError('File %s does not exist!' % args.flist)
      #logging.error('ERROR: file %s does not exist!' % args.flist)

   log.debug('loading root files')
   file_queue = LockedObject(Queue()) #should reserve some space
   with open(args.flist) as inputs:
      for path in inputs:
         #no threading issue
         if not os.path.isfile(path.strip()):
            raise IOError('File %s does not exist!' % path)
         file_queue.object.put(path.strip())

   log.debug('creating shared objects and threads')
   pu_histo = LockedObject(None) if args.isMc else None
   out_json = LockedObject(LumiJson())
   threads = [Extractor("Thread %i" % i, file_queue, pu_histo, out_json) 
              for i in xrange(args.threads)]

   log.debug('starting threaded analysis')
   for thread in threads:
      thread.start()
   
   log.debug('waiting for threads to finish')
   for thread in threads:
      thread.join()

   log.debug('saving information to %s' % args.output)
   with out_json as json:
      json.dump(args.output)

   log.debug('saving root information to %s' % args.output.replace('.json', '.pu.root'))
   if args.isMc:
      tfile = ROOT.TFile.Open(args.output.replace('.json', '.pu.root'),'RECREATE')
      tfile.cd()
      with pu_histo as histo:
         histo.Write()
      tfile.Close()
   
   sys.exit(0)
