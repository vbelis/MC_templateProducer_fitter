
	
void petersonFunctionPlot(){
	TFile* MChisto_file = new TFile("out_bFragHist.root","read");

	TH1F* Hmc_bF_pt = (TH1F*)MChisto_file->Get("Hmc_bF_pt");
        Hmc_bF_pt->Scale(1/Hmc_bF_pt->Integral("width"));
	Hmc_bF_pt->SetName("p_{T}^{B}/p_{T}^{b}");
	TF1* bFrag_peterson = new TF1("D_{b}^{h}(z)","[0]/(x*(1-1/x-[1]/(1-x))^2)",0,1.);

        bFrag_peterson->SetParameter(0,1);
        bFrag_peterson->FixParameter(1,0.006);
        bFrag_peterson->FixParameter(0,bFrag_peterson->GetParameter(0)/bFrag_peterson->Integral(0,1));
        bFrag_peterson->SetLineWidth(2);
//        bFrag_peterson->SetLineStyle(2);
        bFrag_peterson->SetLineColor(kBlack);
    
        TCanvas* CbFrag = new TCanvas("CbFrag","CbFrag");
        Hmc_bF_pt->Draw("hist,e,sames");
        bFrag_peterson->Draw("same");
        
	TF1* bFrag_peterson_clone = (TF1*)bFrag_peterson->Clone("bFrag_peterson_clone"); 
	bFrag_peterson_clone->FixParameter(1,0.005);
        bFrag_peterson_clone->SetLineColor(kRed);
        bFrag_peterson_clone->FixParameter(0,bFrag_peterson_clone->GetParameter(0)/bFrag_peterson_clone->Integral(0,1));
	bFrag_peterson_clone->Draw("same");
	
	TF1* bFrag_peterson_clone2 = (TF1*)bFrag_peterson->Clone("bFrag_peterson_clone2"); 
	bFrag_peterson_clone2->FixParameter(1,0.007);
        bFrag_peterson_clone2->SetLineColor(kGreen);
        bFrag_peterson_clone2->FixParameter(0,bFrag_peterson_clone2->GetParameter(0)/bFrag_peterson_clone2->Integral(0,1));
	bFrag_peterson_clone2->Draw("same");

	bFrag_peterson->SetTitle("D_{b}^{h}(z), #varepsilon_{b}=0.006");
	bFrag_peterson_clone->SetTitle("D_{b}^{h}(z), #varepsilon_{b}=0.005");
	bFrag_peterson_clone2->SetTitle("D_{b}^{h}(z), #varepsilon_{b}=0.007");
	CbFrag->BuildLegend();

	TLatex* fragmentationFormula = new TLatex(0.4,4,"D_{b}^{h}(z) = #frac{N(#varepsilon_{b})}{z[1-1/z-#varepsilon_{b}/(1-z)]^{2}}");
        fragmentationFormula->Draw();
        fragmentationFormula->SetTextFont(42);
        //fragmentationFormula->SetTextSize(0.07);
	CbFrag->Update();

        TFile* outFunctionHist = new TFile("outFunctionHist.root","recreate");
	CbFrag->Write();

	cout<<bFrag_peterson->Integral(0,1)<<endl;
	cout<<bFrag_peterson_clone->Integral(0,1)<<endl;
	cout<<Hmc_bF_pt->Integral("width")<<endl;
    }
