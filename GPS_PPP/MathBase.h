#pragma once

struct time_common
{
	int year_cm;
	int month_cm;
	int day_cm;
	int hour_cm;
	int minte_cm;
	double second_cm;
};

struct time_gpst
{
	int week_gps;
	double fract;
};

double Convert_Cm2Jd(time_common cm);
time_gpst Convert_Jd2Gpst(double JD);

void  Get_E_A(double x_s,double y_s,double z_s,double x_r,double y_r,double z_r,double b_r,double l_r,double h_r,double &elev,double &azi);
double Get_atan(double z,double y);
void ITRF2GEO(double x,double y,double z,double &L,double &B,double &H);//笛卡尔坐标系转换大地坐标系