#pragma once
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iomanip>
#include <iostream>
#include <string>
#include <any>
#include <utility>

#include "ConsoleLogger.h"

using namespace std;

#define		HISTOGRAM_PIXEL			5
#define		HISTOGRAM_RESOLUTION	60
#define		DRAW_SYMBOL_CODE		219
#define		LABLES_MAX_SIZE			16


//class Histogram
//{
//public:
//	Histogram() {};
//	virtual ~Histogram() {};
//protected:
//	static map<std::string, int> mapStrHistData;
//	static map<int, int> mapIntHistData;
//};

class StrHistogram

{
private:
	int maxStepHist;
	int iPixel;
	static map<std::string, int> mapStrHistData;
	volatile static CConsoleLoggerEx* coloured_console1;
	static CConsoleLoggerEx* getInstance(bool& checkStat)
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

	static bool clearConsoleMemory(void)
	{
		delete coloured_console1;
		return true;
	}

public:
	StrHistogram(int iPx = HISTOGRAM_PIXEL) : maxStepHist(0), iPixel(iPx) {
		/*if (coloured_console1 == NULL)
		{

			coloured_console1 = new CConsoleLoggerEx();
		}
		*/
	};
	~StrHistogram() {};

	bool openNewConsoleWindow(string strWindow) {
		bool bStat = false;
		CConsoleLoggerEx* sngPrt = getInstance(bStat);
		if (bStat)
			sngPrt->Create(strWindow.c_str());

		return true;
	}


	bool closeConsoleWindow(void) {
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
	bool updStrHitogramData(std::string key) {

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
	bool updStrHitogramDataBatch(std::string key, int data) {


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

	void printHistogram(void)
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
};

class IntHistogram
{
private:
	int maxStepHist;
	int iPixel;
	static map<unsigned int, int> mapIntHistData;
	volatile static CConsoleLoggerEx* coloured_console2;
	static CConsoleLoggerEx* getInstance(bool& checkStat)
	{
		checkStat = false;
		if (coloured_console2 == NULL)
		{
			// To make thread safe 
			if (coloured_console2 == NULL)
			{
				coloured_console2 = new CConsoleLoggerEx();
				checkStat = true;
			}
			//}
		}

		return (CConsoleLoggerEx*)coloured_console2;
	}

	static bool clearConsoleMemory(void)
	{
		delete coloured_console2;
		return true;
	}

public:
	IntHistogram(int iPx = HISTOGRAM_PIXEL) : maxStepHist(0), iPixel(iPx){
		//if (coloured_console2 == NULL)
		//{
		//	coloured_console2 = new CConsoleLoggerEx();
		//	coloured_console2->Create("");
		//}
	};


	~IntHistogram() {};


	bool openNewConsoleWindow(string strWindow) {
		bool bStat = false;
		CConsoleLoggerEx* sngPrt = getInstance(bStat);
		if(bStat)
			sngPrt->Create(strWindow.c_str());

		return true;
	}


	bool closeConsoleWindow(void) {
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
	bool updIntHitogramData(int key) {
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
	bool updIntHitogramDataBatch(int key, int data) {
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

	void printHistogram(void)
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
};

