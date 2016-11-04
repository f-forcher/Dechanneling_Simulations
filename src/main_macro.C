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
	std::vector<const char*> elenco_cristalli_sim { "STF45" //,
	//"STF49",
	};

	char numero_run[FILENAME_MAX];
	for (const auto& crys : elenco_cristalli_sim) {
		string crystal_name( crys );

		TH1D* histogram5 = nullptr;
		TH1D* histogram10 = nullptr;

		for (auto i = 1; i <= 1000; ++i) {
			snprintf( numero_run, FILENAME_MAX, "%04d", i ); // print the number of the simulation job to select, with trailing zeroes
			string nome_file_dat = string( "run" ) + numero_run + "/cr_interaction.dat"; // e.g. run0321/cr_interaction.dat
			DBG( std::clog << "nome_file_dat: " << nome_file_dat << std::endl
			; , ; )
			clog << numero_run << std::endl;
			mions::read_histograms( crystal_name, "run0002/cr_interaction.dat", histogram5, histogram10 );
		}

		string canvas_name = "Crystal simulation: " + crystal_name;
		auto cSim = new TCanvas( "cRcLd", canvas_name.c_str() );
		cSim->Divide( 2, 1 );
		cSim->cd( 1 );
		histogram5->Draw();
		cSim->cd( 2 );
		histogram10->Draw();
	}

	return 0;
}

