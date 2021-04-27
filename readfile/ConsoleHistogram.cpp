#include "ConsoleHistogram.h"
#include "ConsoleLogger.h"

#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iomanip>

#include <string>
#include <any>
#include <utility>
#include <iomanip>

using namespace std;

map<std::string, int> StrHistogram::mapStrHistData;
map<unsigned int, int> IntHistogram::mapIntHistData;

volatile CConsoleLoggerEx *StrHistogram::coloured_console1 = NULL;
volatile CConsoleLoggerEx* IntHistogram::coloured_console2 = NULL;

CConsoleLoggerEx* StrHistogram::getInstance(bool& checkStat)
{
	checkStat = false;
	if (coloured_console1 == NULL)
	{
		// To make thread safe 
		if (coloured_console1 == NULL)

			coloured_console1 = new CConsoleLoggerEx();
		checkStat = true;

		//}
	}

	return (CConsoleLoggerEx*)coloured_console1;
}

bool StrHistogram::clearConsoleMemory(void)
{
	delete coloured_console1;
	return true;
}


StrHistogram::StrHistogram(int iPx) : maxStepHist(0), iPixel(iPx) {
	/*if (coloured_console1 == NULL)
	{

		coloured_console1 = new CConsoleLoggerEx();
	}
	*/
};

StrHistogram::~StrHistogram() {};

bool StrHistogram::openNewConsoleWindow(string strWindow) {
	bool bStat = false;
	CConsoleLoggerEx* sngPrt = getInstance(bStat);
	if (bStat)
		sngPrt->Create(strWindow.c_str());

	return true;
}


bool StrHistogram::closeConsoleWindow(void) {
	bool bStat = false;
	CConsoleLoggerEx* sngPrt = getInstance(bStat);

	sngPrt->Close();

	clearConsoleMemory();
	return true;
}

/**
	* ------------------------------------------------------------
	* <summary>
	*  Increment the value of the String key with single step
	* </summary>
	* ------------------------------------------------------------*/
bool StrHistogram::updStrHitogramData(std::string key) {

	std::map<std::string, int>::iterator it = mapStrHistData.find(key);
	if (it != mapStrHistData.end())
	{
		it->second += 1;
		if (maxStepHist < it->second)
			maxStepHist = it->second;
	}
	else
	{
		mapStrHistData.insert(pair<string, int>(key, 1));
		if (maxStepHist < 1)
			maxStepHist = 1;
	}

	return true;
}

/**
	* ------------------------------------------------------------
	* <summary>
	*  Increment the value of the String key with batch input "data"
	* </summary>
	* ------------------------------------------------------------*/
bool StrHistogram::updStrHitogramDataBatch(std::string key, int data) {


	std::map<std::string, int>::iterator it = mapStrHistData.find(key);
	if (it != mapStrHistData.end())
	{
		it->second = data;
		if (maxStepHist < data)
			maxStepHist = it->second;
	}
	else
	{
		mapStrHistData.insert(pair<std::string, int>(key, data));
		if (maxStepHist < data)
			maxStepHist = data;
	}

	return true;
}

void StrHistogram::printHistogram(void)
{
	bool bStat = false;
	CConsoleLoggerEx* sngPrt = getInstance(bStat);

	double stepHist = iPixel;

	string printData("");
	for (auto it : mapStrHistData)
	{
		char arr[LABLES_MAX_SIZE] = { 0 };

		memset(arr, ' ', sizeof(arr) / sizeof(char) - 1);
		memcpy(arr, it.first.c_str(), it.first.size());
		string tp(arr);
		tp += " | ";

		int iResolution = (it.second / (int)stepHist < HISTOGRAM_RESOLUTION) ? (it.second / (int)stepHist) : HISTOGRAM_RESOLUTION;
		vector<int> vect(iResolution, DRAW_SYMBOL_CODE);
		string str(vect.begin(), vect.end());

		tp += str;
		tp += " [";
		tp += std::to_string(it.second);
		tp += "]\n";

		printData += tp;
	}

	if (0 != printData.compare(""))
	{
		sngPrt->cls();
		sngPrt->cprintf(sngPrt->COLOR_GREEN, printData.c_str());
	}
}


