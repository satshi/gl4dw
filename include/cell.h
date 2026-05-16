// セルのクラス

#ifndef _CELL_H
#define _CELL_H

#include"p_cell.h"//原始的なセル
#include "vector4.h"	//頂点のクラス

//距離の最小値のクラス。
class min_d
{
  public:
	int ix;		//最小になる点の番号
	const Vector4 *vp;	//最小になるベクトルのポインタ
	double d;	//距離の最小値

	//コンストラクタ
	min_d()	{ix=0; vp=NULL; d=0.0;}
	
	min_d(const Vector4& v, const aVector4& vx, double mm=0){minD(v,vx,mm);}
	
	//データを求める関数
	/*double 距離の最小値の最小値。これよりも小さい値は認めない*/
	/*Vector4&中心のベクトル。この点からの距離の最小値を求める*/
	/*vertices&この点たちの中から最小を求める*/
	void minD(const Vector4&, const aVector4&, double mm=0);
	void minD(double mm, const Vector4& v, const aVector4& vx){minD(v,vx,mm);}//昔のものとの互換性のため。
};


//セルクラス。頂点からも作れる。面の並べ替えもできる。
class cell:public p_cell
{
  public:
	cell():p_cell(){}
	cell(INDEX sz):p_cell(sz){}
	cell(const aINDEX& x):p_cell(x){}
	cell(const Vector4&, const aVector4&);//頂点から作る。

	typedef Ary<cell> acell;
	void F_sort(const acell& edges);//稜を参照しながら面の要素を並べ替える。
	virtual BOOL read(istream& is);
	virtual BOOL write(ostream& os) const;
};
#endif
