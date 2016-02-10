#pragma once
#include "Observation.h"
#include "SP3.h"
#include "MathBase.h"
#include "SatPosition.h"
#include "CLK.h"



class Equation_note//一个观测历元中某颗卫星构造方程所用的数据
{
public:
	time_gpst time_ob;//观测时间
	double X_r,Y_r,Z_r;//接收机坐标，待求值，未知
	double X_s,Y_s,Z_s;//卫星坐标，由精密卫星文件内插得到
	double X_v,Y_v,Z_v;//卫星速度，由精密卫星文件内插得到
	double x_approx,y_approx,z_approx;//接收机近似坐标，起算数据，由o文件得到
	double L1,L2,P1,P2;//该时刻的观测数据
	double dt;//接收机钟差
	double dT;//卫星钟差
	double atmos;//大气延迟误差
	double Trop_M_w,Trop_M_d;//映射函数
	double Trop_tzd_w,Trop_tzd_d;//延迟分量

	Equation_note *next;
};

class Equation_epoch//一个历元组成方程所用到的所有数据
{
public:
	Equation_note *data;
	Equation_epoch *next;//下个历元的数据
	int num;//这个历元共有多少可用卫星
};

class Equation_epochs//一个o文件对应的所有方程组
{
public:
	Equation_epoch *datas;
	int num_epoch;
};

class Equation_database
{
public:
	Equation_database(){};
	Equation_database(Observation obsev,SP3 sp3,SP3 sp3_1,SP3 sp3_3,CLK clk2,CLK clk1,CLK clk3);
	~Equation_database();
	SatPosition Insert_Lagrange(time_gpst t,char *sat_id);
	double Insert_dT(time_gpst t,char *sat_id);
	Equation_epochs D;
	Observation O2;
	SP3 Sp3,Sp3_1,Sp3_3;
	CLK clk;
	int number_of_equations;
};