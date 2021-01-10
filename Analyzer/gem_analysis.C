#define gem_analysis_cxx
#include "gem_analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
void gem_analysis::Loop()
{
	output_file->cd();
	int m=3;
	//GE+1/1
	TH2D** h_2Dhlayer1plusZ = new TH2D*[m];
	TH2D** h_2Dhlayer2plusZ = new TH2D*[m];
	TH1D** h_1Dhlayer1plusZ = new TH1D*[m];
	TH1D** h_1Dhlayer2plusZ = new TH1D*[m];
	for(int i=0; i<m; i++){
 	TString name[3]={"Propagated hits from any ME station","Propagated hits with ME1/1 station", "Matched hits"};
	std::string names[3] ={"prop_", "prop_withME11_", "matched_"};
	char hist_name[256];
	sprintf (hist_name, "%s%d_pos",names[i].c_str(),i);
	h_2Dhlayer1plusZ[i] = new TH2D(TString::Format("h_%s_2DLY1",hist_name), "Layer1 "+name[i] ,200, -300., 300., 200, -300., 300.);
	h_2Dhlayer2plusZ[i] = new TH2D(TString::Format("h_%s_2DLY2",hist_name), "Layer2 "+name[i] ,200, -300., 300., 200, -300., 300.);	
	h_1Dhlayer1plusZ[i] = new TH1D(TString::Format("h_%s_1DLY1",hist_name), "Layer1 "+name[i] ,36,  0., 36.);	
	h_1Dhlayer2plusZ[i] = new TH1D(TString::Format("h_%s_1DLY2",hist_name), "Layer2 "+name[i] ,36,  0., 36.);

	h_2Dhlayer1plusZ[i]->GetXaxis()->SetTitle("Global X");
	h_2Dhlayer1plusZ[i]->GetYaxis()->SetTitle("Global Y");
	h_1Dhlayer1plusZ[i]->GetXaxis()->SetTitle("Superchamber LY1");
	h_1Dhlayer1plusZ[i]->GetYaxis()->SetTitle("Events");
	h_2Dhlayer1plusZ[i]->SetOption("colz"); 
	h_2Dhlayer2plusZ[i]->GetXaxis()->SetTitle("Global X");
        h_2Dhlayer2plusZ[i]->GetYaxis()->SetTitle("Global Y");
        h_1Dhlayer2plusZ[i]->GetXaxis()->SetTitle("Superchamber LY2");
        h_1Dhlayer2plusZ[i]->GetYaxis()->SetTitle("Events");
	h_2Dhlayer2plusZ[i]->SetOption("colz");
	h_1Dhlayer1plusZ[i]->SetMarkerStyle(20);
	h_1Dhlayer1plusZ[i]->SetMarkerColor(kBlack);
	h_1Dhlayer1plusZ[i]->SetMarkerSize(1.0);
	h_1Dhlayer1plusZ[i]->SetOption("P");	
	h_1Dhlayer2plusZ[i]->SetMarkerStyle(20);
        h_1Dhlayer2plusZ[i]->SetMarkerColor(kBlack);
        h_1Dhlayer2plusZ[i]->SetMarkerSize(1.0);
	h_1Dhlayer2plusZ[i]->SetOption("P");
	}
	//GE-1/1
	TH2D** h_2Dhlayer1minusZ = new TH2D*[m];
        TH2D** h_2Dhlayer2minusZ = new TH2D*[m];
        TH1D** h_1Dhlayer1minusZ = new TH1D*[m];
        TH1D** h_1Dhlayer2minusZ = new TH1D*[m];
        for(int i=0; i<m; i++){
        TString name[3]={"Propagated hits from any ME station","Propagated hits with ME1/1 station", "Matched hits"};
	std::string names[3] ={"prop_", "prop_withME11_", "matched_"};
	char hist_name[256];
        sprintf (hist_name, "%s%d_neg",names[i].c_str(),i);
	h_2Dhlayer1minusZ[i] = new TH2D(TString::Format("h_%s_2DLY1",hist_name), "Layer1 "+name[i] ,200, -300., 300., 200, -300., 300.);
        h_2Dhlayer2minusZ[i] = new TH2D(TString::Format("h_%s_2DLY2",hist_name), "Layer2 "+name[i] ,200, -300., 300., 200, -300., 300.);
        h_1Dhlayer1minusZ[i] = new TH1D(TString::Format("h_%s_1DLY1",hist_name), "Layer1 "+name[i] ,36,  0., 36.);
        h_1Dhlayer2minusZ[i] = new TH1D(TString::Format("h_%s_1DLY2",hist_name), "Layer2 "+name[i] ,36,  0., 36.);
        
        h_2Dhlayer1minusZ[i]->GetXaxis()->SetTitle("Global X");
        h_2Dhlayer1minusZ[i]->GetYaxis()->SetTitle("Global Y");
        h_1Dhlayer1minusZ[i]->GetXaxis()->SetTitle("Superchamber LY1");
        h_1Dhlayer1minusZ[i]->GetYaxis()->SetTitle("Events");
        h_2Dhlayer1minusZ[i]->SetOption("colz"); 
        h_2Dhlayer2minusZ[i]->GetXaxis()->SetTitle("Global X");
        h_2Dhlayer2minusZ[i]->GetYaxis()->SetTitle("Global Y");
        h_1Dhlayer2minusZ[i]->GetXaxis()->SetTitle("Superchamber LY2");
        h_1Dhlayer2minusZ[i]->GetYaxis()->SetTitle("Events");
        h_2Dhlayer2minusZ[i]->SetOption("colz");
        h_1Dhlayer1minusZ[i]->SetMarkerStyle(20);
        h_1Dhlayer1minusZ[i]->SetMarkerColor(kBlack);
        h_1Dhlayer1minusZ[i]->SetMarkerSize(1.0);
        h_1Dhlayer1minusZ[i]->SetOption("P");    
        h_1Dhlayer2minusZ[i]->SetMarkerStyle(20);
        h_1Dhlayer2minusZ[i]->SetMarkerColor(kBlack);
        h_1Dhlayer2minusZ[i]->SetMarkerSize(1.0);
        h_1Dhlayer2minusZ[i]->SetOption("P");
        }


   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

//Checking all the propagted muons from ME stations to GEM
      for(std::size_t i=0; i< mu_propagatedGlb_z->size(); i++){
		if((mu_propagated_region->at(i) > 0) && (mu_propagated_layer->at(i) ==1)){   //GE+1/1 Layer1 no ME1/1 selection
		
		h_2Dhlayer1plusZ[0]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
		h_1Dhlayer1plusZ[0]->Fill(mu_propagated_chamber->at(i));
		if(mu_isME11->at(i)){ //with ME1/1 selection
		h_2Dhlayer1plusZ[1]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));	
		h_1Dhlayer1plusZ[1]->Fill(mu_propagated_chamber->at(i));

		bool matched = false;	
		for(std::size_t j =0; j<gemRecHit_g_z->size(); j++){	
		//matching condition
		float condition = sqrt(std::pow((std::fabs(mu_propagatedGlb_x->at(i) - gemRecHit_g_x->at(j))),2) + std::pow((std::fabs(mu_propagatedGlb_y->at(i) - gemRecHit_g_y->at(j))),2));
		if(condition < 10.){ //in cm
		matched = true;
		}
		}//end rechit loop
		if(matched){
		h_2Dhlayer1plusZ[2]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer1plusZ[2]->Fill(mu_propagated_chamber->at(i));
		}//matched condition
		}//ME1/1 condition ends
		}
		else if((mu_propagated_region->at(i) > 0) && (mu_propagated_layer->at(i) ==2)){   //GE+1/1 Layer2 no ME1/1 selection
		
		h_2Dhlayer2plusZ[0]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer2plusZ[0]->Fill(mu_propagated_chamber->at(i));
                if(mu_isME11->at(i)){ //with ME1/1 selection
		h_2Dhlayer2plusZ[1]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer2plusZ[1]->Fill(mu_propagated_chamber->at(i));
              
		bool matched = false; 
		for(std::size_t j =0; j<gemRecHit_g_z->size(); j++){ 
		//matching condition
		float condition = sqrt(std::pow((std::fabs(mu_propagatedGlb_x->at(i) - gemRecHit_g_x->at(j))),2) + std::pow((std::fabs(mu_propagatedGlb_y->at(i) - gemRecHit_g_y->at(j))),2));
		if(condition < 10.){ //in cm
		matched = true;
		                    }
				    } //end rechit loop
		if(matched){
		h_2Dhlayer2plusZ[2]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer2plusZ[2]->Fill(mu_propagated_chamber->at(i));
				    } //matched condition

			            }//ME1/1 condition ends
				    }
		else if((mu_propagated_region->at(i) < 0) && (mu_propagated_layer->at(i) ==1)){   //GE-1/1 Layer1 no ME1/1 selection
		h_2Dhlayer1minusZ[0]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer1minusZ[0]->Fill(mu_propagated_chamber->at(i));
                if(mu_isME11->at(i)){ //with ME1/1 selection
		h_2Dhlayer1minusZ[1]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer1minusZ[1]->Fill(mu_propagated_chamber->at(i));
               
		bool matched = false; 
		for(std::size_t j =0; j<gemRecHit_g_z->size(); j++){	
                //matching condition
		float condition = sqrt(std::pow((std::fabs(mu_propagatedGlb_x->at(i) - gemRecHit_g_x->at(j))),2) + std::pow((std::fabs(mu_propagatedGlb_y->at(i) - gemRecHit_g_y->at(j))),2));
                if(condition < 10.){ //in cm
    		matched = true;
	            }
		    }//end rechit loop
		if(matched){
		h_2Dhlayer1minusZ[2]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer1minusZ[2]->Fill(mu_propagated_chamber->at(i));
		}//matched condition
		}//ME1/1 condition ends
		}
                else if((mu_propagated_region->at(i) < 0) && (mu_propagated_layer->at(i) ==2)){   //GE-1/1 Layer2 no ME1/1 selection
		h_2Dhlayer2minusZ[0]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer2minusZ[0]->Fill(mu_propagated_chamber->at(i));
                if(mu_isME11->at(i)){ //with ME1/1 selection
		h_2Dhlayer2minusZ[1]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
                h_1Dhlayer2minusZ[1]->Fill(mu_propagated_chamber->at(i));
              
		bool matched = false; 
		for(std::size_t j =0; j<gemRecHit_g_z->size(); j++){ 
                //matching condition
		float condition = sqrt(std::pow((std::fabs(mu_propagatedGlb_x->at(i) - gemRecHit_g_x->at(j))),2) + std::pow((std::fabs(mu_propagatedGlb_y->at(i) - gemRecHit_g_y->at(j))),2));
		if(condition < 10.){ //in cm
		matched = true;
                                    }
				    } //end rechit loop
                 if(matched){
                 h_2Dhlayer2minusZ[2]->Fill(mu_propagatedGlb_x->at(i),mu_propagatedGlb_y->at(i));
		 h_1Dhlayer2minusZ[2]->Fill(mu_propagated_chamber->at(i));
			}// matched condition

				    }//ME1/1 condition ends
		    		    }
		else{
		std::cout<< " no matching rechit found"<<std::endl;}
					
				    }	
				    } // major for loop ends
		//Now do efficiency
		//Layer 1 +z
		TH2D *hist_2Dmatchedlayer1plusZ = (TH2D*)h_2Dhlayer1plusZ[2]->Clone("hist_2Dmatchedlayer1plusZ");
                TH2D *hist_2Dpropagatedlayer1plusZ = (TH2D*)h_2Dhlayer1plusZ[1]->Clone();
		hist_2Dmatchedlayer1plusZ->Divide(hist_2Dpropagatedlayer1plusZ);
                 
                TH1D *hist_1Dmatchedlayer1plusZ = ( TH1D*)h_1Dhlayer1plusZ[2]->Clone("hist_1Dmatchedlayer1plusZ");
                hist_1Dmatchedlayer1plusZ->Divide(h_1Dhlayer1plusZ[1]);
               
		//Layer 2 +z
		TH2D *hist_2Dmatchedlayer2plusZ = (TH2D*)h_2Dhlayer2plusZ[2]->Clone("hist_2Dmatchedlayer2plusZ");
                hist_2Dmatchedlayer2plusZ->Divide(h_2Dhlayer2plusZ[1]);

                TH1D *hist_1Dmatchedlayer2plusZ = ( TH1D*)h_1Dhlayer2plusZ[2]->Clone("hist_1Dmatchedlayer2plusZ");
                hist_1Dmatchedlayer2plusZ->Divide(h_1Dhlayer2plusZ[1]);

 
		hist_2Dmatchedlayer1plusZ->SetOption("colz");
		hist_2Dmatchedlayer1plusZ->SetTitle("Efficiency for +z Layer1");
		hist_2Dmatchedlayer1plusZ->GetXaxis()->SetTitle("Global X");
		hist_2Dmatchedlayer1plusZ->GetYaxis()->SetTitle("Global Y");
		hist_2Dmatchedlayer1plusZ->SetStats(kFALSE);

		hist_1Dmatchedlayer1plusZ->SetOption("P");
		hist_1Dmatchedlayer1plusZ->SetTitle("Efficiency for +z Layer1");
		hist_1Dmatchedlayer1plusZ->GetXaxis()->SetTitle("Superchamber LY1");	                
		hist_1Dmatchedlayer1plusZ->GetYaxis()->SetTitle("Events");
		hist_1Dmatchedlayer1plusZ->SetStats(kFALSE);
	
		hist_2Dmatchedlayer2plusZ->SetOption("colz");
                hist_2Dmatchedlayer2plusZ->SetTitle("Efficiency for +z Layer2");
                hist_2Dmatchedlayer2plusZ->GetXaxis()->SetTitle("Global X");
                hist_2Dmatchedlayer2plusZ->GetYaxis()->SetTitle("Global Y");
		hist_2Dmatchedlayer2plusZ->SetStats(kFALSE);

                hist_1Dmatchedlayer2plusZ->SetOption("P");
                hist_1Dmatchedlayer2plusZ->SetTitle("Efficiency for +z Layer2");
                hist_1Dmatchedlayer2plusZ->GetXaxis()->SetTitle("Superchamber LY2");
                hist_1Dmatchedlayer2plusZ->GetYaxis()->SetTitle("Events");
		hist_1Dmatchedlayer2plusZ->SetStats(kFALSE);	

		//Layer 1 -z
		TH2D *hist_2Dmatchedlayer1minusZ = (TH2D*)h_2Dhlayer1minusZ[2]->Clone("hist_2Dmatchedlayer1minusZ");
                TH2D *hist_2Dpropagatedlayer1minusZ = (TH2D*)h_2Dhlayer1minusZ[1]->Clone();
                hist_2Dmatchedlayer1minusZ->Divide(hist_2Dpropagatedlayer1minusZ);

                TH1D *hist_1Dmatchedlayer1minusZ = ( TH1D*)h_1Dhlayer1minusZ[2]->Clone("hist_1Dmatchedlayer1minusZ");
                hist_1Dmatchedlayer1minusZ->Divide(h_1Dhlayer1minusZ[1]);

		//Layer 2 -z
		TH2D *hist_2Dmatchedlayer2minusZ = (TH2D*)h_2Dhlayer2minusZ[2]->Clone("hist_2Dmatchedlayer2minusZ");
                hist_2Dmatchedlayer2minusZ->Divide(h_2Dhlayer2minusZ[1]);

                TH1D *hist_1Dmatchedlayer2minusZ = ( TH1D*)h_1Dhlayer2minusZ[2]->Clone("hist_1Dmatchedlayer2minusZ");
                hist_1Dmatchedlayer2minusZ->Divide(h_1Dhlayer2minusZ[1]);


                hist_2Dmatchedlayer1minusZ->SetOption("colz");
                hist_2Dmatchedlayer1minusZ->SetTitle("Efficiency for -z Layer1");
                hist_2Dmatchedlayer1minusZ->GetXaxis()->SetTitle("Global X");
                hist_2Dmatchedlayer1minusZ->GetYaxis()->SetTitle("Global Y");
                hist_2Dmatchedlayer1minusZ->SetStats(kFALSE);

                hist_1Dmatchedlayer1minusZ->SetOption("P");
                hist_1Dmatchedlayer1minusZ->SetTitle("Efficiency for -z Layer1");
                hist_1Dmatchedlayer1minusZ->GetXaxis()->SetTitle("Superchamber LY1");
                hist_1Dmatchedlayer1minusZ->GetYaxis()->SetTitle("Events");
                hist_1Dmatchedlayer1minusZ->SetStats(kFALSE);

                hist_2Dmatchedlayer2minusZ->SetOption("colz");
                hist_2Dmatchedlayer2minusZ->SetTitle("Efficiency for -z Layer2");
                hist_2Dmatchedlayer2minusZ->GetXaxis()->SetTitle("Global X");
                hist_2Dmatchedlayer2minusZ->GetYaxis()->SetTitle("Global Y");
                hist_2Dmatchedlayer2minusZ->SetStats(kFALSE);

                hist_1Dmatchedlayer2minusZ->SetOption("P");
                hist_1Dmatchedlayer2minusZ->SetTitle("Efficiency for -z Layer2");
                hist_1Dmatchedlayer2minusZ->GetXaxis()->SetTitle("Superchamber LY2");
                hist_1Dmatchedlayer2minusZ->GetYaxis()->SetTitle("Events");
                hist_1Dmatchedlayer2minusZ->SetStats(kFALSE);

	
				output_file->cd();
				TDirectory* d1_output = output_file->mkdir("GE_positiveZ");
                                d1_output->cd();
				for(int i=0;i<3; i++){
				h_2Dhlayer1plusZ[i]->Write();
				h_2Dhlayer2plusZ[i]->Write();
				h_1Dhlayer1plusZ[i]->Write();
                                h_1Dhlayer2plusZ[i]->Write();
				}
				TDirectory* d2_output = output_file->mkdir("efficiency_GE_positiveZ");
        			d2_output->cd();
				hist_2Dmatchedlayer1plusZ->Write();
				hist_1Dmatchedlayer1plusZ->Write();
				hist_2Dmatchedlayer2plusZ->Write();
				hist_1Dmatchedlayer2plusZ->Write();					
				
				TDirectory* d3_output = output_file->mkdir("GE_negativeZ");
                                d3_output->cd();
                                for(int i=0;i<3; i++){
                                h_2Dhlayer1minusZ[i]->Write();
                                h_2Dhlayer2minusZ[i]->Write();
                                h_1Dhlayer1minusZ[i]->Write();
                                h_1Dhlayer2minusZ[i]->Write();
                                }
                                TDirectory* d4_output = output_file->mkdir("efficiency_GE_negativeZ");
                                d4_output->cd();
                                hist_2Dmatchedlayer1minusZ->Write();
                                hist_1Dmatchedlayer1minusZ->Write();
                                hist_2Dmatchedlayer2minusZ->Write();
                                hist_1Dmatchedlayer2minusZ->Write();

				output_file->Close();
					}
