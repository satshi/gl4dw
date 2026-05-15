/* -------------------------------------------------------------------------
 *	‘½–E‘Ì‚ğ¶¬‚·‚éƒNƒ‰ƒX‚Ìƒwƒbƒ_
 *	‚P‚X‚X‚U”N@‚P‚OŒ@@RŒû@“N
 * ---------------------------------------------------------------------- */

#ifndef PGEN_H_
#define PGEN_H_

class polytope;

class polytope_generater
{
  public:
	virtual void generate(polytope&)=0;
};

class mn_generater:polytope_generater
{
  public:
	int m;
	int n;

	mn_generater(int mm, int nn)
	{
		m=mm;
		n=nn;
	}
	virtual void generate(polytope&);
};

class anti_mn_generater:mn_generater
{
  public:
	int m;
	int n;
	anti_mn_generater(int mm, int nn)
		:mn_generater(mm,nn){}
	virtual void generate(polytope&);
};

class dual_generater:polytope_generater
{
	
};
#endif  //ifndef PGEN_H_
