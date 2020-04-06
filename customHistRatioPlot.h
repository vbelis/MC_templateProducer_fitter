///////////////////////////////////////////////////////////
/// Author: Vasilis Belis.
/// Custom Histogram Ratio Plotter.
/// Presentation & Publication (?) quality. CMS Guidlines.
///////////////////////////////////////////////////////////

void customHistRatioPlot(TH1F* h1,TH1F* h2, TCanvas* c,std::string opt) {

 while(opt != "p" && opt != "s" && opt != "0"){
	 cout<<"Choose \"p\"=\"Preliminary\" or \"s\"=\"Simulation\" or \"0\"= just the CMS Logo"<<endl;
 }
   if(opt == "p") opt="Preliminary";
   else if(opt=="s") opt = "Simulation";
   else opt= "";
   
   gStyle->SetLegendBorderSize(0);
   //Upper plot will be in pad1
   TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   pad1->SetBottomMargin(0.015); // Upper and lower plot are joined
//   pad1->SetGridx();         // Vertical grid
//   pad1->SetGridy(); // horizontal grid
   pad1->SetTickx();
   pad1->SetTicky();
   pad1->Draw();             // Draw the upper pad: pad1
   pad1->cd();               // pad1 becomes the current pad
//   h1->SetStats(0);          // No statistics on upper plot
   h1->Draw("E,hist");               // Draw h1
   h2->Draw("E,hist,sames");         // Draw h2 on top of h1 with stats box "sames". It will be on top of the other.

   // Do not draw the Y axis label on the upper plot and redraw a small
   // axis instead, in order to avoid the first label (0) to be clipped.
   //h1->GetYaxis()->SetLabelSize(0.);
   //TGaxis *axis = new TGaxis( -5, 20, -5, 220, 20,220,510,"");
   //axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   //axis->SetLabelSize(15);
   //axis->Draw();

   // lower plot will be in pad
   c->cd();          // Go back to the main canvas before defining pad2
   TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.25);
   pad2->SetGridx(); // vertical grid
   pad2->SetGridy(); // horizontal grid
   pad2->SetTickx();
   pad2->SetTicky();
   pad2->Draw();
   pad2->cd();       // pad2 becomes the current pad

   // Define the ratio plot
   TH1F *h3 = (TH1F*)h1->Clone("h3");
   h3->SetLineColor(kBlack);
  // h3->SetMinimum(0.5);  // Define Y ..
  // h3->SetMaximum(1.5); // .. range
   h3->Sumw2();
   h3->SetStats(0);      // No statistics on lower plot
   h3->Divide(h2);
   h3->SetMarkerStyle(20);
   h3->Draw("ep");       // Draw the ratio plot

   // h1 settings
   h1->SetLineColor(kBlue);
   h1->SetLineWidth(2);

   //h1 axis upper-plot settings
   h1->GetYaxis()->SetTitleSize(30);
   h1->GetYaxis()->SetTitleFont(43);
   h1->GetYaxis()->SetTitleOffset(1.);
   //Choose the max value of the upper-pad Y axis properly:
   h1->GetYaxis()->SetRangeUser(0,std::max(h1->GetMaximum(),h2->GetMaximum())*1.1);
   h1->GetXaxis()->SetLabelSize(0.);//So it does not clip with lower pad.
   h1->GetXaxis()->SetTitleSize(0.);//So it does not clip with lower pad.

   // h2 settings
   h2->SetLineColor(kRed);
   h2->SetLineWidth(2);

   
   //BuildLegend on upper pad
   pad1->BuildLegend();
   pad1->Update();
   
   //Draw CMS Logo on Upper Pad:
   pad1->cd();
   std::string option = "#bf{CMS} #it{"+opt+"}";
   TLatex * cms_logo = new TLatex(h1->GetXaxis()->GetXmin(),h1->GetMaximum()*1.022,option.std::string::c_str());
   cms_logo->Draw();
   cms_logo->SetTextFont(42);
   cms_logo->SetTextSize(0.07);
   
   pad2->cd();
   // Ratio plot (h3) settings
   h3->SetTitle(""); // Remove the ratio title

   // Y axis ratio plot settings
   std::string name1(h1->GetName()), name2(h2->GetName());
   std::string ratioYaxisTitle("#frac{"+name1+"}{"+name2+"}");
   h3->GetYaxis()->SetTitle(ratioYaxisTitle.std::string::c_str());
   //h3->GetYaxis()->SetRangeUser(h3->GetMinimum()*0.97,h3->GetMaximum()*1.03);
   h3->GetYaxis()->CenterTitle(1);
   h3->GetYaxis()->SetNdivisions(505);
   h3->GetYaxis()->SetTitleSize(25);
   h3->GetYaxis()->SetTitleFont(43);
   h3->GetYaxis()->SetTitleOffset(1.2);
   h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetYaxis()->SetLabelSize(22);

   // X axis ratio plot settings
   h3->GetXaxis()->SetTitleSize(25);
   h3->GetXaxis()->SetTitleFont(43);
   h3->GetXaxis()->SetTitleOffset(3.9);
   h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetXaxis()->SetLabelSize(22);
}
