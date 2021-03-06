//Original Data File
const char * inputdatafile="ORIGINAL_DATA/bkg_01_002.dat"; //file with input data

//Defining the files for initialroot file
const char * initial_root_file= "ROOTFILES/initial1.root"; //for storing the histogram in rootbkg_01_000.dat
const char * initialhisto="initialroothisto"; //name of histogram in rootfile
const char * initialhistopdf="PLOTS/initialhisto5.pdf";//initial histogram as pdf file


//Files for initialcombofit
const char * allhistogramsfile="ROOTFILES/initialallhistograms5.root"; //Save the histogram in this root file
const char * file_estimated_parameters="DATA/initialestimates5.dat"; //file stores  the estimated parameters for fit
const char * outputfile ="DATA/initialEnergyerror5.dat"; //file storing errors 


//Files for getting etrue and ecalculated data
const  char * input1=outputfile; //estimated energy from the fit parameters
const  char * input2="DATA/tabulatedenergy.dat"; //true energy calculated from nudat2
const  char * output="DATA/EcalEtrue5.dat";//stores the  data manipulated from input1 and input2

//Files for plotting etrue vs ecal
const char * filedata=output; //File storing the estimated and true energy and their errors
const char * etruecalcrootfile="ROOTFILES/true_estimatedplot5.root"; //root file to save the plot
const char * filenamee="DATA/slope_intercept5.dat"; //file to store slope and intercept of plot
const char * pdfetrue="PLOT/EtrueECalc5.pdf"; //pdf file location

//Defining the files for finalroot file
const char * final_root_file="ROOTFILES/final5.root"; //Stores the root file
const char * finalhisto="finalroothisto"; //name of histogram in rootfile
const char * intercept_slopefile=filenamee;//This file contains the slope and intercept data created by etruevsecal macro
const char * finalhistopdf="PLOT/finalhisto5.pdf";

//Files for finalcombofit
const char * allhistogramsfinal="ROOTFILES/finalallhistogram5.root";
const char * file_estimated_parameters_final="DATA/finalestimates5.dat";
const char * outputfilefinal="DATA/finalEnergyError5.dat";



//resolution files
const char * dataafile=outputfilefinal;//A,mean,sigma,error in A,error in mean, error in sigma,N for final fit
const char * pdfresoluton="PLOT/resolutionplot5.pdf"; //pdf file to save the plot
const char * resolution_results="DATA/results_from_resolution5.dat";//stores the results obtained form the resolution plot
const char * savingtoroot="ROOTFILES/resolution5.root";// saves the plot in the root file

//random resolution files
const char * errors_fromresolution=resolution_results; //"results_from_resolution.dat";
const char * randata="FINAL/randomdata5.dat"; //storing the mean and sigma from toy mc
const char * saving_random="PLOT/randompdffile5.pdf";

//Some constants
double b1=0.15448454;
double m1=0.38903224;
double Emin=0;
const int numberOfChannels=16384;
double Emax=numberOfChannels;

//Different Functions initialization:
void makingRootFile(const char *originaldatafile,const char *rootfilename,const char *,const char *pdfname,int chn,double emin,double emax);
void initialrootfile();
void combofit(const char * estimatedparameters,const char * fileroot,const char * histoname,const char * resultroot,const char * results );
void finalrootfile();
void etruevsecaldata();
void etruevsecal();
void resolution();
void random_resolution();
void peakcheck(const char *, const char *);
void initialpeakcheck();
void finalpeakcheck();

//Main function
void singlecode()
{
  /* initialrootfile();
  combofit(file_estimated_parameters,initial_root_file,initialhisto,allhistogramsfile,outputfile); //initial combo fit
  /* etruevsecaldata();
  etruevsecal();
  finalrootfile();
  combofit(file_estimated_parameters_final,final_root_file,finalhisto,allhistogramsfinal,outputfilefinal);//final combo fit
  resolution();
  random_resolution();*/
  initialpeakcheck();
  //finalpeakcheck();
  cout<<"successfully completed "<<endl;
  exit(0);
  
}


//This functin makes the root file based on the given information
void makingRootFile(const char *originaldatafile,const char *rootfilename,const char *histogram_name,const char *pdfname,int chn,double emin,double emax)
{
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  TFile *file=new TFile(rootfilename,"RECREATE"); //Root file to store the histograms
  TH1F *histo=new TH1F(histogram_name,"#font[22]{Calibrated Energy Spectrum for original data}",chn,emin,emax);
  
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
  cout<<"stored histogram in the root file : "<<rootfilename<<endl;
  cout<<"sotred the pdf plot in the   file : "<<pdfname<<endl;
  file->Close();
}


//Defining the initial root file
void initialrootfile()
{
  cout<<"Working on initial root file "<<endl;
  double correctedEmin=Emin*m1-b1;
  double correctedEmax=Emax*m1-b1;
  cout<<"correctedEmin = "<<correctedEmin<<endl;
  cout<<"correctedEmax = "<<correctedEmax<<endl;
  makingRootFile(inputdatafile,initial_root_file,initialhisto,initialhistopdf,numberOfChannels,correctedEmin,correctedEmax);
  cout<<"Initial root file created successfully "<<endl;
  
}

//Final root file
void finalrootfile()
{
  //Reading the intercept and slope form a file
  cout<<"Working on final root file "<<endl;
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
  makingRootFile(inputdatafile,final_root_file,finalhisto,finalhistopdf,numberOfChannels,correctedEmin,correctedEmax);
  cout<<"Final root file created successfully "<<endl;
}

