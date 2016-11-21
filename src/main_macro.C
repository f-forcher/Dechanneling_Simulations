/*
 * main_macro.C
 *
 *  Created on: Sep 21, 2016
 *      Author: fforcher
 */

//============================================================================
// Name        : bP_05.cpp
// Author      : Francesco Forcher
// Version     : 1.1
// Description : Modify Plot_v04 and use dispatcher&observers to handle begin/end job
//============================================================================
//#include "AnalysisFactory.h"
//#include "AnalysisInfo.h"
//#include "EventSource.h"
//#include "SourceFactory.h"
//#include "util/include/Dispatcher.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <cstdlib>
#include <unistd.h> // getcwd
#include <map>
#include <sstream>
#include <array>
#include <cmath>
#include <cstdio> //snprintf
#include <string>

#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TH1D.h>

//#include "analizza_dechanneling.h"
#include "dbg_macro.h"
//#include "Hello.h"
#include "DatiSimulazioni.h"
#include "read_histograms.h"
#include "read_histograms_color.h"
//#include "my_typedefs.h"

//GLOBALS meglio in un file a parte
//Directory del progetto
TDirectory* ROOT_PROJDIR = nullptr;
char PROJECT_DIR[FILENAME_MAX] = "[NOT SET]";

/*
 * First argument from command line
 */
