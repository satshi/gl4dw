//セルのクラス
#include "p_cell.h"

//INDEX ixがp_cell cに属するかどうか
BOOL p_cell::inclusion(INDEX ix) const
{
	for(INDEX i=0;i<n;i++)
	{
		if(ix==ptr[i])return TRUE;
	}
	return FALSE;
}

//cell c1がcell c2に含まれるかどうか
BOOL p_cell::inclusion(const p_cell& c1) const
{
	for(INDEX i=0;i<c1.n;i++)
	{
		if( !inclusion(c1[i]) )return FALSE;
	}
	return TRUE;
}

//c1,c2の共通部分
p_cell intersection(const p_cell& c1, const p_cell& c2)
{
	p_cell ret(MAX_NUMBER_PER_CELL);
	ret.n=0;

	for(INDEX i=0;i<c1.n;i++)
	{
		if(c2.inclusion(c1[i]))
		{
			ret[ret.n]=c1[i];
			ret.n++;
		}
	}
	return ret;
}

//
//以下の関数は自分自身がソートされているときにのみ使う。
//大小関係を決める
int cellcmp(const p_cell& c1, const p_cell& c2)
{
	int i;
	for(i=0;i<c1.n;i++)
	{
		if(i>=c2.n)
			return 1;
		else if(c1[i]<c2[i])
			return 1;
		else if (c1[i]>c2[i])
			return -1;
	}
	
	if(c2.n>c1.n)return -1;
	else return 0;
}

//INDEX ixがp_cell cに属するかどうか
BOOL p_cell::inclusion_s(INDEX ix)  const
{
	int l=0,u=n-1;
	int m=(u+l)/2;
	
	if(ix==ptr[u])return TRUE;
	while(1)
	{
		if(ix==ptr[m])		return TRUE;
		else 
		{
			if(u-l<=1)break;
			
			if(ix>ptr[m])	l=m;
			else 				u=m;
		}
		
		m=(u+l)/2;
	};
	return FALSE;
}

//cell c1がcell c2に含まれるかどうか
BOOL p_cell::inclusion_s(const p_cell& c1)  const
{
	for(INDEX i=0;i<c1.n;i++)
	{
		if( !inclusion_s(c1[i]) )return FALSE;
	}
	return TRUE;
}

//c1,c2の共通部分
p_cell intersection_s(const p_cell& c1, const p_cell& c2)
{
	p_cell ret(MAX_NUMBER_PER_CELL);
	ret.n=0;

	for(INDEX i=0;i<c1.n;i++)
	{
		if(c2.inclusion_s(c1[i]))
		{
			ret[ret.n]=c1[i];
			ret.n++;
		}
	}
	return ret;
}

