
#include"points.h"

cells* points::edges_of_unit_length()
{
	int i,j,m=0;
	cells e(MAX_NUMBER_OF_EDGES);

	for(i=0;i<n-1;i++)
	{
/*		if((i%100)==0)
		{
			if(e.interrupt(i*100/n))return NULL;
		}
*/
		for(j=i+1;j<n;j++)
		{
			if (eql(distance(ptr[i], ptr[j]), edgelength))
			{
				e[m].renew(2);
				e[m][0]=i;
				e[m][1]=j;
				m++;
			}
		}
	}

	e.n=m;
	return new cells(e);
}

void points::rotation(double* th)
{
	for(int i=0;i<n;i++)
	{
		ptr[i].rotation(th);
	}
}


BOOL points::read(istream& is)
{
	is>>n;
	is>>edgelength;
	renew(n);
	for(int i=0;i<n;i++)
	{
		is>>ptr[i];
	}
	return TRUE;
}

BOOL points::write(ostream& os) const
{
	os<<n<<" "<<edgelength<<endl;
	for(int i=0;i<n;i++)os<<ptr[i]<<endl;
	return TRUE;
}
