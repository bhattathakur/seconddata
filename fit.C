 {
  TFile f("ROOTFILES/final3.root");
  int n = 16384;
  TH1F *h = (TH1F*)f.Get("finalroothisto3");
  TH1F chn("chn", "", n, -0.5, n-0.5);
  for (int bin=1; bin<=n; bin++) chn.SetBinContent( bin, h->GetBinContent(bin) );
  
  // Fit spectrum with bad calibration.
  double elo = 606; // range of approximate energy
  double ehi = 620;
  int blo = h->FindBin(elo); // range in bin number
  int bhi = h->FindBin(ehi);
  double clo = chn.GetBinCenter(blo); // range in channel number (~ bin number)
  double chi = chn.GetBinCenter(bhi);
  chn.Fit("gaus","remq","",clo,chi);
  TF1 f1("f1","[0]*TMath::Gaus(x,[1],[2],1)+[3]+[4]*x");
  f1.SetParameters( gaus->Integral(clo,chi) / h->GetBinWidth(1),
		    gaus->GetParameter(1),
		    gaus->GetParameter(2),
		    0,
		    0 );
  chn.Fit("f1","remq","",clo,chi);
  chn.Fit("f1","remq","",clo,chi);
  chn.Fit("f1","remq","",clo,chi);
  double x1 = 609.320;
  double y_1 = f1.GetParameter(1);
  
  elo = 2620;
  ehi = 2660;
  blo = h->FindBin(elo); // range in bin number
  bhi = h->FindBin(ehi);
  clo = chn.GetBinCenter(blo); // range in channel number (~ bin number)
  chi = chn.GetBinCenter(bhi);
  chn.Fit("gaus","remq","",clo,chi);
  f1.SetParameters( gaus->Integral(clo,chi) / h->GetBinWidth(1),
		    gaus->GetParameter(1),
		    gaus->GetParameter(2),
		    0,
		    0 );
  chn.Fit("f1","remq","",clo,chi);
  chn.Fit("f1","remq","",clo,chi);
  chn.Fit("f1","remq","",clo,chi);
  double x2 = 2614.511;
  double y2 = f1.GetParameter(1);

  double mi = (y2-y_1)/(x2-x1);
  double bi = y2 - mi*x2;
  double m  = 1/mi;
  double b  = -bi/mi;
  cout << m << endl;
  cout << b << endl;

  TH1F ene;
  ene.SetName("ene");
  // Iterate until the spectrum converges.
  for (int iter=0; iter<3; iter++) {
    double mold  = m;
    double bold  = b;
    ene.SetBins(h->GetNbinsX(),
		b,
		b + m*n );
    for (int bin=1; bin<=n; bin++) {
      ene.SetBinContent( bin, h->GetBinContent(bin) );
    }

    // Fit spectrum with new calibration to check energy scale.
    // These ranges should be close to the true energy now,
    // but not perfect until iterating a few times.
    elo = 606; // range of approximate energy
    ehi = 620;
    ene.Fit("gaus","remq","",elo,ehi);
    f1.SetParameters( gaus->Integral(elo,ehi) / ene.GetBinWidth(1),
		      gaus->GetParameter(1),
		      gaus->GetParameter(2),
		      0,
		      0 );
    ene.Fit("f1","remq","",elo,ehi);
    ene.Fit("f1","remq","",elo,ehi);
    ene.Fit("f1","remq","",elo,ehi);
    x1 = 609.320;
    y_1 = f1.GetParameter(1);

    elo = 2600;
    ehi = 2630;
    ene.Fit("gaus","remq","",elo,ehi);
    f1.SetParameters( gaus->Integral(elo,ehi) / h->GetBinWidth(1),
		      gaus->GetParameter(1),
		      gaus->GetParameter(2),
		      0,
		      0 );
    ene.Fit("f1","remq","",elo,ehi);
    ene.Fit("f1","remq","",elo,ehi);
    ene.Fit("f1","remq","",elo,ehi);
    x2 = 2614.511;
    y2 = f1.GetParameter(1);

    mi = (y2-y_1)/(x2-x1);
    bi = y2 - mi*x2;
    m  = 1/mi   * mold;
    b  = -bi/mi + bold;
    cout << m << endl;
    cout << b << endl;
  }
}