CConsoleLoggerEx* IntHistogram::getInstance(bool& checkStat)
{
	checkStat = false;
	if (coloured_console2 == NULL)
	{
		// To make thread safe 
		if (coloured_console2 == NULL)
		{
			IntHistogram::coloured_console2 = new CConsoleLoggerEx();
			checkStat = true;
		}
		//}
	}

	return (CConsoleLoggerEx*)coloured_console2;
}

bool IntHistogram::clearConsoleMemory(void)
{
	delete coloured_console2;
	return true;
}


IntHistogram::IntHistogram(int iPx) : maxStepHist(0), iPixel(iPx) {
	//if (coloured_console2 == NULL)
	//{
	//	coloured_console2 = new CConsoleLoggerEx();
	//	coloured_console2->Create("");
	//}
};


IntHistogram::~IntHistogram() {};


bool IntHistogram::openNewConsoleWindow(string strWindow) {
	bool bStat = false;
	CConsoleLoggerEx* sngPrt = getInstance(bStat);
	if (bStat)
		sngPrt->Create(strWindow.c_str());

	return true;
}


bool IntHistogram::closeConsoleWindow(void) {
	bool bStat = false;
	CConsoleLoggerEx* sngPrt = getInstance(bStat);

	sngPrt->Close();

	clearConsoleMemory();
	return true;
}

/**
 * ------------------------------------------------------------
 * <summary>
 *  Increment the value of the Int key with single step
 * </summary>
 * ------------------------------------------------------------*/
bool IntHistogram::updIntHitogramData(int key) {
	std::map<unsigned int, int>::iterator it = mapIntHistData.find(key);
	if (it != mapIntHistData.end())
	{
		it->second += 1;
		if (maxStepHist < it->second)
			maxStepHist = it->second;
	}
	else
	{
		mapIntHistData.insert(pair<int, int>(key, 1));
		if (maxStepHist < 1)
			maxStepHist = 1;
	}

	return true;
}

/**
 * ------------------------------------------------------------
 * <summary>
 *  Increment the value of the Int key with batch input "data"
 * </summary>
 * ------------------------------------------------------------*/
bool IntHistogram::updIntHitogramDataBatch(int key, int data) {
	std::map<unsigned int, int>::iterator it = mapIntHistData.find(key);
	if (it != mapIntHistData.end())
	{
		it->second = data;
		if (maxStepHist < data)
			maxStepHist = it->second;
	}
	else
	{
		mapIntHistData.insert(pair<int, int>(key, data));
		if (maxStepHist < data)
			maxStepHist = data;
	}

	return true;
}

void IntHistogram::printHistogram(void)
{
	bool bStat = false;
	CConsoleLoggerEx* sngPrt = getInstance(bStat);

	double stepHist = iPixel;

	string printData("");
	for (auto it : mapIntHistData)
	{
		if (it.second >= 3)
		{
			char arr[LABLES_MAX_SIZE] = { 0 };
			std::string strConvert = to_string(it.first);
			memset(arr, ' ', sizeof(arr) / sizeof(char) - 1);
			memcpy(arr, strConvert.c_str(), strConvert.size());
			string tp(arr);
			tp += " | ";

			int iResolution = (it.second / (int)stepHist < HISTOGRAM_RESOLUTION) ? (it.second / (int)stepHist) : HISTOGRAM_RESOLUTION;
			vector<int> vect(iResolution, DRAW_SYMBOL_CODE);
			string str(vect.begin(), vect.end());

			tp += str;
			tp += " [";
			tp += std::to_string(it.second);
			tp += "]\n";

			printData += tp;
		}
	}

	if (0 != printData.compare(""))
	{
		sngPrt->cls();
		sngPrt->cprintf(sngPrt->COLOR_GREEN, printData.c_str());
	}
}

