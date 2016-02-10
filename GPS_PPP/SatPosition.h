#pragma once

class SatPosition
{
public:
	SatPosition();
	SatPosition(char *id,double accuracy,double x,double y,double z);//P
	SatPosition(char *id,double accuracy,double x,double y,double z,double x_v,double y_v,double z_v);//V
	SatPosition(char *id,double accuracy);
	~SatPosition();
public:
	char *Sat_Id;
	double Sat_Accuracy;
	double X,Y,Z;// km
	double X_Vel,Y_Vel,Z_Vel;// dm/s
	double clock_each;
	double clock_rate_change;

};
