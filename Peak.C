TH1F * CheckAllPeaks(int fileNumber,int status,int peakNumber)
{
  // TString filename ("ROOTFILES/initialallhistograms1.root");
 TString filename=(status==0)?"ROOTFILES/initialallhistograms":"ROOTFILES/finalallhistogram";
 filename=filename+to_string(fileNumber)+".root";
 cout<<"filename: "<<filename<<endl;

  TFile * file=new TFile(filename);
  file->ls();
  if(file->IsOpen())cout<<filename<<" opened successfully"<<endl;
  
  // cout<<"Which peak ?"<<endl;
  // cin>>peakNumber;
  TString input ="h"+to_string(peakNumber);
  cout<<"peak : "<<input<<endl;
					  
 TH1F * h= (TH1F*)file->Get(input);
 h->Draw();

 return h;
  file->Close();
    
}
  void Peak()
  {
    gROOT->Reset();
    cout<<"Enter file number(1-40), filestatus(0-1),peaknumber(1-23):"<<endl;
    int fileNumber,status,peakNumber;
    cin>>fileNumber>>status>>peakNumber;
    
    CheckAllPeaks(fileNumber,status,peakNumber);
       
  }
