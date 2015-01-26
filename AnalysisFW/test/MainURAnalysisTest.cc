#include <iostream>


#include "TChain.h"


#include "./URAnalysisTest.C"
#include "../src/FileOpener.C"


int main(int argc, char *argv[])
{
  FileOpener f;
  TChain* tree = new TChain("Events");
  TChain* metadata = new TChain("metadata");
  tree = f.OpenFile("test", tree, metadata);
  URAnalysisTest* a = new URAnalysisTest("test", "test2", -1, tree);
  a->analyze();
  return 0;
  
  
//   if(argc == 2)
//   {
//     
//     URAnalysisTest* a = new URAnalysisTest(argv[1]);
//     a->Analyze();
//     return 0;
//   }
//   else
//   {
//     std::cout << "This program should be invoked with exactly one command line argument!\n";
//     return 1;
//   }
}
