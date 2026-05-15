#ifndef POINTS_H_
#define POINTS_H_

#include "cells.h"

//点の集合
class points:public aVector4
{
  public:

	double edgelength;
	
	points():aVector4(){}
	points(int nn):aVector4(nn){}
	points(const aVector4& vx):aVector4(vx){}

	//同じ長さの稜を作る。
	cells* edges_of_unit_length();
	//回転する
	void rotation(double* th);
	
	//入出力に使う関数をオーバーライド
	BOOL read(istream&);
	BOOL write(ostream&) const;
};

#endif //#ifndef POINTS_H_
