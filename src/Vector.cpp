#include "vector4.h"

//	================================================
//	========	４次元ベクトルの関数	========
//	================================================


//	****************	関数	*****************



//　ベクトルを回転する。
// double* th は６つの角度の成分を持つ配列
// 回転されたベクトルを返す。元のベクトルはそのまま。
// ２つの成分の間の回転を合成することによって、任意の回転を得ている。

Vector4 rotation(double* th, const Vector4& v1)
{
	int i,j,m=0;
	Vector4& v2=*new Vector4();
	Vector4 v3;

	v3=v1;
	v2=v1;
	for(i=1;i<4;i++)
	{
		for(j=0;j<i;j++)
		{
			//  i成分とj成分の間の回転
			//  つまりij平面上の回転
			if(th[m]!=0)
			{
				v2.x[i]= v3.x[i]*cos(th[m])+v3.x[j]*sin(th[m]);
				v2.x[j]=-v3.x[i]*sin(th[m])+v3.x[j]*cos(th[m]);
				v3=v2;
			}
			m++;
		}
	}
	return v2;
}

void Vector4::rotation(double* th)
{
	int i,j,m=0;
	Vector4 v2,v3;

	v3=*this;
	for(i=1;i<4;i++)
	{
		for(j=0;j<i;j++)
		{
			//  i成分とj成分の間の回転
			//  つまりij平面上の回転
			if(th[m]!=0)
			{
				x[i]= v3.x[i]*cos(th[m])+v3.x[j]*sin(th[m]);
				x[j]=-v3.x[i]*sin(th[m])+v3.x[j]*cos(th[m]);
				v3=*this;
			}
			m++;
		}
	}
}
