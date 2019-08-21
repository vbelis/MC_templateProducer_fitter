

void Graphics(Int_t & m,Int_t & n){   cout<<endl<<endl<<"--------------------[INCLUSIVE STUDY FIT]----------------------"<<endl;
    cout<<"   Number of events N_evt= "<< m <<" & Number ''experiments''  n = "<<n<<"\n";
    cout<<"          c --> muon + X "<<endl;
    cout<<"          b --> muon + X' "<<endl;
    cout<<"          uds --> muon + X'' "<<endl;
    cout<<"---------------------------------------------------------------"<<endl;   }


//-------------------------------------------------DEFINING ALL FILES AND HISTOGRAMS GLOBALLY--------------------------------------------------------------------------------

     TFile *fftestb = new TFile("../../templates/b_template_QCD_Pt-15to300_10JetpTcut.root");
     TFile *fftestc = new TFile("../../templates/c_template_QCD_Pt-15to300_10JetpTcut.root");
     TFile *fftestl = new TFile("../../templates/uds_template_QCD_Pt-15to300_10JetpTcut.root");

     TH1F *Hpt_rel_b_no_dif=(TH1F*)fftestb->Get("Hpt_rel_no_dif");
     TH1F *Hpt_rel_c_no_dif=(TH1F*)fftestc->Get("Hpt_rel_no_dif");
     TH1F * Hpt_rel_l_no_dif = (TH1F*) fftestl->Get("Hpt_rel_no_dif");
     auto Hpt_rel_cl_no_dif = new TH1F(*Hpt_rel_c_no_dif);    
/*
     TFile *template_file = new TFile("../../templates/MC_pTrel_060719.root","read");

     TH1F *Hpt_rel_b_no_dif=(TH1F*)template_file->Get("p_{T}^{rel}(b#rightarrow#mu+X)");
     TH1F *Hpt_rel_c_no_dif=(TH1F*)template_file->Get("p_{T}^{rel}(c#rightarrow#mu+X)");
     TH1F *Hpt_rel_l_no_dif = (TH1F*) template_file->Get("p_{T}^{rel}(q#rightarrow#mu+X)");
     TH1F *Hpt_rel_cl_no_dif = new TH1F(*Hpt_rel_c_no_dif);
*/
     TH1F *Hdata=new TH1F("Hdata","Pseudo-data points;p_{T}^{rel};entries/bin", 60, 0., 3.5);
//CAUTION I CHANGE THE BINNING TO INVASTIGATE THE FITTING PROCEDURE
     TH1F *Hdata_b=new TH1F("Hdata_b","Pseudo data of b quark p_{T}^{rel}; p_{T}^{rel}; entries/bin", 60, 0., 3.5);
     TH1F *Hdata_c=new TH1F("Hdata_c","Pseudo data of c quark p_{T}^{rel}; p_{T}^{rel}; entries/bin", 60, 0., 3.5);
     TH1F *Hdata_l=new TH1F("Hdata_l","Pseudo data of uds quarks p_{T}^{rel}; p_{T}^{rel}; entries/bin", 60, 0., 3.5);
     TH1F *Hdata_cl=new TH1F("Hdata_cl","Pseudo data of udsc quarks p_{T}^{rel}; p_{T}^{rel}; entries/bin", 60, 0., 3.5);


     TH1F *Hpullb=new TH1F("Hpullb","Pull Test a_{b}; pull=#frac{exp-truth}{Error_{exp}}; entries/bin", 80 , -4., 4.);
     TH1F *Hpullc=new TH1F("Hpullc","Pull Test a_{c}; pull=#frac{exp-truth}{Error_{exp}}; entries/bin", 80 , -4., 4.);
     TH1F *Hpulll=new TH1F("Hpulll","Pull Test a_{l}; pull=#frac{exp-truth}{Error_{exp}}; entries/bin", 80 , -4., 4.);

     //Double_t shift = 0.5*Hpull->GetBinWidth(1);
     //Hpull->GetXaxis()->SetLimits(-4.-shift,4.-shift);

     TH1F *Hpull=new TH1F("Hpull","Pull Test Fitting Parameter fb; pull=#frac{exp-truth}{Error_{exp}}; entries/bin", 40 , -4., 4.);  


//------------------------------------------------------PULL TEST FUNCTION -------------------------------------------------------------------------------


