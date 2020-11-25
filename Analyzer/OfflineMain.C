#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TProfile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TString.h>
#include <TTree.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gem_analysis.C"

int main(Int_t argc, Char_t *argv[]) {

  if (argc<2) {
	std::cerr << "Please give 2 arguments \n"
              << "InputFileName" << "\n"
              << "outputFileName" << "\n"
              << std::endl;
    return -1;
}

const char *inputFileList   = argv[1];
const char *outFileName     = argv[2];

gem_analysis* tree=
    new gem_analysis(inputFileList, outFileName);
   
   tree->Loop();
   
   return 0;
}

