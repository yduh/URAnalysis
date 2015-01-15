#ifndef ObjExpression_H
#define ObjExpression_H

#include "CommonTools/Utils/interface/StringObjectFunction.h"

template <typename EDObject>
class ObjExpression{
public:
  ObjExpression(std::string &expr):
    functor_(expr) {}
  virtual ~ObjExpression() {}
  virtual void fill(const EDObject &obj) =0;
  virtual void reserve(size_t i) {}
  virtual void clear() {}
  virtual void debug() {}

protected:
  StringObjectFunction<EDObject> functor_;
};

#include "FWCore/Utilities/interface/InputTag.h"

struct BranchInfo{
  enum typeID {
    DOUBLE,
    SHORT, 
    USHORT,
    INT, 
    UINT,
    FLOAT, 
    LONG, 
    ULONG,
    BOOL    };
  BranchInfo(std::string& prefix, const edm::InputTag &tag):
    name(prefix+"_"+tag.label()),
    expr((tag.instance().empty()) ? tag.label() : tag.instance()),
    str_type((tag.process().empty()) ? "/D" : tag.process())
  {
    if(tag.process().empty()) type = DOUBLE;
    else if(tag.process() == "/D") type = DOUBLE;
    else if(tag.process() == "/S") type = SHORT ;
    else if(tag.process() == "/s") type = USHORT;
    else if(tag.process() == "/I") type = INT   ;
    else if(tag.process() == "/i") type = UINT  ;
    else if(tag.process() == "/F") type = FLOAT ;
    else if(tag.process() == "/L") type = LONG  ;
    else if(tag.process() == "/l") type = ULONG ;
    else if(tag.process() == "/O") type = BOOL  ;
    else type = DOUBLE;
  }

  std::string name, expr, str_type;
  typeID type;
};

#endif
