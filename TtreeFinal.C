/// This macro will open the acii file :FINAL/TimeInterceptSlopeResolutionfortree.dat and store data into different branches of the
/// data file data: SN time FWHM intercept slope time-error FWHM-erro intercept-error slope-error

void TtreeFinal()
{
   Int_t           sn;
   Double_t        time;
   Double_t        fwhm;
   Double_t        intercept;
   Double_t        slope;
   Double_t        timeError;
   Double_t        fwhmError;
   Double_t        interceptError;
   Double_t        slopeError;

   TString asciiFile="FINAL/TimeInterceptSlopeResolutionfortree.dat"; //this file stores the data
   TString filename = "time_vs_others.root";                          //to store results of tree

   ifstream inputfile(asciiFile);                                     //input datafile
   if(inputfile)cout<<"Successfully opened the file: "<<asciiFile<<endl;
   

   TFile * rootFile=new TFile(filename,"RECREATE");                   //TFile for storing the data of tree
   TTree *tree = new TTree("T","Time vs Others");                     //Defining tree 

   tree->Branch("sn",&sn,"sn/I");
   tree->Branch("time",&time,"time/D");
   tree->Branch("fwhm",&fwhm,"fwhm/D");
   tree->Branch("intercept",&intercept,"intercept/D");
   tree->Branch("slope",&slope,"slope/D");
   tree->Branch("timeError",&timeError,"timeError/D");
   tree->Branch("fwhmError",&fwhmError,"fwhmError/D");
   tree->Branch("interceptError",&interceptError,"interceptError/D");
   tree->Branch("slopeError",&slopeError,"slopeError/D");
   
    while(inputfile>>sn>>time>>fwhm>>intercept>>slope>>timeError>>fwhmError>>interceptError>>slopeError)
	{
	  // cout<<"inside while loop"<<endl;
	   // cout<<sn<<'\t'<<time<<'\t'<<fwhm<<'\t'<<intercept<<'\t'<<slope<<'\t'<<timeError<<'\t'<<fwhmError<<'\t'<<interceptError<<'\t'<<slopeError<<'\n';
	   tree->Fill();
	 }
	    
   tree->Write();
   rootFile->Close();
}
