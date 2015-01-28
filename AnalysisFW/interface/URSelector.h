#ifndef URSelector_h
#define URSelector_h

#include <string>

#include "../../AnalysisTools/scripts/URStreamer.h"



// class URStreamer;

class URSelectorOR;

class URSelectorBase
{
  public:
    URSelectorBase(){text_="";};
    URSelectorBase(std::string text) {text_ = text;};
    URSelectorBase* operator||(URSelectorBase* other);
    URSelectorBase* operator&&(URSelectorBase* other);
    virtual bool select(URStreamer* event) = 0;
    
  private:
    std::string text_;
};



class URSelectorOR: public URSelectorBase
{
  public:
    URSelectorOR(URSelectorBase* first, URSelectorBase* second): first_(first), second_(second) {};
    virtual bool select(URStreamer* event){return (first_->select(event))||(second_->select(event));};

  private:
    URSelectorBase* first_;
    URSelectorBase* second_;
};



class URSelectorAND: public URSelectorBase
{
  public:
    URSelectorAND(URSelectorBase* first, URSelectorBase* second): first_(first), second_(second) {};
    virtual bool select(URStreamer* event){return (first_->select(event))&&(second_->select(event));};

  private:
    URSelectorBase* first_;
    URSelectorBase* second_;
};



URSelectorBase* URSelectorBase::operator||(URSelectorBase* other)
{
  URSelectorOR* result = new URSelectorOR(this,other);
  return result;
}


URSelectorBase* URSelectorBase::operator&&(URSelectorBase* other)
{
  URSelectorAND* result = new URSelectorAND(this,other);
  return result;
}


class URMuonsSelector: public URSelectorBase
{
  public:
    virtual bool select(URStreamer* event) {if(event->muons().size() > 1) return true; return false;};
};



class URElectronsSelector: public URSelectorBase
{
  public:
    virtual bool select(URStreamer* event) {if(event->electrons().size() > 1) return true; return false;};
};



class URJetsSelector: public URSelectorBase
{
  public:
    virtual bool select(URStreamer* event) {if(event->jets().size() > 4) return true; return false;};
};



#endif // URSelector_h