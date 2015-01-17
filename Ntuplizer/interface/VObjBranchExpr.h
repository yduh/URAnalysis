#ifndef VObjBranchExpr_H
#define VObjBranchExpr_H

#include "URAnalysis/Ntuplizer/interface/ObjExpression.h"
#include "URAnalysis/Utilities/interface/typeConversion.h"
#include "URAnalysis/Ntuplizer/interface/EventTree.h"
#include "TTree.h"
#include <vector>
#include <iostream>
#include <memory>

template <typename EDObject, typename VType>
class VObjBranchExpr: public ObjExpression<EDObject> {
public:
  VObjBranchExpr(std::string branch_name, EventTree& tree, std::string &expr):
    ObjExpression<EDObject>(expr),
    branch_vals_(),
    name_(branch_name)
  {
    //std::cout<<name_ <<": set branch to vals addr: " << &branch_vals_ << std::endl;
    branch_ = tree.branch(branch_name, &branch_vals_);
    //std::cout<<name_ <<": set branch to vals addr: " << &branch_vals_ << std::endl;
  }

  ~VObjBranchExpr(){ /*delete branch_vals_;*/ }
  virtual void fill(const EDObject &obj) {branch_vals_.push_back( ura::as<VType>(this->functor_(obj)));}
  virtual void reserve(size_t i) {branch_vals_.reserve(i);}
  virtual void clear() {branch_vals_.clear();}
  virtual void debug() {std::cout<<name_ <<" vals addr: "<< &branch_vals_<< " branch addr: "<< (std::vector<VType>*) branch_->GetAddress() << std::endl;}

private:
  std::vector<VType> branch_vals_;
  TBranch *branch_;
  std::string name_;
};

template <typename EDObject>
ObjExpression<EDObject>* VObjBranchExprFactory(BranchInfo &info, EventTree& tree)
{
  switch(info.type){
  case BranchInfo::typeID::USHORT : return new VObjBranchExpr<EDObject, unsigned short>(info.name, tree, info.expr);
  case BranchInfo::typeID::DOUBLE : return new VObjBranchExpr<EDObject, double>(info.name, tree, info.expr);	       
  case BranchInfo::typeID::SHORT  : return new VObjBranchExpr<EDObject, short >(info.name, tree, info.expr);	       
  case BranchInfo::typeID::INT    : return new VObjBranchExpr<EDObject, int>(info.name, tree, info.expr);	       
  case BranchInfo::typeID::UINT   : return new VObjBranchExpr<EDObject, unsigned int>(info.name, tree, info.expr);  
  case BranchInfo::typeID::FLOAT  : return new VObjBranchExpr<EDObject, float>(info.name, tree, info.expr);	       
  case BranchInfo::typeID::LONG   : return new VObjBranchExpr<EDObject, long>(info.name, tree, info.expr);	       
  case BranchInfo::typeID::BOOL   : return new VObjBranchExpr<EDObject, bool>(info.name, tree, info.expr); 	       
  case BranchInfo::typeID::ULONG  : return new VObjBranchExpr<EDObject, unsigned long>(info.name, tree, info.expr); 
  default: return NULL;
  }
  //return ret;
}

#endif 
