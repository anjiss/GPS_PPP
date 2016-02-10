#include "StdAfx.h"
#include "CLK.h"
#include <fstream>
#include <iostream>
using namespace std;

CLK::CLK(){}

CLK::CLK(ifstream &indata)
{
	num=0;
	char data_in_line[256];
	bool end_bool=1;
	char *end="END OF HEADER";
	while (end_bool)
	{
		indata.getline(data_in_line,255);
		if (strstr(data_in_line,end))
		{
			end_bool=0;
		}
	}

	char **acc=new char *[11];
	for (int i=0;i<11;i++)
	{
		acc[i]=new char[20];
	}
	Clk_node *current_nd=data;

	while (1)//开始读文件
	{
		Clk_node *temp_nd=new Clk_node;
		temp_nd->gps_data=new Clk_node_nd;
		
		temp_nd->gps_data->id=new char [3];
		indata.getline(data_in_line,255);
		int stopii=sscanf(data_in_line,"%s%s%s%s%s%s%s%s%s%s%s",acc[0],acc[1],acc[2],acc[3],acc[4],acc[5],acc[6],acc[7],acc[8],acc[9],acc[10]);
		if (stopii==-1)
		{
			break;
		}
		char *gps_lab="AS";
		if (strstr(acc[0],gps_lab))
		{
			Clk_node_nd *temp_ndnd=new Clk_node_nd;
			int lab_i=0;
			time_common temp;
			temp.year_cm=atoi(acc[2]);
			temp.month_cm=atoi(acc[3]);
			temp.day_cm=atoi(acc[4]);
			temp.hour_cm=atoi(acc[5]);
			temp.minte_cm=atoi(acc[6]);
			temp.second_cm=atof(acc[7]);
			double temp_jd=Convert_Cm2Jd(temp);
			temp_ndnd->time_g=Convert_Jd2Gpst(temp_jd);
			temp_ndnd->id=acc[1];
			temp_ndnd->dT=atof(acc[9]);
			temp_nd->gps_data=temp_ndnd;
			temp_nd->num_s=0;
			Clk_node_nd *current_ndnd=temp_nd->gps_data;
			
			for (int i=0;i<11;i++)
			{
				acc[i]=new char[20];
			}
			int ii=1;
			indata.getline(data_in_line,255);
			sscanf(data_in_line,"%s%s%s%s%s%s%s%s%s%s%s",acc[0],acc[1],acc[2],acc[3],acc[4],acc[5],acc[6],acc[7],acc[8],acc[9],acc[10]);
			int stop_i;
			while (strstr(acc[0],gps_lab))
			{
				temp_ndnd=new Clk_node_nd;
				temp_ndnd->id=acc[1];
				temp_ndnd->dT=atof(acc[9]);
				temp_ndnd->time_g=temp_nd->gps_data->time_g;
				temp_nd->num_s++;
				current_ndnd->next=temp_ndnd;
				current_ndnd=current_ndnd->next;
				ii++;
				for (int i=0;i<11;i++)
				{
					acc[i]=new char[20];
				}
				indata.getline(data_in_line,255);
				stop_i=sscanf(data_in_line,"%s%s%s%s%s%s%s%s%s%s%s",acc[0],acc[1],acc[2],acc[3],acc[4],acc[5],acc[6],acc[7],acc[8],acc[9],acc[10]);
				if (stop_i==-1)
				{
					break;
				}
			}
			if (num==0)
			{
				data=temp_nd;
				current_nd=data;
				num++;
			} 
			else
			{
				current_nd->next=temp_nd;
				current_nd->next->last=current_nd;
				current_nd=current_nd->next;
				num++;
			}
		}
	}

}

CLK CLK::CLK_add(CLK clk1,CLK clk2,CLK clk3)
{
	CLK re;
	Clk_node *current_nd=clk2.data;
	for (int i=0;i<clk2.num-1;i++)
	{
		current_nd=current_nd->next;
	}
	current_nd->next=clk3.data;
	clk3.data->last=current_nd;

	current_nd=clk1.data;
	for (int i=0;i<clk1.num-1;i++)
	{
		current_nd=current_nd->next;
	}
	current_nd->next=clk2.data;
	clk2.data->last=current_nd;
	re.data=clk1.data;
	re.num=clk1.num+clk2.num+clk3.num;

	return re;
}

CLK::~CLK(void)
{
}
