#ifndef AnalyzerBase_cxx
#define AnalyzerBase_cxx

#include <typeinfo>


#include "AnalyzerBase.h"
#include "URSelector.h"



void AnalyzerBase::Initialize(const std::string myName_, const std::string sampleName_, const std::string text_, const int maxEvents_)
{
//   event = new URStreamer(tree)
  maxEvents = maxEvents_;
  myName = myName_;
  text = text_;
  sampleName = sampleName_;
  std::string outFileName = myName + "__Histograms__" + sampleName + "__" + text + ".root";
  outFile = new TFile(outFileName.c_str(), "RECREATE");
}



void AnalyzerBase::InitSelector()
{
//   s = new URSelector(); // New approach to selectors
}



AnalyzerBase::~AnalyzerBase()
{
  outFile->Close();
}

#endif // AnalyzerBase_cxx
