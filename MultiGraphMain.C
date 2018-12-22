#include "Checkingfile.h" //preprocessor for checking if the file is opened successfully or not
#include "DividingData.h" //for diving the data into two partss based on file name and rownumber
//inputfile
TString inputdata1="TimeInterceptSlopeResolution1.dat"; //input data file has time->resolution->intercept->slope->timeerror->resolutionerror->intercept error->slope error
TString inputdata2="TimeInterceptSlopeResolution2.dat"; //input data file has time->resolution->intercept->slope->timeerror->resolutionerror->intercept error->slope error
//resolution vs time
TString pdfresolution="combinedresolutionvstime.pdf"; //pdf file location
TString resolutionformat="%lg%lg%*lg%*lg%lg%lg%*lg%*lg";
TString resolutiontitling="FWHM vs Time  Plot;time (s); FWHM (eV);";
TString resolutionpar0Name="<FWHM>";

//intercpet vs time
//TString interceptpdf="FINAL/combinedinterceptvstime.pdf"; //pdf file location
TString interceptformat="%lg%*lg%lg%*lg%lg%*lg%lg%*lg";
//TString intercepttitling="Intercept vs Time  Plot;time (s); Intercept(keV) ;";
TString interceptpar0Name="<Intercept>";

//slope vs time
//TString slopepdf="FINAL/combinedslopevstime.pdf";
TString slopeformat="%lg%*lg%*lg%lg%lg%*lg%*lg%lg";
//TString slopetitle="Slope vs Time Plot;time(s);Slope(keV/chn);";
TString slopepar0Name="<Slope>"; 

//void checkFileOpening(TString);
TGraphErrors * getErrorGraph(TString datafile,TString formatting,TString graphTitle,Int_t markerColor=2,Int_t markerStyle=10);

void MultiGraphMain()
{
  TCanvas * can=new TCanvas();
  TGraphErrors *graph11=getErrorGraph(inputdata1,resolutionformat,resolutiontitling);//Data file 1
  graph11->Fit("pol0");
  graph11->GetFunction("pol0")->SetParName(0,resolutionpar0Name); //par0name
  graph11->GetFunction("pol0")->SetLineColorAlpha(kBlue,1);
  graph11->GetFunction("pol0")->SetLineStyle(3);
  graph11->SetLineColor(2);
  // graph11->Draw("ap");
   
  TGraphErrors *graph12=getErrorGraph(inputdata2,resolutionformat,resolutiontitling,3);//Date file 2
  graph12->SetLineColor(3);
   graph12->Fit("pol0");
  graph12->GetFunction("pol0")->SetParName(0,resolutionpar0Name); //par0name
  graph12->GetFunction("pol0")->SetLineColorAlpha(kBlue,1);
  graph12->GetFunction("pol0")->SetLineStyle(3);
   // TGraphErrors *graph20=getErrorGraph(inputdata,interceptformat,intercepttitling);
  //  TGraphErrors *graph30=getErrorGraph(inputdata,slopeformat,slopetitle);
  auto mg=new TMultiGraph();
  mg->Add(graph11);
  mg->Add(graph12);
  // mg->Add(graph30);
  mg->Draw("ap");
  mg->SetTitle("FWHM vs Time Plot; Time(s);FWHM(eV)");
  gStyle->SetOptFit(0001);
  //Forcing the display of fit parameters
  //force drawing of canvas to generate the fit TPaveStats
  //  c1->Update();
   auto stats1 = (TPaveStats*)graph11->GetListOfFunctions()->FindObject("stats");
   auto stats2 = (TPaveStats*)graph12->GetListOfFunctions()->FindObject("stats");
   stats1->SetTextColor(kRed);
   stats2->SetTextColor(kGreen);
   stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
   stats2->SetX1NDC(0.72); stats2->SetX2NDC(0.92); stats2->SetY1NDC(0.78);
   //  c1->Modified();
   gPad->SetTicks(1,1);
  gPad->Modified();
  gPad->Update();
  can->BuildLegend();
  can->SaveAs(pdfresolution);
  /*  
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
  can->SaveAs("all.pdf");*/
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
