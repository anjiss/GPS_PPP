#include "stdafx.h"
#include "ErrorCrct.h"
#include "MathBase.h"
#include <cmath>


void Saastamoinen(double P,double e,double B,double H,double T,double &D,double &W)
{
	double f=1-0.00266*cos(2*B)-0.00028*H;
	double d=0.002277*P/f;
	double w=(0.002277*e/f)*(1225/T+0.05);
	D=d;
	W=w;
}

void Niell(double x,double y,double z,double doy,double E,double &D,double &W)
{
	double a_havg15=1.2769934*pow(10.0,-3);
	double a_havg30=1.2686230*pow(10.0,-3);
	double a_havg45=1.2465397*pow(10.0,-3);
	double a_havg60=1.2196049*pow(10.0,-3);
	double a_havg75=1.2045996*pow(10.0,-3);
	double ahavg15=0;
	double ahavg30=1.2709626*pow(10.0,-5);
	double ahavg45=2.6523662*pow(10.0,-5);
	double ahavg60=3.2000452*pow(10.0,-5);
	double ahavg75=4.1202191*pow(10.0,-5);
	double b_havg15=2.9153695*pow(10.0,-3);
	double b_havg30=2.9152299*pow(10.0,-3);
	double b_havg45=2.9288445*pow(10.0,-3);
	double b_havg60=2.9022565*pow(10.0,-3);
	double b_havg75=2.9024912*pow(10.0,-3);
	double bhavg15=0;
	double bhavg30=2.1414979*pow(10.0,-5);
	double bhavg45=3.0160779*pow(10.0,-5);
	double bhavg60=7.2562722*pow(10.0,-5);
	double bhavg75=11.723375*pow(10.0,-5);
	double c_havg15=62.61050*pow(10.0,-3);
	double c_havg30=62.837393*pow(10.0,-3);
	double c_havg45=63.721774*pow(10.0,-3);
	double c_havg60=63.824265*pow(10.0,-3);
	double c_havg75=64.258455*pow(10.0,-3);
	double chavg15=0;
	double chavg30=9.0128400*pow(10.0,-5);
	double chavg45=4.3497037*pow(10.0,-5);
	double chavg60=84.795348*pow(10.0,-5);
	double chavg75=170.37206*pow(10.0,-5);
	double aw15=5.8021879*pow(10.0,-1);
	double aw30=5.6794847*pow(10.0,-1);
	double aw45=5.8118019*pow(10.0,-1);
	double aw60=5.9727542*pow(10.0,-1);
	double aw75=6.1641693*pow(10.0,-1);
	double bw15=1.4275268*pow(10.0,-1);
	double bw30=1.5138625*pow(10.0,-1);
	double bw45=1.457252*pow(10.0,-1);
	double bw60=1.5007428*pow(10.0,-1);
	double bw75=1.7599082*pow(10.0,-1);
	double cw15=4.3472961*pow(10.0,-1);
	double cw30=4.6729510*pow(10.0,-1);
	double cw45=4.3908931*pow(10.0,-1);
	double cw60=4.4626982*pow(10.0,-1);
	double cw75=5.4736038*pow(10.0,-1);
	
	double a_h=2.53*pow(10.0,-5);
	double b_h=5.49*pow(10.0,-3);
	double c_h=1.14*pow(10.0,-3);

	double p_l,p_b,p_h;//测站的大地坐标,l代表纬度
	ITRF2GEO(x,y,z,p_l,p_b,p_h);
	
	double a_havg,ahavg,aw,b_havg,bhavg,bw,c_havg,chavg,cw;

	if (p_l<15 || p_l==15)
	{
		a_havg=a_havg15;
		ahavg=ahavg15;
		aw=aw15;
		b_havg=b_havg15;
		bhavg=bhavg15;
		bw=bw15;
		c_havg=c_havg15;
		chavg=chavg15;
		cw=cw15;
	}
	else if ((p_l>15 && p_l<30) || p_l==30 )
	{
		double m=p_l-15;
		a_havg=a_havg15+m*(a_havg30-a_havg15)/15;
		ahavg=ahavg15+m*(ahavg30-ahavg15)/15;
		aw=aw15+m*(aw30-aw15)/15;
		b_havg=b_havg15+m*(b_havg30-b_havg15)/15;
		bhavg=bhavg15+m*(bhavg30-bhavg15)/15;
		bw=bw15+m*(bw30-bw15)/15;
		c_havg=c_havg15+m*(c_havg30-c_havg15)/15;
		chavg=chavg15+m*(chavg30-chavg15)/15;
		cw=cw15+m*(cw30-cw15)/15;
	}
	else if ((p_l>30 && p_l<45) || p_l==45 )
	{
		double m=p_l-30;
		a_havg=a_havg30+m*(a_havg45-a_havg30)/15;
		ahavg=ahavg30+m*(ahavg45-ahavg30)/15;
		aw=aw30+m*(aw45-aw30)/15;
		b_havg=b_havg30+m*(b_havg45-b_havg30)/15;
		bhavg=bhavg30+m*(bhavg45-bhavg30)/15;
		bw=bw30+m*(bw45-bw30)/15;
		c_havg=c_havg30+m*(c_havg45-c_havg30)/15;
		chavg=chavg30+m*(chavg45-chavg30)/15;
		cw=cw30+m*(cw45-cw30)/15;
	}
	else if ((p_l>45 && p_l<60) || p_l==60 )
	{
		double m=p_l-45;
		a_havg=a_havg45+m*(a_havg60-a_havg45)/15;
		ahavg=ahavg45+m*(ahavg60-ahavg45)/15;
		aw=aw45+m*(aw60-aw45)/15;
		b_havg=b_havg45+m*(b_havg60-b_havg45)/15;
		bhavg=bhavg45+m*(bhavg60-bhavg45)/15;
		bw=bw45+m*(bw60-bw45)/15;
		c_havg=c_havg45+m*(c_havg60-c_havg45)/15;
		chavg=chavg45+m*(chavg60-chavg45)/15;
		cw=cw45+m*(cw60-cw45)/15;
	}
	else if ((p_l>60 && p_l<75) || p_l==75 )
	{
		double m=p_l-60;
		a_havg=a_havg60+m*(a_havg75-a_havg60)/15;
		ahavg=ahavg60+m*(ahavg75-ahavg60)/15;
		aw=aw60+m*(aw75-aw60)/15;
		b_havg=b_havg60+m*(b_havg75-b_havg60)/15;
		bhavg=bhavg60+m*(bhavg75-bhavg60)/15;
		bw=bw60+m*(bw75-bw60)/15;
		c_havg=c_havg60+m*(c_havg75-c_havg60)/15;
		chavg=chavg60+m*(chavg75-chavg60)/15;
		cw=cw60+m*(cw75-cw60)/15;
	}
	else
	{
		a_havg=a_havg75;
		ahavg=ahavg75;
		aw=aw75;
		b_havg=b_havg75;
		bhavg=bhavg75;
		bw=bw75;
		c_havg=c_havg75;
		chavg=chavg75;
		cw=cw75;
	}
	double ah=a_havg+ahavg*cos((doy-28)/365.25);
	double bh=b_havg+bhavg*cos((doy-28)/365.25);
	double ch=c_havg+chavg*cos((doy-28)/365.25);
	double sinE=sin(E);
	double md1=(1+ah/(1+bh/(1+ch)))/(sinE+ah/(sinE+bh/(sinE+ch)));
	double md2=p_h*((1/sinE) - (1+a_h/(1+b_h/(1+c_h)))/(sinE+a_h/(sinE+b_h/(sinE+c_h))));
	double md=md1+md2;//干分量
	double mw=(1+aw/(1+bw/(1+cw)))/(sinE+aw/(sinE+bw/(sinE+cw)));//湿分量
	D=md;
	W=mw;
}

