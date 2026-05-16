/*
* ４次元から３次元への射影のクラス
*  実現部
*/

#include"proj.h"

const projector projector::standerd;
const stereo stereo::standerd;
const spherical_projector spherical_projector::standerd;


//基本クラス　正射影
Vector3 projector::projection(const Vector4& v) const
{
	return Vector3(v*ptr[0],v*ptr[1],v*ptr[2]);
}

//派生クラス　立体射影
Vector3 stereo::projection(const Vector4& v) const
{
	double vp3=vp*ptr[3];
	double v3=v*ptr[3];
	double n=vp3/(vp3-v3);
	Vector4 pr(v-vp);
	return projector::projection(vp+n*pr);
}

Vector3 spherical_projector::projection(const Vector4& v) const
{
	Vector3 ret;
	double v0=v*ptr[0];
	double v1=v*ptr[1];
	double v2=v*ptr[2];
	double v3=v*ptr[3];
	
	if(!eql(v1,0.0))	ret[0]=atan(v0/v1);
	else		ret[0]=M_PI/2;
	if(!eql(v3,0.0))	ret[1]=atan(v2/v3);
	else		ret[1]=M_PI/2;

	if(!eql(((v2*v2)+(v3*v3)),0.0))
		ret[2]=atan(sqrt(((v0*v0)+(v1*v1))/((v2*v2)+(v3*v3))));
	else ret[2]=M_PI/2;
	
	return ret;
}
