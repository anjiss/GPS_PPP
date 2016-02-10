#pragma once
#include "MathBase.h"
#include <fstream>
using namespace std;

class Clk_node_nd
{
public:
	time_gpst time_g;//时间
	char *id;
	double dT;//对应卫星的钟差
	Clk_node_nd *next;
};
class Clk_node
{
public:

	Clk_node_nd *gps_data;
	int num_s;//总共有多少卫星
	Clk_node *next;
	Clk_node *last;
};

class CLK
{
public:
	CLK();
	CLK(ifstream &indata);
	CLK CLK_add(CLK clk1,CLK clk2,CLK clk3);
	~CLK();
public:
	Clk_node *data;
	int num;//总共有多少个node
};