void data_fit(){

     Hpt_rel_b_no_dif->GetXaxis()->SetRangeUser(0,3.5);
     Hpt_rel_c_no_dif->GetXaxis()->SetRangeUser(0,3.5);
     Hpt_rel_l_no_dif->GetXaxis()->SetRangeUser(0,3.5);
     Hpt_rel_cl_no_dif->GetXaxis()->SetRangeUser(0,3.5);

     Hpt_rel_b_no_dif->SetName("p_{T}^{rel}(b#rightarrow#mu+X)");
     Hpt_rel_c_no_dif->SetName("p_{T}^{rel}(c#rightarrow#mu+X)");
     Hpt_rel_l_no_dif->SetName("p_{T}^{rel}(q#rightarrow#mu+X)");
     Hpt_rel_cl_no_dif->SetName("p_{T}^{rel}(q#rightarrow#mu+X)");


     //Hpt_rel_b_no_dif->GetYaxis()->SetTitleFont(42);



     Hpt_rel_b_no_dif->Sumw2();
     Hpt_rel_c_no_dif->Sumw2(); 
     Hpt_rel_l_no_dif->Sumw2();
     Hpt_rel_cl_no_dif->Sumw2();

       Hpt_rel_c_no_dif->SetLineColor(kRed);
       Hpt_rel_b_no_dif->SetLineColor(kBlue);
       Hpt_rel_l_no_dif->SetLineColor(kGreen); 
       Hpt_rel_cl_no_dif->Add(Hpt_rel_l_no_dif);
       Hpt_rel_cl_no_dif->SetLineColor(kOrange-3);

    //DEFINING FIT FUNCTION FROM THE FUNCTION DEFINED ABOVE
/*
    TF1 *f = new TF1("f",fit_funct,0.,6.,2);
    f->SetParNames("a_{b}","a_{c}");
    f->SetLineStyle(2);
    f->SetParLimits(0,0,10000);
    f->SetParLimits(1,0,10000);
*/
    //DEFINING A FUNCTIONS WITH WHICH WE PARAMETRIZE THE pT_rel DISTRIBUTIONS


//pT_rel with no dif.
    TF1 *B_no_dif = new TF1("B_no_dif","[0]*pow(x,[1])*exp([2]*x+[3]*pow(x,2)+[4]*pow(x,3)+[5]*pow(x,4)+[6]*pow(x,5)+[7]*pow(x,6)+[8]*pow(x,7)+[9]*pow(x,8)+[10]*pow(x,9))",0.,3.5);
//    TF1 *B_no_dif = new TF1("B_no_dif","[0]*pow(x,[1])*exp([2]*x+[3]*pow(x,2))",0.,3.5);
        B_no_dif->SetParNames("ab","bb","cb","db","eb","ffb");   
                 B_no_dif->SetLineColor(kBlue);

//    TF1 *C_no_dif = new TF1("C_no_dif","[0]*pow(x,[1])*exp([2]*x+[3]*pow(x,2)+[4])",0.,3.5);
    TF1 *C_no_dif = new TF1("C_no_dif","[0]*pow(x,[1])*exp([2]*x+[3]*pow(x,2)+[4]*pow(x,3)+[5]*pow(x,4)+[6]*pow(x,5)+[7]*pow(x,6)+[8]*pow(x,7)+[9]*pow(x,8)+[10]*pow(x,9))",0.,3.5);

       C_no_dif->SetParNames("ac","bc","cc","dc","ec","ffc");
       C_no_dif->SetLineColor(kRed);

//    TF1 *L_no_dif = new TF1("L_no_dif","[0]*pow(x,[1])*exp([2]*x+[3]*pow(x,2))",0.,3.5);
    TF1 *L_no_dif = new TF1("L_no_dif","[0]*pow(x,[1])*exp([2]*x+[3]*pow(x,2)+[4]*pow(x,3)+[5]*pow(x,4)+[6]*pow(x,5)+[7]*pow(x,6)+[8]*pow(x,7)+[9]*pow(x,8)+[10]*pow(x,9))",0.,3.5);

       L_no_dif->SetParNames("al","bl","cl","dl","el","ffl");
       L_no_dif->SetLineColor(kGreen);
//And for merging c and uds distributions.
  //  TF1 *CL_no_dif = new TF1("CL_no_dif","[0]*pow(x,[1])*exp([2]*x+[3]*pow(x,2))",0.,3.5);
    TF1 *CL_no_dif = new TF1("CL_no_dif","[0]*pow(x,[1])*exp([2]*x+[3]*pow(x,2)+[4]*pow(x,3)+[5]*pow(x,4)+[6]*pow(x,5)+[7]*pow(x,6)+[8]*pow(x,7)+[9]*pow(x,8)+[10]*pow(x,9))",0.,3.5);
       CL_no_dif->SetParNames("acl","bcl","ccl","dcl","ecl","ffcl");
       CL_no_dif->SetLineColor(kOrange-3);

          Hpt_rel_b_no_dif->GetXaxis()->SetTitle("p_{T}^{rel} [GeV]");
          Hpt_rel_b_no_dif->GetYaxis()->SetTitle("Entries/Bin");
          //Hpt_rel_b_no_dif->GetYaxis()->CenterTitle(1);
          //Hpt_rel_b_no_dif->GetYaxis()->SetTitleSize(0.065);
          Hpt_rel_b_no_dif->SetTitle("");
          Hpt_rel_b_no_dif->GetYaxis()->SetTitle(" ");
          Hpt_rel_b_no_dif->GetXaxis()->SetTitleSize(0.05);
          Hpt_rel_b_no_dif->GetXaxis()->SetTitleOffset(0.65);

          Hpt_rel_c_no_dif->GetXaxis()->SetTitle("p_{T}^{rel} [GeV]");
          Hpt_rel_c_no_dif->SetTitle("");
          Hpt_rel_c_no_dif->GetYaxis()->SetTitle(" ");
          Hpt_rel_c_no_dif->GetXaxis()->SetTitleSize(0.05);
          Hpt_rel_c_no_dif->GetXaxis()->SetTitleOffset(0.65);

          Hpt_rel_l_no_dif->GetXaxis()->SetTitle("p_{T}^{rel} [GeV]");
          Hpt_rel_l_no_dif->SetTitle("");
          Hpt_rel_l_no_dif->GetYaxis()->SetTitle(" ");
          Hpt_rel_l_no_dif->GetXaxis()->SetTitleSize(0.05);
          Hpt_rel_l_no_dif->GetXaxis()->SetTitleOffset(0.65);

          Hpt_rel_cl_no_dif->GetXaxis()->SetTitle("p_{T}^{rel} [GeV]");
          Hpt_rel_cl_no_dif->SetTitle("");
          Hpt_rel_cl_no_dif->GetYaxis()->SetTitle(" ");
          Hpt_rel_cl_no_dif->GetXaxis()->SetTitleSize(0.05);
          Hpt_rel_cl_no_dif->GetXaxis()->SetTitleOffset(0.65);

//No_dif fits
          //ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit");//https://root.cern.ch/root/html/tutorials/fit/fitNormSum.C.html
   ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(100000);
 
                TCanvas *input_parametrization_canvas = new TCanvas("Parametrizing the input distributions (no_dif)");

                 input_parametrization_canvas->cd(1);	      
                 //gStyle->SetStatY(0.9);                
                 //// Set y-position (fraction of pad size)
                 //gStyle->SetStatX(1.3);                
                 //// Set x-position (fraction of pad size)
                 //gStyle->SetStatW(0.25);                
                 //// Set width of stat-box (fraction of pad size)
                 //gStyle->SetStatH(0.07);                
                 // Set height of stat-box (fraction of pad size)
                 input_parametrization_canvas->Divide(2,2);
                 input_parametrization_canvas->cd(1);
                 input_parametrization_canvas->cd(1)->SetTickx();
                 input_parametrization_canvas->cd(1)->SetTicky();
   
                 B_no_dif->SetParameter(0,2e+02);
                 Hpt_rel_b_no_dif->Fit(B_no_dif,"L");
                 
                 Hpt_rel_b_no_dif->Draw("hist,same");
                 gStyle->SetOptFit(100);
           //cout<<"Hpt_rel_b_no_dif->Integral('width')= "<<Hpt_rel_b_no_dif->Integral("width")<< ", B_no_dif->Integral(0,3.5)= "<<B_no_dif->Integral(0,3.5)<<endl;     
 
                 input_parametrization_canvas->cd(2);
                 input_parametrization_canvas->cd(2)->SetTickx();
                 input_parametrization_canvas->cd(2)->SetTicky();
                 C_no_dif->SetParameter(0,2e+02);
                 Hpt_rel_c_no_dif->Fit(C_no_dif,"L");
                 Hpt_rel_c_no_dif->Draw("hist,same");
                 gStyle->SetOptFit(100);
           //cout<<"Hpt_rel_c_no_dif->Integral('width')= "<<Hpt_rel_c_no_dif->Integral("width")<< ", C_no_dif->Integral(0,3.5)= "<<C_no_dif->Integral(0,3.5)<<endl;     

                 input_parametrization_canvas->cd(3);
                 input_parametrization_canvas->cd(3)->SetTickx();
                 input_parametrization_canvas->cd(3)->SetTicky();
                 L_no_dif->SetParameter(0,2e+02);
                 Hpt_rel_l_no_dif->Fit(L_no_dif,"L");
                 Hpt_rel_l_no_dif->Draw("hist,same");
                 gStyle->SetOptFit(100);
           //cout<<"Hpt_rel_l_no_dif->Integral('width')= "<<Hpt_rel_l_no_dif->Integral("width")<< ", L_no_dif->Integral(0,3.5)= "<<L_no_dif->Integral(0,3.5)<<endl;     

                 input_parametrization_canvas->cd(4);
                 input_parametrization_canvas->cd(4)->SetTickx();
                 input_parametrization_canvas->cd(4)->SetTicky();
                 CL_no_dif->SetParameter(0,1.5e+02);
                 Hpt_rel_cl_no_dif->Fit(CL_no_dif,"L");
                 Hpt_rel_cl_no_dif->Draw("hist,same");
                 gStyle->SetOptFit(100);
		 
//NO_DIF:

//1. Normalizing the fitting functions so the normalization of the f_e gives b purity.
            C_no_dif->SetParameter(0,C_no_dif->GetParameter(0)/Hpt_rel_c_no_dif->Integral("width"));
            B_no_dif->SetParameter(0,B_no_dif->GetParameter(0)/Hpt_rel_b_no_dif->Integral("width"));
            L_no_dif->SetParameter(0,L_no_dif->GetParameter(0)/Hpt_rel_l_no_dif->Integral("width"));
            CL_no_dif->SetParameter(0,CL_no_dif->GetParameter(0)/Hpt_rel_cl_no_dif->Integral("width"));
/*
//2. Normalizing the fitting functions so that fitting parameters are number of events.
            C_no_dif->SetParameter(0,C_no_dif->GetParameter(0)/Hpt_rel_c_no_dif->GetEntries());
            B_no_dif->SetParameter(0,B_no_dif->GetParameter(0)/Hpt_rel_b_no_dif->GetEntries());
            L_no_dif->SetParameter(0,L_no_dif->GetParameter(0)/Hpt_rel_l_no_dif->GetEntries());
            CL_no_dif->SetParameter(0,CL_no_dif->GetParameter(0)/Hpt_rel_cl_no_dif->GetEntries());
*/
	
    TString B_no_dif_formula,L_no_dif_formula,C_no_dif_formula,CL_no_dif_formula,newCL_no_dif_formula;
    B_no_dif_formula = B_no_dif->GetFormula()->GetExpFormula("P");
    C_no_dif_formula = C_no_dif->GetFormula()->GetExpFormula("P");
    L_no_dif_formula = L_no_dif->GetFormula()->GetExpFormula("P");
    CL_no_dif_formula = CL_no_dif->GetFormula()->GetExpFormula("P");
    newCL_no_dif_formula = C_no_dif_formula + L_no_dif_formula;

/******************************************************
//   TCanvas * test = new TCanvas("Testing Fitters");
    TF1 *B_no_dif_copy = new TF1("B_no_dif_copy",B_no_dif_formula,0.,3.5);
    TF1 *C_no_dif_copy = new TF1("C_no_dif_copy",C_no_dif_formula,0.,3.5);
    TF1 *L_no_dif_copy = new TF1("L_no_dif_copy",L_no_dif_formula,0.,3.5);
    TF1 *CL_no_dif_copy = new TF1("CL_no_dif_copy",CL_no_dif_formula,0.,3.5);

*************************************************************/
    
        TFile *data_file = new TFile("../../samples/bParking18_data/data_output_plots_pTjet10.root","read");
        TH1F * Hdata_pt_rel_no_dif = (TH1F*)data_file->Get("Hdata_pt_rel_no_dif");
        Hdata_pt_rel_no_dif->SetLineColor(kBlack);
        Hdata_pt_rel_no_dif->SetLineWidth(2);
        Hdata_pt_rel_no_dif->SetMarkerStyle(20);
        Hdata_pt_rel_no_dif->Sumw2();
        Hdata_pt_rel_no_dif->GetXaxis()->SetRangeUser(0.,3.5);
        Hdata_pt_rel_no_dif->SetTitle("");
        Hdata_pt_rel_no_dif->SetName("p_{T}^{rel}(inc. data)");
        Hdata_pt_rel_no_dif->GetYaxis()->SetTitle("#frac{1}{N}#frac{dN}{dp_{T}^{rel}}");
        Hdata_pt_rel_no_dif->GetYaxis()->SetTitleSize(0.04);
        Hdata_pt_rel_no_dif->GetYaxis()->SetTitleFont(42);
        Hdata_pt_rel_no_dif->GetYaxis()->SetTitleOffset(0.6);
        Hdata_pt_rel_no_dif->Scale(1/Hdata_pt_rel_no_dif->Integral("width"));

//NO_DIF:
        //gStyle->SetOptFit(1);
   
        TF1 * my_fit_no_dif = new TF1("my_fit_no_dif","[0]*"+B_no_dif_formula+"+(1-[0])*"+CL_no_dif_formula,0.,3.5);
        my_fit_no_dif->SetLineColor(kViolet);
        my_fit_no_dif->SetLineWidth(3);
        my_fit_no_dif->SetParName(0,"f_b");
        
        TF1 * my_3fit_no_dif = new TF1("my_3fit_no_dif","[0]*"+B_no_dif_formula+"+[1]*"+C_no_dif_formula+"+[2]*"+L_no_dif_formula,0.,3.5);
        my_3fit_no_dif->SetLineColor(kViolet);
        my_3fit_no_dif->SetLineWidth(3);
        my_3fit_no_dif->SetParName(0,"f_b");
        my_3fit_no_dif->SetParName(1,"f_c");
        my_3fit_no_dif->SetParName(2,"f_q");
        my_3fit_no_dif->SetParameter(0,0.7);
        my_3fit_no_dif->SetParLimits(0,0.,1.);
        my_3fit_no_dif->SetParLimits(1,0.,1.);
        my_3fit_no_dif->SetParLimits(2,0.,1.);

        TCanvas * data_fit_pt_rel_no_dif = new TCanvas("data fit pt_rel_no_dif");

	data_fit_pt_rel_no_dif->cd()->SetTickx();
	data_fit_pt_rel_no_dif->cd()->SetTicky();
        Hdata_pt_rel_no_dif->GetYaxis()->CenterTitle(1);
        Hdata_pt_rel_no_dif->GetYaxis()->SetTitleSize(0.06);
        Hdata_pt_rel_no_dif->Fit(my_fit_no_dif);
    
        TF1 * B_no_dif_fit_component = new TF1("B_no_dif_fit_component",std::to_string(my_fit_no_dif->GetParameter(0))+"*"+B_no_dif_formula,0.,3.5);
        B_no_dif_fit_component->SetTitle("b#rightarrow#mu+X: B(p_{T}^{rel})");
        B_no_dif_fit_component->SetLineColor(kBlue);
        B_no_dif_fit_component->SetLineStyle(2);
        B_no_dif_fit_component->SetLineWidth(2);
        TF1 * CL_no_dif_fit_component = new TF1("CL_no_dif_fit_component","(1-"+std::to_string(my_fit_no_dif->GetParameter(0))+")*("+CL_no_dif_formula+")",0.,3.5);
        CL_no_dif_fit_component->SetTitle("udsc#rightarrow#mu+X': CQ(p_{T}^{rel})");
        CL_no_dif_fit_component->SetLineColor(kRed);
        CL_no_dif_fit_component->SetLineStyle(2);
        CL_no_dif_fit_component->SetLineWidth(2);

        B_no_dif_fit_component->Draw("same");
        CL_no_dif_fit_component->Draw("same");
        gStyle->SetLegendBorderSize(0);//TLegend with no border!
        
        data_fit_pt_rel_no_dif->cd()->BuildLegend();

       TLatex * cms_logo = new TLatex(Hdata_pt_rel_no_dif->GetXaxis()->GetXmin(),Hdata_pt_rel_no_dif->GetMaximum()*1.095,"CMS");
       cms_logo->SetTextSize(0.065);
       cms_logo->Draw("same");

        //3-Parameter Fit:

        TCanvas * data_3fit_pt_rel_no_dif = new TCanvas("data_3fit_pt_rel_no_dif","data_3fit_pt_rel_no_dif");
	    data_3fit_pt_rel_no_dif->cd()->SetTickx();
	    data_3fit_pt_rel_no_dif->cd()->SetTicky();
        TH1F* Hdata_pt_rel_no_dif_clone = (TH1F*) Hdata_pt_rel_no_dif->Clone();
        Hdata_pt_rel_no_dif_clone -> GetYaxis()->SetRangeUser(-0.01,0.85*Hdata_pt_rel_no_dif->GetYaxis()->GetXmax());
        Hdata_pt_rel_no_dif_clone->GetYaxis()->CenterTitle(1);
        Hdata_pt_rel_no_dif_clone->GetYaxis()->SetTitleSize(0.06);
        Hdata_pt_rel_no_dif_clone->Fit(my_3fit_no_dif);

        TF1 * B_no_dif_3fit_component = new TF1("B_no_dif_3fit_component",std::to_string(my_3fit_no_dif->GetParameter(0))+"*"+B_no_dif_formula,0.,3.5);
        B_no_dif_3fit_component->SetTitle("b#rightarrow#mu+X: B(p_{T}^{rel})");
        B_no_dif_3fit_component->SetLineColor(kBlue);
        B_no_dif_3fit_component->SetLineStyle(2);
        B_no_dif_3fit_component->SetLineWidth(2);
        TF1 * C_no_dif_3fit_component = new TF1("C_no_dif_3fit_component",std::to_string(my_3fit_no_dif->GetParameter(1))+"*"+C_no_dif_formula,0.,3.5);
        C_no_dif_3fit_component->SetTitle("c#rightarrow#mu+X': C(p_{T}^{rel})");
        C_no_dif_3fit_component->SetLineColor(kRed);
        C_no_dif_3fit_component->SetLineStyle(2);
        C_no_dif_3fit_component->SetLineWidth(2);
        //TF1 * L_no_dif_3fit_component = new TF1("L_no_dif_3fit_component","(1-"+std::to_string(my_3fit_no_dif->GetParameter(0))+"-"+std::to_string(my_3fit_no_dif->GetParameter(1))+")*"+L_no_dif_formula,0.,3.5);
        TF1 * L_no_dif_3fit_component = new TF1("L_no_dif_3fit_component",std::to_string(my_3fit_no_dif->GetParameter(2))+"*"+L_no_dif_formula,0.,3.5);
        L_no_dif_3fit_component->SetTitle("uds#rightarrow#mu+X': CQ(p_{T}^{rel})");
        L_no_dif_3fit_component->SetLineColor(kGreen);
        L_no_dif_3fit_component->SetLineStyle(2);
        L_no_dif_3fit_component->SetLineWidth(2);

        B_no_dif_3fit_component->Draw("same");
        C_no_dif_3fit_component->Draw("same");
        L_no_dif_3fit_component->Draw("same");

        data_3fit_pt_rel_no_dif->cd()->BuildLegend();
 
        cms_logo->Draw("same");     

        TLatex * text_fit_no_dif_1 = new TLatex();
        TLatex * text_fit_no_dif_2 = new TLatex();
        TLatex * text_fit_no_dif_3 = new TLatex();
        text_fit_no_dif_1->SetTextFont(42);
        text_fit_no_dif_2->SetTextFont(42);
        text_fit_no_dif_3->SetTextFont(42);

        TString bPurity_no_dif(std::to_string(my_fit_no_dif->GetParameter(0)));
        TString bPurity_no_dif_err(std::to_string(my_fit_no_dif->GetParError(0)));
        TString cPurity_no_dif(std::to_string(1-my_fit_no_dif->GetParameter(0)));
        TString cPurity_no_dif_err(std::to_string(my_fit_no_dif->GetParError(0)));

        
        data_fit_pt_rel_no_dif->cd();
        text_fit_no_dif_1->DrawLatex(2,0.5*Hdata_pt_rel_no_dif->GetMaximum(),"P_{b}= "+bPurity_no_dif+" #pm "+bPurity_no_dif_err);
        text_fit_no_dif_2->DrawLatex(2,0.4*Hdata_pt_rel_no_dif->GetMaximum(),"P_{c}= "+cPurity_no_dif+" #pm "+cPurity_no_dif_err);
        
        data_3fit_pt_rel_no_dif->cd();
        bPurity_no_dif = std::to_string(my_3fit_no_dif->GetParameter(0));
        bPurity_no_dif_err = std::to_string(my_3fit_no_dif->GetParError(0));
        cPurity_no_dif = std::to_string(my_3fit_no_dif->GetParameter(1));
        cPurity_no_dif_err = std::to_string(my_3fit_no_dif->GetParError(1));
 //       TString udsPurity_no_dif(std::to_string(1-my_3fit_no_dif->GetParameter(0)-my_3fit_no_dif->GetParameter(1)));
   //     TString udsPurity_no_dif_err(std::to_string(sqrt(my_3fit_no_dif->GetParError(0)*my_3fit_no_dif->GetParError(0)+my_3fit_no_dif->GetParError(1)*my_3fit_no_dif->GetParError(1))));
        TString udsPurity_no_dif(std::to_string(my_3fit_no_dif->GetParameter(2)));
        TString udsPurity_no_dif_err(std::to_string(my_fit_no_dif->GetParError(2)));
        text_fit_no_dif_1->DrawLatex(2,0.5*Hdata_pt_rel_no_dif->GetMaximum(),"P_{b}= "+bPurity_no_dif+" #pm "+bPurity_no_dif_err);
        text_fit_no_dif_2->DrawLatex(2,0.4*Hdata_pt_rel_no_dif->GetMaximum(),"P_{c}= "+cPurity_no_dif+" #pm "+cPurity_no_dif_err);
        text_fit_no_dif_3->DrawLatex(2,0.3*Hdata_pt_rel_no_dif->GetMaximum(),"P_{q}= "+udsPurity_no_dif+" #pm "+udsPurity_no_dif_err);



  //21.06.19: data/fit ratio plots:
  //Using TRatioPlot for fit-data residual did not work well: 
  // 1) if I cut the range at 3.5 GeV (pT_rel) nan/Inf propagates to pad, because fitting function is null after 3.5, however the Histos are not...even if they are displayed up to 3.5
  // 2) cannot understand how it computes the residual/error...
  //Lets make a ratio plot graph from scratch: 1 Canvas, 2 pads with the Histo/fit plot and below the smaller (in vertical size) ratio TGraphError..

        TCanvas* ratio_data_2fit_canvas = new TCanvas("ratio_data_2fit_canvas","ratio_data_2fit_canvas");
	gStyle->SetFillStyle(0);
        ratio_data_2fit_canvas->Divide(1,2);
	ratio_data_2fit_canvas->cd(1);
	data_fit_pt_rel_no_dif->DrawClonePad();

        
	int nRatioBins = Hdata_pt_rel_no_dif->FindBin(3.5);
	float ratio_value[nRatioBins], ratio_error[nRatioBins], x_axis_value[nRatioBins], x_axis_width[nRatioBins];
	
        for(int ibin=1;ibin<=nRatioBins;++ibin){
        	float fit_value = Hdata_pt_rel_no_dif->GetFunction("my_fit_no_dif")->Eval(Hdata_pt_rel_no_dif->GetBinCenter(ibin));
        	float data_value = Hdata_pt_rel_no_dif->GetBinContent(ibin);
        	float data_error = Hdata_pt_rel_no_dif->GetBinError(ibin);
                ratio_value[ibin-1] = data_value/fit_value; 
        	ratio_error[ibin-1] = data_error/fit_value;          
		x_axis_value[ibin-1] = Hdata_pt_rel_no_dif->GetBinCenter(ibin);
		x_axis_width[ibin-1] = 0.5*Hdata_pt_rel_no_dif->GetBinWidth(ibin);
  	                                            }

	ratio_data_2fit_canvas->cd(2);
    TGraphErrors* ratio_2plot = new TGraphErrors(nRatioBins,x_axis_value,ratio_value,x_axis_width,ratio_error);
	ratio_2plot->SetMarkerStyle(20);
    ratio_2plot->SetTitle("");
	ratio_2plot->GetXaxis()->SetTitle("p_{T}^{rel} [GeV]");
	ratio_2plot->GetYaxis()->SetTitle("#frac{Data}{Fit}");
	ratio_2plot->GetYaxis()->CenterTitle(1);
	ratio_2plot->GetYaxis()->SetTitleSize(0.07);
	ratio_2plot->GetXaxis()->SetTitleSize(0.05);
	ratio_2plot->GetYaxis()->SetTitleOffset(0.5);
	ratio_2plot->GetYaxis()->SetRangeUser(0.9,1.1);
	ratio_2plot->GetXaxis()->SetRangeUser(0,3.5);
        ratio_data_2fit_canvas->cd(2);
	ratio_data_2fit_canvas->cd(2)->SetTickx();
	ratio_data_2fit_canvas->cd(2)->SetTicky();
	ratio_data_2fit_canvas->cd(2)->SetGridx();
	ratio_data_2fit_canvas->cd(2)->SetGridy();
	ratio_2plot->Draw("APZ");
        


        TCanvas* ratio_data_3fit_canvas = new TCanvas("ratio_data_3fit_canvas","ratio_data_3fit_canvas");
        ratio_data_3fit_canvas->Divide(1,2);
	ratio_data_3fit_canvas->cd(1);
        data_3fit_pt_rel_no_dif->DrawClonePad(); //draws the whole canvas with the 2 pads on the new upper pad.
        for(int ibin=1;ibin<=nRatioBins;++ibin){
        	float fit_value = Hdata_pt_rel_no_dif_clone->GetFunction("my_3fit_no_dif")->Eval(Hdata_pt_rel_no_dif_clone->GetBinCenter(ibin));
        	float data_value = Hdata_pt_rel_no_dif_clone->GetBinContent(ibin);
        	float data_error = Hdata_pt_rel_no_dif_clone->GetBinError(ibin);
                ratio_value[ibin-1] = data_value/fit_value; 
        	ratio_error[ibin-1] = data_error/fit_value;          
		x_axis_value[ibin-1] = Hdata_pt_rel_no_dif_clone->GetBinCenter(ibin);
		x_axis_width[ibin-1] = 0.5*Hdata_pt_rel_no_dif_clone->GetBinWidth(ibin);
  	                                            }

    ratio_data_3fit_canvas->cd(2);
    TGraphErrors* ratio_3plot = new TGraphErrors(nRatioBins,x_axis_value,ratio_value,x_axis_width,ratio_error);
	ratio_3plot->SetMarkerStyle(20);
        ratio_3plot->SetTitle("");
	ratio_3plot->GetXaxis()->SetTitle("p_{T}^{rel} [GeV]");
	//ratio_3plot->GetXaxis()->SetRangeUser(0.,x_axis_value[nRatioBins-1]+x_axis_width[nRatioBins-1]);
	ratio_3plot->GetYaxis()->SetTitle("#frac{Data}{Fit}");
	ratio_3plot->GetYaxis()->CenterTitle(1);
	ratio_3plot->GetYaxis()->SetTitleSize(0.07);
	ratio_3plot->GetXaxis()->SetTitleSize(0.05);
	ratio_3plot->GetYaxis()->SetTitleOffset(0.5);
	ratio_3plot->GetYaxis()->SetRangeUser(0.9,1.1);
	ratio_3plot->GetXaxis()->SetRangeUser(0,3.5);
        ratio_data_3fit_canvas->cd(2);
	ratio_data_3fit_canvas->cd(2)->SetTickx();
	ratio_data_3fit_canvas->cd(2)->SetTicky();
	ratio_data_3fit_canvas->cd(2)->SetGridx();
	ratio_data_3fit_canvas->cd(2)->SetGridy();
	ratio_3plot->Draw("APZ");
        
	
	TFile * pt_rel_fit_output = new TFile("new_directMINIAOD_pTrel_fit.root","recreate");
        input_parametrization_canvas->Write();
        data_fit_pt_rel_no_dif->Write();

}

