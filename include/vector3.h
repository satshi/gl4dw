
#ifndef _VECTOR3_H
#define _VECTOR3_H


#include<math.h>
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#include<iostream.h>
#include"dust.h"

//	****************	３次元ベクトルのクラス		**********
class Vector3
{
	public:
	double x[3];

	// コンストラクター
	Vector3();
	Vector3(double,double,double);
	Vector3(const Vector3&);

	//演算子
	friend Vector3 operator+(const Vector3&,const Vector3&);
	friend Vector3 operator-(const Vector3&,const Vector3&);
	friend Vector3 operator*(double,const Vector3&);//スカラー倍
	friend Vector3 operator*(const Vector3&,double);//スカラー倍
	friend double  operator*(const Vector3&,const Vector3&); //内積
	friend double  dot(const Vector3&,const Vector3&); //内積
	friend Vector3 operator/(const Vector3&,const Vector3&); //ベクトル積
	friend Vector3 cross(const Vector3&,const Vector3&); //ベクトル積

	Vector3& operator=(const Vector3&);
	Vector3& operator+=(const Vector3&);
	Vector3& operator-=(const Vector3&);
	Vector3& operator*=(double);
	Vector3& operator/=(double);
	double& operator[](int i)
	{
		return x[i];
	}

	const double operator[](int i) const
	{
		return x[i];
	}
	

	//関数
	double norm() const;//	長さ
	friend double norm(const Vector3&);//  長さ
	friend double distance(const Vector3&, const Vector3&);//距離
	friend Vector3 rotation(double* /* 角度の配列３個の成分*/,Vector3&);
	void rotation(double* /* 角度の配列３個の成分*/);
	//回転
};
//	--------	ストリーム入出力	-----------
ostream& operator<<(ostream&,Vector3&);
istream& operator>>(istream&,Vector3&);

//インライン関数
//		コンストラクター
inline Vector3::Vector3()
{
	x[0]=0;
	x[1]=0;
	x[2]=0;
}

inline Vector3::Vector3(double x1,double x2,double x3)
{
	x[0]=x1;
	x[1]=x2;
	x[2]=x3;
}

inline Vector3::Vector3(const Vector3& v)
{
	x[0]=v.x[0];
	x[1]=v.x[1];
	x[2]=v.x[2];
}

//		************	演算子		************
inline Vector3 operator+(const Vector3& v1,const Vector3& v2)
{
	return Vector3(v1.x[0]+v2.x[0], v1.x[1]+v2.x[1], v1.x[2]+v2.x[2]);
}


inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x[0]-v2.x[0], v1.x[1]-v2.x[1], v1.x[2]-v2.x[2]);
}

//	スカラー倍
inline Vector3 operator*(double k, const Vector3& v2)
{
	return Vector3(k*(v2.x[0]), k*(v2.x[1]),k*(v2.x[2]));
}

//	スカラー倍
inline Vector3 operator*(const Vector3& v2,double k)
{
	return Vector3(k*(v2.x[0]), k*(v2.x[1]),k*(v2.x[2]));
}


inline double operator*(const Vector3& v1, const Vector3& v2) //　内積（スカラー積）
{
	
	return (v1.x[0])*(v2.x[0]) + (v1.x[1])*(v2.x[1]) + (v1.x[2])*(v2.x[2]);
}

inline double dot(const Vector3& v1, const Vector3& v2) //　内積（スカラー積）
{
	
	return (v1.x[0])*(v2.x[0]) + (v1.x[1])*(v2.x[1]) + (v1.x[2])*(v2.x[2]);
}

inline Vector3 operator/(const Vector3& v1, const Vector3& v2)	//　外積（ベクトル積）
{
	return Vector3((v1.x[1]) * (v2.x[2]) - (v1.x[2]) * (v2.x[1]),
			   (v1.x[2]) * (v2.x[0]) - (v1.x[0]) * (v2.x[2]),
			   (v1.x[0]) * (v2.x[1]) - (v1.x[1]) * (v2.x[0]));
}

inline Vector3 cross(const Vector3& v1, const Vector3& v2)	//　外積（ベクトル積）
{
	return Vector3((v1.x[1]) * (v2.x[2]) - (v1.x[2]) * (v2.x[1]),
			   (v1.x[2]) * (v2.x[0]) - (v1.x[0]) * (v2.x[2]),
			   (v1.x[0]) * (v2.x[1]) - (v1.x[1]) * (v2.x[0]));
}

inline Vector3& Vector3::operator=(const Vector3& v1)
{
	x[0]=v1.x[0];
	x[1]=v1.x[1];
	x[2]=v1.x[2];
	return *this;
}

inline Vector3& Vector3::operator+=(const Vector3& v1)
{
	x[0]+=v1.x[0];
	x[1]+=v1.x[1];
	x[2]+=v1.x[2];
	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& v1)
{
	x[0]-=v1.x[0];
	x[1]-=v1.x[1];
	x[2]-=v1.x[2];
	return *this;
}

//	スカラー倍
inline Vector3& Vector3::operator*=(double k)
{
	x[0]*=k;
	x[1]*=k;
	x[2]*=k;
	return *this;
}

inline Vector3& Vector3::operator/=(double k)
{
	x[0]/=k;
	x[1]/=k;
	x[2]/=k;
	return *this;
}

// ベクトルのノルム（長さ）を求める
inline double Vector3::norm() const
{
	return sqrt(x[0]*x[0] + x[1]*x[1] + x[2]*x[2]);
}

inline double norm(const Vector3& v)
{
	return v.norm();
}
// ２つのベクトル（点）の間の距離を求める
inline double distance(const Vector3& v1, const Vector3& v2)
{
	return (v1-v2).norm();
}


//	--------	ストリーム入出力	----------
inline ostream& operator<<(ostream& os, Vector3& v)
{
	return(os<<v.x[0]<<" "<<v.x[1]<<" "
		<<v.x[2]);
}

inline istream& operator>>(istream& is,Vector3& v)
{
	return(is>>v.x[0]>>v.x[1]>>v.x[2]);
}

#endif
