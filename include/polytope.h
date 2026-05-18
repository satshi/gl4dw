/* -------------------------------------------------------------------------

 *	多胞体クラスのヘッダ

多胞体の表示などで機種依存部をおそらく含まない部分。
実際に使うときは多重継承などで機種依存部とあわせる。
 * ---------------------------------------------------------------------- */

#ifndef _POLYTOPE_H
#define _POLYTOPE_H

#include "cells.h"
#include "proj.h"
#include "points.h"
#include <memory>

//多胞体
class polytope
{
 public:
	char* name;
	std::unique_ptr<points> vertices;
	std::unique_ptr<cells> edges;
	std::unique_ptr<cells> faces;
	std::unique_ptr<cells> Facets;

	std::unique_ptr<points> Facet_normals;
	std::unique_ptr<cells> Facets_to_faces;
	std::unique_ptr<cells> Facets_to_edges;
	std::unique_ptr<cells> faces_to_edges;
	std::unique_ptr<flag> flag_Facets;
	std::unique_ptr<flag> flag_faces;
	std::unique_ptr<flag> flag_edges;
	std::unique_ptr<flag> flag_vertices;

	polytope();
	polytope(const polytope&) = delete;
	polytope& operator=(const polytope&) = delete;
	virtual ~polytope();

	//===================		 入力関数
	BOOL read_vertices(istream& is);
	BOOL read_Facet_normals(istream& is);
	BOOL read_faces(istream& is);
	BOOL read_Facets(istream& is);
	
	void load_base(char*);

	//========================	   要素を生成する関数
	BOOL make__Facets();
	BOOL make__Facets_to_faces();
	BOOL make__Facets_to_edges();
	BOOL make__faces_to_edges();
	BOOL make_faces_from_Facets();
	BOOL make_edges_from_Facets_and_faces();
	BOOL make__edges_from_vertices();

	//多胞体を加工する関数
	polytope* slice(const aVector4&, double);
	polytope* cut(const aVector4&, double, BOOL include_slice=FALSE);

	//３次元データを出力する。

	BOOL pov_blob(ostream& os, const projector& ev=projector::standerd);
	BOOL pov_cylinder(ostream& os, const projector& ev=projector::standerd);
	BOOL pov_polygon(ostream& os, const projector& ev=projector::standerd);
	BOOL write_x(ostream& os, const projector& ev=projector::standerd);
};

inline polytope::polytope()
{
	name=NULL;
}

//===================		 入力関数
inline BOOL polytope::read_vertices(istream& is)
{
	vertices.reset(new points());
	is>>(*vertices);
	return TRUE;
}

inline BOOL polytope::read_Facet_normals(istream& is)
{
	Facet_normals.reset(new points());
	is>>(*Facet_normals);
	return TRUE;
}

inline BOOL polytope::read_faces(istream& is)
{
	faces.reset(new cells());
	is>>(*faces);
	return TRUE;
}

inline BOOL polytope::read_Facets(istream& is)
{
	Facets.reset(new cells());
	is>>(*Facets);
	return TRUE;
}


//========================	   要素を生成する関数
inline BOOL polytope::make__Facets()
{
	if((!vertices) || (!Facet_normals))return FALSE;
	Facets.reset(new cells(*Facet_normals, *vertices));
	flag_Facets.reset(new flag(Facets->n));
	return TRUE;
}

inline BOOL polytope::make__Facets_to_faces()
{
	if((!Facets) || (!faces))return FALSE;
	Facets_to_faces.reset(new cells(*faces, *Facets));
	return TRUE;
}

inline BOOL polytope::make__Facets_to_edges()
{
	if((!Facets) || (!edges))return FALSE;
	Facets_to_edges.reset(new cells(*edges, *Facets));
	return TRUE;
}

inline BOOL polytope::make__faces_to_edges()
{
	if((!faces) || (!edges))return FALSE;
	faces_to_edges.reset(new cells(*edges, *faces));
	return TRUE;
}

inline BOOL polytope::make__edges_from_vertices()
{
	if(!vertices)return FALSE;
	edges.reset(vertices->edges_of_unit_length());
	flag_edges.reset(new flag(edges->n));
	return TRUE;
}

#endif
