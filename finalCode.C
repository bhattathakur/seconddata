int file=8;

//Original Data File
string fileDirectory="ORIGINAL_DATA/"; //basic format for the input files 
string inputfilelist="ORIGINAL_DATA/originalfilelist.dat"; //This file has the list of all files
string  inputdatafile;

//Defining the files for initialroot file
string  inputCalibration;
string  initial_root_file;
string  initialhistoname;
string  initialhistopdf;

//Files for initialcombofit
string  initialallhistoroot;
string  initialEstimatedParameters;
string  outputErrorFile;

//Files for getting etrue and ecalculated data
string input1;
string input2;
string output;

//Files for plotting etrue vs ecal;
string  filedata;
string  etruecalcrootfile;
string  filenamee;
string  pdfetrue;

//Defining the files for finalroot file
string  outputCalibration;
string  final_root_file;
string  finalhisto;
string  intercept_slopefile;
string  finalhistopdf;

//Files for finalcombofit
string  allhistogramsfinal;
string  finalEstimatedParameters;
string  outputfilefinal;

//resolution files
string  dataafile;
string  pdfresoluton;
string  resolution_results;
string  savingtoroot;

//random resolution files
string  errors_fromresolution;
string  randata;
string  saving_random;

//Some constants
double b1,m1,b2,m2,b1Error,m1Error,b2Error,m2Error;
double Emin=0;
double correctedEmin,correctedEmax;
const int numberOfChannels=16384;
double Emax=numberOfChannels;
const int NUMBER_OF_FILES =40;
string desiredFile[]={};
string  File[]={};

//Function Initializtion
string * arrayForFiles(const char *,int );
void checkfileOpening(string fileIn);
void makingRootFile(string originaldatafile,string rootfilename,string ,string pdfname,int chn,double emin,double emax);
void initialrootfile();
void combofit(string  estimatedparameters,string  fileroot,string  histoname,string  resultroot,string  results );
void finalrootfile();
void etruevsecaldata();
void etruevsecal();
void resolution();
void random_resolution();
void peakcheck(string , string );
void initialpeakcheck();
void finalpeakcheck();
void fileArray(string files[],int size);
void checkfileOpening(string fileIn);
void readFile(int fileNo);
string toString(int n);
void modifyFiles();

