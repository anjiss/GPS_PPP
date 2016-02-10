#include "StdAfx.h"
#include "Adjustment_PPP.h"
#include "Matrix.h"
#include "Equation_database.h"
#include <cmath>
#include "Mathbase.h"
#include <iostream>
#include <iomanip>
using namespace std;

Adjustment_PPP::Adjustment_PPP(Equation_database a)
{
	ofstream outposition("resault.txt");
	ppp=a;
	Equation_note *current_nd;
	Equation_epoch *current_ep;
	current_ep=ppp.D.datas;
	cout<<a.D.num_epoch;

	double xxx=0;
	double yyy=0;
	double zzz=0;
	double ttt=0;
	
	double w_eth=7.2921151467E-5;
	double C_lit=299792458.0;
	double f1=1575.42E6;
	double f2=1227.60E6;
	double f1_2=pow(f1,2);
	double f2_2=pow(f2,2);
	double lamda1=C_lit/f1;
	double lamda2=C_lit/f2;
	double f=(f1_2*f1-f2_2*f2)/(f1_2-f2_2);
	double lamda=C_lit/f;


	int checknum=0;

	double ave_x=0;
	double ave_y=0;
	double ave_z=0;
	double ave_num=0;

	while (checknum<ppp.D.num_epoch-1)
	{
		int n=current_ep->num;
		Matrix A(2*n,4+n);//文献中的B
		Matrix P(2*n,2*n);
		Matrix C(2*n,2*n);//C是P的逆
		Matrix l(2*n,1);//文献中的f
		Matrix delta_x_last(4+n,1);

		double *N_if=new double[n];
		for (int i_n=0;i_n<n;i_n++)
		{
			N_if[i_n]=1;
		}

		
		double re_delta;

		for (int iii=0;iii<3;iii++)
		{
			current_nd=current_ep->data;
			for (int i=0;i<n;i++)//行赋值
			{
				double p0=sqrt( pow(current_nd->X_s-current_ep->data->X_r,2) + pow(current_nd->Y_s-current_ep->data->Y_r,2) + pow(current_nd->Z_s-current_ep->data->Z_r,2) );
				double p0_delta=((current_nd->X_s-current_ep->data->X_r)*current_nd->Y_s - (current_nd->Y_s-current_ep->data->Y_r)*current_nd->X_s)*w_eth/C_lit;//地球自转改正	
				p0=p0+p0_delta;

				double p_relativity=-2*(current_nd->X_s*current_nd->X_v + current_nd->Y_s*current_nd->Y_v + current_nd->Z_s*current_nd->Z_v)/C_lit;
				p0=p0-p_relativity;

				A.data[i][0]=(current_ep->data->X_r - current_nd->X_s)/p0;
				A.data[i][1]=(current_ep->data->Y_r - current_nd->Y_s)/p0;
				A.data[i][2]=(current_ep->data->Z_r - current_nd->Z_s)/p0;
				A.data[i][3]=-1;

				A.data[i+n][0]=(current_ep->data->X_r - current_nd->X_s)/p0;
				A.data[i+n][1]=(current_ep->data->Y_r - current_nd->Y_s)/p0;
				A.data[i+n][2]=(current_ep->data->Z_r - current_nd->Z_s)/p0;
				A.data[i+n][3]=-1;

				A.data[i+n][4+i]=1;

				double L_if=(f1_2*current_nd->L1 - f2_2*current_nd->L2)/(f1_2-f2_2);
				double P_if=(f1_2*current_nd->P1 - f2_2*current_nd->P2)/(f1_2-f2_2);
				l.data[i][0]=P_if-p0 + current_nd->atmos + ttt + current_nd->dT*C_lit;
				l.data[i+n][0]=L_if*lamda-p0 + current_nd->atmos + ttt + current_nd->dT*C_lit;
				
				//l.data[i][0]=l.data[i][0]/100.0;
				//l.data[i+n][0]=l.data[i+n][0]/100.0;
				
				double elev,temp;
				double b_temp,l_temp,h_temp;
				ITRF2GEO(current_nd->X_r,current_nd->Y_r,current_nd->Z_r,l_temp,b_temp,h_temp);
				Get_E_A(current_nd->X_s,current_nd->Y_s,current_nd->Z_s,current_nd->X_r,current_nd->Y_r,current_nd->Z_r,b_temp,l_temp,h_temp,elev,temp);

				C.data[i][i]=1/pow(sin(elev),2);//分子的单位是cm
				C.data[i+n][i+n]=1/pow(sin(elev),2);//分子的单位是m

				current_nd=current_nd->next;

			}
			P=C.Inverse_P();
			Matrix N=A.Transpose()*P*A;
			delta_x_last=N.Inverse()*A.Transpose()*P*l;

			Matrix V=A*delta_x_last-l;
			Matrix delta=V.Transpose()*P*V;
			re_delta=delta.data[0][0]/(2*n-(n+4));
			re_delta=sqrt(re_delta);

			xxx=delta_x_last.data[0][0];
			yyy=delta_x_last.data[1][0];
			zzz=delta_x_last.data[2][0];
			ttt=delta_x_last.data[3][0];
			for (int i_n=0;i_n<n;i_n++)
			{
				N_if[i_n]=delta_x_last.data[4+i_n][0];
			}
			current_ep->data->X_r=current_ep->data->X_r+xxx;
			current_ep->data->Y_r=current_ep->data->Y_r+yyy;
			current_ep->data->Z_r=current_ep->data->Z_r+zzz;
			cout<<re_delta<<endl;
		}
		outposition<<"第"<<setw(4)<<checknum<<"历元计算结果：";
		outposition<<setw(20)<<setprecision(12)<<current_ep->data->X_r;
		outposition<<setw(20)<<setprecision(12)<<current_ep->data->Y_r;
		outposition<<setw(20)<<setprecision(12)<<current_ep->data->Z_r<<endl;

		ave_x=ave_x+current_ep->data->X_r;
		ave_y=ave_y+current_ep->data->Y_r;
		ave_z=ave_z+current_ep->data->Z_r;
		
		current_ep=current_ep->next;
		current_nd=current_ep->data;
		checknum++;
		
	}
	cout<<"改正坐标"<<endl;
	cout<<setprecision(20)<<ave_x/checknum<<endl;
	cout<<setprecision(20)<<ave_y/checknum<<endl;
	cout<<setprecision(20)<<ave_z/checknum<<endl;

}

Adjustment_PPP::~Adjustment_PPP()
{
}
