//Original Data File
const char * inputdatafile="bkg_01_001.dat"; //file with input data

//Defining the files for initialroot file
const char * initial_root_file="initialtest.root"; //for storing the histogram in rootbkg_01_000.dat
const char * initialhistopdf="initialhistotest.pdf";//initial histogram as pdf file

//Defining the files for finalroot file
const char * final_root_file="final4.root"; //Stores the root file
const char * intercept_slopefile="slope_intercept4.dat"; //This file contains the slope and intercept data created by etruevsecal macro
const char * finalhistopdf="finalhistotest.pdf";
 

//Some constants
double b1=0.15448454;
double m1=0.38903224;
double Emin=0;
const int numberOfChannels=16384;
double Emax=numberOfChannels;

//Different Functions initialization:
void makingRootFile(const char *originaldatafile,const char *rootfilename,const char *pdfname,int chn,double emin,double emax);
void initialrootfile();
void finalrootfile();



//Main function
void singlecode()
{
  initialrootfile();
  
  // finalrootfile();
}


//This functin makes the root file based on the given information
void makingRootFile(const char *originaldatafile,const char *rootfilename,const char *pdfname,int chn,double emin,double emax)
{
   
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  TFile *file=new TFile(rootfilename,"RECREATE"); //Root file to store the histograms
  TH1F *histo=new TH1F("histo","#font[22]{Calibrated Energy Spectrum for original data}",chn,emin,emax);
  
   ifstream input(originaldatafile);
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
		  histo->SetBinContent(x,y); //SetBinContent(bin,content)
		  cout<<line<<endl;
		  nlines++;
		}
	     }
     	   cout<<"Successfully read data file "<<originaldatafile<<" to create the histogram"<<endl;
	   input.close();
	 }
   else
	 {
	   cout<<"Unable to open the data file to create energy spectrum"<<endl;
	   return 0;
	 }
  cout<<"Total lines = "<<nlines<<endl;
  histo->GetXaxis()->SetTitle("Energy(keV)");
  histo->GetYaxis()->SetTitle("Counts/Channel");
  gStyle->SetOptStat(1000000001);//shows only name of the histogram
  histo->Draw();
  c->SaveAs(pdfname);
  histo->Write();
  cout<<"stored histogram in the root file: "<<rootfilename<<endl;
  cout<<"sotred the pdf plot in the file "<<pdfname<<endl;
  file->Close();
}

void initialrootfile()
{
  double correctedEmin=Emin*m1-b1;
  double correctedEmax=Emax*m1-b1;
  cout<<"correctedEmin = "<<correctedEmin<<endl;
  cout<<"correctedEmax = "<<correctedEmax<<endl;

  makingRootFile(inputdatafile,initial_root_file,initialhistopdf,numberOfChannels,correctedEmin,correctedEmax);
  
}
void finalrootfile()
{
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
	return 0;
    }
  
  double bnew=m2*b1+b2;
  double mnew=m1*m2;

  double correctedEmin=Emin*mnew-bnew;
  double correctedEmax=Emax*mnew-bnew;
  cout<<"correctedEmin = "<<correctedEmin<<endl;
  cout<<"correctedEmax = "<<correctedEmax<<endl;

  //Creating root file
  makingRootFile(inputdatafile,final_root_file,finalhistopdf,numberOfChannels,correctedEmin,correctedEmax);

}
