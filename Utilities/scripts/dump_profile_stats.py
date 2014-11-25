#! /bin/env python
__doc__='''
Dumps profile statiscs saved in prf format 
(as produced by python default profiler)
'''


import sys
import pstats

if len(sys.argv) < 2 or '-h' in sys.argv or '--help' in sys.argv:
        print 'Usage dump_profile_stats.py profile_stat_files.prf'
	print __doc__
        sys.exit(1)

files = filter(lambda x: '.prf' in x, sys.argv)
stats = pstats.Stats(files[0])
for f in files[1:]:
    stats.add(f)
stats.sort_stats('cumulative')
stats.print_stats()
