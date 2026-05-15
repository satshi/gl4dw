#ifndef _VECTOR_H
#define _VECTOR_H

#include<math.h>
#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#include<iostream.h>
#include "vector3.h"
#include "tary.h"

//	**********	４次元ベクトルのクラス		*******************

class Vector4
{
	public:
	double x[4];	//	成分

	// コンストラクター
	Vector4();
	Vector4(double,double,double,double);
	Vector4(const Vector4&);

	//演算子
	friend Vector4 operator+(const Vector4&,const Vector4&);
	friend Vector4 operator-(const Vector4&,const Vector4&);
	friend Vector4 operator*(double,const Vector4&); // スカラー倍
	friend Vector4 operator*(const Vector4&,double); // スカラー倍
	friend double operator*(const Vector4&,const Vector4&); //内積
	friend double dot(const Vector4&,const Vector4&); //内積

	Vector4& operator=(const Vector4&);
	Vector4& operator+=(const Vector4&);
	Vector4& operator-=(const Vector4&);
	Vector4& operator*=(double);
	Vector4& operator/=(double);

	double& operator[](int i)
	{
		return x[i];
	}

	const double operator[](int i) const
	{
		return x[i];
	}

	//関数
	double norm();//  長さ
	//回転
	void rotation(double* /* 角度の配列 6個の成分　*/);
	friend Vector4 rotation(double* /* 角度の配列 6個の成分　*/,Vector4&);

	//ベクトルの配列
	typedef Ary<Vector4> aVector4;
	
	//射影
	Vector3 projection();
	Vector3 projection(const aVector4&);
	friend double distance(const Vector4&,const Vector4&); // 長さ
	friend istream& operator>>(istream&,Vector4&);
	friend ostream& operator<<(ostream&,const Vector4&);
};

//インライン関数

//	コンストラクター
inline Vector4::Vector4()
{
	x[0]=0;
	x[1]=0;
	x[2]=0;
	x[3]=0;
}

inline Vector4::Vector4(double x1,double x2,double x3,double x4)
{
	x[0]=x1;
	x[1]=x2;
	x[2]=x3;
	x[3]=x4;
}

inline Vector4::Vector4(const Vector4& v)
{
	x[0]=v.x[0];
	x[1]=v.x[1];
	x[2]=v.x[2];
	x[3]=v.x[3];
}

//		*********	演算子	**************
inline Vector4 operator+(const Vector4& v1,const Vector4& v2)
{
	return Vector4(v1.x[0]+v2.x[0], v1.x[1]+v2.x[1], v1.x[2]+v2.x[2], v1.x[3]+v2.x[3]);
}


inline Vector4 operator-(const Vector4& v1,const Vector4& v2)
{
	return Vector4(v1.x[0]-v2.x[0], v1.x[1]-v2.x[1], v1.x[2]-v2.x[2], v1.x[3]-v2.x[3]);
}

//	スカラー倍
inline Vector4 operator*(double k,const Vector4& v2)
{
	return Vector4(k*(v2.x[0]), k*(v2.x[1]), k*(v2.x[2]), k*(v2.x[3]));
}

//	スカラー倍
inline Vector4 operator*(const Vector4& v2,double k)
{
	return Vector4(k*(v2.x[0]), k*(v2.x[1]), k*(v2.x[2]), k*(v2.x[3]));
}

//内積
inline double operator*(const Vector4& v1,const Vector4& v2) 
{
	return (v1.x[0])*(v2.x[0]) + (v1.x[1])*(v2.x[1]) + (v1.x[2])*(v2.x[2]) + (v1.x[3])*(v2.x[3]);
}

//内積 おそらくこちらを使うほうが望ましい
inline double dot(const Vector4& v1,const Vector4& v2) 
{
	return (v1.x[0])*(v2.x[0]) + (v1.x[1])*(v2.x[1]) + (v1.x[2])*(v2.x[2]) + (v1.x[3])*(v2.x[3]);
}

inline Vector4& Vector4::operator=(const Vector4& v1)
{
	x[0]=v1.x[0];
	x[1]=v1.x[1];
	x[2]=v1.x[2];
	x[3]=v1.x[3];
	return *this;
}

inline Vector4& Vector4::operator+=(const Vector4& v1)
{
	x[0]+=v1.x[0];
	x[1]+=v1.x[1];
	x[2]+=v1.x[2];
	x[3]+=v1.x[3];
	return *this;
}

inline Vector4& Vector4::operator-=(const Vector4& v1)
{
	x[0]-=v1.x[0];
	x[1]-=v1.x[1];
	x[2]-=v1.x[2];
	x[3]-=v1.x[3];
	return *this;
}

//	スカラー倍
inline Vector4& Vector4::operator*=(double k)
{
	x[0]*=k;
	x[1]*=k;
	x[2]*=k;
	x[3]*=k;
	return *this;
}

inline Vector4& Vector4::operator/=(double k)
{
	x[0]/=k;
	x[1]/=k;
	x[2]/=k;
	x[3]/=k;
	return *this;
}


//	****************	関数	*****************

// ベクトルのノルム（長さ）を求める
inline double Vector4::norm()
{
	return sqrt( x[0]*x[0] + x[1]*x[1] + x[2]*x[2] + x[3]*x[3]);
}

// ２つのベクトル（点）の間の距離を求める
inline double distance(const Vector4& v1,const Vector4& v2)
{
	return (v1-v2).norm();
}

//３次元への射影
inline Vector3 Vector4::projection()
{
	return Vector3(x[0], x[1], x[2]);
}

inline Vector3 Vector4::projection(const aVector4& basis)
{
	return Vector3((*this)*basis[0], (*this)*basis[1], (*this)*basis[2]);
}

//定数

typedef Vector4::aVector4 aVector4;

//	--------	ストリーム入出力	----------
inline ostream& operator<<(ostream& os, const Vector4& v)
{
	return(os<<(v.x[0])<<" "<<(v.x[1])<<" "
		<<(v.x[2])<<" "<<(v.x[3]));
}

inline istream& operator>>(istream& is,Vector4& v)
{
	return(is>>(v.x[0])>>(v.x[1])>>(v.x[2])>>(v.x[3]));
}

#endif
