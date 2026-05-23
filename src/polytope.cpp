/* -------------------------------------------------------------------------
 *	多胞体クラスの関数
 * ---------------------------------------------------------------------- */
#include "polytope.h"
#include <stdlib.h>
#include <stdio.h>

using std::cerr;
using std::endl;

#define NONSENSE_INDEX (-1)
#define message(A)

polytope::~polytope()
{
}

polytope* polytope::slice(const aVector4& e, double b)
{
	int i;

	if((!edges) || (!vertices))return NULL;

	flag f_v(vertices->n);
	points new_v(edges->n);
	cell ix_e(edges->n);

	f_v.gen(e[3], *vertices, b);

	new_v.n=0;
	for(i=0;i<edges->n;i++)
	{
		int i0=(*edges)[i][0], i1=(*edges)[i][1];

		if(f_v[i0] ^ f_v[i1])
		{
			//稜と切断面との交点を求める。
			Vector4& v0=(*vertices)[i0];
			Vector4& v1=(*vertices)[i1];
			double d0=v0*e[3]-b;
			double d1=v1*e[3]-b;

			new_v[new_v.n]=1/(d0-d1)*(d0 * v1 - d1 * v0);
			ix_e[i]=new_v.n;
			new_v.n++;
		}
		else ix_e[i]=NONSENSE_INDEX;
	}
		polytope* ret=new polytope();
		ret->vertices.reset(new points(new_v));
		//切り口の胞を設定する。
		ret->Facets.reset(new cells(1));
		(*(ret->Facets))[0].renew(new_v.n);
		for(i=0;i<ret->Facets->n;i++)(*(ret->Facets))[0][i]=i;

		ret->Facet_normals.reset(new points(1));
		(*(ret->Facet_normals))[0]=e[3];

	if(faces)//面のデータがあれば稜のデータを作る。
	{
		if(!faces_to_edges)make__faces_to_edges();
		cells new_e(faces->n);

		new_e.n=0;
		for(int i=0;i<faces_to_edges->n;i++)
		{
			cell& cc=(*faces_to_edges)[i];
			int vi=0;
			for(int j=0;j<cc.n;j++)
			{
				if(ix_e[cc[j]]!=NONSENSE_INDEX)
				{
					if(vi==0)new_e[new_e.n].renew(2);

					new_e[new_e.n][vi]=ix_e[cc[j]];

					if(vi==1)
					{
						new_e.n++;
						goto next_face;
					}
					vi++;
				}
			}
		  next_face: ;
		}
		ret->edges.reset(new cells(new_e));
	}

	if(Facets)//胞のデータがあれば面のデータを作る。
	{
		if(!Facets_to_edges)make__Facets_to_edges();
		cells new_f(Facets->n);
		cell buf(MAX_NUMBER_PER_CELL);
		new_f.n=0;
		for(int i=0;i<Facets_to_edges->n;i++)
		{
			cell& cc=(*Facets_to_edges)[i];
			buf.n=0;

			for(int j=0;j<cc.n;j++)
			{
				if(ix_e[cc[j]]!=NONSENSE_INDEX)
				{
					buf[buf.n]=ix_e[cc[j]];
					buf.n++;
				}
			}

			if(buf.n!=0)
			{
				new_f[new_f.n]=buf;
				new_f.n++;
			}
		}
		ret->faces.reset(new cells(new_f));
	}
	return ret;
}

