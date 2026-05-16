#include "cells.h"
//	***************** 	セルたちの関数		*********************
//コンストラクタ
/*
cells::cells(char* fname )
{
	int i;
	ifstream ifs(fname);

	ifs>>nf;
	fa=new   Cell[nf+1];
	for(i=1;i<nf;i++)ifs>>fa[i];
}
*/

//下位のセルc1のデータと上位のセルc2に属する頂点のデータから、
//上位のセルに属する下位のセルのデータを求める
cells::cells(const acell& c1,const acell& c2,int vn/*=0*/)
{
	int i,j,k,m;
	cell buf(MAX_NUMBER_PER_CELL);

	renew(c2.n);
	if(vn==0)
	{
		for(i=0;i<c2.n;i++)
			for(j=0;j<c2[i].n;j++)
				vn=vn>c2[i][j] ? vn : c2[i][j];
	vn++;
	}

	int *hash=new int[vn+1];
	
	for(i=0;i<vn;i++)hash[i]=0;


	for(i=0;i<n;i++)
	{
		// メッセージ処理、パーセント表示
		if((i%100)==0)
		{
			if(interupt(i*100/n))return;
		}
		// ここまで

		for(j=0;j<c2[i].n;j++)hash[c2[i][j]]=1;
		m=0;
		for(j=0;j<c1.n;j++)
		{

			for(k=0;k<c1[j].n;k++)
			{
				if(hash[c1[j][k]]==0)goto next;
			}
			//c1[j]がc2[i]にふくまれていたら
			buf[m]=j;
			m++;
		  next:;
		}
		buf.n=m;
		ptr[i]=buf;
		for(j=0;j<c2[i].n;j++)hash[c2[i][j]]=0;
	}
	delete[] hash;
}


cells::cells(const aVector4& center /*セルの中心*/ , const aVector4& vx /*頂点*/ )
{
	renew(center.n);

	int i;
	for(i=0;i<n;i++)
	{
//      メッセージ処理、パーセント表示
		if((i%100)==0)
		{
			if(interupt(i*100/n))return;
		}
//      ここまで
		ptr[i]=cell(center[i], vx);
	}
}

//逆に解く
void cells::inverse(const acell& ce)
{
	int i,j,nn=0,m;

	//要素の最大値を求める
	for(i=0;i<ce.n;i++)
		for(j=0;j<ce[i].n;j++)
			if(nn<ce[i][j]) nn=ce[i][j];

	renew(nn);

	cell buf(MAX_NUMBER_PER_CELL);//一時変数
	for(i=0;i<n;i++)
	{
//      メッセージ処理、パーセント表示
			if(interupt(i*100/n))return;
//      ここまで
		m=0;

		for(j=0;j<ce.n;j++)
		{
			if(ce[j].inclusion_s(i)) //iがce[j]にふくまれていれば
			{
				buf[m]=j;
				m++;
			}
		}
		buf.n=m;
		ptr[i]=buf;
	}
}

//逆に解く
cells* cells::inverse() const
{
	int i,j,nn=0,m;
	cells* ret;

	//要素の最大値を求める
	for(i=0;i<n;i++)
		for(j=0;j<ptr[i].n;j++)
			if(nn<ptr[i][j]) nn=ptr[i][j];

	ret=new cells(nn);
	cell buf(MAX_NUMBER_PER_CELL);//一時変数
	for(i=0;i<ret->n;i++)
	{
//      メッセージ処理、パーセント表示
		if(i%100==0)
		{
			if(ret->interupt(i*100/(ret->n)))return NULL;
		}
//      ここまで
		m=0;

		for(j=0;j<n;j++)
		{
			if(ptr[j].inclusion_s(i)) //iがce[j]にふくまれていれば
			{
				buf[m]=j;
				m++;
			}
		}
		buf.n=m;
		(*ret)[i]=buf;
	}
	return ret;
}

cells* cells::break_face()
{
	int i,j,nn,k,c=0;
	int* ix;
	cells  ed(MAX_NUMBER_OF_EDGES);

	for(i=0;i<n;i++)
	{
		ix=ptr[i];
		nn=ptr[i].n;
		for(j=0;j<nn-1;j++)
		{
			for(k=0;k<c;k++)if(ed[k][0]==ix[j] && ed[k][1]==ix[j+1]
							 || ed[k][1]==ix[j] && ed[k][0]==ix[j+1])goto miss;
			ed[c].renew(2);
			ed[c][0]=ix[j]; ed[c][1]=ix[j+1];
			c++;
			miss:;
		}
		for(k=0;k<c;k++)if(ed[k][0]==ix[0] && ed[k][1]==ix[nn-1]
						 || ed[k][1]==ix[0] && ed[k][0]==ix[nn-1])goto miss2;
		ed[c].renew(2);
		ed[c][0]=ix[0]; ed[c][1]=ix[nn-1];
		c++;
		miss2:;
	}
	ed.n=c;
	return new cells(ed);
}

//並べ替え、面の場合に順番を正しく並べ替える
void cells::F_sort(const acell& eds)
{
	int i;

	for(i=0;i<n;i++)
	{
		ptr[i].F_sort(eds);
//      メッセージ処理、パーセント表示
		if(i%100==0)
		{
			if(interupt(i*100/n))return;
		}
//      ここまで
	}
}

//ストリーム入出力
BOOL cells::write(ostream& os) const
{
	int i;
	os<<n<<endl;
	for(i=0;i<n;i++)
	{
		os<<ptr[i]<<endl;
	}
	return TRUE;
}

//	***********************		フラグの関数	********************
void flag::gen(const Vector4& vv, const aVector4& vx, double b)
{
	int i;

	for(i=0;i<n;i++)
	{
		if((vx[i] * vv)>b)
		{
			ptr[i]=1;
		}
		else
		{
			ptr[i]=0;
		}
	}
}

void flag::gen_from(const cells& ces,const flag& fls)
{
	int i,j;

	for(i=0;i<n;i++) ptr[i]=0;

	for(i=0;i<fls.n;i++)
	{
		if(fls[i])
			for(j=0;j<ces[i].n;j++)
			{
				ptr[ ces[i][j] ]=1;
			}
	}
}

void flag::gen_surface(const cells& ces,const flag& fls)
{
	int i,j;

	for(i=0;i<n;i++) ptr[i]=0;

	for(i=0;i<fls.n;i++)
	{
		if(fls[i])
			for(j=0;j<ces[i].n;j++)
			{
				switch(ptr[ ces[i][j] ])
				{
					case(0):ptr[ces[i][j]]=-ces[i].n;break;
					case(-1):ptr[ces[i][j]]=ces[i].n;break;
				}
			}
		else
			for(j=0;j<ces[i].n;j++)
			{
				if(ptr[ ces[i][j] ] == 0)
					ptr[ ces[i][j] ] = -1;
				else if( ptr[ ces[i][j] ] < -3)
					ptr[ ces[i][j] ] *= -1;
			}
	}

	for(i=0;i<n;i++)
	{
		ptr[i]*=(ptr[i]>0);
	}
}

//表面の胞だけを取り出す関数　to_childに胞ー＞面のデータ、、f_childに
//面のフラグ（あらかじめgen_surfaceをしておく。
void flag::gen_up(const cells& to_child,const flag& f_child)
{
	int i,j;

	for(i=0;i<n;i++)
	{
		if(ptr[i])//表の胞だけ処理する。
		{
			ptr[i]=0;
			for(j=0;j<to_child[i].n;j++)
			{
				if(f_child[ to_child[i][j] ])//表面の面を含んでいたら。
				{
					ptr[i]=1;
					break;
				}
			}
		}
	}
}
