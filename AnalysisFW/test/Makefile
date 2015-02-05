all:streamer TestFWK

streamer:streamergen dict

streamergen:
	../../AnalysisTools/scripts/make_tree_proxy.py ../../test_ntuple.root Events

dict:
	g++ `root-config --cflags` -Wall -c Dict.cxx -o URStreamerDict.o

main:
	g++ -I../interface/ -I../src/ `root-config --cflags` `root-config --libs` -lboost_program_options URStreamerDict.o MainURAnalysisTest.cc -o MainURAnalysisTest

TestFWK:
	g++ -I../interface/ -I../src/ `root-config --cflags` `root-config --libs` -lboost_program_options URStreamerDict.o ../../AnalysisFW/interface/URDriver.h ../../AnalysisFW/src/URParser.cc ../../AnalysisFW/src/AnalyzerBase.C ../../AnalysisFW/src/URStandardSelectors.cc ../../AnalysisFW/src/URSelector.cc TestFWK.cc -o TestFWK
