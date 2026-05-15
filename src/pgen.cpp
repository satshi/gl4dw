/* -------------------------------------------------------------------------
 *	多胞体を生成するクラスのメンバー関数
 *	１９９６年　１０月　　山口　哲
 * ---------------------------------------------------------------------- */

#include "polytope.h"
#include "pgen.h"

/* -------------------------------------------------------------------------
 *	角柱を生成する
 * ---------------------------------------------------------------------- */
void mn_generater::generate(polytope& p)
{
	double lm,ln,ll;
	int i,j,c=0;

	lm=1.0/sin(M_PI/m);
	ln=1.0/sin(M_PI/n);
	
	delete p.vertices;
	p.vertices=new points(m*n);
	for(i=0;i<m;i++)for(j=0;j<n;j++)
	{
		(*p.vertices)[c][0]=lm*cos(2.0*M_PI*i/m);
		(*p.vertices)[c][1]=lm*sin(2.0*M_PI*i/m);
		(*p.vertices)[c][2]=ln*cos(2.0*M_PI*j/n);
		(*p.vertices)[c][3]=ln*sin(2.0*M_PI*j/n);
		c++;
	}
	ll=1.0/sqrt(lm*lm+ln*ln);
	for(i=0;i<p.vertices->n;i++)(*p.vertices)[i]*=ll;
	p.vertices->edgelength=distance((*p.vertices)[1],(*p.vertices)[2]);

	points fcenter(m*n+m+n);//面の中心。一時的に使う。
	c=0;
	for(i=0;i<m;i++)for(j=0;j<n;j++)
	{
		fcenter[c][0]=lm*cos(2.0*M_PI*(i+0.5)/m)/ll;
		fcenter[c][1]=lm*sin(2.0*M_PI*(i+0.5)/m)/ll;
		fcenter[c][2]=ln*cos(2.0*M_PI*(j+0.5)/n)/ll;
		fcenter[c][3]=ln*sin(2.0*M_PI*(j+0.5)/n)/ll;
		c++;
	}
	for(i=0;i<m;i++)
	{
		fcenter[c][0]=cos(2.0*M_PI*i/m);
		fcenter[c][1]=sin(2.0*M_PI*i/m);
		fcenter[c][2]=0;
		fcenter[c][3]=0;
		c++;
	}
	for(i=0;i<n;i++)
	{
		fcenter[c][0]=0;
		fcenter[c][1]=0;
		fcenter[c][2]=cos(2.0*M_PI*i/n);
		fcenter[c][3]=sin(2.0*M_PI*i/n);
		c++;
	}

	delete p.Facet_nomals;
	p.Facet_nomals=new points(m+n);
	c=0;
	for(i=0;i<m;i++)
	{
		(*p.Facet_nomals)[c][0]=cos(2.0*M_PI*(i+0.5)/m);
		(*p.Facet_nomals)[c][1]=sin(2.0*M_PI*(i+0.5)/m);
		(*p.Facet_nomals)[c][2]=0;
		(*p.Facet_nomals)[c][3]=0;
		c++;
	}
	for(i=0;i<n;i++)
	{
		(*p.Facet_nomals)[c][0]=0;
		(*p.Facet_nomals)[c][1]=0;
		(*p.Facet_nomals)[c][2]=cos(2.0*M_PI*(i+0.5)/n);
		(*p.Facet_nomals)[c][3]=sin(2.0*M_PI*(i+0.5)/n);
		c++;
	}
	delete p.faces;p.faces=NULL;
	p.make__edges_from_vertices();
	delete p.faces;p.faces=new cells(fcenter,*p.vertices);
	p.make__Facets();

	delete p.flag_Facets;
	p.flag_Facets=new flag(p.Facet_nomals->n);
	delete p.flag_faces;
//	p.flag_faces=new flag(p.fcenter->n);
	delete p.Facets_to_edges;p.Facets_to_edges=NULL;
	delete p.Facets_to_faces;p.Facets_to_faces=NULL;
}

/* -------------------------------------------------------------------------
 *	半角柱を生成する
 * ---------------------------------------------------------------------- */
