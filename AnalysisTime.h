//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Dec  9 13:26:27 2018 by ROOT version 5.34/36
// from TTree T/Time vs Others
// found on file: time_vs_others.root
//////////////////////////////////////////////////////////

#ifndef AnalysisTime_h
#define AnalysisTime_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class AnalysisTime {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           sn;
   Double_t        time;
   Double_t        fwhm;
   Double_t        intercept;
   Double_t        slope;
   Double_t        timeError;
   Double_t        fwhmError;
   Double_t        interceptError;
   Double_t        slopeError;

   // List of branches
   TBranch        *b_sn;   //!
   TBranch        *b_time;   //!
   TBranch        *b_fwhm;   //!
   TBranch        *b_intercept;   //!
   TBranch        *b_slope;   //!
   TBranch        *b_timeError;   //!
   TBranch        *b_fwhmError;   //!
   TBranch        *b_interceptError;   //!
   TBranch        *b_slopeError;   //!

   AnalysisTime(TTree *tree=0);
   virtual ~AnalysisTime();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalysisTime_cxx
AnalysisTime::AnalysisTime(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("time_vs_others.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("time_vs_others.root");
      }
      f->GetObject("T",tree);

   }
   Init(tree);
}

AnalysisTime::~AnalysisTime()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalysisTime::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalysisTime::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AnalysisTime::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("sn", &sn, &b_sn);
   fChain->SetBranchAddress("time", &time, &b_time);
   fChain->SetBranchAddress("fwhm", &fwhm, &b_fwhm);
   fChain->SetBranchAddress("intercept", &intercept, &b_intercept);
   fChain->SetBranchAddress("slope", &slope, &b_slope);
   fChain->SetBranchAddress("timeError", &timeError, &b_timeError);
   fChain->SetBranchAddress("fwhmError", &fwhmError, &b_fwhmError);
   fChain->SetBranchAddress("interceptError", &interceptError, &b_interceptError);
   fChain->SetBranchAddress("slopeError", &slopeError, &b_slopeError);
   Notify();
}

Bool_t AnalysisTime::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnalysisTime::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnalysisTime::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AnalysisTime_cxx