//Method for fitting all the peaks of the histogram and saving error parameters in  a File
void combofit(const char * estimatedparameters,const char * fileroot,const char * histoname,const char * resultroot,const char * results )
{
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
  ifstream datafile(estimatedparameters);
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

  TH1F *his = (TH1F*)MyFile->Get(histoname); //histo is the name of histogram stored in MyFile
  
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
 cout<<"Done with combo fit"<<endl;
 }

//This macro helps to create e-true and e-calc data:
void etruevsecaldata()
{
  cout<<"Working to get e true and e calcualted data:"<<endl;
  ifstream file1(input1);
  ifstream file2(input2);
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
  ofstream file4(output);
  if(file4.is_open())
    {
	while(1)
	  {
	    file1>>amplitude>>mean>>sigma>>errorAmp>>errorMean>>errorSigma>>N;
	    file2>>trueE>>errorE;
	    if(!file1.good()|| !file2.good())break;
	    file4<<setw(10)<<mean<<setw(10)<<trueE<<setw(10)<<errorMean<<setw(10)<<errorE<<endl;
	  }
	cout<<"successfully stored the E-Calc,E-true and erros in the file "<<output<<endl;
    }
  else
    {
	cout<<"Unable to open file "<<output<<endl;
	return 0;
    }
  cout<<"Done with etrue and ecalc data creation "<<endl;
}

//Macro to plot etrue vs ecalcualted
void etruevsecal()
{
  cout<<"Working to plot etrue vs ecal"<<endl;
  auto c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(42);
  auto graph=new TGraphErrors(filedata,"%lg%lg%lg%lg","");//E-calc,E-true,errorE-Calc,errorE-true
  graph->SetTitle("E-True Vs  E-estimated  Plot;E_{estimated}(eV);E_{true}(eV);");
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
  auto legend=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  //legend->SetHeader("The Legend Title");
  legend->AddEntry(graph->GetFunction("pol1"),"E_{estimated}=P_{0}+P_{1}E_{true}","l");
  legend->AddEntry(graph,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  legend->Draw();
  
  //Saving the plot in root file
  auto file=new TFile(etruecalcrootfile,"RECREATE");
  if(file->IsOpen())cout<<etruecalcrootfile <<" opened successfully"<<endl;
  else
    {
	cout<<"error in opeing the file "<< etruecalcrootfile <<endl;
    }
  c->SaveAs(pdfetrue);
  graph->Write();
  c->Write();

  
  //Files to save the slope and intercept from etrue vs ecalcualted plot
  ofstream outputgraph(filenamee);
  if(outputgraph.is_open())
   {
     outputgraph<<setw(10)<<  graph->GetFunction("pol1")->GetParameter(0)<<setw(10)<<graph->GetFunction("pol1")->GetParameter(1)<<endl;
     cout<<"Successfully stored intercept and slope in the file"<<filenamee<<endl;
   }
 else
   {
     cout<<"Unable to open the file "<< filenamee<<endl;
     return 0;
   }
  cout<<"etrue vs ecalc plot created "<<endl;
}
//Macro for getting resolution

void resolution()
{
  cout<<"working on resolution "<<endl;
  //Data file containing final errors and parameters
  ifstream inputres(dataafile);
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
  TGraphErrors *expgraph=new TGraphErrors(dataafile,"%*lg%lg%lg%*lg%lg%lg%*lg","");//A,mean,sigma,error in A,error in mean, error in sigma,N
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
  auto leg=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  leg->AddEntry(expgraph->GetFunction("pol1"),"#sigma=p_{0}+p_{1}E","l");
  leg->AddEntry(expgraph,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  leg->Draw();

  c->SaveAs(pdfresoluton);//Using as the pdf file for the plot
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
  ofstream resolution_error(resolution_results);
  if(resolution_error.is_open())
    {
	resolution_error<<setw(12)<<slope<<setw(12)<<slope_error<<setw(12)<<intercept<<setw(12)<<intercept_error<<endl;
	cout<<"Successfully stored the m, dm , b and db in the file "<<resolution_results<<endl;
    }
  else cout<<"Unable to open the file "<<resolution_results<<endl;
  cout<<"resolution successful"<<endl;
 }

///////$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$/////////

//Macro for random resolution
void random_resolution()
{
  cout<<"working in random resolution "<<endl;
  const int ENERGY=1332;
  const int TRIALS=pow(10,6);
  double m,dm,b,db;
  
  //Creating the canvas
  TCanvas *can=new TCanvas();

  //Defining the histogram to will with random numbers
  TH1F *  ranhis=new TH1F("ranhis","Histogram filled with Random resolution values",TRIALS/25,0.94,1.1);

  //Checking if the input file is open
  ifstream inputfromran(errors_fromresolution);
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
	for(int i=0;i<3;i++)
	  {
	    cout<<ranhis->GetFunction("gaus")->GetParameter(i)<<setw(20)
		  <<ranhis->GetFunction("gaus")->GetParError(i)<<endl;
	  }
	
	//storing the parameter of fit in datafile
	ofstream ranoutput(randata);
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
}

//Macro for checking the fitting of the peak of the histogram 
void peakcheck(const char * rootfilename,const char * histo_in_root)
{
 	  TFile *MyFile = new TFile(rootfilename,"READ");
	  if(MyFile->IsOpen())cout<<rootfilename<<" file opened successfully\n";
	  else cout<<rootfilename<<" was not opened\n";
	  
	  TH1F *h = (TH1F*)MyFile->Get(histo_in_root);
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
void initialpeakcheck()
{
  cout<<"working in initial peak check"<<endl;
  peakcheck(initial_root_file,initialhisto); //name of root file and name of histo stored in the root file
}
void finalpeakcheck()
{
  cout<<"working in final peak check "<<endl;
  peakcheck(final_root_file,finalhisto);//name of root file and name of histo stored in the root file
}