void anti_mn_generater::generate(polytope& p)
{
	double lm,ln,ll;
	int i,j,c=0,cc=0,k;

	m *= 2; n *= 2;
	lm=1.0/sin(M_PI/m);
	ln=1.0/sin(M_PI/n);
	delete p.vertices;
	p.vertices=new points(m*n/2);
	for(i=0;i<m;i++)for(j=0;j<n;j+=2)
	{
		(*p.vertices)[c][0]=lm*cos(2.0*M_PI*i/m);
		(*p.vertices)[c][1]=lm*sin(2.0*M_PI*i/m);
		(*p.vertices)[c][2]=ln*cos(2.0*M_PI*(j+i%2)/n);
		(*p.vertices)[c][3]=ln*sin(2.0*M_PI*(j+i%2)/n);
		c++;
	}
	ll=1.0/sqrt(lm*lm+ln*ln);
	for(i=0;i<p.vertices->n;i++)(*p.vertices)[i]*=ll;
	p.vertices->edgelength=distance((*p.vertices)[1], (*p.vertices)[2]);


	points fcen(m+n);
	c=0;

	for(i=0;i<m;i++)
	{
		fcen[c][0]=cos(2.0*M_PI*i/m);
		fcen[c][1]=sin(2.0*M_PI*i/m);
		fcen[c][2]=0;
		fcen[c][3]=0;
		c++;
	}
	for(i=0;i<n;i++)
	{
		fcen[c][0]=0;
		fcen[c][1]=0;
		fcen[c][2]=cos(2.0*M_PI*i/n);
		fcen[c][3]=sin(2.0*M_PI*i/n);
		c++;
	}

	delete p.Facet_nomals;
	p.Facet_nomals=new points(m+n+m*n/2);
	c=0;
	for(i=0;i<m;i++)for(j=0;j<n;j+=2)
	{
		(*p.Facet_nomals)[c][0]=lm*cos(2.0*M_PI*i/m);
		(*p.Facet_nomals)[c][1]=lm*sin(2.0*M_PI*i/m);
		(*p.Facet_nomals)[c][2]=ln*cos(2.0*M_PI*(j+i%2-1)/n);
		(*p.Facet_nomals)[c][3]=ln*sin(2.0*M_PI*(j+i%2-1)/n);
		c++;
	}

	for(i=0;i<c;i++)(*p.Facet_nomals)[i]*=ll;

	for(i=0;i<m;i++)
	{
		(*p.Facet_nomals)[c][0]=cos(2.0*M_PI*(i+0.5)/m);
		(*p.Facet_nomals)[c][1]=sin(2.0*M_PI*(i+0.5)/m);
		(*p.Facet_nomals)[c][2]=0;
		(*p.Facet_nomals)[c][3]=0;
		c++;
	}
	for(i=0;i<n;i++)
	{
		(*p.Facet_nomals)[c][0]=0;
		(*p.Facet_nomals)[c][1]=0;
		(*p.Facet_nomals)[c][2]=cos(2.0*M_PI*(i+0.5)/n);
		(*p.Facet_nomals)[c][3]=sin(2.0*M_PI*(i+0.5)/n);
		c++;
	}
	p.make__Facets();
	cells facese(fcen,*p.vertices);
	delete p.faces;
	p.faces=new cells(m*n*2+m+n);
	for(i=0;i<m+n;i++)(*p.faces)[i]=facese[i];
	c=m+n;
	for(i=0;i<m*n/2;i++)
	{
		for(j=0;j<4;j++)
		{
			cell buf((int)3);
			cc=0;
			for(k=0;k<4;k++)
			{
				if(j!=k)
				{
					buf[cc]=(*p.Facets)[i][k];
					cc++;
				}
			}
			(*p.faces)[c]=buf;
			c++;
		}
	}
	delete p.flag_Facets;
	p.flag_Facets=new flag(p.Facet_nomals->n);
	delete p.flag_faces;
	p.flag_faces=new flag(p.faces->n);
	delete p.Facets_to_faces;p.Facets_to_faces=NULL;
	delete p.Facets_to_edges;p.Facets_to_edges=NULL;
}
