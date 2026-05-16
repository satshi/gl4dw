// セルのクラス

#ifndef _P_CELL_H
#define _P_CELL_H

#include "dust.h"

#include"tary.h"//配列のテンプレート。
				//typedef int INDEXが定義されている
//#include "points.h"	//頂点のクラス

typedef Ary<INDEX> aINDEX;


class p_cell:public aINDEX
{
  public:
	p_cell():aINDEX(){}
	p_cell(INDEX sz):aINDEX(sz){}
	p_cell(const aINDEX& x):aINDEX(x){}
	// 演算子
	BOOL inclusion(INDEX ix) const;//cが要素としてixを持つかどうか
	BOOL inclusion(const p_cell&) const;//包含関係
	friend p_cell intersection(const p_cell&, const p_cell&);//共通部分

//以下の関数は自分自身がソートされているときにのみ使う。
//friend は両方ソートされているときのみ
	friend int cellcmp(const p_cell&, const p_cell&);
	BOOL inclusion_s(INDEX ix) const;//cが要素としてixを持つかどうか
	BOOL inclusion_s(const p_cell&) const;//包含関係
	p_cell intersection_s(const p_cell&);//共通部分
};


typedef Ary<p_cell> ap_cell;  //cellの配列

#endif