//------------------------------------ OLD PULL TEST & FIT STABILITY TEST & DEBUGGING------------------------------------------------------------------
/********************************************************************************************************************************

void Pull(Int_t N_evt, Int_t N){

     Graphics(N_evt, N);

            double  data,pull,bias,max_bias,fb_t;
            vector<double> Bias;//The only reason for this is to store tha bias, find the maximum and then make the range of the Hbias....
                                // I could as well define a static matrix with N entries, but... let's learn some C++ dynamic vectors :P...
           // Hdata->Sumw2();//Save the errors of the histogram.

 //           int n=9;//how many steps of fb_t 0.1->0.9
 //           double Fb_t[9]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9}, Fb_e[n],eFb_e[9],eFb_t[9]={0.}, BIAS[n],eBIAS[9]={0.},PULL[n],ePULL[9]={0.},sigmaPULL[9]={0.},esigmaPULL[9]={0.},Ratio[9]={0.}, eRatio[9]={0.};//When I put n in Fb_t it thinks it is dynamic and cannot be initialized.    

//Study only fb {0.5->0.9} because according to the lepton-D* analysis b purity = 0.77
// Here B(x) & CL(x) fits
            int n=5;//how many steps of fb_t 0.5->0.9
            double Fb_t[5]={0.5,0.6,0.7,0.8,0.9}, Fb_e[5],eFb_e[5],eFb_t[5]={0.}, BIAS[5],eBIAS[5]={0.},PULL[5],ePULL[5]={0.},sigmaPULL[5]={0.},esigmaPULL[5]={0.},Ratio[5]={0.}, eRatio[5]={0.};//When I put n in Fb_t it thinks it is dynamic and cannot be initialized.    

           double n_b,n_cl,fb_e=0.,efb_e=0.,n_b_f=0.,n_cl_f=0.,en_cl_f=0.,en_b_f=0.,f_b=0.,fb_f=0.,efb_f=0.,N_b_mean,N_cl_mean;
           TRandom3 x;
           x.SetSeed(0);


        /*
              for(int ibin=0;ibin<Hdata_pt_rel->GetSize();++ibin){
              float res =  (Hdata_pt_rel->GetBinContent(ibin)- Hdata_pt_rel->GetFunction("ffitter_3")->Eval(Hdata_pt_rel->GetBinCenter(ibin)) )/Hdata_pt_rel->GetBinError(ibin);
              Hpt_rel_exp_fit_residual -> SetBinContent(ibin,res);
              Hpt_rel_exp_fit_residual -> SetBinError(ibin,1);
                                                                 }
        */
        //OMG_PLS->cd(2);
        //Hpt_rel_sim_vs_data->Draw("E1");

