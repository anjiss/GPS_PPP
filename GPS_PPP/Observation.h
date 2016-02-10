#pragma once
#include <fstream>
#include "MathBase.h"
#include "Epochs.h"
using namespace std;

class Hu_node
{
public:
	double RMS;
	double b_delta_avg;
	char *id;
	time_gpst time_g;
	Hu_node *next;
};

class Hu
{
public:
	int num;//该弧段中共有多少历元
	Hu_node *datas;
	Hu *next;//下一段弧
};

class HuZong
{
public:
	int num_hu;//总共有多少弧段
	Hu *datas;
};

class Observation
{
public:
	Observation(ifstream &indata);
	Observation();
	void Zhoutiao();
	~Observation();
public:
	double x_approx,y_approx,z_approx;//14
	double antenna_h;//14
	double interval;//10
	Epochs_ob data;
	HuZong data_n;
};

