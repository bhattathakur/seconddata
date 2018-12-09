#include "Checkingfile.h";                                  //For checking the opening of the file
TGraphErrors* getGraph(TString datafile,TString formatting,TString title,const char * int markerColor=4,int markerStyle=21) 
{
  Checkingfile(datafile);                                   //Check if given file is opened or not
  TGraph * graph=new TGraphErrors(datafile,formatting,"");  //datafile name, formatiting, option
  graph->SetTitle(title);                                   //title of the plot,x title,ytitle
  graph->GetYaxis()->SetTitleOffset(1.2);
  graph->GetXaxis()->SetTitleOffset(1.2);
  graph->SetMarkerColor(markerColor);                       //marker-color
  graph->SetMarkerStyle(markerStyle);                       //marker-style
  graph->SetLineColor(9);
  graph->SetLineWidth(2);
  return graph;
}
