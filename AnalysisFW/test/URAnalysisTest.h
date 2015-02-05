#ifndef URAnalysisTest_h
#define URAnalysisTest_h

#include <iostream>

#include "../src/AnalyzerBase.C"
#include "../../AnalysisTools/scripts/URStreamer.h"
// #include "../../AnalysisTools/scripts/Dict.cxx"

class URAnalysisTest : public AnalyzerBase
{
  public:
    URAnalysisTest(const std::string sampleName_, const std::string text_, const int maxEvents_ = -1, TTree* tree=0) : 
      AnalyzerBase("URAnalysisTest", "output") {};
      
    void begin();
    void analyze();
    void end();
    void postProcess();

  private:
    URStreamer* event;
    // Nothing by default
    // Add your private variables/methods here
};

#endif // URAnalysisTest_h
