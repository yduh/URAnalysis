#ifndef VObjBranchExpr_H
#define VObjBranchExpr_H

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "TTree.h"
#include <vector>
#include <iostream>
#include <memory>

template <typename EDObject>
class VObjBranchExpr {
public:
  VObjBranchExpr(std::string branch_name, TTree* tree, std::string &expr):
    branch_vals_(),
    functor_(expr),
    name_(branch_name)
  {
    //std::cout<<name_ <<": set branch to vals addr: " << &branch_vals_ << std::endl;
    branch_ = tree->Branch(branch_name.c_str(), &branch_vals_);
    //std::cout<<name_ <<": set branch to vals addr: " << &branch_vals_ << std::endl;
  }

  ~VObjBranchExpr(){ /*delete branch_vals_;*/ }
  void fill(const EDObject &obj) {branch_vals_.push_back(functor_(obj));}
  void reserve(size_t i) {branch_vals_.reserve(i);}
  void clear() {branch_vals_.clear();}
  void debug() {std::cout<<name_ <<" vals addr: "<< &branch_vals_<< " branch addr: "<< (std::vector<double>*) branch_->GetAddress() << std::endl;}
private:
  std::vector<double> branch_vals_;
  TBranch *branch_;
  StringObjectFunction<EDObject> functor_;
  std::string name_;
};

#endif 
