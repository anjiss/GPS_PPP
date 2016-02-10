#pragma once
#include "MathBase.h"
#include "SatPosition.h"

class Epochs//一个精密星历历元的数据
{
public:
	Epochs(int n)
	{
		Sat_XYZ= new SatPosition *[n];
	}
//	~Epochs();
public:
	int Year_Start;
	int Month_Start;
	int Day_of_Month_St;
	int Hour_Start;
	int Minute_Start;
	double Second_Start;
	time_gpst time_gps;
	SatPosition **Sat_XYZ;
};

class Observation_Data
{
public:
	double C1,L1,L2,P1,P2,n1,n2,n_delta;
	int num11,num12,num21,num22,num31,num32,num41,num42,num51,num52;
};

class Epochs_ob_node
{
public:
	Epochs_ob_node(int num)
	{
		number=num;
		data=new Observation_Data *[number];//一个历元的数据
		Sat_ID=new char*[number];
		for (int i=0;i<number;i++)
		{
			data[i]=new Observation_Data;
			Sat_ID[i]=new char[3];
		}
	}
public:
	time_common time_c;
	time_gpst time_g;
	int flag;//等于零时该历元可用
	int number;//观测到的卫星个数
	char **Sat_ID;//二维数组
	Observation_Data **data;
	Epochs_ob_node *next;
};

class Epochs_ob
{
public:
	Epochs_ob()
	{
		Epoch_Number=0;
		e_current=e_first;
	}
public:
	Epochs_ob_node *e_first;
	Epochs_ob_node *e_current;
	int Epoch_Number;

};