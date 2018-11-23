void newCalibration()
{
  // void makingRootFile(string originaldatafile,string rootfilename,string histogram_name,string pdfname,int chn,double emin,double emax)
  //{
  TString histogram_name("newcalibration");
  TString originaldatafile("ORIGINAL_DATA/bkg_000.dat");
  TString pdfname("newcalibrateadhisto");
  int chn=16384;
  double emin=0;
  double emax=16384;
  cout<<"---------------------------------------------------"<<endl;
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  // TFile *file=new TFile(rootfilename.c_str(),"RECREATE"); //Root file to store the histograms
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
		  //		  cout<<line<<endl;
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
  
  //Calibration Function
  // Energy calibration function....:      0.15448454 keV +     0.38903224 keV/chn
  double b= 0.15448454, m= 0.38903224 ;
    
  //Trying to get total number of bins in the given histogram
  int nbins=histo->GetXaxis()->GetNbins();
  cout<<"nbins :"<<nbins<<endl;

  cout<<"BinContent of each bin:"<<endl;
  for(int i=1;i<=nbins;i++)
    {
	
	double x=histo->GetXaxis()->GetBinCenter(i);
	int y=histo->GetBinContent(i);
	double xnew=x*m+b;
     
	//	cout<<"Bin :"<<i<<"original-Bincenter = "<<x<<" Modified-Bincenter = "<<xnew<<"  BinContent = "<<y<<endl;
	printf("Bin : %d original-Bincenter = %0.2f Modified-BinCenter %0.2f BinContent = %d\n",i,x,xnew,y); 
	
    }
  
 
  cout<<"---------------------------------------------------"<<endl;
 
}
