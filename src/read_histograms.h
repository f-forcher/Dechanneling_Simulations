/*
 * read_histograms.h
 *
 *  Created on: Oct 28, 2016
 *      Author: fforcher
 */

#ifndef READ_HISTOGRAMS_H_
#define READ_HISTOGRAMS_H_

// Per poter usare questa macro sia compilando che eseguendo.
// https://root.cern.ch/root/htmldoc/guides/users-guide/ROOTUsersGuide.html#moving-between-interpreter-and-compiler
#ifndef __CLING__

#include <string>

#include "TH1D.h"

// Se non siamo nell'interprete, ma stiamo compilando, metti la forward declaration perche' verra' linkata quando compili eclipse
namespace mions {

void read_histograms(std::string nome_cristallo,
					 std::string nomefiledati_dat,
					 TH1D*& histogram5,
					 TH1D*& histogram5_rnd,
					 TH1D*& histogram10,
					 TH1D*& histogram10_rnd
					 );

}
#else
// Altrimenti includi il file della macro. Nel compilatore naturalmente direbbe multiple definition quando linka l'altro
// file.

#include "read_histograms.C"

#endif



#endif /* READ_HISTOGRAMS_H_ */
