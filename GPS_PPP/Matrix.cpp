#include "StdAfx.h"
#include "Matrix.h"
#include <iostream>
#include <iomanip>
using namespace std;

Matrix::Matrix()
{
	row=0;
	col=0;
	data=NULL;
}
Matrix::Matrix(int n, int m)//构造函数，构造矩阵N*M 并初始化为0矩阵
{
	row=n;
	col=m;
	data=new double *[n];
	for(int i=0;i<n;i++)
	{
		data[i]=new double[m];
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			data[i][j]=0.0;
}
Matrix::Matrix(int n, int m,double d)
{
	row=n;
	col=m;
	data=new double *[n];
	for(int i=0;i<n;i++)
	{
		data[i]=new double[m];
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			if (i!=j)
				data[i][j]=0.0;
			else
				data[i][j]=d;
		}
}

Matrix::Matrix(int n, int m,double d[])
{
	row=n;
	col=m;
	data=new double *[n];
	for(int i=0;i<n;i++)
	{
		data[i]=new double[m];
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		{
			if (i!=j)
				data[i][j]=0.0;
			else
				data[i][j]=d[i];
		}

}

Matrix::~Matrix()
{
	for(int i=0;i<row;i++)
	{
		delete []data[i];
		data[i]=NULL;
	}
	delete [] data;
	data=NULL;
}

Matrix & Matrix::operator +(Matrix &a)
{
	if(row!=a.row||col!=a.col)
	{
		cout<<"\n\t\t非同行矩阵，不能相加!\n";
		Matrix *c=new Matrix();
		return *c;
	}
	Matrix *b=new Matrix(a.row,a.col);
	for(int i=0;i<a.row;i++)
	{
		for(int j=0;j<a.col;j++)
		{
			b->data[i][j]=data[i][j]+a.data[i][j];
		}
	}
	return *b;
}

Matrix & Matrix::operator -(Matrix &a)
{
	if(row!=a.row||col!=a.col)
	{
		cout<<"\n\t\t非同行矩阵，不能相减!\n";
		Matrix *c=new Matrix();
		return *c;
	}
	Matrix *b=new Matrix(a.row,a.col);
	for(int i=0;i<a.row;i++)
	{
		for(int j=0;j<a.col;j++)
		{
			b->data[i][j]=data[i][j]-a.data[i][j];
		}
	}
	return *b;
}

Matrix & Matrix::operator *(Matrix &a)
{
	if(col!=a.row)
	{
		cout<<"\n\t\t行列数不满足要求，不能相乘!\n";
		Matrix *c=new Matrix();
		return *c;
	}
	Matrix *b=new Matrix(row,a.col);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<a.col;j++)
		{
//			b->data[i][j]=data[i][j]-a.data[i][j];
			double temp=0;
			for(int k=0;k<col;k++)
			{
				temp+=(data[i][k]*a.data[k][j]);
			}
			b->data[i][j]=temp;
		}
	}
	return *b;
}

Matrix & Matrix::operator *(double d)
{
	Matrix *b=new Matrix(row,col);
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			b->data[i][j]=data[i][j]*d;
		}
	}
	return *b;

}

Matrix & Matrix::Transpose()//转置
{
	Matrix *b=new Matrix(col,row);
	for(int i=0;i<col;i++)
		for(int j=0;j<row;j++)
			b->data[i][j]=data[j][i];
	return *b;
}

Matrix & Matrix::Inverse_P()//求逆
{
	Matrix *b=new Matrix(col,row);
	for (int i=0;i<col;i++)
	{
		b->data[i][i]=1/data[i][i];
	}
	return *b;
}

Matrix & Matrix::Inverse()//求逆
{
	if(col!=row)//如果矩阵不是方阵
	{
		cout<<"\n\t\t该矩阵行列数不相等，不能求狭义逆!\n";
		Matrix *c=new Matrix();
		return *c;
	}
	Matrix *b=new Matrix(col,row);
	for(int k=0;k<col;k++)
	{
		Matrix i_M(col,col);
		i_M=*this;
		Matrix i_L(col,1);
		i_L.data[k][0]=-1;
//		cout<<"IM与IL的初始值"<<endl;
//		i_M.disp();
//		i_L.disp();
		for(int i=0;i<row-1;i++)
		{
			Matrix i_R(col,col,1);//
			for(int j=i+1;j<col;j++)
			{
				i_R.data[j][i]=-i_M.data[j][i]/i_M.data[i][i];
			}
//			cout<<"IR循环"<<i<<"次后的结果"<<endl;
//			i_R.disp();
			i_M=i_R*i_M;
			i_L=i_R*i_L;
//			cout<<"此时IM的值为"<<endl;
//			i_M.disp();
		}

		b->data[row-1][k]=-i_L.data[row-1][0]/i_M.data[row-1][row-1];
		for(int i=row-1;i>-1;i--)
		{
			double temp=0;
			for(int j=row-1;j>i;j--)
			{
				temp+=(b->data[j][k]*i_M.data[i][j]);
			}
			b->data[i][k]=(-i_L.data[i][0]-temp)/i_M.data[i][i];
		}
	}
	return *b;
}

Matrix & Matrix::operator = (const Matrix &a)
{
	if(data!=NULL)
	{
		for(int i=0;i<row;i++)
		{
			delete [] data[i];
			data[i]=NULL;
		}
		delete [] data;
		data=NULL;
	}
	row=a.row;
	col=a.col;
	data=new double *[row];
	for(int i=0;i<row;i++)
	{
		data[i]=new double[col];
	}
	for(int i=0;i<a.row;i++)
	{
		for(int j=0;j<a.col;j++)
		{
			data[i][j]=a.data[i][j];
		}
	}
	return *this;
}
void Matrix::input()
{
	cout<<"请输入矩阵中的数据：";
	for(int i=0;i<row;i++)
	{
		cout<<"\n请输入第"<<i+1<<"行数据：\n";
		for(int j=0;j<col;j++)
		{
			cout<<"data["<<i<<"]["<<j<<"]=";
			cin>>data[i][j];
		}
	}
}
void Matrix::disp()
{
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			cout<<setprecision(15)<<setw(20)<<data[i][j]<<'\t';
		cout<<endl;
	}
}