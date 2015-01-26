//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 12 19:03:11 2010 by ROOT version 5.22/00d
// from TTree my_tree/my_tree
// found on file: Ntuple__MinBias_7TeV-pythia8__Spring10-START3X_V26B-v1__AllSelections_100_1.root
//////////////////////////////////////////////////////////

#ifndef TreeReader_h
#define TreeReader_h

#include <vector>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "URStreamer.h"
#include "FileOpener.C"



class TreeReader : public virtual URStreamer , public FileOpener {
public :

   TreeReader() { std::cout << "TreeReader: Please call constructor with arguments!\n";};
   TreeReader(const std::string sampleName, TTree *tree=0, TTree *metadataTree=0);
   virtual void     Init(TTree *tree, TTree *metadataTree);
   virtual Long64_t LoadMetadataTree(Long64_t entry);
   virtual void     GetMetadata();
   virtual ~TreeReader();
   virtual Int_t    Cut(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
};

#endif // TreeReader_h

#ifdef TreeReader_cxx
TreeReader::TreeReader(const std::string sampleName, TTree *tree, TTree *metadataTree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     TChain* chain = new TChain("MyNtupleMaking/my_tree");
     TChain* metadataChain = new TChain("MyNtupleMaking/metadata_tree");
     OpenFile(sampleName, chain, metadataChain);
     tree = chain;
     metadataTree = metadataChain;
   }
   Init(tree, metadataTree);
}



TreeReader::~TreeReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}



Long64_t TreeReader::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fChain->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fChain;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}



Long64_t TreeReader::LoadMetadataTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fMetadataTree) return -5;
  Long64_t centry = fMetadataTree->LoadTree(entry);
  if (centry < 0) return centry;
  if (!fMetadataTree->InheritsFrom(TChain::Class()))  return centry;
  TChain *chain = (TChain*)fMetadataTree;
  if (chain->GetTreeNumber() != fCurrent) {
    fCurrent = chain->GetTreeNumber();
    Notify();
  }
  return centry;
}



void TreeReader::GetMetadata()
{
  if (fMetadataTree == 0) return;
  Long64_t ientry = LoadMetadataTree(0);
  if (ientry < 0) return;
  fMetadataTree->GetEntry(0);
}



void TreeReader::Init(TTree *tree, TTree *metadataTree)
{
  InitReco(tree);
  InitMetadata(metadataTree);
  GetMetadata();
  Notify();
}



Int_t TreeReader::Cut(Long64_t entry)
{
  // Avoid warning about unused parameter
  // This line should be removed if the function is changed so to use the parameter entry
  (void) entry;
  
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

#endif // #ifdef TreeReader_cxx
