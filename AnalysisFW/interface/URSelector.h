#ifndef URSelector_h
#define URSelector_h

#include <string>



class URStreamer;

class URSelector
{
  public:
    URSelector(){text_="";};
    URSelector(std::string text) {text_ = text;};
    URSelector& operator||(URSelector& other);
    URSelector& operator&&(URSelector& other);
    virtual bool select(URStreamer* event) {std::cout << "W A R N I N G ! URSelector::select(...): Base class select method called!\n"; return false;};
    
  private:
    std::string text_;
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



URSelector& URSelector::operator||(URSelector& other)
{
  URSelectorOR* result = new URSelectorOR(*this,other);
  return *result;
}


URSelector& URSelector::operator&&(URSelector& other)
{
  URSelectorAND* result = new URSelectorAND(*this,other);
  return *result;
}


#endif // URSelector_h
