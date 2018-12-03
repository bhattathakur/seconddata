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
  h->Fit("gaus","rem","",min,max);
  cout<<fixed<<setprecision(2)<<"\v";
  double constant=h->GetFunction("gaus")->GetParameter(0);
  //  double divisor=h->GetBinWidth(1);
  //  cout<<"BinWidth = :"<<divisor<<endl;
  double constant1=h->GetFunction("gaus")->Integral(min,max)/ h->GetBinWidth(1);
  cout<<"constant:"<<setfill(' ')<<setw(7)<<constant<<endl;
  cout<<"constant1:"<<setfill(' ')<<setw(7)<<constant1<<endl;
  double mean=h->GetFunction("gaus")->GetParameter(1);
  cout<<"mean:"<<setfill(' ')<<setw(11)<<mean<<endl;
  double sigma=h->GetFunction("gaus")->GetParameter(2);
  cout<<"sigma:"<<setfill(' ')<<setw(10)<<sigma<<endl<<"\v";
 
  h->Draw();
  return can;
  file->Close();
}

void GetParameters()
{
  cout<<"Enter file number(1-40), file(initial/final):(1/2)"<<endl;
  int fileNumber,status;
  cin>>fileNumber>>status;
  CheckAllPeaks(fileNumber,status);
}
