#include "StdAfx.h"
#include "SatPosition.h"

SatPosition::SatPosition()
{
	Sat_Id=new char[3];
	Sat_Accuracy=0;
	X=0;
	Y=0;
	Z=0;
	X_Vel=0;
	Y_Vel=0;
	Z_Vel=0;
}

SatPosition::SatPosition(char *id,double accuracy,double x,double y,double z)
{
	Sat_Id=new char[3];
	Sat_Id=id;
	Sat_Accuracy=accuracy;
	X=x;
	Y=y;
	Z=z;
	X_Vel=0;
	Y_Vel=0;
	Z_Vel=0;
}

SatPosition::SatPosition(char *id,double accuracy,double x,double y,double z,double x_v,double y_v,double z_v)
{
	Sat_Id=new char[3];
	Sat_Id=id;
	Sat_Accuracy=accuracy;
	X=x;
	Y=y;
	Z=z;
	X_Vel=x_v;
	Y_Vel=y_v;
	Z_Vel=z_v;
}

SatPosition::SatPosition(char *id,double accuracy)
{
	Sat_Id=new char[3];
	Sat_Id=id;
	Sat_Accuracy=accuracy;
	X=0;
	Y=0;
	Z=0;
	X_Vel=0;
	Y_Vel=0;
	Z_Vel=0;
}

SatPosition::~SatPosition()
{
}
