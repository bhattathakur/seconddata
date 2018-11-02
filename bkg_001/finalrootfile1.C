//Energy calibration function....:      0.15448454 keV +     0.38903224 keV/chn
void finalrootfile1(){
   //Defining the files
  const char * root_file="ROOTFILES/final1.root"; //Stores the root file
  const char * inputdatafile="DATA/bkg_001.dat"; //original data files which stores two columns of data
  const char * intercept_slopefile="DATA/slope_intercept1.dat"; //This file contains the slope and intercept data created by etruevsecal macro
    
    //Defining the constants
  double b1=0.15448454;
  double m1=0.38903224;
  double Emin=0;
  const int numberOfChannels=16384;
  double Emax=numberOfChannels;

  //Reading the intercept and slope form a file
  double b2,m2;
  ifstream intercepslope(intercept_slopefile);
  if(intercepslope.is_open())
    {
	while(1)
	  {
	    intercepslope>>b2>>m2;
	    if(!intercepslope.good())break;
	  }
	cout<<"Successfully read the intercept and slope from the file "<<intercept_slopefile<<endl;
	cout<<"intercept = "<<b2 <<" and slope = "<<m2<<endl;
    }
  else
    {
	cout<<"Error in reading file "<<intercept_slopefile<<endl;
    }
  
  double bnew=m2*b1+b2;
  double mnew=m1*m2;

  double correctedEmin=Emin*mnew-bnew;
  double correctedEmax=Emax*mnew-bnew;
  cout<<"correctedEmin = "<<correctedEmin<<endl;
  cout<<"correctedEmax = "<<correctedEmax<<endl;

 
  
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  TFile *file=new TFile(root_file,"RECREATE"); //Root file to store the histograms
  TH1F *histofinal=new TH1F("histofinal","#font[22]{Final Calibrated Energy Spectrum}",numberOfChannels,correctedEmin,correctedEmax);
   int x,y; //for storing the data in histogram
   ifstream input(inputdatafile);
   string line;
   int nlines=0; //for counting the number of lines
   if(input.is_open())
	 {
	  
	   int flag=0;
	   while(getline(input,line))
		 {
		   flag++;
		   if(flag>6 && flag <16391)
		     {
			 stringstream sstr(line);
			 cout<<line<<endl;
			 sstr>>x>>y; //Reading the data file into two columns
			 if(!input.good())break;
			 histofinal->SetBinContent(x,y); //SetBinContent(bin,content)
			 nlines++;
		     }
		 }
	   cout<<"Successfully read data file "<<inputdatafile<<" to create the histogram"<<endl;
	   input.close();
	 }
   else
	 {
	   cout<<"Unable to open the data file to create energy spectrum"<<endl;
	   return 0;
	 }
  cout<<"Total lines = "<<nlines<<endl;
  histofinal->GetXaxis()->SetTitle("Energy(keV)");
  histofinal->GetYaxis()->SetTitle("Counts/Channel");
  gStyle->SetOptStat(1000000001);//shows only name of the histogram
  histofinal->Draw();
  histofinal->Write();
  cout<<"stored histogram in the root file: "<<root_file<<endl;
  //  file->Close();
}
