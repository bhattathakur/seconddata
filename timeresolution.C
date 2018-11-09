timeresolution()
{
   // const char * filedata="DATA/bkg0E_estandE_true.dat"; //File storing the estimated and true energy and their errors
  // const char * rootfile="ROOTFILES/bkg0true_estimated_enregyplot.root"; //root file to save the plot
  // const char * filenamee="DATA/bkg0slope_intercept.dat"; //file to store slope and intercept of plot
  const char * pdfetrue="FINAL/resolutionvstimesecond.pdf"; //pdf file location
  char * inputdata="FINAL/compiledtimeresolution.dat";
  auto c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(20);
  graph_expected=new TGraphErrors(inputdata,"%lg%lg%lg%lg","");//time, resolution, runtime/2,error in resolution
  graph_expected->SetTitle("FWHM vs Time  Plot;time (s); FWHM (eV);");
  graph_expected->GetYaxis()->SetTitleOffset(1.2);
  graph_expected->GetXaxis()->SetTitleOffset(1.2);
  graph_expected->SetMarkerColor(4);
  graph_expected->SetMarkerStyle(21);
  graph_expected->SetLineColor(9);
  graph_expected->SetLineWidth(2);
  graph_expected->Draw("AP");
  graph_expected->Fit("pol0");
  // graph_expected->GetFunction("pol0")->SetLineStyle(2);
  graph_expected->GetFunction("pol0")->SetParName(0,"FWHM");
  // graph_expected->GetFunction("pol0")->SetParName(1,"Slope(P_{1})");

  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();
  c->SaveAs(pdfetrue);
  
  /*//Legend
  auto legend=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  //legend->SetHeader("The Legend Title");
  legend->AddEntry(graph_expected->GetFunction("pol0"),"E_{estimated}=P_{0}+P_{1}E_{true}","l");
  legend->AddEntry(graph_expected,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  legend->Draw();
  /*
//Saving the plot in root file
  file=new TFile(rootfile,"RECREATE");
  if(file->IsOpen())cout<<rootfile <<" opened successfully"<<endl;
  c->SaveAs(pdfetrue);
  graph_expected->Write();
  c->Write();
  //c->Close();
  ofstream outputgraph(filenamee);
  if(outputgraph.is_open())
   {
     outputgraph<<setw(10)<<  graph_expected->GetFunction("pol0")->GetParameter(0)<<setw(10)<<graph_expected->GetFunction("pol0")->GetParameter(1)<<endl;
     cout<<"Successfully stored intercept and slope in the file"<<filenamee<<endl;
   }
 else
   {
     cout<<"Unable to open the file "<< filenamee<<endl;
     return 0;
     }*/
} 
