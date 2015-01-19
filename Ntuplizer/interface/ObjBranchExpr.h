#ifndef ObjBranchExpr_H
#define ObjBranchExpr_H

#include "URAnalysis/Ntuplizer/interface/ObjExpression.h"
#include "URAnalysis/Utilities/interface/typeConversion.h"
#include "URAnalysis/Ntuplizer/interface/EventTree.h"
#include "TTree.h"
#include <vector>
#include <iostream>
#include <memory>

template <typename EDObject, typename Type>
class ObjBranchExpr: public ObjExpression<EDObject> {
public:
  ObjBranchExpr(BranchInfo &info, EventTree& tree, std::string &expr):
    ObjExpression<EDObject>(expr),
    branch_val_(),
    name_(info.name)
  {
    //std::cout<<name_ <<": set branch to vals addr: " << &branch_val_ << std::endl;
    branch_ = tree.branch(info.name+info.str_type, &branch_val_);
    //std::cout<<name_ <<": set branch to vals addr: " << &branch_val_ << std::endl;
  }

  ~ObjBranchExpr(){ /*delete branch_val_;*/ }
  virtual void fill(const EDObject &obj) {branch_val_ = ura::as<Type>(this->functor_(obj));}
  virtual void debug() {std::cout<<name_ <<" vals addr: "<< &branch_val_<< " branch addr: "<< (Type*) branch_->GetAddress() << std::endl;}

private:
  Type branch_val_;
  TBranch *branch_;
  std::string name_;
};

template <typename EDObject>
ObjExpression<EDObject>* ObjBranchExprFactory(BranchInfo &info, EventTree& tree)
{
  switch(info.type){
  case BranchInfo::typeID::USHORT : return new ObjBranchExpr<EDObject, unsigned short>(info, tree, info.expr);
  case BranchInfo::typeID::DOUBLE : return new ObjBranchExpr<EDObject, double>(info, tree, info.expr);	       
  case BranchInfo::typeID::SHORT  : return new ObjBranchExpr<EDObject, short >(info, tree, info.expr);	       
  case BranchInfo::typeID::INT    : return new ObjBranchExpr<EDObject, int>(info, tree, info.expr);	       
  case BranchInfo::typeID::UINT   : return new ObjBranchExpr<EDObject, unsigned int>(info, tree, info.expr);  
  case BranchInfo::typeID::FLOAT  : return new ObjBranchExpr<EDObject, float>(info, tree, info.expr);	       
  case BranchInfo::typeID::LONG   : return new ObjBranchExpr<EDObject, long>(info, tree, info.expr);	       
  case BranchInfo::typeID::BOOL   : return new ObjBranchExpr<EDObject, bool>(info, tree, info.expr); 	       
  case BranchInfo::typeID::ULONG  : return new ObjBranchExpr<EDObject, unsigned long>(info, tree, info.expr); 
  default: return NULL;
  }
  //return ret;
}

#endif 
