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



void read_histograms(std::string nome_cristallo,
					 std::string nomefiledati_dat,
					 TH1D*& histogram5,
					 TH1D*& histogram5_rnd,
					 TH1D*& histogram10,
					 TH1D*& histogram10_rnd
					 ) {


	//We should already be inside the right folder

	auto pathfiledati_dat = "./crystal_simulations/" +
			nome_cristallo + "/"
			+ nomefiledati_dat;



	// select +- 5 microrad in nomehisto5, +-10 in nomehisto10
	string nomehisto5 = "hdati5_" + nome_cristallo;
	string nomehisto5_rnd = "hdati5_rnd_" + nome_cristallo;
	string nomehisto10 = "hdati10_" + nome_cristallo;
	string nomehisto10_rnd = "hdati10_rnd_" + nome_cristallo;
	string titlehisto5 = nome_cristallo + ", cuts at +- 5 microrad";
	string titlehisto5_rnd = nome_cristallo + ", cuts at +- 5 microrad, randomized";
	string titlehisto10 = nome_cristallo + ", cuts at +- 10 microrad";
	string titlehisto10_rnd = nome_cristallo + ", cuts at +- 5 microrad, randomized";
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

		TH1D* histogram5_dat;
		TH1D* histogram10_dat;
		TH1D* histogram5_rnd_dat;
		TH1D* histogram10_rnd_dat;

		TRandom* rnd = new TRandom3();

		if (histogram5 == nullptr or histogram10 == nullptr) {
			histogram5_dat = new TH1D(
			/* name */nomehisto5.c_str(),
			/* title */titlehisto5.c_str(),
			/* X-dimension */120, -200, 400 );

			histogram10_dat = new TH1D(
			/* name */nomehisto10.c_str(),
			/* title */titlehisto10.c_str(),
			/* X-dimension */120, -200, 400 );

			histogram5_rnd_dat = new TH1D(
			/* name */nomehisto5_rnd.c_str(),
			/* title */titlehisto5_rnd.c_str(),
			/* X-dimension */120, -200, 400 );

			histogram10_rnd_dat = new TH1D(
			/* name */nomehisto10_rnd.c_str(),
			/* title */titlehisto10_rnd.c_str(),
			/* X-dimension */120, -200, 400 );
		} else {
			histogram5_dat      = histogram5;
			histogram10_dat     = histogram10;
			histogram5_rnd_dat  = histogram5_rnd;
			histogram10_rnd_dat = histogram10_rnd;
		}

		//dati.print(datisize);

		//Read events and select those with entry angle between -+5 and +-10 microrad
		for (ULong64_t i = 0; i < datisize; ++i) {

			ev = dati.getEvent( i );
			// #1=ipart 2=nturn 3=icoll 4=previous interaction 5=interaction
			//          6=kick_x 7=kick_y 8=E_in 9=E_out 10=xp_in 11=yp_in 12=cr_ang
			Double_t x_entrata = rnd->Gaus(ev[9] , 4.4 * MICRO_);
			Double_t delta_x = ev[5]; //x_uscita - x_entrata

			DBG( std::clog << "delta_x: " << delta_x << std::endl; , ; )
			if (x_entrata / MICRO_ > -5 and x_entrata / MICRO_ < 5) {
				//vHistograms.front()->Fill(x_uscita-x_entrata);
				histogram5_dat->Fill( -delta_x / MICRO_ );
				//histogram5_rnd_dat->Fill( -delta_x / MICRO_ + rnd->Gaus(-delta_x / MICRO_ ,5) ); // 5 murad of uncertainty
				histogram5_rnd_dat->Fill( rnd->Gaus(-delta_x / MICRO_ ,5) ); // 5 murad of uncertainty
			}

			if (x_entrata / MICRO_ > -10 and x_entrata / MICRO_ < 10) {
				//vHistograms.front()->Fill(x_uscita-x_entrata);
				histogram10_dat->Fill( -delta_x / MICRO_ );
				//histogram10_rnd_dat->Fill( -delta_x / MICRO_ + rnd->Gaus(-delta_x / MICRO_ ,5) );
				histogram10_rnd_dat->Fill( rnd->Gaus(-delta_x / MICRO_ ,5) );
			}
		}

		// Should be correct in either cases of the "if" above
		histogram5      = histogram5_dat;
		histogram10     = histogram10_dat;
		histogram5_rnd  = histogram5_rnd_dat;
		histogram10_rnd = histogram10_rnd_dat;
		// Technically not necessary now, but maybe I'll add more conditions
	}  else {
		cerr << "[ERROR]: File .dat not opened!" << endl;
		return;
	}

}

}
