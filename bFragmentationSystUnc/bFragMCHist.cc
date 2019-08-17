#include "tree_class.h"

     float Dphi(float phi1,float phi2){

      float result = phi1 - phi2;
      while (result > float(M_PI)) result -= float(2*M_PI);
      while (result <= -float(M_PI)) result += float(2*M_PI);

        return result;
                                                                   }

         float deltaR(float eta1,float phi1,float eta2, float phi2){

          return TMath::Sqrt((eta1-eta2)*(eta1-eta2)+Dphi(phi1,phi2)*Dphi(phi1,phi2));
                                                               }

void bFragMCHist(){
     float jet_pt_cut =10.,jet_eta_cut = 2.1, muon_pt_cut = 9., muon_eta_cut = 1.5;
     float xsec_15to20 = 2799000.0,xsec_20to30 = 2526000.0,xsec_30to50 = 1362000.0,xsec_50to80 = 376600.0, xsec_80to120 = 88930.0, xsec_120to170 = 21230.0, xsec_170to300 = 7055.0;
     //XSDB for DAS=QCD_Pt-*_MuEnrichedPt5_TuneCP5_13TeV_pythia8
     float relative_weight_20to30=1.; //Let the relative statistical weight of the events be normalized according to the 20to30 xsec.
     float relative_weight_15to20 = xsec_15to20/xsec_20to30, relative_weight_30to50 = xsec_30to50/xsec_20to30, relative_weight_50to80=xsec_50to80/xsec_20to30, relative_weight_80to120=xsec_80to120/xsec_20to30, relative_weight_120to170=xsec_120to170/xsec_20to30,relative_weight_170to300=xsec_170to300/xsec_20to30;
	
	TH1F* Hmc_bF_pt=new TH1F("Hmc_bF_pt",";p_{T}^{B}/p_{T}^{b};#frac{1}{N} #frac{dN}{dz}",50,0,1.5);
	Hmc_bF_pt->SetLineWidth(2);
	Hmc_bF_pt->SetLineColor(kBlue);
	
	TH1F* Hmc_bF_p=new TH1F("Hmc_bF_p",";p^{B}/p^{b};#frac{1}{N} #frac{dN}{dz}",50,0,1.5);
	Hmc_bF_p->SetLineWidth(2);
	Hmc_bF_p->SetLineColor(kRed);
	
	TH1F* Hmc_bF_e=new TH1F("Hmc_bF_e",";E^{B}/E^{b};#frac{1}{N} #frac{dN}{dz}",50,0,1.5);
	Hmc_bF_e->SetLineWidth(2);
	Hmc_bF_e->SetLineColor(kGreen);
	
	TH1F* Hmc_bF_par=new TH1F("Hmc_bF_par",";(E+p_{L})_{B}/^{}(E+p)_{b}; #frac{1}{N}#frac{dN}{dz}",50,0,1.5);
	Hmc_bF_par->SetLineWidth(2);
	Hmc_bF_par->SetLineColor(kViolet);

	TH1F* Hmc_bF_ptJet=new TH1F("Hmc_bF_ptJet",";pT(B)/pT(bJet); #frac{1}{N}#frac{dN}{dz}",50,0,1.5);
	Hmc_bF_ptJet->SetLineWidth(2);
	Hmc_bF_ptJet->SetLineColor(kBlack);

	TChain* chain_sample = new TChain("demo/mytree");
//	chain_sample->Add("/home/vasilis/Research/Inclusive_bPurity_Study/samples/MINIAOD_QCD_samples_15to300_pTrelCalc/*.root");
	chain_sample->Add("/home/vasilis/QCD_Pt-15to20_test.root");
	
	tree_class MC;
	MC.Init(chain_sample,"ALL");
	int nentries=chain_sample->GetEntries();
        cout<<"Analyzing MC "<<nentries<<" events"<<endl;

	for(int ientry=0;ientry<nentries;++ientry){
		MC.GetEntry(ientry);
	//	cout<<MC.ancQuark_m->size()<<endl;
	        //if(MC.bFragmentation_function_pT->empty()) continue;
                if(MC.muon_pt->size() == 0 || MC.jet_pt->size()==0) continue;
                if(MC.muon_pt->at(0)<muon_pt_cut || MC.jet_pt->at(0)<jet_pt_cut || abs(MC.jet_eta->at(0))>jet_eta_cut || abs(MC.muon_eta->at(0))>muon_eta_cut) continue;
		float DR=(MC.muon_eta->at(0),MC.muon_phi->at(0),MC.jet_eta->at(0),MC.jet_phi->at(0));
		
		if(DR>=0.4) cout<<"Muon outside of jet cone"<<endl;
		else{
		std::string current_input_file(chain_sample->GetFile()->GetName());
		float current_weight=-9999;
                if(current_input_file.std::string::find("15to20") != std::string::npos) current_weight=relative_weight_15to20; 
                else if(current_input_file.std::string::find("20to30") != std::string::npos) current_weight=relative_weight_20to30;
                else if(current_input_file.std::string::find("30to50") != std::string::npos)  current_weight=relative_weight_30to50;
                else if(current_input_file.std::string::find("50to80") != std::string::npos) current_weight=relative_weight_50to80;
                else if(current_input_file.std::string::find("80to120") != std::string::npos) current_weight=relative_weight_80to120;
                else if(current_input_file.std::string::find("120to170") != std::string::npos) current_weight=relative_weight_120to170;
                else if(current_input_file.std::string::find("170to300") != std::string::npos) current_weight=relative_weight_170to300;
	//        Hmc_bF_pt->Fill(MC.bFragmentation_function_pT->at(0),current_weight);
                if(MC.ancQuark_pdgId->empty() || MC.primHadron_pdgId->empty()) continue;

	//	if(MC.map_quark_jet_muon->at(0) == true && abs(MC.ancQuark_pdgId->at(0)) == 5 && (abs((int)MC.primHadron_pdgId->at(0)/100)==5 || abs((int)MC.primHadron_pdgId->at(0)/1000)==5)){
		cout<<MC.genJet_flavour->size()<<endl;
		cout<<MC.genJet_pt->at(0)<<endl;
		cout<<MC.jet_pt->at(0)<<endl;
		if(MC.map_quark_jet_muon->at(0) == true && abs(MC.ancQuark_pdgId->at(0)) == 5){
		          ROOT::Math::PtEtaPhiMVector p4Hadron(MC.primHadron_pt->at(0),MC.primHadron_y->at(0),MC.primHadron_phi->at(0),MC.primHadron_m->at(0));
		          ROOT::Math::PtEtaPhiMVector p4Quark(MC.ancQuark_pt->at(0),MC.ancQuark_y->at(0),MC.ancQuark_phi->at(0),MC.ancQuark_m->at(0));
			  Hmc_bF_pt->Fill(p4Hadron.pt()/p4Quark.pt(),current_weight);
			  Hmc_bF_p->Fill(p4Hadron.P()/p4Quark.P(),current_weight);
			  Hmc_bF_e->Fill(p4Hadron.E()/p4Quark.E(),current_weight);
			  Hmc_bF_par->Fill((p4Hadron.E()+p4Hadron.Vect().Dot(p4Quark.Vect().Unit()))/(p4Quark.E()+p4Quark.P()),current_weight);
			  Hmc_bF_ptJet->Fill(p4Hadron.pt()/MC.genJet_pt->at(0),current_weight);
		}
		   }//DR<0.4
	}

	TCanvas* CfragFunc = new TCanvas("CfragFunc","CfragFunc");
	Hmc_bF_pt->Draw("hist,e");
	Hmc_bF_p->Draw("hist,e,sames");
	Hmc_bF_e->Draw("hist,e,sames");
	Hmc_bF_par->Draw("hist,e,sames");
	//Hmc_bF_ptJet->Draw("hist,e,sames");
	CfragFunc->BuildLegend();

	TFile* output_file = new TFile("out_bFragHist.root","recreate");
	CfragFunc->Write();
	Hmc_bF_pt->Write();
	Hmc_bF_p->Write();
	Hmc_bF_e->Write();
	Hmc_bF_par->Write();
	Hmc_bF_ptJet->Write();
	 
	delete output_file;
}
