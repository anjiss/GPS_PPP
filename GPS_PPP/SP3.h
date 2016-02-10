#pragma once
#include <fstream>
#include "SatPosition.h"
#include "Epochs.h"
using namespace std;


class SP3
{
public:
	SP3(ifstream &indata);
	SP3();
	~SP3();
public:
	//-------------------------------Line 1
	char *Version_Symbol;
	char *P_or_V_Flag;
	int Year_Start;
	int Month_Start;
	int Day_of_Month;
	int Hour_Start;
	int Minute_Start;
	double Second_Start;
	int Number_of_Epochs;
	char *Data_Used;
	char *Coordinate_Sys;
	char *Orbit_Type;
	char *Agency;
	//-------------------------------Line 2
	char *Symbols;
	int GPS_Week;
	double Seconds_of_Week;
	double Epoch_Interval;
	int Mod_Jul_Day_St;
	double Fractional_Day;
	//-------------------------------Line 3
	int Number_of_Sats;
	SatPosition **SatAccuracy;//保存所有卫星的标号和精度
	Epochs **epochs;

};

