#define gem_analysis_cxx
#include "gem_analysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
void gem_analysis::Loop()
{
//   In a ROOT session, you can do:
//      root> .L gem_analysis.C
//      root> gem_analysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	//TFile *file1 = new TFile("run_338702.root","RECREATE");
	
	//output_file = TFile::Open(fname,"RECREATE");
        output_file->cd();
	TH1D *hmatched = new TH1D("hmatched", "Matched Hits", 100, -250, 250);
	TH1D *htotal = new TH1D("htotal", "Total Hits", 100, -250, 250);
	
	TH1D *hmatched_x = new TH1D("hmatched_x", "mathed_pos_x", 500, -250, 250);
	TH1D *hmatched_y = new TH1D("hmatched_y", "mathed_pos_y", 500, -250, 250);
	TH1D *hmatched_z = new TH1D("hmatched_z", "mathed_pos_z", 300, -600, 600);
	TH1D *hmatched_r = new TH1D("hmatched_r", "mathed_pos_r", 200,  100, 300);
  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
	   
//	std::cout<<"event number "<<event_eventNumber<<std::endl;
//	std::cout<<"run number "<<event_runNumber<<std::endl;

//	std::cout<<"====END LOOP--"<<std::endl;
//	std::cout<<" nrechits "<<gemRecHit_nRecHits<<std::endl;
//	if(gemSegment_nSegments != 0){
//	std::cout<<" nsegments "<<gemSegment_nSegments<<std::endl;
//		}
       if(mu_propagatedGlb_x->size() !=0 && gemRecHit_g_x->size() != 0)
{
	std::vector<float> matched;
        std::vector<float> matched_pos_x;
	std::vector<float> matched_pos_y; 
	std::vector<float> matched_pos_z;
	std::vector<float> matched_pos_r;

	matched_pos_x.clear();
	matched_pos_y.clear();
	matched_pos_z.clear();
	matched_pos_r.clear();
	matched.clear();
	
        //double matched = 0.;
	for(int i =0; i< mu_propagatedGlb_x->size(); i++){
 	//std::cout<<"segment x "<<mu_propagatedGlb_x->at(i)<<'\t'<<" rechit x "<<gemRecHit_g_x->at(i)<<std::endl;	
	if(gemRecHit_g_z->at(i) < 0){
	if(std::fabs(mu_propagatedGlb_x->at(i) - gemRecHit_g_x->at(i)) < 0.5){ 		//in cm
//	std::cout<<"segment x "<<mu_propagatedGlb_x->at(i)<<'\t'<<" rechit x "<<gemRecHit_g_x->at(i)<<std::endl;
	
	matched.push_back(mu_propagatedGlb_x->at(i));

	matched_pos_x.push_back(mu_propagatedGlb_x->at(i));
	matched_pos_y.push_back(mu_propagatedGlb_y->at(i));
	matched_pos_z.push_back(mu_propagatedGlb_z->at(i));
	matched_pos_r.push_back(mu_propagatedGlb_r->at(i));
	//std::cout<<"matched "<<matched.size()<<std::endl;
	}
//	if(matched.size() != 0){
//	std::cout<<"matched "<<matched.at(i)<<std::endl;
	//	hmatched->Fill(matched.at(i));
//	}//matched++;

/*	if(matched!=0){
	double total_seg = gemSegment_nSegments;
//	std::cout<<"matched hits "<<matched<<'\t'<<total_seg<<std::endl;
 	double efficiency = matched/total_seg;
	//std::cout<<std::setprecision(5)<<" eff "<<efficiency<<std::endl;
        h1->Fill(efficiency);
	h1->GetXaxis()->SetTitle("efficiency");
	}*/
	htotal->Fill(mu_propagatedGlb_x->at(i));
}
}
for(int i=0; i < matched.size(); i++){
	//std::cout<<"matched "<<matched.size()<<std::endl;
	hmatched->Fill(matched.at(i));

	hmatched_x->Fill(matched_pos_x.at(i));
	hmatched_y->Fill(matched_pos_y.at(i));
	hmatched_z->Fill(matched_pos_z.at(i));
	hmatched_r->Fill(matched_pos_r.at(i));
}

}
}
TH1D *h1 = (TH1D*)hmatched->Clone("Efficiency");
TH1D *h2 = (TH1D*)htotal->Clone("h2");
h1->Divide(h2);
h1->Draw("ep");
h1->SetTitle("Efficiency");
h1->GetXaxis()->SetTitle("pos x");
h1->GetYaxis()->SetTitle("Efficiency");
h1->SetStats(kFALSE);
h1->SetMarkerStyle(22);
h1->SetMarkerSize(1.0);
h1->SetMarkerColor(kRed);

//file1->cd();
output_file->cd();
htotal->Write();
hmatched->Write();
hmatched_x->Write();
hmatched_y->Write();
hmatched_z->Write();
hmatched_r->Write();
h1->Write();
//file1->Close();
output_file->Close();
}
