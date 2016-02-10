#pragma once

class Matrix
{
public:
	Matrix();
	Matrix(int n,int m);
	Matrix(int n, int m,double d);
	Matrix(int n, int m,double d[]);
	~Matrix();
	Matrix & operator +(Matrix &a);
	Matrix & operator -(Matrix &a);
	Matrix & operator *(Matrix &a);
	Matrix & operator *(double d);
	Matrix & Transpose();
	Matrix & Inverse();
	Matrix & Inverse_P();//对角阵求逆
	Matrix & operator= (const Matrix &a);
	void input();
	void disp();

	int row;//矩阵的行数
	int col;//矩阵的列数
	double **data;
};
