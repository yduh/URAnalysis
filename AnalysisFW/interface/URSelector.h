#ifndef URSelector_h
#define URSelector_h

#include <string>

#include "AnalyzerBase.h"

class URSelector
{
  public:
    URSelector(AnalyzerBase* a_, std::string text_) {a = a_; text = text_;};
    
  private:
    AnalyzerBase* a;
    std::string text;
};

#endif // URSelector_h