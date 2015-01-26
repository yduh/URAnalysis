#ifndef FileOpener_cxx
#define FileOpener_cxx

// #include <cstdlib>
#include <fstream>

#include "TChain.h"
#include "FileOpener.h"


TChain* FileOpener::OpenFile(const std::string sampleName, TChain* chain, TChain* metadataChain)
{
//   std::string fileList = "../fileLists/fileList_" + sampleName + ".txt";
  std::string fileList = "./fileList_" + sampleName + ".txt";
  std::ifstream fileNames(fileList.c_str());
  if(!fileNames.good())
  {
    std::cout << "E R R O R ! File list \"" << fileList << "\" does not exist!\n";
    std::cout << "            Exiting...\n";
    exit(1);
  }
  std::string fileName;
//   bool metadataLoaded = false; // FIXME: Commented for the time being
  while(fileNames >> fileName)
  {
    // FIXME: no metadata for the time being
//     if(!metadataLoaded)
//     {
//       metadataChain->Add(fileName.c_str());
//       metadataLoaded = true;
//     }
    std::cout << "I N F O : Adding file " << fileName << " to the chain.\n";
    chain->Add(fileName.c_str());
  }
  return chain;
}

#endif // FileOpener_cxx
