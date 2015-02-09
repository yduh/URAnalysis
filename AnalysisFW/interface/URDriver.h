#ifndef URDriver_h
#define URDriver_h

/*
class URDriver<T> T = Analyzer

Class to handle the analysis of Ntuples in a threaded way
 */

#include "URParser.h"
#include "PathReader.h"
#include "SafeQueue.h"
#include <vector>
#include "Worker.h"
#include <stdio.h>
#include "TFileMerger.h"
#include <iostream>
#include <stdio.h>
#include "TFile.h"
#include "TTree.h"
#include "Logger.h"
#include <sstream>
#include "TThread.h"
#include "TROOT.h"

template<typename T>
class AnalysisWorker: public Worker{
public:
  AnalysisWorker(std::string id, SafeQueue<std::string>& inputs, std::string outname):
    Worker(id),
    inputs_(inputs),
    analyzer_(outname)
  {    
    analyzer_.begin();
  }

private:
  virtual void work()
  {
    while(!inputs_.empty())
    {
      //get input file name from the queue
      std::string input_file = inputs_.pop();
      Logger::log().debug() << id_ << ": got input file: " <<
	input_file << std::endl;

      //open and read it
      TFile *file = TFile::Open(input_file.c_str());
      TTree *tree = (TTree*) file->Get("Events");

      //assign to analyzer
      analyzer_.setTree(tree);

      //analyze
      Logger::log().debug() << id_ << ": Analyzing file" <<
	input_file << std::endl;
      analyzer_.analyze();

      file->Close();
    }
    analyzer_.end();
    Logger::log().debug() << id_ <<
      "No more files to analyze, exiting" << std::endl;
  }
  T analyzer_;
  SafeQueue<std::string> &inputs_;
};

template<typename T>
class URDriver{
public:
  URDriver():
    reader_()
  {
    //define CLI and CFG options
    URParser &parser = URParser::instance();
    opts::options_description &opts = parser.optionGroup("processing", "CLI and CFG options on how to run the analyzer");
    opts::positional_options_description &args = parser.args();

    opts.add_options()
      ("input", opts::value<std::string>(), "path of the file containing the list of root files to be processed")
      ("output", opts::value<std::string>(), "path of the root file to be produced")
      ("threads", opts::value<int>()->default_value(2), "number of threads to be used for processing");
    
    //make input and output positional (even though are still valid in CLI)
    args.add("input", 1);
    args.add("output", 1);

    opts::options_description &generic = parser.optionGroup("generic");
    generic.add_options()
      ("verbose,v", "prints debugging output");

    //set logger level
    Logger::log().setLevel(Logger::Level::WARNING);
  }


  //this does mostly what a main would do, saving you to write it again every new analyzer
  int run()
  {
    T::setOptions();
    URParser &parser = URParser::instance();
    parser.parseArguments();
    opts::variables_map &values = parser.values();

    if(values.count("verbose"))
    {
      Logger::log().warning() << "Setting the log level to DEBUG. " <<
	"Brace yourselves, printout madness is coming!" << std::endl;
      Logger::log().setLevel(Logger::Level::DEBUG);
    }

    //FIXME: should test that lask of input raises error
    //Get options and fill input file queue
    SafeQueue<std::string> input_files;
    std::string file_list = values["input"].as<std::string>();
    std::string output_file = values["output"].as<std::string>();
    Logger::log().debug() << "Input file is: " << file_list << 
      std::endl << "Output file is: " << output_file << std::endl;

    reader_.fill(input_files, file_list);
    const int n_threads = values["threads"].as<int>();
    Logger::log().debug() << "Running with " << n_threads << " threads"<< std::endl;

    //create (but do NOT use) a TThread, to trigger the spotless and 
    //clean ROOT implementation to consider thread safety a priority
    //and protect the global variables (!)
    TThread dummy;

    //create threads with unique names
    AnalysisWorker<T> *workers[n_threads];
    std::vector<std::string> outputs;
    //workers.reserve(n_threads);
    for(int i=0; i<n_threads; i++)
    {
      std::string outname = std::tmpnam(NULL);
      outname += ".root";
      Logger::log().debug() << "Output file of thread " << i <<
	"will be: " << outname << std::endl;
      
      std::ostringstream id;
      id << "AnalysisWorker_" << i;
      workers[i] = new AnalysisWorker<T>(id.str(), input_files, outname);
      outputs.push_back(outname);
    }

    //run threads, wait for them to finish and free memory
    Logger::log().debug() << "Starting threads" << std::endl;
    for(int i=0; i<n_threads; i++) workers[i]->start();

    Logger::log().debug() << "Waiting for threads to finish..." << 
      std::endl;
    for(int i=0; i<n_threads; i++) workers[i]->join();
    for(int i=0; i<n_threads; i++) delete workers[i];
    
    //merge the files
    Logger::log().debug() << "Merging output files..." << std::endl;
    TFileMerger merger;
    merger.OutputFile(output_file.c_str());
    for(auto& file : outputs) merger.AddFile(file.c_str(), false); //why false? no clue, copied from old fwk
    bool isMerged = merger.Merge();
    
    if(!isMerged)
    {
      Logger::log().fatal() <<"Error in merging thread outputs!" << std::endl;
      throw 42;
    }
    
    // for(auto& file : outputs) 
    // {
    //   if(!remove(file.c_str()))
    //   {
    // 	Logger::log().fatal() <<"Error removing file: " << file << std::endl;
    // 	throw 42;
    //   }
    // }
    return 0;
  }
private:
  PathReader reader_;
};

#endif
