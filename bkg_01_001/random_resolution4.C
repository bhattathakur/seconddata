void random_resolution4(){
  const char * errors_fromresolution="DATA/results_from_resolution4.dat";
  const char * randata="/home/Thakur.Bhatta/seconddata/final/randomdata4.dat"; //storing the mean and sigma from toy mc
  const char * saving_random="PLOT/randompdf4.pdf";

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
	    cout<<random_slope<<endl;
	    double random_intercept=gRandom->Gaus(b,db);
	    cout<<random_intercept<<endl;
	    double random_sigma=random_slope*ENERGY+random_intercept;
	    cout<< random_sigma<<endl;
	    ranhis->Fill(random_sigma);
	    
	  }
	ranhis->GetXaxis()->SetTitle("#sigma=m_{random}#times1332+b_{random}");
	ranhis->GetYaxis()->SetTitle("Counts");
	ranhis->Draw();
	ranhis->Fit("gaus");
	gStyle->SetOptFit(1111);
	can->Update();
		//Getting the paramters of the fit:
	cout<<ranhis->GetFunction("gaus")->GetParameter(0)<<endl;
	cout<<ranhis->GetFunction("gaus")->GetParameter(1)<<endl;
	cout<<ranhis->GetFunction("gaus")->GetParameter(2)<<endl;
	cout<<ranhis->GetFunction("gaus")->GetParError(0)<<endl;
	cout<<ranhis->GetFunction("gaus")->GetParError(1)<<endl;
	cout<<ranhis->GetFunction("gaus")->GetParError(2)<<endl;
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
}
