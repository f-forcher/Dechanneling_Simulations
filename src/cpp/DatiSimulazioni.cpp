/*
 * DatiChanneling.cpp
 *
 *  Created on: Sep 27, 2016
 *      Author: fforcher
 */

#include "../DatiSimulazioni.h"

namespace mions {

/*
 DatiChanneling::DatiChanneling() {
 // TODO Auto-generated constructor stub

 }
 */

DatiSimulazioni::DatiSimulazioni(std::string nome_file_dati) {


	//  131072 = 2^17, tipical number of events in the range 100 000 - 500 000

	std::ifstream file_dati( nome_file_dati );

	if (file_dati) {
		ipart.reserve(16384);
		nturn.reserve(16384);
		icoll.reserve(16384);
		previous_interaction.reserve(16384);
		interaction.reserve(16384);

		kick_x.reserve(16384); //  x_uscita - x_entrata
		kick_y.reserve(16384); //  y_uscita - y_entrata
		E_in  .reserve(16384); //  initial energy?
		E_out .reserve(16384); //  after-interaction energy?
		xp_in .reserve(16384); //  x_entrata
		yp_in .reserve(16384); //  y_entrata
		cr_ang.reserve(16384); //  ?

		unsigned long long tipart;
		unsigned long long tnturn;
		unsigned long long ticoll;
		short tprevious_interaction;
		short tinteraction;

		//Temporary variables
		Double_t tkick_x;
		Double_t tkick_y;
		Double_t tE_in;
		Double_t tE_out;
		Double_t txp_in;
		Double_t typ_in;
		Double_t tcr_ang;


		//First line is comment, we discard it
		// The first line
		// "#1=ipart 2=nturn 3=icoll 4=previous interaction 5=interaction      6=kick_x 7=kick_y 8=E_in 9=E_out 10=xp_in 11=yp_in 12=cr_ang\n"
		// is 127 char long (128 with newline, which will not be extracted)
		std::string firstline(128, '\0');
		std::getline(file_dati,firstline); // getline leave the newline at the start of the stream: "\n101 1 1 ..."
		file_dati.ignore(); // Skip the newline

		while (file_dati >> tipart) {
			file_dati >> tnturn;
			file_dati >> ticoll;
			file_dati >> tprevious_interaction;
			file_dati >> tinteraction;

			file_dati >> tkick_x;
			file_dati >> tkick_y;
			file_dati >> tE_in;
			file_dati >> tE_out;
			file_dati >> txp_in;
			file_dati >> typ_in;
			file_dati >> tcr_ang;

			ipart.emplace_back( tipart );
			nturn.emplace_back( tnturn );
			icoll.emplace_back( ticoll );
			previous_interaction.emplace_back( tprevious_interaction );
			interaction.emplace_back( tinteraction );

			kick_x .emplace_back( tkick_x );
			kick_y .emplace_back( tkick_y );
			E_in   .emplace_back( tE_in );
			E_out  .emplace_back( tE_out );
			xp_in  .emplace_back( txp_in );
			yp_in  .emplace_back( typ_in );
			cr_ang .emplace_back( tcr_ang );
		};
	} else {
		std::cerr << "[ERROR]: Tried to open " << nome_file_dati << std::endl;
		throw "[ERROR]: File .dat not opened";
	}

}

DatiSimulazioni::~DatiSimulazioni() {
	// TODO Auto-generated destructor stub
}

void DatiSimulazioni::print(ULong64_t from, ULong64_t to) const {
	using namespace std;
	EventoPassaggio ev;

	for (ULong64_t i = from; i < to; ++i) {
		ev = getEvent( i );

		// Stampa i valori dell'evento
		for (const auto& dato : ev) {
			cout << dato << " ";
		}
		cout << endl;
	}
}

EventoPassaggio DatiSimulazioni::getEvent(ULong64_t index) const {
	EventoPassaggio ev;

	ev[0]  = nturn[index];
	ev[1]  = icoll[index];
	ev[2]  = previous_interaction[index];
	ev[3]  = interaction[index];

	ev[4]  = kick_x[index];
	ev[5]  = kick_y[index];
	ev[6]  = E_in[index];
	ev[7]  = E_out[index];
	ev[8]  = xp_in[index];
	ev[9]  = yp_in[index];
	ev[10] = cr_ang[index];

	return ev;
}

} /* namespace mions */
