#include "/home/vasilis/Research/customHistRatioPlot/customHistRatioPlot.h"

void inclusiveJetPlotter(){
/*
	TFile *b_template = new TFile("~/Research/Inclusive_bPurity_Study/templates/b_template_QCD_Pt-15to300_10JetpTcut_220619.root");
	TFile *c_template = new TFile("../../templates/c_template_QCD_Pt-15to300_10JetpTcut_220619.root");
	TFile *uds_template = new TFile("../../templates/uds_template_QCD_Pt-15to300_10JetpTcut_220619.root");
*/
        TFile* data_sample = new TFile("../../samples/bParking18_data/data_output_plots_pTjet10.root","read");
	TFile* mc_template = new TFile("/home/vasilis/Research/Inclusive_bPurity_Study/templates/MC_pTrel_060719.root","read");
	
	TH1F* Hmc_brecoJet_pt = (TH1F*) mc_template->Get("p_{T}^{bJet}");
	Hmc_brecoJet_pt->SetName("p_{T}^{bJet} MC");
        Hmc_brecoJet_pt->Scale(0.785/Hmc_brecoJet_pt->Integral("width"));
	Hmc_brecoJet_pt->SetLineWidth(2);
	Hmc_brecoJet_pt->SetLineColor(kBlue);

        //Choose the pTJet composition b,c,udsg and then the name accordingly.	
	//TH1F* Hmc_crecoJet_pt = (TH1F*) mc_template->Get("p_{T}^{cJet}");
	TH1F* Hmc_crecoJet_pt = (TH1F*) mc_template->Get("p_{T}^{qJet}");
	//Hmc_crecoJet_pt->Add((TH1F*) mc_template->Get("p_{T}^{qJet}"));
	Hmc_crecoJet_pt->Scale(1/Hmc_crecoJet_pt->Integral("width"));
	Hmc_crecoJet_pt->SetLineWidth(2);
	Hmc_crecoJet_pt->SetLineColor(kRed);
	
	TH1F* Hmc_udsrecoJet_pt = (TH1F*) mc_template->Get("p_{T}^{qJet}");
   
        TH1F* Hmc_recoJet_pt = (TH1F*)Hmc_brecoJet_pt->Clone();
	Hmc_recoJet_pt->Add(Hmc_crecoJet_pt,(float)(1-Hmc_brecoJet_pt->Integral("width")));
	cout<<Hmc_brecoJet_pt->Integral("width")<<", "<<Hmc_recoJet_pt->Integral("width")<<endl;
	Hmc_recoJet_pt->SetName("p_{T}^{Jet}(b+udsg) MC");
//	Hmc_recoJet_pt->SetName("p_{T}^{Jet}(b+c) MC");
//	Hmc_recoJet_pt->SetName("p_{T}^{Jet}(b+cudsg) MC");

	TH1F *Hdata_recoJet_pt = (TH1F*) data_sample->Get("Hdata_jet_pt");
	Hdata_recoJet_pt->SetTitle("");
	Hdata_recoJet_pt->SetName("p_{T}^{Jet} DATA");
	Hdata_recoJet_pt->SetLineColor(kBlack);
        Hdata_recoJet_pt->Scale(1/Hdata_recoJet_pt->Integral("width"));
	Hdata_recoJet_pt->SetLineWidth(2);
	
	TCanvas *mc_vs_data = new TCanvas("jet_pt_data_vs_mc","jet_pt_data_vs_mc");        
	customHistRatioPlot(Hdata_recoJet_pt,Hmc_recoJet_pt,mc_vs_data,"p");

}
