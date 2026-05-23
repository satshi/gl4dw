#include "polytope_loader.h"
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <limits>
#include <nlohmann/json.hpp>
#include <set>
#include <stdexcept>
#include <utility>

using std::cerr;
using std::endl;
using std::ifstream;
using std::ios;

polytope poly;
std::string data_dir = "data_json";

static int open_json_file(ifstream& is, std::string& fname, const std::string& file_name)
{
	if(is.is_open()) is.close();
	is.clear();

	std::filesystem::path path = std::filesystem::path(data_dir) / file_name;
	fname = path.string();
	is.open(fname.c_str(), ios::in);
	if(is) return 1;

	if(data_dir == "data_json")
	{
		is.clear();
		path = std::filesystem::path("..") / "data_json" / file_name;
		fname = path.string();
		is.open(fname.c_str(), ios::in);
		if(is) return 1;
	}
	return 0;
}

static void clear_polytope()
{
	poly.vertices.reset();
	poly.edges.reset();
	poly.faces.reset();
	poly.Facets.reset();
	poly.Facet_normals.reset();
	poly.Facets_to_faces.reset();
	poly.Facets_to_edges.reset();
	poly.faces_to_edges.reset();
	poly.flag_Facets.reset();
	poly.flag_faces.reset();
	poly.flag_edges.reset();
	poly.flag_vertices.reset();
}

static Vector4 read_vector4(const nlohmann::json& item, const char* key)
{
	if(!item.is_array() || item.size() != 4)
	{
		throw std::runtime_error(std::string(key) + " entries must be arrays of four numbers");
	}
	return Vector4(
		item.at(0).get<double>(),
		item.at(1).get<double>(),
		item.at(2).get<double>(),
		item.at(3).get<double>());
}

static std::unique_ptr<points> read_json_points(const nlohmann::json& data, const char* key)
{
	const nlohmann::json& items = data.at(key);
	if(!items.is_array())
	{
		throw std::runtime_error(std::string(key) + " must be an array");
	}

	std::unique_ptr<points> result(new points(static_cast<int>(items.size())));
	for(int i=0;i<result->n;i++)
	{
		(*result)[i] = read_vector4(items.at(i), key);
	}
	return result;
}

static std::unique_ptr<cells> read_json_cells(const nlohmann::json& data, const char* key, int max_index)
{
	const nlohmann::json& items = data.at(key);
	if(!items.is_array())
	{
		throw std::runtime_error(std::string(key) + " must be an array");
	}

	std::unique_ptr<cells> result(new cells(static_cast<int>(items.size())));
	for(int i=0;i<result->n;i++)
	{
		const nlohmann::json& indices = items.at(i);
		if(!indices.is_array())
		{
			throw std::runtime_error(std::string(key) + " entries must be arrays");
		}
		(*result)[i].renew(static_cast<int>(indices.size()));
		for(int j=0;j<(*result)[i].n;j++)
		{
			int index = indices.at(j).get<int>();
			if(index < 0 || index >= max_index)
			{
				throw std::runtime_error(std::string(key) + " contains an out-of-range index");
			}
			(*result)[i][j] = index;
		}
	}
	return result;
}

static double compute_edge_length(const cells& faces, const points& vertices)
{
	std::set<std::pair<int, int>> edges;
	for(int i=0;i<faces.n;i++)
	{
		const cell& face = faces[i];
		for(int j=0;j<face.n;j++)
		{
			int a = face[j];
			int b = face[(j + 1) % face.n];
			if(a > b) std::swap(a, b);
			edges.insert(std::make_pair(a, b));
		}
	}

	double edge_length = std::numeric_limits<double>::max();
	for(std::set<std::pair<int, int>>::const_iterator it = edges.begin(); it != edges.end(); ++it)
	{
		edge_length = std::min(edge_length, distance(vertices[it->first], vertices[it->second]));
	}
	if(edge_length == std::numeric_limits<double>::max())
	{
		throw std::runtime_error("faces do not describe any edges");
	}
	return edge_length;
}

static void normalize_polytope()
{
	if(!poly.vertices || poly.vertices->n == 0) return;

	double l = (*poly.vertices)[0].norm();
	if(l == 0.0)
	{
		throw std::runtime_error("first vertex has zero length");
	}
	for(int i=0;i<poly.vertices->n;i++)
	{
		(*poly.vertices)[i] *= 1.0 / l;
	}
	poly.vertices->edgelength *= 1.0 / l;

	if(poly.Facet_normals)
	{
		for(int i=0;i<poly.Facet_normals->n;i++)
		{
			Vector4& cv = (*poly.Facet_normals)[i];
			double n = cv.norm();
			if(n != 0.0) cv *= 1.0 / n;
		}
	}
}

static int ReadPolytopeJsonFromStream(ifstream& is)
{
	try
	{
		nlohmann::json data;
		is >> data;

		clear_polytope();
		poly.vertices = read_json_points(data, "vertices");
		poly.faces = read_json_cells(data, "faces", poly.vertices->n);
		poly.Facet_normals = read_json_points(data, "facetCenters");
		poly.vertices->edgelength = compute_edge_length(*poly.faces, *poly.vertices);

		if(data.find("facetToVertex") != data.end())
		{
			poly.Facets = read_json_cells(data, "facetToVertex", poly.vertices->n);
		}
		else if(!poly.make__Facets())
		{
			throw std::runtime_error("cannot derive facets from facetCenters");
		}

		if(data.find("facetToFace") != data.end())
		{
			poly.Facets_to_faces = read_json_cells(data, "facetToFace", poly.faces->n);
		}
		else if(!poly.make__Facets_to_faces())
		{
			throw std::runtime_error("cannot derive facet-to-face table");
		}

		poly.flag_vertices.reset(new flag(poly.vertices->n));
		poly.flag_faces.reset(new flag(poly.faces->n));
		poly.flag_Facets.reset(new flag(poly.Facets->n));

		normalize_polytope();
		return 1;
	}
	catch(const std::exception& e)
	{
		cerr<<"Cannot read JSON polytope: "<<e.what()<<endl;
		clear_polytope();
		return 0;
	}
}

int ReadPolytopeJson(char* pname)
{
	std::string fname;
	ifstream is;
	if(!open_json_file(is, fname, std::string(pname) + ".json"))
	{
		cerr<<"Cannot open file"<<fname<<endl;
		return 0;
	}
	return ReadPolytopeJsonFromStream(is);
}

int ReadPolytope(char* pname)
{
	std::string fname;
	ifstream is;
	if(!open_json_file(is, fname, std::string(pname) + ".json"))
	{
		cerr<<"Cannot open file"<<fname<<endl;
		return 0;
	}
	return ReadPolytopeJsonFromStream(is);
}
