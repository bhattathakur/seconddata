TgraphFromTree()
{
  TCanvas *can=new TCanvas();
  can->SetGrid();
  gPad->SetTicks(1,1);
  TFile * readtree=new TFile("time_vs_others.root");//Name of root file
  TTree * mytree=(TTree*)readtree->Get("T");//reading the given tree as mytree
  mytree->Draw("fwhm:time:fwhmError:timeError","sn>20","goff"); //goff->without graphics
  //mytree->Draw("ap");
  TGraphErrors * graph=new TGraphErrors(mytree->GetSelectedRows(),mytree->GetV2(),mytree->GetV1(),mytree->GetV3(),mytree->GetV4());
  
  graph->SetMarkerStyle(15);
  graph->SetMarkerColor(2);
  graph->SetMarkerSize(30);
  graph->Fit("pol0");
  graph->Draw("ap");
  can->Update();
}
