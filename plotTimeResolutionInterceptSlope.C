#include "Checkingfile.h" //preprocessor for checking if the file is opened successfully or not
//inputfile
const char * inputdata="FINAL/TimeInterceptSlopeResolution.dat"; //input data file has time->resolution->intercept->slope->timeerror->resolutionerror->intercept error->slope error
//resolution vs time
const char * pdfresolution="FINAL/resolutionvstime.pdf"; //pdf file location
const char * resolutionformat="%lg%lg%*lg%*lg%lg%lg%*lg%*lg";
const char * titling="FWHM vs Time  Plot;time (s); FWHM (eV);";
const char * resolutionpar0Name="#bar{FWHM}";

//intercpet vs time
const char * interceptpdf="FINAL/interceptvstime.pdf"; //pdf file location
const char * interceptformat="%lg%*lg%lg%*lg%lg%*lg%lg%*lg";
const char * intercepttitling="Intercept vs Time  Plot;time (s); Intercept(keV) ;";
const char * interceptpar0Name="#bar{Intercept}";

//slope vs time
const char * slopepdf="FINAL/slopevstime.pdf";
const char * slopeformat="%lg%*lg%*lg%lg%lg%*lg%*lg%lg";
const char * slopetitle="Slope vs Time Plot;time(s);Slope(keV/chn);";
const char * slopepar0Name="#bar{slope}";

//const char * 
//slope vs time


void getGraph(const char * formatting,const char * title,const char * pdfname,const char * par0name,
		  int setfillcolor,int pad,int framecolor=30,const char * datafile=inputdata);
void checkFileOpening(const char *);
//auto can=new TCanvas();
 
void plotTimeResolutionInterceptSlope()
{
  //  auto can=new TCanvas();
  can->Divide(1,3);
   
  getGraph(resolutionformat,titling,pdfresolution,resolutionpar0Name,20,1);
  
   getGraph(interceptformat,intercepttitling,interceptpdf,interceptpar0Name,25,2);
   // can->cd(3);
  getGraph(slopeformat,slopetitle,slopepdf,slopepar0Name,28,3);
  can->Draw();
  can->SaveAs("all.pdf");
}
void getGraph(const char * formatting,const char * title,const char * pdfname,const char * par0name,
		  int setfillcolor,int pad,int framecolor=30,const char * datafile=inputdata)
{
  checkFileOpening(inputdata);
  can->cd(pad);
  auto c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(setfillcolor); //setfillcolor 20
  auto graph=new TGraphErrors(datafile,formatting,""); //datafile name, formatiting, option
  graph->SetTitle(title);//title of the plot,x title,ytitle
  graph->GetYaxis()->SetTitleOffset(1.2);
  graph->GetXaxis()->SetTitleOffset(1.2);
  graph->SetMarkerColor(4);
  graph->SetMarkerStyle(21);
  graph->SetLineColor(9);
  graph->SetLineWidth(2);
  graph->Draw("AP");
  graph->Fit("pol0");
  graph->GetFunction("pol0")->SetParName(0,par0name); //par0name

  c->GetFrame()->SetFillColor(framecolor);//frame color 
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();
  c->SaveAs(pdfresolution);
}
