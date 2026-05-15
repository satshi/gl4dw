//セルのクラス
#include "cell.h"

//距離の最小値のクラスの関数。
void min_d::minD(const Vector4& vv,const aVector4& vx, double md)
{
	int i;
	double dis;
	d=vv*vx[0];
	for(i=0;i<vx.n;i++)
	{
		dis=vv*vx[i];
		if(/*(md<dis) &&*/ dis>d)
		{
			ix=i;
			d=dis;
		}
	}
	vp=&(vx[ix]);
}


//ある点（cellの中心）から同じ距離（最小）にある点たちをcellとする。
//

cell::cell(const Vector4& center, const aVector4& vx)
{
	INDEX i, m=0, ix[MAX_NUMBER_PER_CELL];
	min_d md;

	md.minD(center, vx);

	for(i=0;i<vx.n;i++)
	{
		if(eql(md.d, center*vx[i]))
		{
			ix[m]=i;
			m++;
		}
	}
	size=m;
	n=m;
	ptr=new INDEX[size];

	for(i=0;i<n;i++)ptr[i]=ix[i];
}


void cell::F_sort(const acell& edges)
{
	INDEX j,k,l,m;

	if(n>3) //   三角形でないならば後の処理をする
	for(j=0;j<n-1;j++)
	{
		for(k=j+1;k<n;k++)
		for(l=0;l<edges.n;l++)
		{
			if( (edges[l][0]==(*this)[j] && edges[l][1]==(*this)[k]) ||
				(edges[l][1]==(*this)[j] && edges[l][0]==(*this)[k])  )
			{
			//入れ換え
			m=(*this)[j+1];(*this)[j+1]=(*this)[k];(*this)[k]=m;
			goto roop1;//ループから抜ける
			}
		}
  roop1:
		;
	}
}

BOOL cell::read(istream& is)
{
	BOOL ret=p_cell::read(is);
	for(int i=0;i<n;i++)
		(ptr[i])--;
	return ret;
}

BOOL cell::write(ostream& os) const
{
	os<<n<<" ";
	for(int i=0;i<n;i++)
		os<<(ptr[i]+1)<<" ";
	return TRUE;
}


