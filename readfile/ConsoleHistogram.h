#pragma once
#include <string>
#include <map>

class CConsoleLoggerEx;

#define		HISTOGRAM_PIXEL			5
#define		HISTOGRAM_RESOLUTION	60
#define		DRAW_SYMBOL_CODE		219
#define		LABLES_MAX_SIZE			16

class StrHistogram
{
private:
	int maxStepHist;
	int iPixel;
	static std::map<std::string, int> mapStrHistData;


public:
	volatile static CConsoleLoggerEx* coloured_console1;

	static CConsoleLoggerEx* getInstance(bool& checkStat);
	static bool clearConsoleMemory(void);

	StrHistogram(int iPx = HISTOGRAM_PIXEL);
	~StrHistogram();

	bool openNewConsoleWindow(std::string strWindow);
	bool closeConsoleWindow(void);

	/**
	 * ------------------------------------------------------------
	 * <summary>
	 *  Increment the value of the String key with single step
	 * </summary>
	 * ------------------------------------------------------------*/
	bool updStrHitogramData(std::string key);

	/**
	 * ------------------------------------------------------------
	 * <summary>
	 *  Increment the value of the String key with batch input "data"
	 * </summary>
	 * ------------------------------------------------------------*/
	bool updStrHitogramDataBatch(std::string key, int data);
	void printHistogram(void);
};

class IntHistogram
{
private:
	int maxStepHist;
	int iPixel;
	static std::map<unsigned int, int> mapIntHistData;

public:
	volatile static CConsoleLoggerEx* coloured_console2;
	static CConsoleLoggerEx* getInstance(bool& checkStat);
	static bool clearConsoleMemory(void);

	IntHistogram(int iPx = HISTOGRAM_PIXEL);
	~IntHistogram();


	bool openNewConsoleWindow(std::string strWindow);
	bool closeConsoleWindow(void);

	/**
	 * ------------------------------------------------------------
	 * <summary>
	 *  Increment the value of the Int key with single step
	 * </summary>
	 * ------------------------------------------------------------*/
	bool updIntHitogramData(int key);

	/**
	 * ------------------------------------------------------------
	 * <summary>
	 *  Increment the value of the Int key with batch input "data"
	 * </summary>
	 * ------------------------------------------------------------*/
	bool updIntHitogramDataBatch(int key, int data);
	void printHistogram(void);
};

