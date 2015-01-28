#ifndef URAnalysisTest_h
#define URAnalysisTest_h

#include <iostream>

#include "../src/AnalyzerBase.C"

class URAnalysisTest : public AnalyzerBase
{
  public:
    URAnalysisTest(const std::string sampleName_, const std::string text_, const int maxEvents_ = -1, TTree* tree=0) : 
      AnalyzerBase("URAnalysisTest", sampleName_, text_, maxEvents_, tree) {};
      
    void begin();
    void analyze();
    void end();
    void postProcess();

  private:
    // Nothing by default
    // Add your private variables/methods here
};

#endif // URAnalysisTest_h
