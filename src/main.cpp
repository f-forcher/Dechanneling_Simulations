//============================================================================
// Name        : main.cpp
// Author      : Francesco Forcher
// Version     : 1.1
// Description : Sample ROOT main for compiling and correct working tests
//============================================================================

//#include "AnalysisFactory.h"
//#include "AnalysisInfo.h"
//#include "EventSource.h"
//#include "SourceFactory.h"
//#include "util/include/Dispatcher.h"
#include <TApplication.h>
using namespace std;

int main_macro(int argc, char* argv[]);

int main(int argc, char* argv[]) {

	// store command line parameters

	//int argc2 = 7;
	//const char* argv2[] = { "./Debug/Ronch_braggPlot_v05", "input",
	//		"bragg_events.txt", "hist", "hh", "ranges", "energyRanges" };

	//cout << "Test main";

	//TApplication Necessary for the graphics
	TApplication theApp( "App", &argc, argv );

	int return_macro = main_macro( argc, argv );

	theApp.Run();
	//mia_dech();

	return return_macro;

}

