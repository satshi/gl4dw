
#ifndef _CELLS_H
#define _CELLS_H

#include "cell.h"

typedef cell::acell acell;

class cells:public acell
{
  public:
	cells():acell(){}
	cells(INDEX n):acell(n){}
	cells(const acell& ac):acell(ac){}
	
	//セルの中心と頂点
	cells(const aVector4& center, const aVector4& vx);

	//上位のセルと下位のセル
	cells(const acell& c1, const acell& c2,int vn=0);
	
	//関数
	//並べ替え。面のデータの場合順番を並べ替える
	void F_sort(const acell&);
	//逆に解く。たとえば面に属する頂点のデータから、
	//頂点を含む面のデータを作る。双対図形を考えるときに有効
	void inverse(const acell&);//自分を新しく作り直す。
	cells* inverse() const;//新しいオブジェクトを作ってポインタを返す。
	
	//面から稜を作る
	cells* break_face();
	
	//長い作業を中断するための関数。
	//中断するときはTRUEをかえす。
	//ライブラリの中では定義されないで別途ソースを作る。
	//inter.cpp
	virtual BOOL interupt(int i);
	virtual BOOL write(ostream& os) const;
};

class flag:public aINDEX
{
  public:
	//コンストラクタ
	flag():aINDEX(){}
	flag(int n):aINDEX(n){};

	//関数
	//セルの法線ベクトル（中心のベクトル）を与え、
	//そのVector4&となす角が９０度未満のものをとる
	void gen(const Vector4&, const aVector4&, double b=0);

	//上位のセルから遺伝させる
	void gen_from(const cells&, const flag&);
	void gen_surface(const cells&, const flag&);

	//表面の胞だけ
	void gen_up(const cells&,const flag&);
};

#endif