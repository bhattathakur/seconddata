initialpeakcheck()
{
  	  const char * filename="ROOTFILES/initial2.root"; //file contaiing original histogram created with initialroot.C
	  const char * histoname="initialhisto";
	  TFile *MyFile = new TFile(filename,"READ");
	  if(MyFile->IsOpen())cout<<filename<<" file opened successfully\n";
	  TH1F *h = (TH1F*)MyFile->Get(histoname);
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
