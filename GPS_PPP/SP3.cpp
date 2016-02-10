#include "StdAfx.h"
#include "SP3.h"
#include "SatPosition.h"
#include "Epochs.h"
#include <iostream>
#include "MathBase.h"


#include <iomanip>
using namespace std;

SP3::SP3(){}
SP3::SP3(ifstream &indata)
{
	char data_in_line[256];
	//------------------------------------------------Read 1st Line
	char *V_P_Y=new char[7];
	Version_Symbol=new char[2];
	P_or_V_Flag=new char[1];
	char *year_start=new char[4];
	char *month_start=new char[2];
	char *day_of_month=new char[2];
	char *hour_start=new char[2];
	char *minute_start=new char[2];
	char *second_start=new char[10];
	char *number_of_epochs=new char[2];
	Data_Used=new char[5];
	Coordinate_Sys=new char[5];
	Orbit_Type=new char[3];
	Agency=new char[4];
	
	indata.getline(data_in_line,255);
	sscanf(data_in_line,"%s%s%s%s%s%s%s%s%s%s%s",V_P_Y,month_start,day_of_month,hour_start,
		minute_start,second_start,number_of_epochs,Data_Used,Coordinate_Sys,Orbit_Type,Agency);
	Version_Symbol[0]=V_P_Y[0];
	Version_Symbol[1]=V_P_Y[1];
	Version_Symbol[2]='\0';
	P_or_V_Flag[0]=V_P_Y[2];
	P_or_V_Flag[1]='\0';
	for (int i=0;i<4;i++)
	{
		year_start[i]=V_P_Y[i+3];
	}
	year_start[4]='\0';
	Year_Start=atoi(year_start);
	Month_Start=atoi(month_start);
	Day_of_Month=atoi(day_of_month);
	Hour_Start=atoi(hour_start);
	Minute_Start=atoi(minute_start);
	Second_Start=atof(second_start);
	Number_of_Epochs=atoi(number_of_epochs);

	//------------------------------------------------Read 2nd Line
	Symbols=new char[2];
	char *gps_week=new char[4];
	char *seconds_of_week=new char[15];
	char *epoch_interval=new char[13];
	char *mod_jul_day_st=new char[5];
	char *fraction_day=new char[15];

	indata.getline(data_in_line,255);
	sscanf(data_in_line,"%s%s%s%s%s%s",Symbols,gps_week,seconds_of_week,epoch_interval,mod_jul_day_st,fraction_day);
	GPS_Week=atoi(gps_week);
	Seconds_of_Week=atof(seconds_of_week);
	Epoch_Interval=atof(epoch_interval);
	Mod_Jul_Day_St=atoi(mod_jul_day_st);
	Fractional_Day=atof(fraction_day);

	//------------------------------------------------Read 3rd Line
	char *Sat_ID=new char[255];
	char *number_of_sats=new char[2];
	
	indata.getline(data_in_line,255);
	sscanf(data_in_line,"%s%s%s",Symbols,number_of_sats,Sat_ID);
	Number_of_Sats=atoi(number_of_sats);
	SatAccuracy =new SatPosition* [32];
	for (int i=0;i<32;i++)
	{
		SatAccuracy[i]=new SatPosition;
	}
	for (int i=0;i<17;i++)
	{
		for (int j=0;j<3;j++)
		{
			SatAccuracy[i]->Sat_Id[j]=Sat_ID[i*3+j];
		}
		SatAccuracy[i]->Sat_Id[3]='\0';
	}

	//------------------------------------------------Read 4th Line
	indata.getline(data_in_line,255);
	sscanf(data_in_line,"%s%s",Symbols,Sat_ID);
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<3;j++)
		{
			SatAccuracy[i+17]->Sat_Id[j]=Sat_ID[i*3+j];
		}
		SatAccuracy[i+17]->Sat_Id[3]='\0';
	}

	//------------------------------------------------Read 5th 6th 7th Line
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);

	//------------------------------------------------Read 8th 9th Line
	char **acc=new char *[17];
	for (int i=0;i<17;i++)
	{
		acc[i]=new char[3];
	}
	indata.getline(data_in_line,255);
	sscanf(data_in_line,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",Symbols,acc[0],acc[1],acc[2],acc[3],acc[4],acc[5],acc[6],acc[7],acc[8],
		acc[9],acc[10],acc[11],acc[12],acc[13],acc[14],acc[15],acc[16],acc[17]);
	for (int i=0;i<17;i++)
	{
		SatAccuracy[i]->Sat_Accuracy=atof(acc[i]);
	}


	indata.getline(data_in_line,255);
	sscanf(data_in_line,"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",Symbols,acc[0],acc[1],acc[2],acc[3],acc[4],acc[5],acc[6],acc[7],acc[8],
		acc[9],acc[10],acc[11],acc[12],acc[13],acc[14],acc[15]);
	for (int i=0;i<15;i++)
	{
		SatAccuracy[i+17]->Sat_Accuracy=atof(acc[i]);
	}
	
	//------------------------------------------------Read 10th 11th 12th Line
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);

	//------------------------------------------------Read 13th 14th Line
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);

	//------------------------------------------------Read 15th 16th Line
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);

	//------------------------------------------------Read 17th 18th Line
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);

	//------------------------------------------------Read 19th 20th 21th 22th Line
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);
	indata.getline(data_in_line,255);

	//------------------------------------------------Read each epochs
	char *year_epoch=new char[4];
	char *month_epoch=new char[2];
	char *day_epoch=new char[2];
	char *hour_epoch=new char[2];
	char *minute_epoch=new char[2];
	char *second_epoch=new char[10];
	char *x_vel=new char[14];
	char *y_vel=new char[14];
	char *z_vel=new char[14];
	char *clock_rate_chg=new char[14];
	char *x_e=new char[14];
	char *y_e=new char[14];
	char *z_e=new char[14];
	char *clock_e=new char[14];
	char *PV_ID=new char[4];

	epochs= new Epochs *[Number_of_Epochs];
	for (int i=0;i<Number_of_Epochs;i++)
	{
		epochs[i]= new Epochs(Number_of_Sats);
	}

	for (int i=0;i<Number_of_Epochs;i++)
	{
		indata.getline(data_in_line,255);//读每个历元的头一条
		sscanf(data_in_line,"%s%s%s%s%s%s%s",Symbols,year_epoch,month_epoch,day_epoch,hour_epoch,minute_epoch,second_epoch);
		epochs[i]->Year_Start=atoi(year_epoch);
		epochs[i]->Month_Start=atoi(month_epoch);
		epochs[i]->Day_of_Month_St=atoi(day_epoch);
		epochs[i]->Hour_Start=atoi(hour_epoch);
		epochs[i]->Minute_Start=atoi(minute_epoch);
		epochs[i]->Second_Start=atof(second_epoch);
		time_common time_epoch;
		time_epoch.year_cm=epochs[i]->Year_Start;
		time_epoch.month_cm=epochs[i]->Month_Start;
		time_epoch.day_cm=epochs[i]->Day_of_Month_St;
		time_epoch.hour_cm=epochs[i]->Hour_Start;
		time_epoch.minte_cm=epochs[i]->Minute_Start;
		time_epoch.second_cm=epochs[i]->Second_Start;
		double temp_JD=Convert_Cm2Jd(time_epoch);
		epochs[i]->time_gps=Convert_Jd2Gpst(temp_JD);
//		cout<<setprecision(15)<<temp_JD<<endl;//-----------------------------------------------测试用
		
		for (int j=0;j<Number_of_Sats;j++)
		{
			indata.getline(data_in_line,255);
			sscanf(data_in_line,"%s%s%s%s%s",PV_ID,x_e,y_e,z_e,clock_e);
			epochs[i]->Sat_XYZ[j]= new SatPosition;
			epochs[i]->Sat_XYZ[j]->Sat_Id[0]=PV_ID[1];
			epochs[i]->Sat_XYZ[j]->Sat_Id[1]=PV_ID[2];
			epochs[i]->Sat_XYZ[j]->Sat_Id[2]=PV_ID[3];
			epochs[i]->Sat_XYZ[j]->Sat_Id[3]=PV_ID[4];
			epochs[i]->Sat_XYZ[j]->X=atof(x_e)*1000;
			epochs[i]->Sat_XYZ[j]->Y=atof(y_e)*1000;
			epochs[i]->Sat_XYZ[j]->Z=atof(z_e)*1000;
			epochs[i]->Sat_XYZ[j]->clock_each=atof(clock_e);

			if (P_or_V_Flag[0]=='V')
			{
				indata.getline(data_in_line,255);
				sscanf(data_in_line,"%s%s%s%s%s",PV_ID,x_vel,y_vel,z_vel,clock_rate_chg);
				epochs[i]->Sat_XYZ[j]->X_Vel=atof(x_vel);
				epochs[i]->Sat_XYZ[j]->Y_Vel=atof(y_vel);
				epochs[i]->Sat_XYZ[j]->Z_Vel=atof(z_vel);
				epochs[i]->Sat_XYZ[j]->clock_rate_change=atof(clock_rate_chg);
			}
		}

		
	}
}

SP3::~SP3(void)
{
}

