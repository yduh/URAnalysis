all:streamer main

streamer:streamergen dict

streamergen:
	../../AnalysisTools/scripts/make_tree_proxy.py ../../test_ntuple.root Events

dict:
	g++ `root-config --cflags` -Wall -c Dict.cxx -o URStreamerDict.o

main:
	g++ -I../interface/ -I../src/ `root-config --cflags` `root-config --libs` URStreamerDict.o MainURAnalysisTest.cc -o MainURAnalysisTest
