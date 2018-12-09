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


TCanvas * getGraph(TString formatting,TString title,TString pdfname,TString par0name,int markerColor=4,int markerStyle=21,
		  int  setfillcolor=0,int framecolor=30,TString datafile=inputdata);
void checkFileOpening(TString);
 
TCanvas * FinalPlotModified()
{
  TCanvas * c=new TCanvas();
  c->Divide(1,3);
  
  c->cd(1);
  getGraph(resolutionformat,titling,pdfresolution,resolutionpar0Name,3);//Kspring+10
  // c1->Draw();
  c->Modified();
  c->Update();
 
  c->cd(2);
  getGraph(interceptformat,intercepttitling,interceptpdf,interceptpar0Name,6,29);//422->Cyan-10
  // c2->Draw();
   c->Modified();
   c->Update();
  
   c->cd(3);
   getGraph(slopeformat,slopetitle,slopepdf,slopepar0Name);//400-Yellow
   //  c3->Draw();
    c->Modified();
    c->Update();
    // c->Update();
   // c->Draw();
  c->SaveAs("all.pdf");
  return c;
}

 TCanvas* getGraph(TString formatting,TString title,TString pdfname,TString par0name,int markerColor=4,int markerStyle=21,
			 int setfillcolor=0,int framecolor=10,TString datafile=inputdata) //frame color and input data default
{
  TCanvas* can=new TCanvas();
  gPad->SetTicks(1,1);
  checkFileOpening(inputdata);
  can->SetGrid();
  can->SetFillColor(setfillcolor); //setfillcolor 20
  auto graph=new TGraphErrors(datafile,formatting,""); //datafile name, formatiting, option
  graph->SetTitle(title);//title of the plot,x title,ytitle
  graph->GetYaxis()->SetTitleOffset(1.2);
  graph->GetXaxis()->SetTitleOffset(1.2);
  //graph->SetMarkerColor(4);
  graph->SetMarkerColor(markerColor);
  // graph->SetMarkerStyle(21);
  graph->SetMarkerStyle(markerStyle);
  graph->SetLineColor(9);
  graph->SetLineWidth(2);
  //Trying to draw line to seperate peaks before 25 th and after 25 th line
  // TLine *line=new TLine(3500000.0,0.0,3500000.0,1.0);
  // line->SetLineColor(kBlue);
  // line->Draw();
  // can->Update();
  graph->Draw("AP");
  graph->Fit("pol0");
  graph->GetFunction("pol0")->SetParName(0,par0name); //par0name
  can->GetFrame()->SetFillColor(framecolor);//frame color 
  can->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  //gPad->SetTicks(1,1);
  can->Update();
  can->SaveAs(pdfname);
  return can;
}
