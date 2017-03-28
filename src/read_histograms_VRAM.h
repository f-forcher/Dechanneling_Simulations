/*
 * read_histograms_VRAM.h
 *
 *  Created on: Jan 13, 2017
 *      Author: fforcher
 */

#ifndef READ_HISTOGRAMS_VRAM_H_
#define READ_HISTOGRAMS_VRAM_H_


// Per poter usare questa macro sia compilando che eseguendo.
// https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#moving-between-interpreter-and-compiler
#ifndef __CLING__

#include <string>

#include "TH2D.h"

// Se non siamo nell'interprete, ma stiamo compilando, metti la forward declaration perche' verra' linkata quando compili eclipse
namespace mions {

void read_histograms_VRAM(std::string nome_cristallo,
					 std::string nomefiledati_dat,
					 TH2D*& histogram,
					 TH2D*& histogram5_rnd,
					 double noise_initialx, // [murad]
					 double noise_deltaxp // [murad]
					 );

}
#else
// Altrimenti includi il file della macro. Nel compilatore naturalmente direbbe multiple definition quando linka l'altro
// file.

#include "cpp/read_histograms_VRAM.C"

#endif





#endif /* READ_HISTOGRAMS_VRAM_H_ */
