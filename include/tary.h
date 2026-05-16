#ifndef _TARY_H_
#define _TARY_H_

#include<iostream.h>
#include <vector>

typedef int INDEX;

template <class Type> class Ary;
template <class Type> istream& operator>>(istream&, Ary<Type>&);
template <class Type> ostream& operator<<(ostream&, const Ary<Type>&);

template <class Type> class Ary {

protected:
	INDEX	size;
	std::vector<Type> storage;

	void sync_ptr()
	{
		ptr = storage.empty() ? NULL : &storage[0];
	}

public:
	INDEX	n;
	Type	*ptr;

	Ary()				{ptr = NULL; size=0; n=0;}
	Ary(INDEX sz)	 		{ storage.resize(sz); size=sz; n=sz; sync_ptr();}
	Ary(const Ary&);

	~Ary()			{}

	void renew(){storage.clear(); size=0; n=0; sync_ptr();}
	void renew(int sz){storage.clear(); storage.resize(sz); size=sz; n=sz; sync_ptr();}

	Type& operator[](int i)
	{
		return ptr[i];
	}

	const Type& operator[](int i) const
	{
		return ptr[i];
	}

	virtual BOOL read(istream& is);
	virtual BOOL write(ostream& os) const;
	operator Type*(){ return ptr;}
	operator Type*()const { return ptr;}

	friend istream& operator>> <Type>(istream&, Ary<Type>&);
	friend ostream& operator<< <Type>(ostream&, const Ary<Type>&);
	
	Ary& operator=(const Ary&);
	Ary operator+(Ary&);
};

template <class Type>
inline Ary <Type>::Ary(const Ary& x)
{
	storage.resize(x.n);
	size = x.n;
	n=x.n;
	sync_ptr();
	for (INDEX i = 0; i < n; i++)
		ptr[i] = x.ptr[i];
}

template <class Type>
inline Ary<Type>& Ary<Type>::operator=(const Ary& x)
{
	if (&x != this) {
		storage.clear();
		storage.resize(x.n);
		size = x.n;
		n=x.n;
		sync_ptr();
		for (int i = 0; i < n; i++)
			ptr[i] = x.ptr[i];
	}
	return (*this);
}

template <class Type>
inline BOOL Ary<Type>::read(istream& is)
{
	is>>n;
	renew(n);
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
