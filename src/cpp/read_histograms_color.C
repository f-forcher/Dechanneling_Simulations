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



//TODO Finire!

void read_histograms_color(std::string nome_cristallo,
					 std::string nomefiledati_dat,
					 Double_t cut,
					 TH1D*& histogramAm,
					 TH1D*& histogramDech,
					 TH1D*& histogramCh,
					 ) {


	//We should already be inside the right folder

	auto pathfiledati_dat = "./crystal_simulations/" +
			nome_cristallo + "/"
			+ nomefiledati_dat;



	// select +- 5 microrad in nomehisto5, +-10 in nomehisto10
	string nomehistoAm = "Amorphous_" + nome_cristallo;
	string nomehistoDech = "Dechanneling_" + nome_cristallo;
	string nomehistoCh = "Channeling_" + nome_cristallo;
	string titlehistoAm = nome_cristallo + ", amorphous fraction";
	string titlehistoDech = nome_cristallo + ", dechanneling fraction";
	string titlehistoCh = nome_cristallo + ", channeling fraction";
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

		TH1D* histogramAm_dat;
		TH1D* histogramDech_dat;
		TH1D* histogramCh_dat;

		if (histogramAm_dat == nullptr or histogramDech_dat == nullptr or histogramCh_dat == nullptr) {
			histogramAm_dat = new TH1D(
			/* name */nomehistoAm.c_str(),
			/* title */titlehistoAm.c_str(),
			/* X-dimension */600 / 4, -200, 400 );

			histogramDech_dat = new TH1D(
			/* name */nomehistoDech.c_str(),
			/* title */titlehistoDech.c_str(),
			/* X-dimension */600 / 4, -200, 400 );

			histogramCh_dat = new TH1D(
			/* name */nomehistoCh.c_str(),
			/* title */titlehistoCh.c_str(),
			/* X-dimension */600 / 4, -200, 400 );
		} else {
			histogramAm_dat = histogramAm;
			histogramDech_dat = histogramDech;
			histogramCh_dat = histogramCh;
		}

		//dati.print(datisize);

		//Read events and select those with entry angle between -+5 and +-10 microrad
		for (ULong64_t i = 0; i < datisize; ++i) {

			ev = dati.getEvent( i );
			// #1=ipart 2=nturn 3=icoll 4=previous interaction 5=interaction
			//          6=kick_x 7=kick_y 8=E_in 9=E_out 10=xp_in 11=yp_in 12=cr_ang
			long interaction = std::lround(ev[4]);
			Double_t x_entrata = ev[9];
			Double_t delta_x = ev[5]; //x_uscita - x_entrata

			DBG( std::clog << "delta_x: " << delta_x << std::endl; , ; )
			if (x_entrata / MICRO_ > -cut and x_entrata / MICRO_ < cut) {
				//vHistograms.front()->Fill(x_uscita-x_entrata);
				switch (interaction) {
					case value:
						histogram5_dat->Fill( - delta_x * 1e6 );
						break;
					default:
						break;
				}
			}
		}

		// Should be correct in either cases of the "if" above
		histogram5 = histogram5_dat;
		histogram10 = histogram10_dat;
		// Technically not necessary now, but maybe I'll add more conditions
	}  else {
		cerr << "[ERROR]: File .dat not opened!" << endl;
		return;
	}

}

}