int main_macro(int argc, char* argv[]) {

	using namespace std;
	using mions::DatiSimulazioni;

	auto nomecrys = string( argv[1] );

	/* Example usage:
	 * ./Optimized_Super/Dechanneling_Simulations STF49 new2
	 * Analyze STF49 with the second improved simulation
	 *
	 * ./Optimized_Super/Dechanneling_Simulations STF49 orig
	 * Analyze the original simulation for STF49
	 */
	auto simvers = (string("orig") == string( argv[2] ) ?
						string("") :
						string("_") + string( argv[2] ));

	// Save the directory of the project (remember you are expected to start it from the
	// top folder of the repo)
	getcwd( PROJECT_DIR, FILENAME_MAX );



//	DatiSimulazioni sim_data_test( "crystal_simulations/STF45/run0553/cr_interaction.dat" );
	//DatiSimulazioni sim_data_test("test/prova_dat");

	/*	if(!sim_data_test) {
	 cerr << "[ERROR]: File not found!" << endl;
	 return -1;
	 }*/

//	sim_data_test.print( sim_data_test.getSize() );
//	DBG( std::clog << "size: " << sim_data_test.getSize() << std::endl
//	; , ; )
	std::vector<const char*> elenco_cristalli_sim {
	// "STF45"
	// "STF49_new"
	 "STF45_new"
	// "STF49_new"
	// "STF99"
	};

	char numero_run[FILENAME_MAX];
//	for (const auto& crys : elenco_cristalli_sim) {

	//Crystal name and simulation version, eg "STF45" or "STF45_new2"
	string crys_namevers( nomecrys + simvers );

	TH1D* histogram5 = nullptr;
	TH1D* histogram10 = nullptr;
	TH1D* histogram5_rnd = nullptr;
	TH1D* histogram10_rnd = nullptr;

	TH1D* histogramAm = nullptr;
	TH1D* histogramDech = nullptr;
	TH1D* histogramCh = nullptr;
	TH1D* histogramOth = nullptr;
	TH1D* histogramTot = nullptr;


	auto f = [&] () {
		for (auto i = 1; i <= 1000; ++i) {
			snprintf( numero_run, FILENAME_MAX, "%04d", i ); // print the number of the simulation job to select, with trailing zeroes
			string nome_file_dat = string( "run" ) + numero_run + "/cr_interaction.dat"; // e.g. run0321/cr_interaction.dat
			DBG( std::clog << "nome_file_dat: " << nome_file_dat << std::endl
			; , ; )
			clog << numero_run << std::endl;
			mions::read_histograms( crys_namevers, nome_file_dat, histogram5, histogram5_rnd, histogram10,
					histogram10_rnd );

			mions::read_histograms_color( crys_namevers, nome_file_dat, 10, histogramAm, histogramDech, histogramCh,
					histogramOth );
		}
	};


	int int_shar = 0;
	auto f2 = [] () {

	};

	f();
//		string canvas_name = "Crystal simulation: " + crystal_name;
//		auto cSim = new TCanvas( "cRcLd", canvas_name.c_str() );
//		cSim->Divide( 2, 1 );
//		cSim->cd( 1 );
//		histogram5->Draw();
//		cSim->cd( 2 );
//		histogram10->Draw();

	string canvas_name_color = "Crystal simulation: " + crys_namevers + "color coded";
	auto cColor = new TCanvas( "cSimColor", canvas_name_color.c_str() );
//		cColor->Divide( 3, 1 );
//		cColor->cd( 1 );
//		histogramAm->Draw();
//		cColor->cd( 2 );
//		histogramDech->Draw();
//		cColor->cd( 3 );
//		histogramCh->Draw();

	histogramTot = new TH1D(
	/* name */"total_histo",
	/* title */"Total Histogram",
	/* X-dimension */600 / 4, -200, 400 );
	histogramTot->Add( histogramAm );
	histogramTot->Add( histogramDech );
	histogramTot->Add( histogramCh );
	histogramTot->Add( histogramOth );

	histogramAm->SetFillColorAlpha( kBlue, 0.4 );
	histogramDech->SetFillColorAlpha( kRed, 0.4 );
	histogramCh->SetFillColorAlpha( kGreen, 0.4 );
	histogramOth->SetFillColorAlpha( kMagenta, 0.4 );
	histogramTot->SetLineColor( kGreen );

	//Normalize, for confronting with the data
//		histogramAm->Scale(1.0/histogramAm->Integral());
//		histogramCh->Scale(1.0/histogramCh->Integral());
//		histogramDech->Scale(1.0/histogramDech->Integral());
//		histogramOth->Scale(1.0/histogramOth->Integral());

	auto totint = histogramAm->Integral() + histogramCh->Integral() + histogramDech->Integral()
			+ histogramOth->Integral();
	histogramAm->Scale( 1.0 / totint );
	histogramCh->Scale( 1.0 / totint );
	histogramDech->Scale( 1.0 / totint );
	histogramOth->Scale( 1.0 / totint );
	histogramTot->Scale( 1.0 / histogramTot->Integral() );

	//histogramAm   -> Draw();
	//histogramCh   -> Draw("same");
	//histogramDech -> Draw("same");
	//histogramOth  -> Draw("same");
	//histogramTot  -> Draw("same");

	// Experimental data
	string nomefile_dati_sperimentali = "../Old_Macros_Dechanneling/Dechanneling_Histograms.root";
	TFile * dati_sperimentali = new TFile( nomefile_dati_sperimentali.c_str() );
	// string nomehistoSper = "hdati10_" + string( crys ); //TODO Generalizzare a un file
	string nomehistoSper = "hdati10_" +  nomecrys;

	TH1D * hDatiSper = (TH1D*) dati_sperimentali->Get( nomehistoSper.c_str() );

//		histogram10->Scale(1.0/histogram10->Integral());
//		hDatiSper->Scale(1.0/hDatiSper->Integral());

	histogram10->Scale( 1.0 / histogram10->GetEntries() );
	histogram10_rnd->Scale( 1.0 / histogram10_rnd->GetEntries() );
	hDatiSper->Scale( 1.0 / hDatiSper->GetEntries() );

	histogram10->SetLineColor( kGreen );
	histogram10->Draw();

	histogram10_rnd->SetLineColor( kRed );
	histogram10_rnd->Draw( "same" );

	hDatiSper->SetLineColor( kRed );
	hDatiSper->SetMarkerStyle( kPlus );
	hDatiSper->SetMarkerSize( 0.5 );
	hDatiSper->Draw( "0 P same" );

//	}

	return 0;
}

