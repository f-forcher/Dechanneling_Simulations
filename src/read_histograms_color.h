/*
 * read_histograms.h
 *
 *  Created on: Oct 28, 2016
 *      Author: fforcher
 */

#ifndef READ_HISTOGRAMS_COLOR_H_
#define READ_HISTOGRAMS_COLOR_H_

// Per poter usare questa macro sia compilando che eseguendo.
// https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#moving-between-interpreter-and-compiler
#ifndef __CLING__

#include <string>

#include "TH1D.h"

// Se non siamo nell'interprete, ma stiamo compilando, metti la forward declaration perche' verra' linkata quando compili eclipse
namespace mions {
/*
 * @Brief: three separate histograms for Channeling, Dechanneling and Amorphous
 * @nome_cristallo: name of the crystal in question
 * @nomefiledati_dat: name of the .dat file with the data
 * @cut: X-angular cuts
 * @histogramAm: Amorphous interaction histogram
 * @histogramDech: Dechanneling histogram
 * @histogramCh: Channeling histogram
 */
void read_histograms_color(std::string nome_cristallo,
					 std::string nomefiledati_dat,
					 Double_t cut,
					 TH1D*& histogramAm,
					 TH1D*& histogramDech,
					 TH1D*& histogramCh,
					 );

}
#else
// Altrimenti includi il file della macro. Nel compilatore naturalmente direbbe multiple definition quando linka l'altro
// file.

#include "read_histograms_color.C"

#endif



#endif /* READ_HISTOGRAMS_COLOR_H_ */