//Main function
void finalCode()
 {
   cout<<"####################### "<<"file: "<< file<<" ####################################"<<endl;
   modifyFiles();
   string * filelist=arrayForFiles(inputfilelist.c_str(),NUMBER_OF_FILES);
   // for(int i=0;i<NUMBER_OF_FILES;i++)
   //  {
   	printf("filelist %2d :%s \n",file,filelist[file-1].c_str());
	//  }
   inputdatafile=fileDirectory+filelist[file-1];
   cout<<"inputFile: "<<inputdatafile<<endl;
   checkfileOpening(inputdatafile);
   initialrootfile();
   combofit(initialEstimatedParameters,initial_root_file,initialhistoname,initialallhistoroot,outputErrorFile); //initial combo fit
   // etruevsecaldata();
   // etruevsecal();
   // finalrootfile();
   // combofit(finalEstimatedParameters,final_root_file,finalhisto,allhistogramsfinal,outputfilefinal);//final combo fit
   //  resolution();
   // random_resolution();
   //initialpeakcheck();
   // finalpeakcheck();
   cout<<"successfully completed "<<endl;
    exit(0);
 }
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% READ CALIBRATION %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//This function reads the calibration values stored in the form b, m , bError, m Error
void readCalibration(string  calibrationfile,double &b,double &m,double &bError,double &mError)
{
  ifstream inputcali(calibrationfile.c_str());
  if(inputcali.is_open())
    {
	cout<<"successfully opened: "<<calibrationfile<<endl;
	while(1)
	  {
	    inputcali>>b>>m>>bError>>mError;
	    
	    if(!inputcali.good())break;
	    cout<<" b = "<<b<<" m = "<<m<<" bError = "<<bError<<" and mError = "<<mError<<endl;
	  }
    }
  
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%MAKING ROOT FILE%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//This functin makes the root file based on the given information
void makingRootFile(string originaldatafile,string rootfilename,string histogram_name,string pdfname,int chn,double emin,double emax)
{
  cout<<"---------------------------------------------------"<<endl;
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  TFile *file=new TFile(rootfilename.c_str(),"RECREATE"); //Root file to store the histograms
  TH1F *histo=new TH1F(histogram_name.c_str(),"#font[22]{Calibrated Energy Spectrum for original data}",chn,emin,emax);
  
  ifstream input(originaldatafile.c_str());
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
		  // cout<<line<<endl;
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
  c->SaveAs(pdfname.c_str());
  histo->Write();
  cout<<"stored histogram in the root file : "<<rootfilename<<endl;
  cout<<"sotred the pdf plot in the   file : "<<pdfname<<endl;
  file->Close();
  cout<<"---------------------------------------------------"<<endl;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%INITIAL ROOT FILE%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Defining the initial root file
void initialrootfile()
{
  cout<<"---------------------------------------------------"<<endl;
  cout<<"Reading the calibration"<<endl;
  readCalibration(inputCalibration,b1,m1,b1Error,m1Error);//Reading the cabration stored in the file
  cout<<"Working on initial root file "<<endl;
  correctedEmin=Emin*m1-b1;
  correctedEmax=Emax*m1-b1;
  cout<<" b1 = "<<b1<<" m1 = "<<m1<<" b1Error = "<<b1Error<<" m1Error = "<<m1Error
	<<" Emin = "<<Emin<<" Emax = "<<Emax<<endl;
  cout<<"correctedEmin = "<<correctedEmin<<endl;
  cout<<"correctedEmax = "<<correctedEmax<<endl;
  makingRootFile(inputdatafile,initial_root_file,initialhistoname,initialhistopdf,numberOfChannels,correctedEmin,correctedEmax);
  cout<<"Initial root file created successfully "<<endl;
  cout<<"---------------------------------------------------"<<endl;
  
}

//Final root file
void finalrootfile()
{
  cout<<"---------------------------------------------------"<<endl;
  cout<<"Working on final root file "<<endl;
  //Reading the intercept and slope form a file
  cout<<"Reading the slope and intercept of the plot "<<endl;
  readCalibration(intercept_slopefile,b2,m2,b2Error,m2Error);
  cout<<" b2 = "<<b2<<" m2 = "<<m2<<" b2Error = "<<b2Error<<" m2Error = "<<m2Error
	<<" Emin = "<<Emin<<" Emax = "<<Emax<<endl;
 cout<<"Finally we have :\n";
 cout<<" b1 = "<<b1<<" m1 = "<<m1<<" b1Error = "<<b1Error<<" m1Error = "<<m1Error<<endl;
 cout<<" b2 = "<<b2<<" m2 = "<<m2<<" b2Error = "<<b2Error<<" m2Error = "<<m2Error<<endl;
 cout<<" Emin = "<<Emin<<" Emax = "<<Emax<<endl;
  
  
  //Calculating bnew mnew and errors
  double bnew=m2*b1+b2;
  double mnew=m1*m2;
  double bnewError=m2Error*b1+b2Error;
  double mnewError=m1*m2Error;
  cout<<"bnew (m2*b1+b2) = " <<bnew<<" mnew (m1*m2) = "<<mnew<<endl;
  cout<<"bnewError=m2Error*b1+b2Error:  "<<bnewError<<endl;
  cout<<"mnewError=m1*m2Error: "<<mnewError<<endl;
  double correctedEmin=Emin*mnew-bnew;
  double correctedEmax=Emax*mnew-bnew;
  cout<<"correctedEmin = "<<correctedEmin<<endl;
  cout<<"correctedEmax = "<<correctedEmax<<endl;

  //Storing new bnew and mnew in the file
  ofstream bmnewfile(outputCalibration.c_str());
  if(bmnewfile.is_open())
    {
	cout<<"Successfully opened the file :"<<outputCalibration<<endl;
	bmnewfile<<bnew<<setw(20)<<mnew<<setw(20)<<bnewError<<setw(20)<<mnewError<<endl;
	cout<<"bnew<<setw(20)<<mnew<<setw(20)<<bnewError<<setw(20)<<mnewError"<<endl;
	cout<<bnew<<setw(20)<<mnew<<setw(20)<<bnewError<<setw(20)<<mnewError<<endl;
    }
  else
    {
	cout<<"Error opening the file "<<outputCalibration<<endl;
	return 0;
    }
 
  //Creating root file
  makingRootFile(inputdatafile,final_root_file,finalhisto,finalhistopdf,numberOfChannels,correctedEmin,correctedEmax);
  cout<<"Final root file created successfully "<<endl;
  cout<<"---------------------------------------------------"<<endl;
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ETRUE ECAL DATA%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  

//This macro helps to create e-true and e-calc data:
void etruevsecaldata()
{
  cout<<"---------------------------------------------------"<<endl;
  cout<<"Working to get e true and e calcualted data:"<<endl;
  ifstream file1(input1.c_str());
  ifstream file2(input2.c_str());
  if(file1.is_open())
    {
	cout<<input1<< " successfully opened"<<endl;
    }
  else
    {
	cout<<"failed to open"<< input1<<endl;
	return 0;
    }
  if(file2.is_open())
    {
	cout<<input2<< " successfully opened"<<endl;
    }
  else
    {
	cout<<"failed to open"<< input2<<endl;
	return 0;
    }
  double amplitude,mean,sigma,errorAmp,errorMean,errorSigma,N;  //input1
  double trueE,errorE; //input2
  //Open file to store the required data:
  ofstream file4(output.c_str());
  if(file4.is_open())
    {
	while(1)
	  {
	    file1>>amplitude>>mean>>sigma>>errorAmp>>errorMean>>errorSigma>>N;
	    file2>>trueE>>errorE;
	    if(!file1.good()|| !file2.good())break;
	    file4<<setw(10)<<trueE<<setw(10)<<mean<<setw(10)<<errorE<<setw(10)<<errorMean<<endl;
	  }
	cout<<"successfully stored the E-true,E-Calc,E-true-error and E-Calc-error in the file "<<output<<endl;
    }
  else
    {
	cout<<"Unable to open file "<<output<<endl;
	return 0;
    }
  cout<<"Done with etrue and ecalc data creation "<<endl;
  cout<<"---------------------------------------------------"<<endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%ETRUE VS ECAL PLOT MACRO%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Macro to plot etrue vs ecalcualted
void etruevsecal()
{
  cout<<"---------------------------------------------------"<<endl;
  cout<<"Working to plot etrue vs ecal"<<endl;
  auto c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(42);
  auto graph=new TGraphErrors(filedata.c_str(),"%lg%lg%lg%lg","");//E-calc,E-true,errorE-Calc,errorE-true
  graph->SetTitle("E-True Vs  E-estimated  Plot;E_{true}(eV);E_{calculated}(eV);");
  graph->GetYaxis()->SetTitleOffset(1.2);
  graph->GetXaxis()->SetTitleOffset(1.2);
  graph->SetMarkerColor(4);
  graph->SetMarkerStyle(21);
  graph->SetLineColor(9);
  graph->SetLineWidth(2);
  graph->Draw("AP");
  graph->Fit("pol1");
  graph->GetFunction("pol1")->SetLineStyle(2);
  graph->GetFunction("pol1")->SetParName(0,"Intercept(P_{0})");
  graph->GetFunction("pol1")->SetParName(1,"Slope(P_{1})");

  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();

  //Legend
  TLegend * legend=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
   legend->AddEntry(graph->GetFunction("pol1"),"E_{estimated}=P_{0}+P_{1}E_{true}","l");
  legend->AddEntry(graph,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  legend->Draw();
  
  //Saving the plot in root file
  cout<<"Writing the etrue-ecalc plot in the root file"<<endl;
  TFile * file=new TFile(etruecalcrootfile.c_str(),"RECREATE");
  if(file->IsOpen())cout<<etruecalcrootfile <<" opened successfully"<<endl;
  else
    {
	cout<<"error in opeing the file "<< etruecalcrootfile <<endl;
    }
  c->SaveAs(pdfetrue.c_str());
  graph->Write();
   c->Write();

  
  //Files to save the slope and intercept from etrue vs ecalcualted plot
   ofstream outputgraph(filenamee.c_str());
  if(outputgraph.is_open())
   {
     outputgraph<<setw(20)<<graph->GetFunction("pol1")->GetParameter(0)<<setw(20)<<graph->GetFunction("pol1")->GetParameter(1)
		    <<setw(20)<<graph->GetFunction("pol1")->GetParError(0)<<setw(20)<<graph->GetFunction("pol1")->GetParError(1)<<endl;
     cout<<"intercept slope  and errrors "<<endl;
     cout<<setw(20)<<graph->GetFunction("pol1")->GetParameter(0)<<setw(20)<<graph->GetFunction("pol1")->GetParameter(1)
	   <<setw(20)<<graph->GetFunction("pol1")->GetParError(0)<<setw(20)<<graph->GetFunction("pol1")->GetParError(1)<<endl;
     cout<<"Successfully stored intercept,slope and errors in the file"<<filenamee<<endl;
   }
 else
   {
     cout<<"Unable to open the file "<< filenamee<<endl;
     return 0;
   }
  cout<<"etrue vs ecalc plot created "<<endl;
  cout<<"---------------------------------------------------"<<endl;
}
//Macro for getting resolution
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Resolution%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void resolution()
{
  cout<<"---------------------------------------------------"<<endl;
  cout<<"working on resolution "<<endl;
  //Data file containing final errors and parameters
  ifstream inputres(dataafile.c_str());
  if(inputres.is_open())
    {
	cout<<"successfully opend the file "<<dataafile<<endl;
    }
  else
    {
	cout<<"Unable to open the file "<<dataafile<<endl;
    }
  
  auto c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(29);
  TGraphErrors *expgraph=new TGraphErrors(dataafile.c_str(),"%*lg%lg%lg%*lg%lg%lg%*lg","");//A,mean,sigma,error in A,error in mean, error in sigma,N
  expgraph->SetTitle("Energy Resolution plot;E(eV);(#sigma);");
  expgraph->SetMarkerColor(4);
  expgraph->SetMarkerStyle(21);
  expgraph->SetLineColor(9);
  expgraph->SetLineWidth(2);
  expgraph->Draw("AP");
  expgraph->Fit("pol1");
  expgraph->GetFunction("pol1")->SetLineStyle(2);
  expgraph->GetFunction("pol1")->SetParName(0,"Intercept(p_{0})");
  expgraph->GetFunction("pol1")->SetParName(1,"Slope(p_{1})");

  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();

  //Legend
  TLegend * leg=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  leg->AddEntry(expgraph->GetFunction("pol1"),"#sigma=p_{0}+p_{1}E","l");
  leg->AddEntry(expgraph,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  leg->Draw();

  c->SaveAs(pdfresoluton.c_str());//Using as the pdf file for the plot
  const int E=1332;
  cout<<fixed<<setprecision(8);
  const double slope=expgraph->GetFunction("pol1")->GetParameter(1);
  const double slope_error=expgraph->GetFunction("pol1")->GetParError(1);
  cout<<"slope = "<<slope<<endl;
  cout<<"slope error = "<<slope_error<<endl;
  const double intercept=expgraph->GetFunction("pol1")->GetParameter(0);
  const double intercept_error=expgraph->GetFunction("pol1")->GetParError(0);
  cout<<"intercept = "<<intercept<<endl;
  cout<<"intercept error = "<<intercept_error<<endl;
  double sig=slope*E+intercept;
  double FWHM=2.355*sig;
  cout<<fixed<<setprecision(3);
  cout<<"Corresponding to E = 1332 keV for (Co-60)): "<<endl;
  cout<<"sigma = "<<sig<<endl;
  cout<<"FWHM  = "<<FWHM<<endl;
  /////////////////////Storing the Error and parameter error in a file////////////////////
  ofstream resolution_error(resolution_results.c_str());
  if(resolution_error.is_open())
    {
	resolution_error<<setw(12)<<slope<<setw(12)<<slope_error<<setw(12)<<intercept<<setw(12)<<intercept_error<<endl;
	cout<<"Successfully stored the m, dm , b and db in the file "<<resolution_results<<endl;
    }
  else cout<<"Unable to open the file "<<resolution_results<<endl;
  cout<<"resolution successful"<<endl;
  cout<<"---------------------------------------------------"<<endl;
 }

///////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/////////

//Macro for random resolution
void random_resolution()
{
  cout<<"---------------------------------------------------"<<endl;
  cout<<"working in random resolution "<<endl;
  const int ENERGY=1332;
  const int TRIALS=pow(10,6);
  double m,dm,b,db;
  
  //Creating the canvas
  TCanvas *can=new TCanvas();

  //Defining the histogram to will with random numbers
  TH1F *  ranhis=new TH1F("ranhis","Histogram filled with Random resolution values",TRIALS/25,0.94,1.1);

  //Checking if the input file is open
  ifstream inputfromran(errors_fromresolution.c_str());
  if(inputfromran.is_open())
    {
	cout<<"Successfully opened "<< errors_fromresolution<<endl;

	//Reading the histogram
	while(1)
	  {
	    inputfromran>>m>>dm>>b>>db;
	    if(!inputfromran.good())break;
	  }
	  
	for(int i=0;i<TRIALS;i++)
	  {
	    double random_slope=gRandom->Gaus(m,dm);
	    // cout<<random_slope<<endl;
	    double random_intercept=gRandom->Gaus(b,db);
	    // cout<<random_intercept<<endl;
	    double random_sigma=random_slope*ENERGY+random_intercept;
	    // cout<< random_sigma<<endl;
	    ranhis->Fill(random_sigma);
	    // cout<<endl;
	  }
	ranhis->GetXaxis()->SetTitle("#sigma=m_{random}#times1332+b_{random}");
	ranhis->GetYaxis()->SetTitle("Counts");
	ranhis->Draw();
	ranhis->Fit("gaus");
	gStyle->SetOptFit(1111);
	can->Update();
	
	//Getting the paramters of the fit:
	cout<<"Parameters and random errors: "<<endl;
	for(int i=0;i<3;i++)
	  {
	    cout<<ranhis->GetFunction("gaus")->GetParameter(i)<<setw(20)
		  <<ranhis->GetFunction("gaus")->GetParError(i)<<endl;
	  }
	
	//storing the parameter of fit in datafile
	ofstream ranoutput(randata.c_str());
	if(ranoutput.is_open())
	  {
	    ranoutput<<fixed<<setprecision(5);
	    ranoutput<<ranhis->GetFunction("gaus")->GetParameter(1)<<setw(10)<<ranhis->GetFunction("gaus")->GetParameter(2)<<endl;
	    cout<<"successfully stored random resolution mc data into file "<<randata<<endl;
	
	  }
	else
	  {
	    cout<<"Unable to open file "<<randata<<endl;
	    return 0;
	  }
    }
  else
    {
	cout<<"Unable to open "<<errors_fromresolution<<endl;
	return 0;
    }
  cout<<"random resolution done successfully"<<endl;
  cout<<"---------------------------------------------------"<<endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Peak Check%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Macro for checking the fitting of the peak of the histogram 
void peakcheck(string  rootfilename,string  histo_in_root)
{
  TFile *MyFile = new TFile(rootfilename.c_str(),"READ");
  if(MyFile->IsOpen())cout<<rootfilename<<" file opened successfully\n";
  else cout<<rootfilename<<" was not opened\n";
  
  TH1F *h = (TH1F*)MyFile->Get(histo_in_root.c_str());
  gStyle->SetOptStat(1000000001);
  h->Draw();
  TF1 *f=new TF1("f1","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");  
  f->SetParNames("A","#mu","#sigma","a1","b1");
  double Amplitude,mean,SD,xmin,xmax;
  cout<<"Enter Amplitude, mean, SD, E-min, E-max"<<endl;
  cin>>Amplitude>>mean>>SD>>xmin>>xmax;
  f->SetParameters(Amplitude,mean,SD,0,0);
  h->Fit("f1","rem+","",xmin,xmax);
  gStyle->SetOptFit(1111);
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Initial Peak Check%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void initialpeakcheck()
{
  cout<<"working in initial peak check"<<endl;
  peakcheck(initial_root_file,initialhistoname); //name of root file and name of histo stored in the root file
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Final Peak Check%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void finalpeakcheck()
{
  cout<<"working in final peak check "<<endl;
  peakcheck(final_root_file,finalhisto);//name of root file and name of histo stored in the root file
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%COMBO FIT%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//Method for fitting all the peaks of the histogram and saving error parameters in  a File
void combofit(string  estimatedparameters,string  fileroot,string  histoname,string  resultroot,string  results )
{
  cout<<"---------------------------------------------------"<<endl;
  cout<<"Working on combo fit for the file "<<fileroot<<endl;
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
  ifstream datafile(estimatedparameters.c_str());
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
  TFile *filee=new TFile(resultroot.c_str(),"RECREATE");
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
  TFile *MyFile = new TFile(fileroot.c_str(),"READ");
  if(MyFile->IsOpen())cout<<fileroot<<" file opened successfully\n";

  TH1F *his = (TH1F*)MyFile->Get(histoname.c_str()); //histo is the name of histogram stored in MyFile
  
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
  ///////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%/////////////////////////////////////
  ofstream myfile(results.c_str());
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
 delete  MyFile;
 cout<<"Done with combo fit"<<endl;
 cout<<"---------------------------------------------------"<<endl;
 }
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%555

//This macro helps to read the given file which contains the number of files in the string format and form an array out of them
 //Reads the files and stores the files in the form of string array
string * arrayForFiles(const char * fileName,int fileNum)
{
  string * intermed =new string[fileNum];
  ifstream inputfile(fileName);
  string nameOfFile;
  int count=0;
    if(inputfile.is_open())
    {
	cout<<"Successfully opened the file "<<fileName<<endl;

	while(inputfile>>nameOfFile)
	  {
	    // getline(inputfile,intermed[count]);
	    intermed[count]=nameOfFile;
	    count++;
	  }
    }
  else
    {
	cout<<"Unable to open the file "<<fileName<<endl;
    }
    return intermed;
  }
//Checks if the file is opened or not
void checkfileOpening(string fileIn)
{
  // fileIn=fileDirectory+fileIn;
  cout<<"Trying to open the file :"<<fileIn<<endl;
  ifstream input;
  input.open(fileIn.c_str());
  if(input.is_open())
    {
	cout<<"Successfully opened the file :"<<fileIn<<endl;
    }
  else
    {
	cout<<"Unable to open the file :"<<fileIn<<endl;
    }
}
string toString(int n)
{
  stringstream ss;
  ss<<n;
  return ss.str();
}

   void modifyFiles()
   {
       inputCalibration="DATA/bnewmnew"+toString(file-1)+".dat"; //Stores data b, m , berror and m error used to find initial initial root file 
       initial_root_file= "ROOTFILES/initial"+toString(file)+".root"; //for storing the histogram in rootbkg_01_000.dat
       initialhistoname="initialroothisto"; //name of histogram in rootfile
       initialhistopdf="PLOTS/initialhisto"+toString(file)+".pdf";//initial histogram as pdf file


     //Files for initialcombofit
       initialallhistoroot="ROOTFILES/initialallhistograms"+toString(file)+".root"; //Save the histogram in this root file
       initialEstimatedParameters="DATA/initialestimates"+toString(file)+".dat"; //file stores  the estimated parameters for fit
       outputErrorFile ="DATA/initialEnergyerror"+toString(file)+".dat"; //file storing errors 


     //Files for getting etrue and ecalculated data
      input1=outputErrorFile; //estimated energy from the fit parameters
      input2="DATA/tabulatedenergy.dat"; //true energy calculated from nudat"+file+"
      output="DATA/dataEcalEtrue"+toString(file)+".dat";//stores the  data manipulated from input1 and input1

     //Files for plotting etrue vs ecal
       filedata=output; //File storing the estimated and true energy and their errors
       etruecalcrootfile="ROOTFILES/true_estimatedplot"+toString(file)+".root"; //root file to save the plot
       filenamee="DATA/slopeintercept"+toString(file)+".dat"; //file to store slope and intercept of plot
       pdfetrue="PLOTS/EtrueECalc"+toString(file)+".pdf"; //pdf file location

     //Defining the files for finalroot file
       outputCalibration="DATA/bnewmnew"+toString(file)+".dat";
       final_root_file="ROOTFILES/final"+toString(file)+".root"; //Stores the root file
       finalhisto="finalroothisto"; //name of histogram in rootfile
	 intercept_slopefile=filenamee;//This file contains the slope and intercept data created by etruevsecal macro
       finalhistopdf="PLOTS/finalhisto"+toString(file)+".pdf";

     //Files for finalcombofit
       allhistogramsfinal="ROOTFILES/finalallhistogram"+toString(file)+".root";
       finalEstimatedParameters="DATA/finalestimates"+toString(file)+".dat";
       outputfilefinal="DATA/finalEnergyError"+toString(file)+".dat";

     //resolution files
       dataafile=outputfilefinal;//A,mean,sigma,error in A,error in mean, error in sigma,N for final fit
       pdfresoluton="PLOTS/resolutionplot"+toString(file)+".pdf"; //pdf file to save the plot
       resolution_results="DATA/results_from_resolution"+toString(file)+".dat";//stores the results obtained form the resolution plot
       savingtoroot="ROOTFILES/resolution"+toString(file)+".root";// saves the plot in the root file

     //random resolution files
       errors_fromresolution=resolution_results; //"results_from_resolution.dat";
       randata="FINAL/randomdata"+toString(file)+".dat"; //storing the mean and sigma from toy mc
       saving_random="PLOTS/randompdffile"+toString(file)+".pdf";
   }