double Trop(int slt1, int slt2,double x_s,double y_s,double z_s,double x_r,double y_r,double z_r,double doy,double &trop_M_w,double &trop_tzd_w,double &trop_M_d,double &trop_tzd_d)
{
	double p_wet,p_dry,M_wet,M_dry;
	if (slt1==1)//干湿分量,调用撒斯塔贝宁
	{
		double E=2.718281828459045;//自然常数
		double t=15;//干温
		t=t+273.15;//绝对温度
		double p=1013.25;
		double RH=0.5;
		double temp=-37.2465+0.213166*t-0.000256908*t*t;
		double e=RH*pow(E,temp);
		double b,h;
		ITRF2GEO(x_r,y_r,z_r,temp,b,h);
		h=h/1000;//萨模型的高程单位是KM
		Saastamoinen(p,e,b,h,t,p_dry,p_wet);
	}
	else if (slt1==2)
	{
	}
	else
	{
	}
	if (slt2==1)//映射函数
	{
		double E,temp;
		double l_r,b_r,h_r;
		ITRF2GEO(x_r,y_r,z_r,l_r,b_r,h_r);
		Get_E_A(x_s,y_s,z_s,x_r,y_r,z_r,b_r,l_r,h_r,E,temp);
		Niell(x_r,y_r,z_r,doy,E,M_dry,M_wet);
	}
	else if (slt2==2)
	{
	}
	else
	{
	}
	trop_M_d=M_dry;
	trop_M_w=M_wet;
	trop_tzd_d=p_dry;
	trop_tzd_w=p_wet;
	double re=p_wet*M_wet + p_dry*M_dry;
	return re;
}