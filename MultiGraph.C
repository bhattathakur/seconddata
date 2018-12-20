#include "Checkingfile.h" //preprocessor for checking if the file is opened successfully or not
//inputfile
TString inputdata="TimeInterceptSlopeResolution.dat"; //input data file has time->resolution->intercept->slope->timeerror->resolutionerror->intercept error->slope error
//resolution vs time
//TStringpdfresolution="FINAL/resolutionvstime.pdf"; //pdf file location
TString resolutionformat="%lg%lg%*lg%*lg%lg%lg%*lg%*lg";
TString resolutiontitling="FWHM vs Time  Plot;time (s); FWHM (eV);";
TString resolutionpar0Name="#bar{FWHM}";

//intercpet vs time
//TString interceptpdf="FINAL/interceptvstime.pdf"; //pdf file location
TString interceptformat="%lg%*lg%lg%*lg%lg%*lg%lg%*lg";
TString intercepttitling="Intercept vs Time  Plot;time (s); Intercept(keV) ;";
TString interceptpar0Name="#bar{Intercept}";

//slope vs time
TString slopepdf="FINAL/slopevstime.pdf";
TString slopeformat="%lg%*lg%*lg%lg%lg%*lg%*lg%lg";
TString slopetitle="Slope vs Time Plot;time(s);Slope(keV/chn);";
TString slopepar0Name="#bar{slope}";

//TString 
//slope vs time

//void checkFileOpening(TString);
TGraphErrors * getErrorGraph(TString datafile,TString formatting,TString graphTitle,Int_t markerColor=2,Int_t markerStyle=10);

void MultiGraph()
{
  TGraphErrors *graph10=getErrorGraph(inputdata,resolutionformat,resolutiontitling,20,1);//resolution
  TGraphErrors *graph20=getErrorGraph(inputdata,interceptformat,intercepttitling);
  TGraphErrors *graph30=getErrorGraph(inputdata,slopeformat,slopetitle);
  auto mg=new TMultiGraph();
  mg->Add(graph10);
  mg->Add(graph20);
  mg->Add(graph30);
  mg->Draw("ap");
  
  auto can=new TCanvas();
  can->GetFrame()->SetFillColor(42);//frame color 
  can->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
   gPad->SetTicks(1,1);
  
  can->Divide(1,3);
   
  can->cd(1);
 
  TGraphErrors *graph1=getErrorGraph(inputdata,resolutionformat,resolutiontitling,20,1);//resolution
  graph1->Fit("pol0");
  graph1->GetFunction("pol0")->SetParName(0,resolutionpar0Name); //par0name
  graph1->Draw("ap");
  can->Update();
    
  can->cd(2);
  // gPad->SetTicks(1,1);
  TGraphErrors *graph2=getErrorGraph(inputdata,interceptformat,intercepttitling);
  graph2->Fit("pol0");
  graph2->GetFunction("pol0")->SetParName(0,interceptpar0Name); //par0name
  graph2->Draw("ap");
  can->Update();
  
  can->cd(3);
  //  gPad->SetTicks(1,1);
  TGraphErrors *graph3=getErrorGraph(inputdata,slopeformat,slopetitle);
  graph3->Fit("pol0");
  graph3->GetFunction("pol0")->SetParName(0,slopepar0Name); //par0name
   graph3->Draw("ap");
   can->Update();

  can->Draw();
  can->SaveAs("all.pdf");
}

//Getting the TGraph object from this function
  TGraphErrors * getErrorGraph(TString datafile,TString formatting,TString graphTitle,Int_t markerColor,Int_t markerStyle)
  {
    checkFileOpening(datafile); //check for opening of the file
    auto graph=new TGraphErrors(datafile,formatting,""); //datafile name, formatiting, option
    graph->SetTitle(graphTitle);//title of the plot,x title,ytitle
    graph->GetYaxis()->SetTitleOffset(1.2);
    graph->GetXaxis()->SetTitleOffset(1.2);
    graph->SetMarkerColor(markerColor); //markerColor
    graph->SetMarkerStyle(markerStyle); //markerStyle
    graph->SetLineColor(9);
    graph->SetLineWidth(2);
    return graph;
  }
