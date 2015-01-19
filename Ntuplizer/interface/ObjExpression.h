#ifndef ObjExpression_H
#define ObjExpression_H

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

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
  BranchInfo(std::string& prefix, const edm::ParameterSet &tag):
    name(prefix+"_"+tag.getParameter<std::string>("name")),
    expr(tag.getParameter<std::string>("expr")),
    str_type(tag.getParameter<std::string>("type"))
  {
    if(expr.empty()) expr = tag.getParameter<std::string>("name");
    if(str_type.empty()) str_type = "/F";
    if(str_type == "/D") type = DOUBLE;
    else if(str_type == "/S") type = SHORT ;
    else if(str_type == "/s") type = USHORT;
    else if(str_type == "/I") type = INT   ;
    else if(str_type == "/i") type = UINT  ;
    else if(str_type == "/F") type = FLOAT ;
    else if(str_type == "/L") type = LONG  ;
    else if(str_type == "/l") type = ULONG ;
    else if(str_type == "/O") type = BOOL  ;
    else type = FLOAT;
  }

  std::string name, expr, str_type;
  typeID type;
};

#endif