/*
TCanvas *TEST2 = new TCanvas("TEST2");
 for(int a=0;a<78000000;a++){
               data=B->GetRandom();
               Hdata_b->Fill(data);       
                                      }
           for(int a=0;a<10000000;a++){
              //  data=ft->GetRandom(); 
               //  Hdata->Fill(data); 
               data=C->GetRandom();
               Hdata_c->Fill(data);   }
           for(int a=0;a<12000000;a++){
             data= L->GetRandom();
             Hdata_l->Fill(data);
                             }    
      auto Hdata_temp = new TH1F( *Hdata_b);
Hdata_temp->Add(Hdata_c);
Hdata->Add(Hdata_temp,Hdata_l);         
Hdata->Scale(1/Hdata->Integral("width"));             
Hdata->Fit(ffitter_2);
*/

/*
ftest->FixParameter(2,B->GetParameter(0));
ftest->FixParameter(3,C->GetParameter(0));

ftest->FixParameter(4,B->GetParameter(1));
ftest->FixParameter(5,C->GetParameter(1));

ftest->FixParameter(6,B->GetParameter(2));
ftest->FixParameter(7,C->GetParameter(2));

ftest->FixParameter(8,B->GetParameter(3));
ftest->FixParameter(9,C->GetParameter(3));

ftest->FixParameter(10,B->GetParameter(4));
ftest->FixParameter(11,C->GetParameter(4));

ftest->FixParameter(12,B->GetParameter(5));
*/
/*
    TRandom3 r(0);//Different seed on every call.
    Hdata->Sumw2();
    for(int r=0;r<n;r++){

       fb_t=Fb_t[r];


              Hpull->Reset();
              Bias.clear();
 

             PULL[r]=0.;
             sigmaPULL[r]=0.;
             BIAS[r]=0.;
             Fb_e[r]=0.;
             eFb_e[r]=0.;

             bias=0.;
        N_b_mean=fb_t*N_evt;
        N_cl_mean=(1-fb_t)*N_evt;
          
         for(int iexp=0;iexp<N;iexp++){// N CMS experiments
          pull=0.;
         n_b=x.Poisson(N_b_mean);  
       //  Hn_b->Fill(n_b);
         n_cl=x.Poisson(N_cl_mean);
        //   n_cl=N_evt-n_b;
              Hdata->Reset();
              Hdata_b->Reset();
              Hdata_cl->Reset();
        //     fe->SetParameter(1,Fb_t[r]);

 
           for(int a=0;a<n_b;a++){
              //  data=ft->GetRandom(); 
               //  Hdata->Fill(data); 
               data=B->GetRandom();
               Hdata_b->Fill(data);       
                                      }
           for(int a=0;a<n_cl;a++){
              //  data=ft->GetRandom(); 
               //  Hdata->Fill(data); 
               data=CL->GetRandom();
               Hdata_cl->Fill(data);       
                                      }
         Hdata->Add(Hdata_cl,Hdata_b);
        // Hdata->Scale(1/Hdata->Integral("width"));

    //   Double_t shift = 0.5*Hpullb->GetBinWidth(1);
     //  Hpull->GetXaxis()->SetLimits(-4.+shift,4.+shift);

          //fe->SetParameters(10000,1000);

              
        //      Hdata->Scale(1/Hdata->Integral("width"));
              //Hdata->Fit(fe,"ME0Q");     
              Hdata->Fit(ffitter_2,"0");
            n_b_f = ffitter_2->GetParameter(0);    
            n_cl_f = ffitter_2->GetParameter(1);    
            en_b_f = ffitter_2->GetParError(0); 
            en_cl_f = ffitter_2->GetParError(1);

           // n_b_f=Hdata->GetFunction("fe")->GetParameter(0);    
          //  n_cl_f=Hdata->GetFunction("fe")->GetParameter(1);    
          //  en_b_f=Hdata->GetFunction("fe")->GetParError(0); 
           // en_cl_f=Hdata->GetFunction("fe")->GetParError(1);


              f_b=n_b/(n_cl+n_b);

            fb_f=(n_b_f)/(n_b_f+n_cl_f);
            efb_f=sqrt(    pow(n_cl_f,2)*pow(en_b_f,2)/(pow(n_b_f+n_cl_f,4)) + pow(n_b_f,2)*pow(en_cl_f,2)/(pow(n_b_f+n_cl_f,4))       );

          // Used for plotting the fb_e vs fb_t
              Fb_e[r]+=fb_f;
              eFb_e[r]+=pow(efb_f,2);
        

      //          pull= (fb_f-f_b)/efb_f;   
                pull=(n_b_f-n_b)/en_b_f;    
//                pull=(n_b_f-N_b_mean)/en_b_f;
                Hpull->Fill(pull);

              bias=(n_b_f-n_b)/(n_b);
              Bias.push_back(bias);//creating dynamically the capaciy of the vector, which will always be N...




             //For the Bias vs F_b(input) & Pull vs F_b(input)
             BIAS[r]+=bias;
             eBIAS[r]+=pow(en_b_f/(n_b),2);
 

     //      Ratio[r]+= fb(output)/fb(input)
             Ratio[r]+=n_b_f/(n_b);
             eRatio[r]+=pow(en_b_f,2);


     //         PULL[r]+=pull;                          
            //cout<<BIAS[r]<< endl;              
            //       cout << fe->GetParameter(1) <<endl;
  
                                                                                             }//end_for experiments loop
//   TCanvas *TEST2 = new TCanvas("TEST2");

               Fb_e[r]=Fb_e[r]/N;
               eFb_e[r]=sqrt(eFb_e[r])/N;

               Ratio[r]=Ratio[r]/N;
               eRatio[r]=sqrt(eRatio[r])/(N*n_b);

               BIAS[r]=BIAS[r]/N;
               eBIAS[r]=sqrt(eBIAS[r])/(N);
        
               //PULL[r]=PULL[r]/N;
               Hpull->Fit("gaus","M,E,0,Q");
               sigmaPULL[r]= Hpull->GetFunction("gaus")->GetParameter(2);
               esigmaPULL[r]=Hpull->GetFunction("gaus")->GetParError(2);
               PULL[r]=Hpull->GetFunction("gaus")->GetParameter(1);
               ePULL[r]=Hpull->GetFunction("gaus")->GetParError(1);

               

//cout << "pull, sigma= "<< PULL[r] <<" +/- " << ePULL[r]<<", " << sigmaPULL[r]<<"+/-" <<esigmaPULL[r] <<"\n" << "fb_e= "<< Fb_e[r] << " +/- " << eFb_e[r] <<", fb(in)=" << Fb_t[r] <<"\n" << endl;


                                                                                                }//enf f_b loop
              max_bias=Bias[0]; //Initialize, to find the biggest element
              for(int v=0; v<Bias.size();v++){       
                                                   
                                                  if( Bias[v]>max_bias ) max_bias=Bias[v];
     
                                                                                                                        }
     TH1F *Hbias = new TH1F("Hbias"," Bias of the fit ;#frac{f^{e}_{b}-f^{t}_{b}}{f^{t}_{b}}; entries/bin",40,-max_bias,max_bias);//Initialization, ranges will change
                 


              for(int v=0; v<Bias.size();v++)  Hbias->Fill(Bias[v]);                        

           TGraphErrors *Fit_vs_True = new TGraphErrors(n,Fb_t,Fb_e,eFb_t,eFb_e);
           Fit_vs_True->SetTitle("Output f_{b} vs Input f_{b}");
           Fit_vs_True->GetXaxis()->SetRangeUser(0.,1.);
           Fit_vs_True->GetXaxis()->SetTitle("f^{t}_{b}");
           Fit_vs_True->GetXaxis()->SetLabelSize(0.05);
           Fit_vs_True->GetXaxis()->SetTitleSize(0.07);
           Fit_vs_True->GetXaxis()->SetTitleOffset(0.5);
           Fit_vs_True->GetYaxis()->SetTitle("f^{e}_{b}");  
           Fit_vs_True->GetYaxis()->SetLabelSize(0.05);  
           Fit_vs_True->GetYaxis()->SetTitleSize(0.07);
           Fit_vs_True->GetYaxis()->SetTitleOffset(0.5);
           Fit_vs_True->SetMarkerStyle(8);
           Fit_vs_True->SetMarkerColor(kBlue);
           Fit_vs_True->SetMarkerSize(1.2);

           TGraphErrors *ratio = new TGraphErrors(n,Fb_t,Ratio,eFb_t,eRatio);
           ratio->SetTitle("Ratio of fb(output)/fb(input)");
           ratio->GetXaxis()->SetRangeUser(0.,1.);
           ratio->GetXaxis()->SetTitle("f^{t}_{b}");
           ratio->GetXaxis()->SetLabelSize(0.05);
           ratio->GetXaxis()->SetTitleSize(0.07);
           ratio->GetXaxis()->SetTitleOffset(0.5);
           ratio->GetYaxis()->SetTitle("#frac{f^{e}_{b}}{f^{t}_{b}}");  
           ratio->GetYaxis()->SetLabelSize(0.05);  
           ratio->GetYaxis()->SetTitleSize(0.07);
           ratio->GetYaxis()->SetTitleOffset(0.5);
           ratio->SetMarkerStyle(8);
           ratio->SetMarkerColor(kBlue);
           ratio->SetMarkerSize(1.2);

           TGraph *Bias_vs_True = new TGraphErrors(n,Fb_t,BIAS,eFb_t,eBIAS);
          // Bias_vs_True->SetTitleFont(13);
           Bias_vs_True->SetTitle("bias vs Input f_{b}");
           Bias_vs_True->GetXaxis()->SetTitle("f^{t}_{b}");
           Bias_vs_True->GetYaxis()->SetTitle("bias");
           Bias_vs_True->SetMarkerStyle(21);     
           Bias_vs_True->SetMarkerSize(1.2);      

           TGraphErrors *Pull_vs_True = new TGraphErrors(n,Fb_t,PULL,eFb_t,ePULL);
           Pull_vs_True->SetTitle("Pull vs Input f_{b}");
           Pull_vs_True->GetXaxis()->SetTitle("f^{t}_{b}");
           Pull_vs_True->GetYaxis()->SetTitle("Pull");
           Pull_vs_True->SetMarkerStyle(22);     
           Pull_vs_True->SetMarkerSize(1.2);   

          TGraphErrors *sigmaPULL_vs_True = new TGraphErrors (n,Fb_t,sigmaPULL,eFb_t,esigmaPULL); 

          sigmaPULL_vs_True ->SetTitle("#sigma of pull vs f_{b}");
          sigmaPULL_vs_True->GetXaxis()->SetTitle("f^{t}_{b}");
          sigmaPULL_vs_True->GetXaxis()->SetLabelSize(0.05);
          sigmaPULL_vs_True->GetXaxis()->SetTitleSize(0.07);
          sigmaPULL_vs_True->GetXaxis()->SetTitleOffset(0.5);

          sigmaPULL_vs_True->GetYaxis()->SetTitle("#sigma");
          sigmaPULL_vs_True->GetYaxis()->SetLabelSize(0.05);  
          sigmaPULL_vs_True->GetYaxis()->SetTitleSize(0.07);
          sigmaPULL_vs_True->GetYaxis()->SetTitleOffset(0.5);


           sigmaPULL_vs_True->SetMarkerStyle(8);
          // Fit_vs_True->SetMarkerColor(kBlue);
           sigmaPULL_vs_True->SetMarkerSize(1.2);          


// Examples of fitting and bias--------------
       TCanvas *fit_results= new TCanvas("Fit Results");
       fit_results->Divide(1,2);

       fit_results->cd(1);
       Hdata->Fit(ffitter_2,"Q");

       fit_results->cd(2);
       Hpull->SetFillStyle(3003);
       Hpull->SetFillColor(kBlue);
       Hpull->Fit("gaus","Q");

       TCanvas *fit_bias= new TCanvas("Bias of Fit");	
       Hbias->SetFillStyle(3005);
       Hbias->SetFillColor(kBlue);
       Hbias->Fit("gaus","L,E,Q");

       fit_results->Print("Fit_Results_Example.pdf");
//---------------------------------------------

       TCanvas *in_out1= new TCanvas("Input fb vs Output fb 1");
       in_out1->Divide(1,2);
       in_out1->cd(1);
       gPad->SetGrid();
 
       Fit_vs_True->Draw("AP");
       Fit_vs_True->Fit("pol1","Q");
       Fit_vs_True->GetFunction("pol1")->SetLineStyle(2);

       in_out1->cd(2);
       gPad->SetGrid();
       ratio->Draw("AP");

       in_out1->Print("fb(in) vs fb(out) & Ratios.pdf");

       TCanvas *in_out3 = new TCanvas("Bias of the fit -vs- fb(input)");
       gPad->SetGrid();
       Bias_vs_True->Draw("AP"); 

       in_out3->Print("Bias vs fb(in).pdf"); 

       TCanvas *in_out2= new TCanvas("Mean and Sigma of pull -vs- fb(input)"); 
       in_out2->Divide(1,2);
       in_out2->cd(1);
       gPad->SetGrid();
       Pull_vs_True->Draw("AP");

      in_out2->cd(2);
      gPad->SetGrid();
      sigmaPULL_vs_True->Draw("AP");
    
      in_out2->Print("Pull vs fb(in).pdf");

      test3->Print("~/Thesis_Exercises/Inclusive_Beauty_Study/fit_results/Input_ptrel.tex"); 

}

********************************************************************************************************************************/
