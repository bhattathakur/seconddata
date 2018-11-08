void timeresolution()
{
  const char * pdfetrue="FINAL/resolutionvstime.pdf"; //pdf file location
  const char * inputdata="DATA/compiledtimeresolution.dat"; //source for data file

  
  atuo resocan=new TCanvas();
  resocan->SetGrid();
  resocan->SetFillColor(20);
  graph=new TGraphErrors(inputdata,"%lg%lg%lg%lg","");//time, resolution, runtime/2,error in resolution
  graph->SetTitle("Resolution vs Time  Plot;time (s); resolution (eV);");
  graph->GetYaxis()->SetTitleOffset(1.2);
  graph->GetXaxis()->SetTitleOffset(1.2);
  graph->SetMarkerColor(4);
  graph->SetMarkerStyle(21);
  graph->SetLineColor(9);
  graph->SetLineWidth(2);
  graph->Draw("AP");
  graph->Fit("pol1");
  graph->GetFunction("pol1")->SetLineStyle(2);
  graph->GetFunction("pol1")->SetParName(0,"Intercept(P_{0})");
  graph->GetFunction("pol1")->SetParName(1,"Slope(P_{1})");

  resocan->GetFrame()->SetFillColor(21);
  resocan->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  resocan->Update();
  resocan->SaveAs(pdfetrue);
  
  /*//Legend
  auto legend=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  //legend->SetHeader("The Legend Title");
  legend->AddEntry(graph->GetFunction("pol1"),"E_{estimated}=P_{0}+P_{1}E_{true}","l");
  legend->AddEntry(graph,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  legend->Draw();
  /*
//Saving the plot in root file
  file=new TFile(rootfile,"RECREATE");
  if(file->IsOpen())cout<<rootfile <<" opened successfully"<<endl;
  c->SaveAs(pdfetrue);
  graph->Write();
  c->Write();
  //c->Close();
  ofstream outputgraph(filenamee);
  if(outputgraph.is_open())
   {
     outputgraph<<setw(10)<<  graph->GetFunction("pol1")->GetParameter(0)<<setw(10)<<graph->GetFunction("pol1")->GetParameter(1)<<endl;
     cout<<"Successfully stored intercept and slope in the file"<<filenamee<<endl;
   }
 else
   {
     cout<<"Unable to open the file "<< filenamee<<endl;
     return 0;
     }*/
} 
