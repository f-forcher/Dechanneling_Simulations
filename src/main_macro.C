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
#include <unistd.h>
#include <map>
#include <sstream>
#include <array>
#include <cmath>

#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>


//#include "analizza_dechanneling.h"
#include "dbg_macro.h"
#include "Hello.h"
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

	auto test = new Hello();

	//auto c1 = new TCanvas();
	//test->Paint();

	return 0;
}