polytope* polytope::cut(const aVector4& e, double b, BOOL include_slice)
{
	int i;
	if((!edges) || (!vertices))return NULL;

	flag f_v(vertices->n);
	points new_v(edges->n+vertices->n);
	cell ix_e(edges->n);
	cell ix_v(vertices->n);

	f_v.gen(e[3], *vertices, b);

	new_v.n=0;
	for(i=0;i<edges->n;i++)
	{
		int i0=(*edges)[i][0], i1=(*edges)[i][1];

		if(f_v[i0] ^ f_v[i1])
		{
			//稜と切断面との交点を求める。
			Vector4& v0=(*vertices)[i0];
			Vector4& v1=(*vertices)[i1];
			double d0=v0*e[3]-b;
			double d1=v1*e[3]-b;

			new_v[new_v.n]=1/(d0-d1)*(d0 * v1 - d1 * v0);
			ix_e[i]=new_v.n;
			new_v.n++;
		}
		else ix_e[i]=NONSENSE_INDEX;
	}
	//int origin=new_v.n;
	polytope* ret=new polytope();

	//頂点を設定する
	for(i=0;i<vertices->n;i++)
	{
		if(f_v[i])
		{
			new_v[new_v.n]=(*vertices)[i];
			ix_v[i]=new_v.n;
			new_v.n++;
		}
		else ix_v[i]=NONSENSE_INDEX;
	}
	ret->vertices.reset(new points(new_v));

	//切り口の胞を設定する。
/*	ret->Facets.reset(new cells(1));
	(*Facets)[0].renew(new_v.n);
	for(i=0;i<Facets->n;i++)(*Facets)[0][i]=i;
*/

	ret->Facet_normals.reset(new points(1));
	(*(ret->Facet_normals))[0]=e[3];

	if(faces)//面のデータがあれば稜のデータを作る。
	{
		if(!faces_to_edges)make__faces_to_edges();
		cells new_e(faces->n+edges->n);

		new_e.n=0;
		if(include_slice)
		for(int i=0;i<faces_to_edges->n;i++)
		{
			cell& cc=(*faces_to_edges)[i];
			int vi=0;
			for(int j=0;j<cc.n;j++)
			{
				if(ix_e[cc[j]]!=NONSENSE_INDEX)
				{
					if(vi==0)new_e[new_e.n].renew(2);

					new_e[new_e.n][vi]=ix_e[cc[j]];

					if(vi==1)
					{
						new_e.n++;
						goto next_face;
					}
					vi++;
				}
			}
		  next_face: ;
		}
		for(int i=0;i<edges->n;i++)
		{
			int i0=(*edges)[i][0],i1=(*edges)[i][1];
			if(f_v[i0] && f_v[i1])
			{
				new_e[new_e.n].renew(2);
				new_e[new_e.n][0]=ix_v[i0];
				new_e[new_e.n][1]=ix_v[i1];
				new_e.n++;
			}
			else if(f_v[i0] && !(f_v[i1]))
			{
				new_e[new_e.n].renew(2);
				new_e[new_e.n][0]=ix_e[i];
				new_e[new_e.n][1]=ix_v[i0];
				new_e.n++;
			}
			else if(!(f_v[i0]) && f_v[i1])
			{
				new_e[new_e.n].renew(2);
				new_e[new_e.n][0]=ix_e[i];
				new_e[new_e.n][1]=ix_v[i1];
				new_e.n++;
			}
		}
		ret->edges.reset(new cells(new_e));

		if(Facets)//胞のデータがあれば面のデータを作る。
		{
			if(!Facets_to_edges)make__Facets_to_edges();
			cells new_f(Facets->n+faces->n);
			cell buf(MAX_NUMBER_PER_CELL);
			
			new_f.n=0;
			for(int i=0;i<Facets_to_edges->n;i++)
			{
				cell& cc=(*Facets_to_edges)[i];
				buf.n=0;
				
				for(int j=0;j<cc.n;j++)
				{
					if(!(ix_e[cc[j]]==NONSENSE_INDEX))
					{
						buf[buf.n]=ix_e[cc[j]];
						buf.n++;
					}
				}
				
				if(buf.n!=0)
				{
					new_f[new_f.n]=buf;
					new_f.n++;
				}
			}
			ret->faces.reset(new cells(new_f));
		}
	}
	return ret;
}

