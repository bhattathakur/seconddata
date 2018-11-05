void etruevsecal4()
{
  const char * filedata="DATA/E_estandE_true4.dat"; //File storing the estimated and true energy and their errors
  const char * rootfile="ROOTFILES/true_estimated_enregyplot4.root"; //root file to save the plot
  const char * filenamee="DATA/slope_intercept4.dat"; //file to store slope and intercept of plot
  const char * pdfetrue="PLOTS/EtrueECalc4.pdf"; //pdf file location
  auto c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(42);
  auto graph=new TGraphErrors(filedata,"%lg%lg%lg%lg","");//E-calc,E-true,errorE-Calc,errorE-true
  graph->SetTitle("E-True Vs  E-estimated  Plot;E_{estimated}(eV);E_{true}(eV);");
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

  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();

  //Legend
  auto legend=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  //legend->SetHeader("The Legend Title");
  legend->AddEntry(graph->GetFunction("pol1"),"E_{estimated}=P_{0}+P_{1}E_{true}","l");
  legend->AddEntry(graph,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  legend->Draw();
  
//Saving the plot in root file
  auto file=new TFile(rootfile,"RECREATE");
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
   }
} 
