#include "StdAfx.h"
#include "Observation.h"
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;


Observation::Observation(){}
Observation::Observation(ifstream &indata)
{
	char data_in_line[256];
	char *end="END OF HEADER";
	bool end_bool=1;

	char *X_appr=new char[14];
	char *Y_appr=new char[14];
	char *Z_appr=new char[14];
	char *antenna_high=new char[14];
	char *interv=new char[10];

	while (end_bool)
	{
		indata.getline(data_in_line,255);
		if (strstr(data_in_line,end))
			end_bool=0;

		if (strstr(data_in_line,"APPROX POSITION"))
		{
			sscanf(data_in_line,"%s%s%s",X_appr,Y_appr,Z_appr);
			x_approx=atof(X_appr);
			y_approx=atof(Y_appr);
			z_approx=atof(Z_appr);
		}
		if (strstr(data_in_line,"ANTENNA"))
		{
			sscanf(data_in_line,"%s",antenna_high);
			antenna_h=atof(antenna_high);
		}
		if (strstr(data_in_line,"INTERVAL"))
		{
			sscanf(data_in_line,"%s",interv);
			interval=atof(interv);
		}
	}
	
	indata.getline(data_in_line,255);
	while (strlen(data_in_line)>1)//读取每个历元
	{
		char *t1=new char[40],*t2=new char[40],*t3=new char[40],*t4=new char[40],*t5=new char[40],*t6=new char[40],*t7=new char[40],*t8=new char[40],*t9=new char[40],*t10=new char[40];
		sscanf(data_in_line,"%s%s%s%s%s%s%s%s",t1,t2,t3,t4,t5,t6,t7,t8);//历元头文件
		char *number_c=new char[2];//观测到的卫星个数
		number_c[0]=t8[0];
		number_c[1]=t8[1];
		number_c[2]='\0';
		int number_i=atoi(number_c);//观测到的卫星个数
		
		Epochs_ob_node *temp=new Epochs_ob_node(number_i);
		temp->time_c.year_cm=atoi(t1)+2000;
		temp->time_c.month_cm=atoi(t2);
		temp->time_c.day_cm=atoi(t3);
		temp->time_c.hour_cm=atoi(t4);
		temp->time_c.minte_cm=atoi(t5);
		temp->time_c.second_cm=atof(t6);
		temp->flag=atoi(t7);
		if (number_i<13)
		{
			for (int i=0;i<number_i;i++)
			{
				temp->Sat_ID[i][0]=t8[i*3+2];
				temp->Sat_ID[i][1]=t8[i*3+1+2];
				temp->Sat_ID[i][2]=t8[i*3+2+2];
				temp->Sat_ID[i][3]='\0';
			}
		} 
		else
		{
			for (int i=0;i<12;i++)
			{
				temp->Sat_ID[i][0]=t8[i*3+2];
				temp->Sat_ID[i][1]=t8[i*3+1+2];
				temp->Sat_ID[i][2]=t8[i*3+2+2];
				temp->Sat_ID[i][3]='\0';
			}
			indata.getline(data_in_line,255);//转行
			sscanf(data_in_line,"%s",t8);
			for (int i=12;i<number_i;i++)
			{
				temp->Sat_ID[i][0]=t8[(i-12)*3];
				temp->Sat_ID[i][1]=t8[(i-12)*3+1];
				temp->Sat_ID[i][2]=t8[(i-12)*3+2];
				temp->Sat_ID[i][3]='\0';
			}
		}
		temp->time_g=Convert_Jd2Gpst(Convert_Cm2Jd(temp->time_c));
		
		for (int i=0;i<number_i;i++)//读每个卫星的观测数据
		{
			indata.getline(data_in_line,255);
			char *get_numbers=new char[14];
			char *get_number1=new char[1];
			char *get_number2=new char[1];
			for (int j=0;j<14;j++)//-------------------------------------------------C1
			{
				get_numbers[j]=data_in_line[j];
			}
			get_numbers[14]='\0';
			get_number1[0]=data_in_line[14];
			get_number2[0]=data_in_line[15];
			get_number1[1]='\0';
			get_number2[1]='\0';
			temp->data[i]->L1=atof(get_numbers);
			temp->data[i]->num11=atoi(get_number1);
			temp->data[i]->num12=atoi(get_number2);

			for (int j=0;j<14;j++)//-------------------------------------------------L1
			{
				get_numbers[j]=data_in_line[j+16];
			}
			get_numbers[14]='\0';
			get_number1[0]=data_in_line[30];
			get_number2[0]=data_in_line[31];
			get_number1[1]='\0';
			get_number2[1]='\0';
			temp->data[i]->L2=atof(get_numbers);
			temp->data[i]->num21=atoi(get_number1);
			temp->data[i]->num22=atoi(get_number2);

			for (int j=0;j<14;j++)//-------------------------------------------------L2
			{
				get_numbers[j]=data_in_line[j+32];
			}
			get_numbers[14]='\0';
			get_number1[0]=data_in_line[46];
			get_number2[0]=data_in_line[47];
			get_number1[1]='\0';
			get_number2[1]='\0';
			temp->data[i]->C1=atof(get_numbers);
			temp->data[i]->num31=atoi(get_number1);
			temp->data[i]->num32=atoi(get_number2);

			for (int j=0;j<14;j++)//-------------------------------------------------P1
			{
				get_numbers[j]=data_in_line[j+48];
			}
			get_numbers[14]='\0';
			get_number1[0]=data_in_line[62];
			get_number2[0]=data_in_line[63];
			get_number1[1]='\0';
			get_number2[1]='\0';
			temp->data[i]->P1=atof(get_numbers);
			temp->data[i]->num41=atoi(get_number1);
			temp->data[i]->num42=atoi(get_number2);

			if (temp->data[i]->P1==0)
			{
				temp->data[i]->P1=temp->data[i]->C1;
			}

			for (int j=0;j<14;j++)//-------------------------------------------------P2
			{
				get_numbers[j]=data_in_line[j+64];
			}
			get_numbers[14]='\0';
			get_number1[0]=data_in_line[78];
			get_number2[0]=data_in_line[79];
			get_number1[1]='\0';
			get_number2[1]='\0';
			temp->data[i]->P2=atof(get_numbers);
			temp->data[i]->num51=atoi(get_number1);
			temp->data[i]->num52=atoi(get_number2);

			indata.getline(data_in_line,255);//跳过S1S2不读
		}


		if (data.Epoch_Number==0)
		{
			data.e_first=temp;
			data.Epoch_Number++;
			data.e_current=data.e_first;
		}
		else
		{
			data.e_current->next=temp;
			data.Epoch_Number++;
			data.e_current=data.e_current->next;
		}

		//----------------------------------------一个历元结束
		indata.getline(data_in_line,255);
	}
//	cout<<data.Epoch_Number;//--------------------------------------------------------------测试用
}

