#include "/home/vasilis/Research/customHistRatioPlot/customHistRatioPlot.h"

void pTrelPlots(){
	
        gStyle->SetLegendBorderSize(0);	
	TFile* template_file= new TFile("~/Research/Inclusive_bPurity_Study/templates/MC_pTrel_060719.root","read");
	TH1F* HpTb_rel_dir = (TH1F*)template_file->Get("p_{T}^{rel}(b#rightarrow#mu+X)_dir");
	TH1F* HpTb_rel_seq = (TH1F*)template_file->Get("p_{T}^{rel}(b#rightarrow..#rightarrow#mu+X)");
	TH1F* HpTb_rel = (TH1F*)template_file->Get("p_{T}^{rel}(b#rightarrow#mu+X)");
	TH1F* HpTb_rel_dir_clone = new (TH1F) (*HpTb_rel_dir);
	//TH1F* HpTb_rel_dir_clone = (TH1F*)HpTb_rel_dir->Clone("p_{T}^{rel}(b#rightarrow#mu+X)_dirClone");
	
	//Normilizing Histos to 1:
	HpTb_rel_dir->Scale(1/HpTb_rel_dir->Integral("width"));
	HpTb_rel_seq->Scale(1/HpTb_rel_seq->Integral("width"));
	HpTb_rel->Scale(1/HpTb_rel->Integral("width"));
        HpTb_rel_dir_clone->Scale(1/HpTb_rel_dir_clone->Integral("width"));
	
	HpTb_rel_dir->GetXaxis()->SetRangeUser(0,3.5); 
	HpTb_rel_seq->GetXaxis()->SetRangeUser(0,3.5);
	HpTb_rel->GetXaxis()->SetRangeUser(0,3.5);
	HpTb_rel_dir_clone->GetXaxis()->SetRangeUser(0,3.5);

	//Set different axis titles to make the final plot nicer:
	HpTb_rel_dir->GetYaxis()->SetTitle("#frac{1}{N} #frac{dN}{dp_{T}^{rel}}");
	HpTb_rel->GetYaxis()->SetTitle("#frac{1}{N} #frac{dN}{dp_{T}^{rel}}");
	
	HpTb_rel->SetName("p_{T}^{rel}(b#rightarrow#mu+X;tot.)");
	HpTb_rel_dir->SetName("p_{T}^{rel}(b#rightarrow#mu+X;dir.)");
	HpTb_rel_dir_clone->SetName("p_{T}^{rel}(b#rightarrow#mu+X;dir.)");
	HpTb_rel_seq->SetName("p_{T}^{rel}(b#rightarrow#3dots#rightarrow#mu+X)");

        //Creating the 2 canvases for the custom ratio-plots: 
	TCanvas* Cdir_seq_ratio = new TCanvas("Cdir_seq_ratio","Cdir_seq_ratio",800,800);
	TCanvas* Ctot_dir_ratio = new TCanvas("Ctot_dir_ratio","Ctot_dir_ratio",800,800);

	Cdir_seq_ratio->cd();
	customHistRatioPlot(HpTb_rel_dir,HpTb_rel_seq,Cdir_seq_ratio,"s");
        
        Ctot_dir_ratio->cd();
	customHistRatioPlot(HpTb_rel,HpTb_rel_dir_clone,Ctot_dir_ratio,"s");
}
