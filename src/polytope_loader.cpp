#include "polytope_loader.h"
#include <fstream>
#include <filesystem>

using std::cerr;
using std::endl;
using std::ifstream;
using std::ios;

polytope poly;
std::string data_dir = "data";

static int open_data_file(ifstream& is, std::string& fname, const std::string& file_name)
{
	if(is.is_open()) is.close();
	is.clear();

	std::filesystem::path path = std::filesystem::path(data_dir) / file_name;
	fname = path.string();
	is.open(fname.c_str(), ios::in);
	if(!is && data_dir == "data")
	{
		is.clear();
		path = std::filesystem::path("..") / "data" / file_name;
		fname = path.string();
		is.open(fname.c_str(), ios::in);
	}
	return !!is;
}

int ReadPolytope(char* pname)
{
	std::string fname;
	std::string ccfname;

	ifstream is;
	if(!open_data_file(is, fname, std::string(pname) + ".poi"))
	{
		cerr<<"Cannot open file"<<fname<<endl;
		return 0;
	}
	poly.read_vertices(is);
	is>>ccfname;
	if(!open_data_file(is, fname, std::string("f") + pname + ".cel"))
	{
		cerr<<"Cannot open file"<<fname<<endl;
		return 0;
	}
	poly.read_faces(is);
	if(!open_data_file(is, fname, ccfname))
	{
		cerr<<"Cannot open file"<<fname<<endl;
		return 0;
	}
	poly.read_Facet_normals(is);
	double l=1.0/(*poly.vertices)[0].norm();
	for(int i=0;i<poly.vertices->n;i++)
	{
		(*poly.vertices)[i]*=l;
	}
	poly.make__Facets();
	poly.make__Facets_to_faces();
	for(int i=0;i<poly.Facets->n;i++)
	{
		Vector4& cv=(*poly.Facet_normals)[i];
		cv*=1.0/cv.norm();
	}

	return 1;
}