BOOL polytope::make_faces_from_Facets()
{
	int i,j,k;
	cells tfaces(MAX_NUMBER_OF_FACES);
	tfaces.n=0;
	int vn;
	cell buf(MAX_NUMBER_PER_CELL);
    if(!Facets)return FALSE;
	if(vertices)
	{
		vn=vertices->n;
	}
	else
	{
		vn=0;
		for(i=0;i<Facets->n;i++)
			for(j=0;j<(*Facets)[i].n;j++)
				vn=vn>(*Facets)[i][j] ? vn : (*Facets)[i][j];
	vn++;
	}

	int *hash=new int[vn+1];
	for(i=0;i<vn;i++)hash[i]=0;

	cerr<<"making faces\n";
	for(i=0; i<Facets->n-1;i++)
	{
		// メッセージ処理、パーセント表示
		if((i%100)==0)
		{
			if(tfaces.interrupt(i*100/Facets->n))return FALSE;
		}
		// ここまで
		cell& c1=(*Facets)[i];
		for(j=0;j<c1.n;j++)hash[c1[j]]=1;

		for(j=i+1; j<Facets->n;j++)
		{
			//cell buf=intersection((*Facets) [i],(*Facets) [j]);
			cell& c2=(*Facets) [j];
			buf.n=0;
			for(k=0;k<c2.n;k++)
			{
				if(hash[c2[k]]!=0)
				{
					buf[buf.n]=c2[k];
					buf.n++;
				}
			}
			
			if(buf.n>=3)  //含まれる頂点の個数が３以上なら面である
			{
				if(!(tfaces.n%50))cerr<<"face "<<tfaces.n<<endl;
				tfaces[tfaces.n]=buf;
				tfaces.n++;
			}
		}
		for(j=0;j<c1.n;j++)hash[c1[j]]=0;
	}

	delete[] hash;
	
	faces.reset(new cells(tfaces));
	cerr<<"making edges\n";
	if(!make_edges_from_Facets_and_faces())return FALSE;
	cerr<<"sorting\n";
	faces->F_sort(*edges);
	return TRUE;
}

BOOL polytope::make_edges_from_Facets_and_faces()
{
	cells tedges(MAX_NUMBER_OF_EDGES);
	tedges.n=0;
	INDEX i,j,k,vn;
	cell buf;
	if(!Facets || !faces)return FALSE;

	if(vertices)
	{
		vn=vertices->n;
	}
	else
	{
		vn=0;
		for(i=0;i<Facets->n;i++)
			for(j=0;j<(*Facets)[i].n;j++)
				vn=vn>(*Facets)[i][j] ? vn : (*Facets)[i][j];
	vn++;
	}

	int *hash=new int[vn+1];
	for(i=0;i<vn;i++)hash[i]=0;

	for(i=0; i<Facets->n-1;i++)
	{
		// メッセージ処理、パーセント表示
		if((i%100)==0)
		{
			if(tedges.interrupt(i*100/Facets->n))return FALSE;
		}
		// ここまで
		cell& c1=(*Facets)[i];
		for(j=0;j<c1.n;j++)hash[c1[j]]=1;
		
		for(j=0; j<faces->n;j++)
		{
			//buf=intersection((*Facets) [i],(*faces) [j]);
			cell& c2=(*faces) [j];
			buf.n=0;
			for(k=0;k<c2.n;k++)
			{
				if(hash[c2[k]]!=0)
				{
					buf[buf.n]=c2[k];
					buf.n++;
				}
			}

			if(buf.n==2)  //含まれる頂点の個数が２なら稜である
			{
				if(!(tedges.n%50))cerr<<"edge "<<tedges.n<<endl;
				tedges[tedges.n]=buf;
				tedges.n++;
			}
		}
		for(j=0;j<c1.n;j++)hash[c1[j]]=0;
	}
	
	delete[] hash;
	//重複を解消する
	INDEX m=1;
	for(i=1;i<tedges.n;i++)
	{
		for(j=0;j<m;j++)
		{
			if((tedges[i][0]==tedges[j][0] && tedges[i][1]==tedges[j][1])
			  ||  (tedges[i][0]==tedges[j][1] && tedges[i][1]==tedges[j][0]))
			  {goto loop1;}//(*edges)[i]と(*edges)[j]が同じなら次へ
		}
		tedges[m]=tedges[i];
		m++;

		loop1:;
	}
	tedges.n=m;
	edges.reset(new cells(tedges));
	return TRUE;
}

