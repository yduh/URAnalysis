#ifndef URSelector_h
#define URSelector_h

#include <string>
#include <iostream>

#include "URParser.h"
#include "Logger.h"

class URStreamer;

class URSelector
{
  public:
    URSelector(){text_=""; baseIsConfigured = false;};
    URSelector(std::string text) {text_ = text; baseIsConfigured = false;};
    URSelector& operator||(URSelector& other);
    URSelector& operator&&(URSelector& other);
    virtual bool select(URStreamer* event) {Logger::log().warning() << "W A R N I N G ! URSelector::select(...): Base class select method called!\n"; return false;};
    virtual void getConfiguration();
    
  private:
    std::string text_;
    bool baseIsConfigured;
};



class URSelectorOR: public URSelector
{
  public:
    URSelectorOR(URSelector& first, URSelector& second): first_(&first), second_(&second) {};
    virtual bool select(URStreamer* event){return (first_->select(event))||(second_->select(event));};

  private:
    URSelector* first_;
    URSelector* second_;
};



class URSelectorAND: public URSelector
{
  public:
    URSelectorAND(URSelector& first, URSelector& second): first_(&first), second_(&second) {};
    virtual bool select(URStreamer* event){return (first_->select(event))&&(second_->select(event));};

  private:
    URSelector* first_;
    URSelector* second_;
};



#endif // URSelector_h

