#include "ConsoleHistogram.h"

map<std::string, int> StrHistogram::mapStrHistData;
map<unsigned int, int> IntHistogram::mapIntHistData;

volatile CConsoleLoggerEx *StrHistogram::coloured_console1 = NULL;
volatile CConsoleLoggerEx* IntHistogram::coloured_console2 = NULL;
//
////map<std::string, int> ConsoleHistogram::mapStrHistData;
////map<int, int> ConsoleHistogram::mapIntHistData;
//
//template<typename T>
//void ConsoleHistogram::printHistogram(void)
//{
//	//CConsoleLoggerEx coloured_console1;
//	//coloured_console1.Create("This is the another console");
//
//	//map<T, int> mapHistData;
//	//if (!ConsoleHistogram::mapStrHistData.empty())
//	//	mapHistData = ConsoleHistogram::mapStrHistData;
//	//else if (!ConsoleHistogram::mapIntHistData.empty())
//	//	mapHistData = ConsoleHistogram::mapIntHistData;
//
//	//for (auto it : mapHistData)
//	//{
//	//	char arr[LABLES_MAX_SIZE] = { 0 };
//	//	memset(arr, ' ', sizeof(arr) / sizeof(char) - 1);
//
//	//	string tp(arr);
//	//	tp += " | ";
//	//	coloured_console1.cprintf(tp.c_str());
//
//	//	vector<int> vect(it.second / stepHist, DRAW_SYMBOL_CODE);
//	//	string str(vect.begin(), vect.end());
//
//	//	tp = str;
//	//	tp += " [";
//	//	tp += std::to_string(it.second);
//	//	tp += "]\n";
//
//	//	coloured_console1.cprintf(coloured_console1.COLOR_GREEN, tp.c_str());
//	//	tp = "";
//	//}
//	//coloured_console1.Close();
//}
