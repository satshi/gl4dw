/* -------------------------------------------------------------------------

 *	‘½–E‘ÌƒNƒ‰ƒX‚Ìƒwƒbƒ_

 *	1996 3 S.yamaguchi

‘½–E‘Ì‚Ì•\Ž¦‚È‚Ç‚Å‹@ŽíˆË‘¶•”‚ð‚¨‚»‚ç‚­ŠÜ‚Ü‚È‚¢•”•ªB
ŽÀÛ‚ÉŽg‚¤‚Æ‚«‚Í‘½dŒp³‚È‚Ç‚Å‹@ŽíˆË‘¶•”‚Æ‚ ‚í‚¹‚éB
 * ---------------------------------------------------------------------- */

#ifndef _POLYTOPE_H
#define _POLYTOPE_H

#include "cells.h"
#include "proj.h"
#include "points.h"

//‘½–E‘Ì
class polytope
{
  public:
	char* name;
	points* vertices;
	cells* edges;
	cells* faces;
	cells* Facets;

	points* Facet_nomals;
	cells* Facets_to_faces;
	cells* Facets_to_edges;
	cells* faces_to_edges;
	flag* flag_Facets;
	flag* flag_faces;
	flag* flag_edges;
	flag* flag_vertices;

	polytope();
	virtual ~polytope();

	//===================		 “ü—ÍŠÖ”
	BOOL read_vertices(istream& is);
	BOOL read_Facet_nomals(istream& is);
	BOOL read_faces(istream& is);
	BOOL read_Facets(istream& is);
	
	void load_base(char*);

	//========================	   —v‘f‚ð¶¬‚·‚éŠÖ”
	BOOL make__Facets();
	BOOL make__Facets_to_faces();
	BOOL make__Facets_to_edges();
	BOOL make__faces_to_edges();
	BOOL make_faces_from_Facets();
	BOOL make_edges_from_Facets_and_faces();
	BOOL make__edges_from_vertices();

	//‘½–E‘Ì‚ð‰ÁH‚·‚éŠÖ”
	polytope* slice(const aVector4&, double);
	polytope* cut(const aVector4&, double, BOOL include_slice=FALSE);

	//‚RŽŸŒ³ƒf[ƒ^‚ðo—Í‚·‚éB

	BOOL pov_blob(ostream& os, const projector& ev=projector::standerd);
	BOOL pov_cylinder(ostream& os, const projector& ev=projector::standerd);
	BOOL pov_polygon(ostream& os, const projector& ev=projector::standerd);
	BOOL write_x(ostream& os, const projector& ev=projector::standerd);
};

inline polytope::polytope()
{
	vertices=NULL;
	edges=NULL;
	faces=NULL;
	Facets=NULL;
	Facets_to_faces=NULL;
	Facets_to_edges=NULL;
	faces_to_edges=NULL;
	flag_Facets=NULL;
	flag_faces=NULL;
	flag_edges=NULL;
	flag_vertices=NULL;
}

//===================		 “ü—ÍŠÖ”
inline BOOL polytope::read_vertices(istream& is)
{
	delete vertices;
	vertices=new points();
	is>>(*vertices);
	return TRUE;
}

inline BOOL polytope::read_Facet_nomals(istream& is)
{
	delete Facet_nomals;
	Facet_nomals=new points();
	is>>(*Facet_nomals);
	return TRUE;
}

inline BOOL polytope::read_faces(istream& is)
{
	delete faces;
	faces=new cells();
	is>>(*faces);
	return TRUE;
}

inline BOOL polytope::read_Facets(istream& is)
{
	delete Facets;
	Facets=new cells();
	is>>(*Facets);
	return TRUE;
}


//========================	   —v‘f‚ð¶¬‚·‚éŠÖ”
inline BOOL polytope::make__Facets()
{
	if((!vertices) || (!Facet_nomals))return FALSE;
	delete Facets;
	Facets=new cells(*Facet_nomals, *vertices);
	delete flag_Facets;
	flag_Facets=new flag(Facets->n);
	return TRUE;
}

inline BOOL polytope::make__Facets_to_faces()
{
	if((!Facets) || (!faces))return FALSE;
	delete Facets_to_faces;
	Facets_to_faces=new cells(*faces, *Facets);
	return TRUE;
}

inline BOOL polytope::make__Facets_to_edges()
{
	if((!Facets) || (!edges))return FALSE;
	delete Facets_to_edges;
	Facets_to_edges=new cells(*edges, *Facets);
	return TRUE;
}

inline BOOL polytope::make__faces_to_edges()
{
	if((!faces) || (!edges))return FALSE;
	delete faces_to_edges;
	faces_to_edges=new cells(*edges, *faces);
	return TRUE;
}

inline BOOL polytope::make__edges_from_vertices()
{
	if(!vertices)return FALSE;
	delete edges;
	edges=vertices->edges_of_unit_length();
	delete flag_edges;
	flag_edges=new flag(edges->n);
	return TRUE;
}

#endif
