#include "Checkingfile.h" //preprocessor for checking if the file is opened successfully or not
//inputfile
TString inputdata="FINAL/TimeInterceptSlopeResolution.dat"; //input data file has time->resolution->intercept->slope->timeerror->resolutionerror->intercept error->slope error
//resolution vs time
TString pdfresolution="FINAL/resolutionvstime.pdf"; //pdf file location
TString resolutionformat="%lg%lg%*lg%*lg%lg%lg%*lg%*lg";
TString titling="FWHM vs Time  Plot;time (s); FWHM (eV);";
TString resolutionpar0Name="<FWHM>";

//intercpet vs time
TString interceptpdf="FINAL/interceptvstime.pdf"; //pdf file location
TString interceptformat="%lg%*lg%lg%*lg%lg%*lg%lg%*lg";
TString intercepttitling="Intercept vs Time  Plot;time (s); Intercept(keV) ;";
TString interceptpar0Name="<Intercept>";

//slope vs time
TString slopepdf="FINAL/slopevstime.pdf";
TString slopeformat="%lg%*lg%*lg%lg%lg%*lg%*lg%lg";
TString slopetitle="Slope vs Time Plot;time(s);Slope(keV/chn);";
TString slopepar0Name="<slope>";

TCanvas* getGraph(TString formatting,TString title,TString pdfname,TString par0name,int markerColor,int markerStyle, int setfillcolor,int framecolor,TString datafile);
 
TCanvas * FinalPlotModified()
{
    getGraph(resolutionformat,titling,pdfresolution,resolutionpar0Name,0,38,inputdata);
    getGraph(interceptformat,intercepttitling,interceptpdf,interceptpar0Name,0,29,inputdata);
    getGraph(slopeformat,slopetitle,slopepdf,slopepar0Name,0,42,inputdata);
}

TCanvas* getGraph(TString formatting,TString title,TString pdfname,TString par0name,int setfillcolor,int framecolor,TString datafile) //frame color and input data default
{
  TCanvas* can=new TCanvas(title,title+"one",400,200);
  gPad->SetTicks(1,1);
  checkFileOpening(datafile);
  can->SetGrid();
  can->SetFillColor(setfillcolor); //setfillcolor 20
  auto graph=new TGraphErrors(datafile,formatting,""); //datafile name, formatiting, option
  //Defining the line
  // TLine * line=new TLine(3500000.0,0.0,3500000,2.5);
  graph->SetTitle(title);//title of the plot,x title,ytitle
  graph->GetYaxis()->SetTitleOffset(1.2);
  graph->GetXaxis()->SetTitleOffset(1.2);
  graph->SetLineColor(9);
  graph->SetLineWidth(2);
  graph->Draw("AP");
  graph->Fit("pol0");
  graph->GetFunction("pol0")->SetParName(0,par0name); //par0name
  can->GetFrame()->SetFillColor(framecolor);//frame color 
  can->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  // line->Draw("same");
  can->Update();
  can->SaveAs(pdfname);
  return can;
}
