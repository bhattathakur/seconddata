//Original Data File
const char * inputdatafile="bkg_01_001.dat"; //file with input data

//Defining the files for initialroot file
const char * initial_root_file="initialtest.root"; //for storing the histogram in rootbkg_01_000.dat
const char * initialhistopdf="initialhistotest.pdf";//initial histogram as pdf file

//Defining the files for finalroot file
const char * final_root_file="finaltest.root"; //Stores the root file
const char * intercept_slopefile="slope_intercept4.dat"; //This file contains the slope and intercept data created by etruevsecal macro
const char * finalhistopdf="finalhistotest.pdf";

//Files for initialcombofit
//const char * filename=initial_root_file;//"initialt.root"; //access the original histogram
const char * allhistogramsfile="allhistogramtest.root"; //Save the histogram in this root file
const char * file_estimated_parameters="initialestimates.dat"; //file stores  the estimated parameters for fit
const char * outputfile ="initialEnergyerrortest.dat"; //file storing errors 
  

//Some constants
double b1=0.15448454;
double m1=0.38903224;
double Emin=0;
const int numberOfChannels=16384;
double Emax=numberOfChannels;

//Different Functions initialization:
void makingRootFile(const char *originaldatafile,const char *rootfilename,const char *pdfname,int chn,double emin,double emax);
void initialrootfile();
void combofit(const char *,const char *,const char *,const char *);
void finalrootfile();




//Main function
void singlecode()
{
  //initialrootfile();
  // finalrootfile();
  combofit(file_estimated_parameters,initial_root_file,allhistogramsfile,outputfile);
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
//Method for fitting all the peaks of the histogram and saving error parameters in  a File
void combofit(const char * estimatedparameters,const char * fileroot,const char * resultroot,const char * results ){
  const  int peakNo=23;
  const  int column=6;
  int row=peakNo/column+1;
  
  //Defining the array to read the paramertes
  double firstParameter[peakNo]={};
  double secondParameter[peakNo]={};
  double thirdParameter[peakNo]={};
  double firstLimit[peakNo]={};
  double secondLimit[peakNo]={};

  //Checking if data file with estimated parameters are opened
  ifstream datafile(estimatedparameters);
  // datafile.open(estimatedparameters); //File containing the estimated fit parameters
  if(datafile.is_open())
	{
	  cout<<" File reading for estimated parameters is done successfully from the file "<<estimatedparameters<<endl;
	  int peakCount=0;
	  while(peakCount<=peakNo)
		{
		  datafile>>firstParameter[peakCount]>>secondParameter[peakCount]>>thirdParameter[peakCount]>>firstLimit[peakCount]>>secondLimit[peakCount];
		  peakCount++;
		}
	  datafile.close();
	}
  else
	{
	  cout<<"Error in reading the file"<<estimatedparameters<<"  for estimated paramters"<<endl;
	  return 0;
	}

  //Creating the canvas and rootfile to store different histograms 
  TCanvas *c1 = new TCanvas("c1","Histogram",500,700);
  c1->SetGrid();
  c1->Divide(column,row);
  TFile *filee=new TFile(resultroot,"RECREATE");
  //checking if Tfile is opened scuccessfully
  if(filee->IsOpen())cout<<"Successfully created a file "<<resultroot<< " to store all histograms with fit"<<endl;
  else
    {
	cout<<"Unable to open the file "<<resultroot<< endl;
	return 0;
    }
  //array for histogram and functions
  TF1 * f[peakNo];
  TH1F * h[peakNo];

  //Checking if TFiles is opened successfully
  TFile *MyFile = new TFile(fileroot,"READ");
  if(MyFile->IsOpen())cout<<fileroot<<" file opened successfully\n";

  TH1F *his = (TH1F*)MyFile->Get("histo"); //histo is the name of histogram stored in MyFile
  
  for(int i=0;i<peakNo;i++)
    {
      f[i]=new TF1(Form("f%d",i),"[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
      f[i]->SetParNames("A","#mu","#sigma","a1","b1");
      f[i]->SetParameters(firstParameter[i],secondParameter[i],thirdParameter[i],0,0);
	cout<<endl;
	cout<<"########################  Peak "<<(i+1)<<"  #########################     "<<endl;
	cout<<endl;
      c1->cd(i+1);
	h[i]=(TH1F*)his->Clone(Form("h%d",i+1));
      h[i]->GetXaxis()->SetTitle("Energy(keV)");
      h[i]->GetXaxis()->CenterTitle();
      h[i]->GetYaxis()->SetTitle("Counts/Channel");
      h[i]->GetYaxis()->CenterTitle();
      h[i]->Fit(f[i],"rem+","",firstLimit[i],secondLimit[i]);
	gStyle->SetOptStat("n");//Name of histogram
	h[i]->Draw();
   	h[i]->Sumw2();
	TPaveStats* stat =(TPaveStats*)h[i]->FindObject("stats");
	stat->SetOptFit(1111);
	// Set stat options
	gStyle->SetStatY(0.9);                
	// Set y-position (fraction of pad size)
	gStyle->SetStatX(0.9);                
	// Set x-position (fraction of pad size)
	gStyle->SetStatW(0.2);                
	// Set width of stat-box (fraction of pad size)
	gStyle->SetStatH(0.4);                
	// Set height of stat-box (fraction of pad size)
	c1->Update();
	c1->Modified();
     	filee->cd();
	//c->SaveAs(initialcanvaspdf);
	h[i]->Write();
    }
  //cout<<"Successfully saved the pdf version of histogram in the file "<<initialcanvaspdf<<endl;
  // filename.close();
  //delete filename;
  ///////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%/////////////////////////////////////

  
 ofstream myfile(results);
 const double binWidth=his->GetBinWidth(1);
 if(myfile.is_open())
 {
   cout<<"Creating the file with A,eA,u,eu,6,e6,N"<<endl;
  myfile<<fixed<<setprecision(2);
     for(int i=0;i<peakNo;i++)
       {
         myfile<<setw(10)<< f[i]->GetParameter(0)<<setw(12)<<f[i]->GetParameter(1)<<setw(12)<<f[i]->GetParameter(2)<<setw(12)<<f[i]->GetParError(0)
			   <<setw(12)<<f[i]->GetParError(1)<<setw(12)<<f[i]->GetParError(2)<<setw(12)<<f[i]->GetParameter(0)/binWidth<<endl;
       }
     cout<<"successfully stored output data in the file "<<results<<endl;
     myfile.close();
 }
 else cout<<"unable to open the file "<<results <<endl;
 //Closing the root file
 //xdelete  filename;
 // filename.close();
 delete  MyFile;
 }