void Observation::Zhoutiao()
{
	for (int i=0;i<32;i++)//分别处理每个卫星的周跳
	{
		//----------------------------------------------开始计算将要处理的卫星的编号
		int ii=i+1;
		char *num_temp=new char[3];
		itoa(ii,num_temp,10);
		char *num_ID=new char[3];
		num_ID[0]='G';
		if (strlen(num_temp)==2)
		{
			num_ID[1]=num_temp[0];
			num_ID[2]=num_temp[1];
			num_ID[3]='\0';
		} 
		else
		{
			num_ID[1]='0';
			num_ID[2]=num_temp[0];
			num_ID[3]='\0';
		}
		//cout<<num_ID;
		//----------------------------------------------结束计算将要处理的卫星的编号,num_ID
		
		int j=1;//历元的标记
		Hu *temp_hu=new Hu;
		Hu_node *temp_hu_nd=new Hu_node;
		Hu *current_hu;
		Hu_node *current_hu_nd;
		Epochs_ob_node *current_ep=data.e_first;
		bool find_i=0;
		int f_i;
		while (1)
		{
			for (f_i=0;f_i<current_ep->number;f_i++)
			{
				if (current_ep->Sat_ID[f_i][0]==num_ID[0] && current_ep->Sat_ID[f_i][1]==num_ID[1] &&current_ep->Sat_ID[f_i][2]==num_ID[2]
					&& current_ep->data[f_i]->L1 !=0.0 && current_ep->data[f_i]->L2 !=0.0
					&& current_ep->data[f_i]->P1 !=0.0 && current_ep->data[f_i]->P2 !=0.0 )
				{
					find_i=1;
					break;//找到该卫星对应的i，退出for循环
				}
			}
			if (find_i==0)
			{
				current_ep=current_ep->next;
				j++;
			}
			else
				break;//退出while循环
		}
		//---------------------------------------------------找到该卫星对应的i，下面开始MW算法
		double aL1=current_ep->data[f_i]->L1;
		double aL2=current_ep->data[f_i]->L2;
		double aP1=current_ep->data[f_i]->P1;
		double aP2=current_ep->data[f_i]->P2;
		double C=299792458.0;//光速
		double af1=1575.42E6;
		double af2=1227.60E6;
		double lamda1=C/af1;
		double lamda2=C/af2;
		double L_delta=(af1*aL1-af2*aL2)/(af1-af2);
		double P_delta=(af1*aL1+af2*aL2)/(af1+af2);
		double lamda_delta=C/(af1-af2);

		double b_delta=(L_delta-P_delta)/lamda_delta;
		temp_hu_nd->b_delta_avg=b_delta;
		temp_hu_nd->RMS=0.25;//有平方
		temp_hu_nd->time_g=current_ep->time_g;
		temp_hu->datas=temp_hu_nd;
		current_hu_nd=temp_hu->datas;
		temp_hu->num=1;
		data_n.datas=temp_hu;
		current_hu=data_n.datas;

		double mark1_b_delta;
		double mark1_b_delta_avg;
		double mark1_RMS;
		time_gpst mark1_time;
		double mark2_b_delta;
		double mark2_b_delta_avg;
		double mark2_RMS;
		time_gpst mark2_time;
		while (1)//开始计算第二次及以后的所有历元
		{
			current_ep=current_ep->next;
			j++;
			bool find_i=0;
			int f_i;
			int jishu_j=0;
			while (1)
			{
				for (f_i=0;f_i<current_ep->number;f_i++)
				{
					if (current_ep->Sat_ID[f_i][0]==num_ID[0] && current_ep->Sat_ID[f_i][1]==num_ID[1] &&current_ep->Sat_ID[f_i][2]==num_ID[2]
						&& current_ep->data[f_i]->L1 !=0.0 && current_ep->data[f_i]->L2 !=0.0
						&& current_ep->data[f_i]->P1 !=0.0 && current_ep->data[f_i]->P2 !=0.0 )
					{
						find_i=1;
						break;//找到该卫星对应的i，退出for循环
					}
				}
				if (find_i==0)
				{
					current_ep=current_ep->next;
					j++;
					jishu_j++;
				}
				else
					break;//退出while循环
			}
			if (jishu_j<4)//2分钟
			{
				double aL1=current_ep->data[f_i]->L1;
				double aL2=current_ep->data[f_i]->L2;
				double aP1=current_ep->data[f_i]->P1;
				double aP2=current_ep->data[f_i]->P2;
				double lamda1=C/af1;
				double lamda2=C/af2;
				double L_delta=(af1*aL1-af2*aL2)/(af1-af2);
				double P_delta=(af1*aL1+af2*aL2)/(af1+af2);
				double lamda_delta=C/(af1-af2);
				double b_delta4=(L_delta-P_delta)/lamda_delta;

				if (fabs(b_delta4-current_hu_nd->b_delta_avg) < 4*current_hu_nd->RMS)//如果没有周跳
				{
					temp_hu_nd=new Hu_node;
					temp_hu_nd->b_delta_avg=current_hu_nd->b_delta_avg+(b_delta4-current_hu_nd->b_delta_avg)/j;
					temp_hu_nd->RMS=current_hu_nd->RMS+(pow(b_delta4-current_hu_nd->b_delta_avg,2)-pow(current_hu_nd->RMS,2))/j;
					temp_hu_nd->time_g=current_ep->time_g;

					current_hu_nd->next=temp_hu_nd;
					current_hu_nd=current_hu_nd->next;
					temp_hu->num++;
				} 
				else//有周跳或者野值
				{
					mark1_b_delta=b_delta4;
					mark1_RMS=current_hu_nd->RMS+(pow(b_delta4-current_hu_nd->b_delta_avg,2)-pow(current_hu_nd->RMS,2))/j;
					mark1_b_delta_avg=current_hu_nd->b_delta_avg+(b_delta4-current_hu_nd->b_delta_avg)/j;
					mark1_time=current_ep->time_g;
					Epochs_ob_node *yezhi=current_ep;

					current_ep=current_ep->next;
					j++;
					bool find_i=0;
					int f_i;
					for (f_i=0;f_i<current_ep->number;f_i++)
					{
						if (current_ep->Sat_ID[f_i][0]==num_ID[0] && current_ep->Sat_ID[f_i][1]==num_ID[1] &&current_ep->Sat_ID[f_i][2]==num_ID[2]
							&& current_ep->data[f_i]->L1 !=0.0 && current_ep->data[f_i]->L2 !=0.0
							&& current_ep->data[f_i]->P1 !=0.0 && current_ep->data[f_i]->P2 !=0.0 )
						{
							find_i=1;
							break;//找到该卫星对应的i，退出for循环
						}
					}

					double aL1=current_ep->data[f_i]->L1;
					double aL2=current_ep->data[f_i]->L2;
					double aP1=current_ep->data[f_i]->P1;
					double aP2=current_ep->data[f_i]->P2;
					double lamda1=C/af1;
					double lamda2=C/af2;
					double L_delta=(af1*aL1-af2*aL2)/(af1-af2);
					double P_delta=(af1*aL1+af2*aL2)/(af1+af2);
					double lamda_delta=C/(af1-af2);
					double b_delta=(L_delta-P_delta)/lamda_delta;

					mark2_b_delta=b_delta;
					mark2_RMS=mark1_RMS+(pow(b_delta-mark1_b_delta_avg,2)-pow(mark1_RMS,2))/j;
					mark2_b_delta_avg=mark1_b_delta_avg+(b_delta-mark1_b_delta_avg)/j;
					mark2_time=current_ep->time_g;

					if (fabs(mark2_b_delta-mark1_b_delta)>1)//历元i为野值
					{
						yezhi->data[i]->P1=0.0;//剔除数据，在equation建立时省略掉
					}
					else//周跳
					{
						temp_hu=new Hu;
						temp_hu_nd=new Hu_node;
						temp_hu_nd->b_delta_avg=mark1_b_delta;
						temp_hu_nd->RMS=0.25;
						temp_hu_nd->time_g=mark1_time;

						temp_hu->datas=temp_hu_nd;
						current_hu_nd=temp_hu->datas;
						temp_hu->num++;

						temp_hu_nd=new Hu_node;
						temp_hu_nd->b_delta_avg=mark1_b_delta+(b_delta-mark1_b_delta)/j;
						temp_hu_nd->RMS=0.25+(pow(b_delta-mark1_b_delta,2)-pow(0.25,2))/j;
						temp_hu_nd->time_g=mark2_time;

						current_hu_nd->next=temp_hu_nd;
						current_hu_nd=current_hu_nd->next;
						temp_hu->num++;
					}
				}
			}
			else
			{
				double aL1=current_ep->data[f_i]->L1;
				double aL2=current_ep->data[f_i]->L2;
				double aP1=current_ep->data[f_i]->P1;
				double aP2=current_ep->data[f_i]->P2;
				double lamda1=C/af1;
				double lamda2=C/af2;
				double L_delta=(af1*aL1-af2*aL2)/(af1-af2);
				double P_delta=(af1*aL1+af2*aL2)/(af1+af2);
				double lamda_delta=C/(af1-af2);
				double b_delta=(L_delta-P_delta)/lamda_delta;

				temp_hu=new Hu;
				temp_hu_nd=new Hu_node;
				temp_hu_nd->b_delta_avg=b_delta;
				temp_hu_nd->RMS=0.25;
				temp_hu_nd->time_g=current_ep->time_g;

			}
		}

	}
}

Observation::~Observation()
{
}
