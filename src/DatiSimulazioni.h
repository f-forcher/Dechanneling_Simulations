/*
 * DatiChanneling.h
 *
 *  Created on: Sep 27, 2016
 *      Author: fforcher
 */

#ifndef DATISIMULAZIONI_H_
#define DATISIMULAZIONI_H_

#include <TROOT.h>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <array>

namespace mions {

using EventoPassaggio = std::array<Double_t,12>;

//TODO Finire la classe

/*
 * Class to read a data file made by SixTrack, which has the following structure:
 * #1=ipart 2=nturn 3=icoll 4=previous interaction 5=interaction      6=kick_x 7=kick_y 8=E_in 9=E_out 10=xp_in 11=yp_in 12=cr_ang
 * 101 1 1 -1 3 -1.407458291926671E-04 0.000000000000000E+00 400.0000000000000 399.9994375913847 -3.035623000000000E-06 -5.586757000000000E-06 0.000000000000000E+00
 * 103 1 1 -1 2 1.364517736088041E-05 5.840654414214292E-06 400.0000000000000 399.9988751836152 -1.467048000000000E-05 7.107398000000000E-06 0.000000000000000E+00
 * 104 1 1 -1 3 -1.340521084495155E-04 0.000000000000000E+00 400.0000000000000 399.9994375913847 -7.652649000000001E-07 -1.791178000000000E-05 0.000000000000000E+00
 * ...
 */
class DatiSimulazioni {
public:
	//DatiChanneling();

	/* @brief: Read the file file_dati and fill the class
	 *
	 */
	//DatiChanneling(std::shared_ptr<std::ifstream> file_dati);
	DatiSimulazioni(std::string nome_file_dati);
	virtual ~DatiSimulazioni();

	/*
	 * @brief: print the events with index from "from" to "to"
	 */
	void print(ULong64_t from, ULong64_t to) const;

	/*
	 * @brief: print the events with index from 0 to "to"
	 */
	void print(ULong64_t to) const {
		print( 0, to );
	}
	;

	/*
	 * @brief: get the four data of a single event ("orizontal" slice)
	 * @return: EventoDechanneling is an std::array<Double_t,4>
	 */
	EventoDechanneling getEvent(ULong64_t index) const;

	/*
	 * @brief: get number of events
	 */
	auto getSize() const {
		return x_entrata.size();
	}

	//TODO getters setters
private:
	/*
	 * Data columns of the file
	 */
	std::vector<unsigned long long> ipart;
	std::vector<unsigned long long> nturn;
	std::vector<unsigned long long> icoll;
	std::vector<unsigned short> previous_interaction;
	std::vector<unsigned short> interaction;

	std::vector<Double_t> kick_x; // x_uscita - x_entrata
	std::vector<Double_t> kick_y; // x_uscita - x_entrata
	std::vector<Double_t> E_in; // x_uscita - x_entrata
	std::vector<Double_t> E_out; // x_uscita - x_entrata
	std::vector<Double_t> xp_in; // x_uscita - x_entrata
	std::vector<Double_t> yp_in; // x_uscita - x_entrata
	std::vector<Double_t> cr_ang; // x_uscita - x_entrata

};

} /* namespace mions */

#endif /* DATISIMULAZIONI_H_ */
