//Energy calibration function....:      0.15448454 keV +     0.38903224 keV/chn
//Energy calibration function....:      0.15448454 keV +     0.38903224 keV/chn-bkg 3 energy calibration function
void initialrootfile3(){
  double b1=0.15448454;
  double m1=0.38903224;
  double Emin=0;
  const int numberOfChannels=16384;
  double Emax=numberOfChannels;
  double correctedEmin=Emin*m1-b1;
  double correctedEmax=Emax*m1-b1;
  cout<<"correctedEmin = "<<correctedEmin<<endl;
  cout<<"correctedEmax = "<<correctedEmax<<endl;

  //Defining the files
  const char * root_file="ROOTFILES/initial3.root"; //for storing the histogram in rootbkg_01_000.dat
  const char * inputdatafile="DATA/bkg_01_000.dat"; //file with input data
  const char * histopdf="PLOTS/initialhisto3.pdf";//initial histogram as pdf file
  
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  TFile *file=new TFile(root_file,"RECREATE"); //Root file to store the histograms
  TH1F *initialhisto=new TH1F("initialhisto","#font[22]{Calibrated Energy Spectrum for original data}",numberOfChannels,correctedEmin,correctedEmax);
  
   ifstream input(inputdatafile);
   int nlines=0; //for counting the number of lines
   string line;   //reads the line as string
   int x,y; //for storing the data in histogram
   if(input.is_open())
	 {

	   int flag=0;
	   while(getline(input,line))
	     {
		 flag++;
		 if(flag>6 && flag<16391)
		{
		  stringstream sstr(line);
		  sstr>>x>>y; //Reading the data file into two columns
		  initialhisto->SetBinContent(x,y); //SetBinContent(bin,content)
		  cout<<line<<endl;
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
  initialhisto->GetXaxis()->SetTitle("Energy(keV)");
  initialhisto->GetYaxis()->SetTitle("Counts/Channel");
  gStyle->SetOptStat(1000000001);//shows only name of the initialhistogram
  initialhisto->Draw();
  c->SaveAs(histopdf);
  initialhisto->Write();
  cout<<"stored initialhistogram in the root file: "<<root_file<<endl;
  cout<<"sotred the pdf plot in the file "<<histopdf<<endl;
  file->Close();
}
