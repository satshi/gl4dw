/*
* ４次元から３次元への射影のクラス
*  ヘッダ
*/

#ifndef PROJ_H_
#define PROJ_H_

#include"points.h"


//基本クラス　正射影
class projector:public points
{
	public:

	//４つのベクトルの組で姿勢を表す。
	projector():points(4)
	{
		ptr[0]=Vector4(1,0,0,0);
		ptr[1]=Vector4(0,1,0,0);
		ptr[2]=Vector4(0,0,1,0);
		ptr[3]=Vector4(0,0,0,1);
	}

	projector(aVector4& vv):points()
	{
		*this=vv;
	}

	virtual Vector3 projection(const Vector4&) const;

	const static projector standerd;
};

//派生クラス　立体射影
class stereo:public projector
{
	public:
	Vector4 vp;//視点

	stereo():projector()
	{
		vp=Vector4(0,0,0,1);
	}

	virtual Vector3 projection(const Vector4&) const;

	const static stereo standerd;
};

class spherical_projector:public projector
{
	public:

	spherical_projector():projector()
	{
	}

	virtual Vector3 projection(const Vector4&) const;

	const static spherical_projector standerd;
};

#endif//#ifdef PROJ_H

