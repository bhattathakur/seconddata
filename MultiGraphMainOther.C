#include "Checkingfile.h" //preprocessor for checking if the file is opened successfully or not
#include "DividingData.h" //for diving the data into two partss based on file name and rownumber


TString root="FINAL/TimeInterceptSlopeResolution";//inputfile
//input data file has time->resolution->intercept->slope->timeerror->resolutionerror->intercept error->slope error

//Two input files to be generated later:
TString inputdata1=root+"1.dat";
TString inputdata2=root+"2.dat";

//This will divide the data into two parts:
const int fileDiv=24;
static int fileCount=1;

//For resolution vs time part
TString pdfresolution="FINAL/combinedresolutionvstime.pdf"; //pdf file location
TString resolutionformat="%lg%lg%*lg%*lg%lg%lg%*lg%*lg";
TString resolutiontitle="#font[22]{FWHM vs Time  Plot};Time (s); FWHM (eV);";
TString resolutionpar0Name="<FWHM>";

//intercpet vs time part
TString interceptpdf="FINAL/combinedinterceptvstime.pdf"; //pdf file location
TString interceptformat="%lg%*lg%lg%*lg%lg%*lg%lg%*lg";
TString intercepttitle="#font[22]{Intercept vs Time  Plot};Time (s); Intercept(keV) ;";
TString interceptpar0Name="<Intercept>";

//slope vs time part
TString slopepdf="FINAL/combinedslopevstime.pdf";
TString slopeformat="%lg%*lg%*lg%lg%lg%*lg%*lg%lg";
TString slopetitle="#font[22]{Slope vs Time Plot};Time(s);Slope(keV/chn);";
TString slopepar0Name="<Slope>"; 

//void checkFileOpening(TString);
TGraphErrors * getErrorGraph(TString datafile1,TString formatting,TString graphTitle,Int_t markerColor=2,Int_t markerStyle=21);
TCanvas * graphCanvas(TString format,TString title,TString par0,TString pdfname,TString datafile1=inputdata1,TString datafile2=inputdata2);
//TCanvas * graphCanvas(TString datafile,TString datafile2,TString format,TString title,TString par0,TString pdfname);

void MultiGraphMainOther()
{
  DividingData(root,fileDiv); //For splitting the data into two parts first 0-25 second 25-end

  graphCanvas(resolutionformat,resolutiontitle,resolutionpar0Name,pdfresolution); //Plot for the resolution vs time
  graphCanvas(interceptformat,intercepttitle,interceptpar0Name,interceptpdf); //Plot for intercept vs time
  graphCanvas(slopeformat,slopetitle,slopepar0Name,slopepdf); //Plot for slope vs time
 }

//Getting the TGraph object from this function
  TGraphErrors * getErrorGraph(TString datafile,TString formatting,TString graphTitle,Int_t markerColor,Int_t markerStyle)
  {
    checkFileOpening(datafile); //check for opening of the file
    auto graph=new TGraphErrors(datafile,formatting,""); //datafile name, formatiting, option
    graph->SetTitle(graphTitle);//title of the plot,x title,ytitle
    graph->GetYaxis()->SetTitleOffset(0.3);
    graph->GetXaxis()->SetTitleOffset(0.3);
    graph->SetMarkerColor(markerColor); //markerColor
    graph->SetMarkerStyle(markerStyle); //markerStyle
    graph->SetLineColor(9);
    graph->SetLineWidth(2);
    return graph;
  }

//Getting the canvas with two plots in different range with different colors
TCanvas * graphCanvas(TString format,TString title,TString par0,TString pdfname,TString datafile1,TString datafile2)
{
  cout<<"plot Number :"<<fileCount<<endl;
  // fileCount++;
  TCanvas * can=new TCanvas();
  
  TGraphErrors *graph11=getErrorGraph(datafile1,format,title);
  graph11->SetTitle("without shielding");
  graph11->Fit("pol0");
  graph11->GetFunction("pol0")->SetParName(0,par0);
  graph11->GetFunction("pol0")->SetLineColorAlpha(kBlue,1);
  graph11->GetFunction("pol0")->SetLineStyle(3);

  graph11->SetLineColor(2);
   
  TGraphErrors *graph12=getErrorGraph(datafile2,format,title,3);
  graph12->SetTitle("with shielding");
  graph12->Fit("pol0");
  graph12->GetFunction("pol0")->SetParName(0,par0); 
  graph12->GetFunction("pol0")->SetLineColorAlpha(kBlue,1);
  graph12->SetLineColor(3);
  graph12->GetFunction("pol0")->SetLineStyle(3);
   
  auto mg=new TMultiGraph();
  mg->Add(graph11);
  mg->Add(graph12);
  mg->Draw("ap");
  mg->SetTitle(title);
  gStyle->SetOptFit(0001);
 
  auto stats1 = (TPaveStats*)graph11->GetListOfFunctions()->FindObject("stats");
  auto stats2 = (TPaveStats*)graph12->GetListOfFunctions()->FindObject("stats");
  stats1->SetTextColor(kRed);
  stats2->SetTextColor(kGreen);
  stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);//stats1->SetY2NDC(0.85);
  stats2->SetX1NDC(0.72); stats2->SetX2NDC(0.92); stats2->SetY1NDC(0.78);

  //Trying to use legend
   auto legend=new TLegend(0.1,0.1,0.3,0.2);
   legend->SetFillColor(422);
   TLegendEntry *le1=legend->AddEntry("graph11","#font[12]{without shielding}","lep");
   le1->SetMarkerColor(kRed);
   le1->SetLineColor(kRed);
			    
   TLegendEntry *le2=legend->AddEntry("graph12","#font[12]{with shielding}","lep");
   le2->SetMarkerColor(kGreen);
   le2->SetLineColor(kGreen);
   //legend->AddEntry("graph11","without sielding","lep");
   // legend->AddEntry("graph12","with sielding","lep");
   legend->Draw();
  // can->BuildLegend();

   //TLatex for the information:
   // TText * info=new TTex(.5,.1,"data taken");
   // info.SetTextSize(0.04);
   // info.DrawLatex(0.5,0.5,"data taken");
   TText * info1=new TText(0.12,0.25,"Data taken from 09/17/2018 to 10/12/2018");
   TText * info2=new TText(0.50,0.25,"Data taken from 10/13/2018 to 12/10/2018");
  
   //info->DrawNDC();
   info1->SetNDC();
   info2->SetNDC();
  
   // info.DrawTextNDC(0.35,0.1,"Data taken from 09/17/2018 to 12/10/2018");
  info1->SetTextSize(0.02);
  info1->SetTextColor(kRed);
  info2->SetTextSize(0.02);
  info2->SetTextColor(kGreen);
  //info->SetTextAngle(45);
  info1->Draw();
  info2->Draw();
  if(fileCount==1)
    {
	TText * info3=new TText(0.65,0.38,"Data taken from 11/16/2018 to 12/10/2018");
	info3->SetNDC();
	info3->SetTextColor(kBlue);
	info3->SetTextSize(0.02);
 	info3->Draw();
    }
  fileCount++;
  gPad->SetTicks(1,1);
  gPad->Modified();
  gPad->Update();
  can->SaveAs(pdfname);
  return can;
}
