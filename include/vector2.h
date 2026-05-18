
#ifndef _VECTOR2_H
#define _VECTOR2_H


#include<math.h>
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#include <iostream>
#include"dust.h"

using std::istream;
using std::ostream;

//	****************	３次元ベクトルのクラス		**********
class Vector2
{
	public:
	double x[2];

	// コンストラクター
	Vector2();
	Vector2(double,double);
	Vector2(const Vector2&);

	//演算子
	friend Vector2 operator+(const Vector2&,const Vector2&);
	friend Vector2 operator-(const Vector2&,const Vector2&);
	friend Vector2 operator*(double,const Vector2&);//スカラー倍
	friend Vector2 operator*(const Vector2&,double);//スカラー倍
	friend double  operator*(const Vector2&,const Vector2&); //内積
	friend double  dot(const Vector2&,const Vector2&); //内積
	friend double  cross(const Vector2&,const Vector2&); //ベクトル積

	Vector2& operator=(const Vector2&);
	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2& operator*=(double);
	Vector2& operator/=(double);
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
	friend double norm(const Vector2&);//  長さ
	friend double distance(const Vector2&, const Vector2&);//距離
	friend Vector2 rotation(double* /* 角度の配列３個の成分*/,Vector2&);
	void rotation(double* /* 角度の配列３個の成分*/);
	//回転
};
//	--------	ストリーム入出力	-----------
ostream& operator<<(ostream&,Vector2&);
istream& operator>>(istream&,Vector2&);

//インライン関数
//		コンストラクター
inline Vector2::Vector2()
{
	x[0]=0;
	x[1]=0;
}

inline Vector2::Vector2(double x1,double x2,double x3)
{
	x[0]=x1;
	x[1]=x2;
}

inline Vector2::Vector2(const Vector2& v)
{
	x[0]=v.x[0];
	x[1]=v.x[1];
}

//		************	演算子		************
inline Vector2 operator+(const Vector2& v1,const Vector2& v2)
{
	return Vector2(v1.x[0]+v2.x[0], v1.x[1]+v2.x[1]);
}


inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x[0]-v2.x[0], v1.x[1]-v2.x[1]);
}

//	スカラー倍
inline Vector2 operator*(double k, const Vector2& v2)
{
	return Vector2(k*(v2.x[0]), k*(v2.x[1]));
}

//	スカラー倍
inline Vector2 operator*(const Vector2& v2,double k)
{
	return Vector2(k*(v2.x[0]), k*(v2.x[1]));
}


inline double operator*(const Vector2& v1, const Vector2& v2) //　内積（スカラー積）
{
	
	return (v1.x[0])*(v2.x[0]) + (v1.x[1])*(v2.x[1]));
}

inline double dot(const Vector2& v1, const Vector2& v2) //　内積（スカラー積）
{
	
	return (v1.x[0])*(v2.x[0]) + (v1.x[1])*(v2.x[1]));
}

inline Vector2 cross(const Vector2& v1, const Vector2& v2)	//　外積（ベクトル積）
{
	return (v1.x[1]) * (v2.x[2]) - (v1.x[2]) * (v2.x[1])
}

inline Vector2& Vector2::operator=(const Vector2& v1)
{
	x[0]=v1.x[0];
	x[1]=v1.x[1];
	return *this;
}

inline Vector2& Vector2::operator+=(const Vector2& v1)
{
	x[0]+=v1.x[0];
	x[1]+=v1.x[1];
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& v1)
{
	x[0]-=v1.x[0];
	x[1]-=v1.x[1];
	return *this;
}

//	スカラー倍
inline Vector2& Vector2::operator*=(double k)
{
	x[0]*=k;
	x[1]*=k;
	return *this;
}

inline Vector2& Vector2::operator/=(double k)
{
	x[0]/=k;
	x[1]/=k;
	return *this;
}

// ベクトルのノルム（長さ）を求める
inline double Vector2::norm() const
{
	return sqrt(x[0]*x[0] + x[1]*x[1]);
}

inline double norm(const Vector2& v)
{
	return v.norm();
}
// ２つのベクトル（点）の間の距離を求める
inline double distance(const Vector2& v1, const Vector2& v2)
{
	return (v1-v2).norm();
}


//	--------	ストリーム入出力	----------
inline ostream& operator<<(ostream& os, Vector2& v)
{
	return(os<<v.x[0]<<" "<<v.x[1]);
}

inline istream& operator>>(istream& is,Vector2& v)
{
	return(is>>v.x[0]>>v.x[1]);
}

#endif
