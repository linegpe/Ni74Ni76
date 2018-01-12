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

    const Int_t kMaxbeta=33;
    Int_t z;
    Int_t Mass;
    Int_t flagall;
    Int_t beta_;
    Double_t beta711;
    Long64_t beta_t[kMaxbeta];
    Int_t beta_deltaz[kMaxbeta];
    Double_t beta_deltaxy[kMaxbeta];

    TBranch *b_z;
    TBranch *b_Mass;
    TBranch *b_flagall;
    TBranch *b_beta711;
    TBranch *b_beta_;
    TBranch *b_beta_t;
    TBranch *b_beta_deltaz;
    TBranch *b_beta_deltaxy;

    t->SetBranchAddress("z", &z, &b_z);
    t->SetBranchAddress("Mass", &Mass, &b_Mass);
    t->SetBranchAddress("flagall", &flagall, &b_flagall);
    t->SetBranchAddress("beta711", &beta711, &b_beta711);
    t->SetBranchAddress("beta", &beta_, &b_beta_);
    t->SetBranchAddress("beta.t", beta_t, &b_beta_t);
    t->SetBranchAddress("beta.deltaz", beta_deltaz, &b_beta_deltaz);
    t->SetBranchAddress("beta.deltaxy", beta_deltaxy, &b_beta_deltaxy);

    t->SetBranchStatus("*", 0);
    t->SetBranchStatus("z*", 1);
    t->SetBranchStatus("Mass*", 1);
    t->SetBranchStatus("flagall*", 1);
    t->SetBranchStatus("beta711*", 1);
    t->SetBranchStatus("beta*", 1);
    t->SetBranchStatus("beta.t*", 1);
    t->SetBranchStatus("beta.deltaz*", 1);
    t->SetBranchStatus("beta.deltaxy*", 1);

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
    TH1F *h_beta_t = new TH1F("h_beta_t","Decay time",5000,0,5.0e+08);
    TH1F *h_beta_deltaz = new TH1F("h_beta_deltaz","Delta z",2,0,2);
    TH1F *h_beta_deltaxy = new TH1F("h_beta_deltaxy","Delta xy",10000,0.0,12.80);

    Long64_t nrow = (Long64_t) t->GetEntries();

    for (Long64_t i=0; i<nrow; i++) {

        //initialization
        for (Int_t ii=0; ii<kMaxbeta; ii++) {
            beta_t[ii]=-1;
            beta_deltaz[ii]=-1;
            beta_deltaxy[ii]=13;
        }//*/

        t->GetEntry(i);

        for (Int_t j=0; j<kMaxbeta; j++) {
            if (flagall==1&&Mass==76&&((z==5)||(z==6))) {
                if (beta_t[j]>0&&beta_deltaz[j]==0&&beta_deltaxy[j]<2){
                    h_beta_t->Fill(beta_t[j]);
                }
            }
        }

    }


    TCanvas *c_beta_t = new TCanvas("c_beta_t","Decay time",1);
    h_beta_t->Draw();

    TFile *outputFile = new TFile("76Cu_beta_t.root","RECREATE");
    outputFile->WriteObject(h_beta_t, "h_beta_t");
	outputFile->Close();
}
