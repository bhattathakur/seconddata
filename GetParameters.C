TCanvas * CheckAllPeaks(int fileNumber,int status)
{
  TCanvas * can=new TCanvas();
  TString filename=(status==1)?"ROOTFILES/initial":"ROOTFILES/final";
  TString name=Form("%d",fileNumber);
  cout<<"file :"<<name<<endl;
  filename=filename+name+".root";
  cout<<"filename: "<<filename<<endl;

  TFile * file=new TFile(filename);
  if(file->IsOpen())cout<<filename<<" opened successfully"<<endl;
  TString input =(status==1)?("initialroothisto"+name):("finalroothisto"+name);
  cout<<"rootfile : "<<input<<endl;
					  
  TH1F * h= (TH1F*)file->Get(input);
  cout<<"\vEnter the range :"<<endl;
  double min,max;
  cin>>min>>max;
  cout<<"\v";
  h->Fit("gausn","rem","",min,max);
  h->GetFunction("gausn")->SetLineColor(3);
  h->GetFunction("gausn")->SetLineStyle(3);
  cout<<fixed<<setprecision(2)<<"\v";
  //double constant=h->GetFunction("gausn")->GetParameter(0);
  //  double divisor=h->GetBinWidth(1);
  //  cout<<"BinWidth = :"<<divisor<<endl;
  double constant=h->GetFunction("gausn")->Integral(min,max)/ h->GetBinWidth(1);
  // cout<<"constant:"<<setfill(' ')<<setw(7)<<constant<<endl;
  cout<<"constant:"<<setfill(' ')<<setw(7)<<constant<<endl;
  double mean=h->GetFunction("gausn")->GetParameter(1);
  cout<<"mean:"<<setfill(' ')<<setw(11)<<mean<<endl;
  double sigma=h->GetFunction("gausn")->GetParameter(2);
  cout<<"sigma:"<<setfill(' ')<<setw(10)<<sigma<<endl<<"\v";
  cout<<setw(10)<<"constant"<<setw(10)<<"mean"<<setw(10)<<"sigma"<<setw(10)<<"xmin"<<setw(10)<<"xmax"<<endl;
  cout<<setw(10)<<constant<<setw(10)<<mean<<setw(10)<<sigma<<setw(10)<<min<<setw(10)<<max<<endl;
  cout<<"\v"<<endl;
  
  //Defining the function to include the fitting parameters
  TF1 *fun=new TF1("fun","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
  fun->SetParameters(constant,mean,sigma,0,0);
  h->Fit("fun","rem+","",min,max);
  
  cout<<"parameter 0: \t"<<fun->GetParameter(0)<<endl;
  cout<<"parameter 1: \t"<<fun->GetParameter(1)<<endl;
  cout<<"parameter 2: \t"<<fun->GetParameter(2)<<endl;
  cout<<"parameter 3: \t"<<fun->GetParameter(3)<<endl;
  cout<<"parameter 4: \t"<<fun->GetParameter(4)<<endl;
  cout<<"parError  0: \t"<<fun->GetParError(0)<<endl;
  cout<<"parError  1: \t"<<fun->GetParError(1)<<endl;
  cout<<"parError  2: \t"<<fun->GetParError(2)<<endl;
  cout<<"          N: \t"<<fun->GetParError(0)/h->GetBinWidth(1)<<endl;
  
  const double binWidth=h->GetBinWidth(1);
  cout<<setw(10)<<"A"<<setw(10)<<"u"<<setw(12)<<"6"<<setw(12)<<"eA"<<setw(12)<<"eu"<<setw(12)<<"e6"<<setw(12)<<"N"<<endl;
  
  cout<<setw(10)<< fun->GetParameter(0)<<setw(12)<<fun->GetParameter(1)<<setw(12)<<fun->GetParameter(2)<<setw(12)<<fun->GetParError(0)
			   <<setw(12)<<fun->GetParError(1)<<setw(12)<<fun->GetParError(2)<<setw(12)<<fun->GetParameter(0)/binWidth<<endl;
       
  
  
  h->Draw();
  return can;
  file->Close();
}

void GetParameters()
{
  cout<<"Enter file number(1-81), file(initial/final):(1/2)"<<endl;
  int fileNumber,status;
  cin>>fileNumber>>status;
  CheckAllPeaks(fileNumber,status);
}
