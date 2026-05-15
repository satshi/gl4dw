
#ifndef _TARY_H_
#define _TARY_H_

#include<iostream.h>
//　インデックスの型
typedef int INDEX;

template <class Type> class Ary;
template <class Type> istream& operator>>(istream&, Ary<Type>&);
template <class Type> ostream& operator<<(ostream&, const Ary<Type>&);

/*----------------------------------------------------------------------
	配列クラステンプレート（インタフェース部）			"tary.h"
----------------------------------------------------------------------*/


//===== 配列クラステンプレート =====//
template <class Type> class Ary {

protected:
	INDEX	size;				// 配列の大きさ（確保したメモリーの大きさ）

public:
	INDEX	n;					// 実質的に意味のある大きさ
	Type	*ptr;				// 先頭要素へのポインタ


	//----- 添え字範囲エラー -----//
/*	class RangeErr {
	private:
		Ary*	ident;
		int		index;
	public:
		RangeErr(Ary* p, int i) : ident(p), index(i) {}
		int Index(void)  { return (index); }
	};
*/
	Ary()				{ptr = NULL; size=0; n=0;}
	Ary(INDEX sz)	 		{ ptr = new Type[size = sz]; n=sz;}
	Ary(const Ary&);

	~Ary()			{ delete[] ptr; }

	void renew(){delete[] ptr; ptr = NULL; size=0; n=0;}
	void renew(int sz){delete[] ptr; ptr = new Type[size = sz]; n=sz;}

	Type& operator[](int i)
	{
//		if (i < 0 || i >= size)
//			throw RangeErr(this, i);		// 添え字範囲エラー送出
		return ptr[i];
	}

	const Type& operator[](int i) const
	{
//		if (i < 0 || i >= size)
//			throw RangeErr(this, i);		// 添え字範囲エラー送出
		return ptr[i];
	}

//	入出力
	virtual BOOL read(istream& is);
	virtual BOOL write(ostream& os) const;
//	ポインタを返す
	operator Type*(){ return ptr;}
	operator Type*()const { return ptr;}

	friend istream& operator>> <Type>(istream&, Ary<Type>&);
	friend ostream& operator<< <Type>(ostream&, const Ary<Type>&);
	
	Ary& operator=(const Ary&);
	Ary operator+(Ary&);
};

//----- コピーコンストラクタ -----//
template <class Type>
inline Ary <Type>::Ary(const Ary& x)
{
	ptr = new Type[x.n];
	size = x.n;
	n=x.n;
	for (INDEX i = 0; i < n; i++)
		ptr[i] = x.ptr[i];
}

//----- 代入演算子 -----//
template <class Type>
inline Ary<Type>& Ary<Type>::operator=(const Ary& x)
{
	if (&x != this) {				// 自分自身へは代入しない
		delete[] ptr;
		ptr = new Type[x.n];
		size = x.n;
		n=x.n;
		for (int i = 0; i < n; i++)
			ptr[i] = x.ptr[i];
	}
	return (*this);
}

//------------   入出力   ---------------
template <class Type>
inline BOOL Ary<Type>::read(istream& is)
{
	is>>n;
	size=n;
	delete[] ptr;
	ptr=new Type[n];
	for(int i=0;i<n;i++)is>>ptr[i];
	return TRUE;
}

template <class Type>
inline BOOL Ary<Type>::write(ostream& os) const
{
	os<<n<<" ";
	for(int i=0;i<n;i++)os<<ptr[i]<<" ";
	return TRUE;
}

template <class Type>
inline istream& operator>>(istream& is, Ary<Type>& x)
{
	x.read(is);
	return is;
}

template <class Type>
inline ostream& operator<<(ostream& os, const Ary<Type>& x)
{
	x.write(os);
	return os;
}
#endif
