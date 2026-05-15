#include"vector3.h"
//	================================================
//	========	3次元ベクトルの関数	========
//	================================================


//		**********	関数	**************


//　ベクトルを回転する。
// double* th は３つの角度の成分を持つ配列
// 回転されたベクトルを返す。元のベクトルはそのまま。
// ２つの成分の間の回転を合成することによって、任意の回転を得ている。
Vector3 rotation(double* th, const Vector3& v1)
{
	int i,j,m=0;
	Vector3 v2,v3;

	v3=v1;
	for(i=1;i<3;i++)
	{
		for(j=0;j<i;j++)
		{
			if(th[m]!=0)
			{
				//  i成分とj成分の間の回転
				//  つまりij平面上の回転
				v2.x[i]= v3.x[i]*cos(th[m])+v3.x[j]*sin(th[m]);
				v2.x[j]=-v3.x[i]*sin(th[m])+v3.x[j]*cos(th[m]);
			}
			v3=v2;
		}
	}
	return v2;
}

void Vector3::rotation(double* th)
{
	int i,j,m=0;
	Vector3 v3;

	for(i=1;i<3;i++)
	{
		for(j=0;j<i;j++)
		{
			v3=*this;
			if(th[m]!=0)
			{
				//  i成分とj成分の間の回転
				//  つまりij平面上の回転
				x[i]= v3.x[i]*cos(th[m])+v3.x[j]*sin(th[m]);
				x[j]=-v3.x[i]*sin(th[m])+v3.x[j]*cos(th[m]);
			}
		}
	}
}
