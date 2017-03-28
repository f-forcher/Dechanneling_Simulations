/*
 * read_histogram_VRAM.C
 *
 *  Created on: Jan 13, 2017
 *      Author: fforcher
 */




/*
 * read_histograms.C
 *
 *  Created on: Oct 28, 2016
 *      Author: fforcher
 */

#include <iostream>
#include <sstream>
#include <cmath>
//#include <map>
#include <string>
#include <memory>
#include <fstream>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TH1D.h"
#include "TRandom.h"
#include "TRandom3.h"

#include "../dbg_macro.h"
#include "../my_typedefs.h"
#include "../DatiSimulazioni.h"

extern char PROJECT_DIR[];


namespace mions {
using std::string;
using std::ifstream;
using std::stringstream;
using std::pow;
using std::endl;
using std::cout;
using std::clog;
using std::cerr;



void read_histograms_VRAM(std::string nome_cristallo,
					 std::string nomefiledati_dat,
					 TH2D*& histogram,
					 TH2D*& histogram_rnd,
					 double noise_initialx, // [murad]
					 double noise_deltaxp // [murad]
					 ) {


	//We should already be inside the right folder
	auto pathfiledati_dat = "./crystal_simulations_VRAM/" +
			nome_cristallo + "/"
			+ nomefiledati_dat;



	// select +- 5 microrad in nomehisto5, +-10 in nomehisto10
	string nomehisto = "hdati_" + nome_cristallo;
	// TODO decidersi coi nomi
	//string nomehisto_rnd = "hdati_rnd_" + nome_cristallo;
	string nomehisto_rnd = "dTheta_x_vs_Impact_x_cor";

	string titlehisto = nome_cristallo + ", 2D deflections plot";
	string titlehisto_rnd = nome_cristallo + ", 2D deflections plot, randomized";
	//clog << nomehisto5 << endl;


	ifstream file_dat( pathfiledati_dat );

	if ( bool( file_dat ) ) {
		// Il codice per la mia analisi qua

		//gStyle->SetPalette(1);
		//gStyle->SetOptStat(1);
		//gStyle->SetOptTitle(1);
		//TGaxis::SetMaxDigits(3);

		/*
		DBG(
				clog << "[LOG]: " << "Crystal " << nome_cristallo << endl; clog << "[LOG]: File "<< nomefiledati_dat << endl << endl;,
				; )
		clog << "[LOG]: Using .dat file";
		*/

		//ifstream file_dat(pathfiledati);

		//Riempi gli istogrammi
		DatiSimulazioni dati( pathfiledati_dat );

		EventoPassaggio ev;
		auto datisize = dati.getSize();

		TH2D* histogram_dat;
		TH2D* histogram_rnd_dat;

		TRandom* rnd = new TRandom3();

		if (histogram == nullptr) {
			histogram_dat = new TH2D(
			/* name */nomehisto.c_str(),
			/* title */titlehisto.c_str(),
			/* X-dimension */250, -30, 200,
			/* Y-dimension */300,-100,200);

			histogram_rnd_dat = new TH2D(
			/* name */nomehisto_rnd.c_str(),
			/* title */titlehisto_rnd.c_str(),
			/* X-dimension */250, -30, 200,
			/* Y-dimension */300,-100,200);

		} else {
			histogram_dat      = histogram;
			histogram_rnd_dat  = histogram_rnd;
		}

		//dati.print(datisize);

		//Read events and select those with entry angle between -+5 and +-10 microrad
		for (ULong64_t i = 0; i < datisize; ++i) {

			ev = dati.getEvent( i );
			// #1=ipart 2=nturn 3=icoll 4=previous interaction 5=interaction
			//          6=kick_x 7=kick_y 8=E_in 9=E_out 10=xp_in 11=yp_in 12=cr_ang
			Double_t x_entrata = ev[9];
			Double_t delta_x = ev[5]; //x_uscita - x_entrata

			//DBG( std::clog << "delta_x: " << delta_x << std::endl; , ; )

			histogram_dat->Fill(-x_entrata / MICRO_, -delta_x / MICRO_);
			//histogram_rnd_dat->Fill( rnd->Gaus(-x_entrata / MICRO_ , 2.8), rnd->Gaus(-delta_x / MICRO_ , noise_deltaxp) );
			histogram_rnd_dat->Fill( rnd->Gaus(-x_entrata / MICRO_ , noise_initialx), rnd->Gaus(-delta_x / MICRO_ , noise_deltaxp) );
		}

		// Should be correct in either cases of the "if" above
		histogram      = histogram_dat;
		histogram_rnd  = histogram_rnd_dat;
		// Technically not necessary now, but maybe I'll add more conditions
	}  else {
		cerr << "[ERROR]: File .dat not opened!" << endl;
		return;
	}

}

}
