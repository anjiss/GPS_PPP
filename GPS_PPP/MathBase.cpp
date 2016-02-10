#include "stdafx.h"

#include "MathBase.h"
#include <cmath>

double Convert_Cm2Jd(time_common cm)
{
	int y,m,int1,int2;
	double JD,UT;
	if (cm.month_cm > 2)
	{
		y=cm.year_cm;
		m=cm.month_cm;
	} 
	else
	{
		y=cm.year_cm-1;
		m=cm.month_cm+12;
	}
	int1=int(365.25*y);
	int2=int(30.6001*(m+1));
	UT=(double)cm.hour_cm+(double)cm.minte_cm/60+(double)cm.second_cm/3600;
	JD=int1+int2+cm.day_cm+UT/24+1720981.5;

	return JD;
}

time_gpst Convert_Jd2Gpst(double JD)
{
	time_gpst gpst;
	gpst.week_gps=int((JD-2444244.5)/7);
	gpst.fract=(double)(JD-2444244.5)/7-gpst.week_gps;
	return gpst;
}

void  Get_E_A(double x_s,double y_s,double z_s,double x_r,double y_r,double z_r,double b_r,double l_r,double h_r,double &elev,double &azi)
{
	double DeltaX,DeltaY,DeltaZ;
	double siteN,siteE,siteU;


	DeltaX=x_s - x_r;
	DeltaY=y_s - y_r;
	DeltaZ=z_s - z_r;

	siteN = - sin(b_r)*cos(l_r)*DeltaX
		- sin(b_r)*sin(l_r)*DeltaY
		+ cos(b_r)*DeltaZ;
	siteE = - sin(l_r)*DeltaX + cos(l_r)*DeltaY;
	siteU =   cos(b_r)*cos(l_r)*DeltaX
		+ cos(b_r)*sin(l_r)*DeltaY
		+ sin(b_r)*DeltaZ;

	azi = Get_atan(siteE,siteN);
	elev =atan( siteU / sqrt(siteN * siteN + siteE * siteE) );

}
double Get_atan(double z,double y)
{
	double x;
	double PI=3.1415926535897932384626433;
	if (fabs(z)<pow(1.0,-10)) x=PI/2;
	else
	{
		if (fabs(y)<pow(1.0,-10)) x=PI;
		else
		{
			x=atan(fabs(y/z));
			if ((y>0)&&(z<0)) x=PI-x;
			else if ((y<0)&&(z<0)) x=PI+x;
			else if((y<0)&&(z>0)) x=2*PI-x;
		}
	}

	return x;
}

void ITRF2GEO(double x,double y,double z,double &l,double &b,double &h)
{
	double e2=0.00669437999013;
	double a=6378137;

	double L,B,H,t,W,N,R;
	R=sqrt(x*x + y*y + z*z);
	t=atan(z/(sqrt(x*x + y*y)));

	L=atan(y/x);//第一次迭代
	if (x<0 && y>0)
		L+=(3.1415926535897932384626433/2);
	if (x<0 && y<0)
		L-=(3.1415926535897932384626433/2);
	B=0;
	W=sqrt(1-e2*sin(B)*sin(B));
	B=atan(tan(t)*(1+a*(e2/z)*(sin(B)/W)));
	H=0;

	for (int i=0;i<10;i++)//多次迭代
	{
		W=sqrt(1-e2*sin(B)*sin(B));
		N=a/W;
		B=atan(tan(t)*(1+a*(e2/z)*(sin(B)/W)));
		H=R*cos(t)/cos(B)-N;
	}
	l=L;
	b=B;
	h=H;
}