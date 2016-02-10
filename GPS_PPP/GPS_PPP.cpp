// GPS_PPP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

#include "SP3.h"
#include "Observation.h"
#include "MathBase.h"
#include "Equation_database.h"
#include "ErrorCrct.h"
#include "Adjustment_PPP.h"
#include "CLK.h"


using namespace std;

void main()
{
	ifstream get_SP3_2("igs17212.sp3");
	ifstream get_SP3_1("igs17211.sp3");
	ifstream get_SP3_3("igs17213.sp3");
	ifstream get_CLK_2("igr17212.clk");
	ifstream get_CLK_1("igr17211.clk");
	ifstream get_CLK_3("igr17213.clk");
	ifstream get_O("aira0010.13o");
	SP3 check_3_2(get_SP3_2);
	SP3 check_3_1(get_SP3_1);
	SP3 check_3_3(get_SP3_3);
	cout<<"精密星历文件读取完毕！"<<endl;
	CLK clk_2(get_CLK_2);
	CLK clk_1(get_CLK_1);
	CLK clk_3(get_CLK_3);
	cout<<"精密钟差文件读取完毕！"<<endl;
	Observation check2(get_O);
	cout<<"观测文件读取完毕！"<<endl;
//	check2.Zhoutiao();
	Equation_database check3(check2,check_3_2,check_3_1,check_3_3,clk_2,clk_1,clk_3);
	cout<<"等式组数据库建立完毕！开始解算："<<endl;
	Adjustment_PPP final_ajs(check3);
	cout<<"解算完毕！"<<endl;
	//double x_s=10209866.1217;
	//double y_s=11050900.4087;
	//double z_s=21749534.5343;
	//double x_r=-2267747.5544;
	//double y_r=5009153.6120;
	//double z_r=3221290.4722;

	//double b,l,h,elev,azi;
	//ITRF2GEO(x_r,y_r,z_r,l,b,h);
	//Get_E_A(x_s,y_s,z_s,x_r,y_r,z_r,b,l,h,elev,azi);
	//cout<<elev*180/3.1415926535897932384626433;
//	cout<<check3.number_of_equations//测试用
		
}


