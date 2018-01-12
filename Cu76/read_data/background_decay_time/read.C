#include "Riostream.h"
#include "TGText.h"
#include "TString.h"
#include "TMath.h"

void read()
{

    TChain *t = (TChain *) new TChain("decay");
    char name[1024];
	Int_t n;
    n=1;
	for(Int_t cont_files=10;cont_files<58;cont_files++){//from 10 to 57
		sprintf(name, "/home/line/Ni74/riken_data/decay_new_ni74_77_%0.1d%0.3d.root",n,cont_files);
		ifstream ifile(name);
		if (ifile){
			t->Add(name);
			std::cout << "Added file " << name << " to chain." << std::endl;
		}
	}//*/
    for(Int_t cont_files=61;cont_files<171;cont_files++){//from 61 to 170
		sprintf(name, "/home/line/Ni74/riken_data/decay_new_ni74_77_%0.1d%0.3d.root",n,cont_files);
		ifstream ifile(name);
		if (ifile){
			t->Add(name);
			std::cout << "Added file " << name << " to chain." << std::endl;
		}
	}//*/
	n=5;
	for(Int_t cont_files=0;cont_files<139;cont_files++){//from 0 to 138
		sprintf(name, "/home/line/Ni74/riken_data/decay_new_ni74_77_%0.1d%0.3d.root",n,cont_files);
		ifstream ifile(name);
		if (ifile){
			t->Add(name);
			std::cout << "Added file " << name << " to chain." << std::endl;
		}
	}//*/
    t->SetMakeClass(1);

    const Int_t kMaxbg=33;
    Int_t z;
    Int_t Mass;
    Int_t flagall;
    Int_t bg_;
    Double_t beta711;
    Long64_t bg_t[kMaxbg];
    Int_t bg_deltaz[kMaxbg];
    Double_t bg_deltaxy[kMaxbg];

    TBranch *b_z;
    TBranch *b_Mass;
    TBranch *b_flagall;
    TBranch *b_beta711;
    TBranch *b_bg_;
    TBranch *b_bg_t;
    TBranch *b_bg_deltaz;
    TBranch *b_bg_deltaxy;

    t->SetBranchAddress("z", &z, &b_z);
    t->SetBranchAddress("Mass", &Mass, &b_Mass);
    t->SetBranchAddress("flagall", &flagall, &b_flagall);
    t->SetBranchAddress("beta711", &beta711, &b_beta711);
    t->SetBranchAddress("bg", &bg_, &b_bg_);
    t->SetBranchAddress("bg.t", bg_t, &b_bg_t);
    t->SetBranchAddress("bg.deltaz", bg_deltaz, &b_bg_deltaz);
    t->SetBranchAddress("bg.deltaxy", bg_deltaxy, &b_bg_deltaxy);

    t->SetBranchStatus("*", 0);
    t->SetBranchStatus("z*", 1);
    t->SetBranchStatus("Mass*", 1);
    t->SetBranchStatus("flagall*", 1);
    t->SetBranchStatus("beta711*", 1);
    t->SetBranchStatus("bg*", 1);
    t->SetBranchStatus("bg.t*", 1);
    t->SetBranchStatus("bg.deltaz*", 1);
    t->SetBranchStatus("bg.deltaxy*", 1);

    TH1F *h_z = new TH1F("h_z","DSSD#",8,0,8);
    TH1F *h_Mass = new TH1F("h_Mass","Mass",6,72,78);
    TH1F *h_beta711_1 = new TH1F("h_beta711_1","Beta F7-F11 DSSD#1",100,0.642,0.647);
    TH1F *h_beta711_2 = new TH1F("h_beta711_2","Beta F7-F11 DSSD#2",100,0.642,0.647);
    TH1F *h_beta711_3 = new TH1F("h_beta711_3","Beta F7-F11 DSSD#3",100,0.642,0.647);
    TH1F *h_beta711_4 = new TH1F("h_beta711_4","Beta F7-F11 DSSD#4",100,0.642,0.647);
    TH1F *h_beta711_5 = new TH1F("h_beta711_5","Beta F7-F11 DSSD#5",100,0.642,0.647);
    TH1F *h_beta711_6 = new TH1F("h_beta711_6","Beta F7-F11 DSSD#6",100,0.642,0.647);
    TH1F *h_beta711_7 = new TH1F("h_beta711_7","Beta F7-F11 DSSD#7",100,0.642,0.647);
    TH1F *h_beta711_8 = new TH1F("h_beta711_8","Beta F7-F11 DSSD#8",100,0.642,0.647);
    TH1F *h_bg_t = new TH1F("h_bg_t","Decay time",5000,0,5.0e+08);
    TH1F *h_bg_deltaz = new TH1F("h_bg_deltaz","Delta z",2,0,2);
    TH1F *h_bg_deltaxy = new TH1F("h_bg_deltaxy","Delta xy",10000,0.0,12.80);

    Long64_t nrow = (Long64_t) t->GetEntries();

    for (Long64_t i=0; i<nrow; i++) {

        //initialization
        for (Int_t ii=0; ii<kMaxbg; ii++) {
            bg_t[ii]=-1;
            bg_deltaz[ii]=-1;
            bg_deltaxy[ii]=13;
        }//*/

        t->GetEntry(i);

        for (Int_t j=0; j<kMaxbg; j++) {
            if (flagall==1&&Mass==76&&((z==5)||(z==6))) {
                if (bg_t[j]>0&&bg_deltaz[j]==0&&bg_deltaxy[j]<2){
                    h_bg_t->Fill(bg_t[j]);
                }
            }
        }

    }


    TCanvas *c_bg_t = new TCanvas("c_bg_t","Decay time",1);
    h_bg_t->Draw();//*/

    TFile *outputFile = new TFile("76Cu_bg_t.root","RECREATE");
    outputFile->WriteObject(h_bg_t, "h_bg_t");
	outputFile->Close();
}
