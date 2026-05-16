#include "gl4d.h"

#include <cmath>

extern polytope poly;

namespace {

bool near(double a, double b)
{
    return std::fabs(a - b) < 1.0e-6;
}

int require(bool ok, int code)
{
    return ok ? 0 : code;
}

} // namespace

int main()
{
    char name[] = "c8";
    if(!ReadPolytope(name)) return 1;

    if(int rc = require(poly.vertices && poly.vertices->n == 16, 2)) return rc;
    if(int rc = require(poly.faces && poly.faces->n == 24, 3)) return rc;
    if(int rc = require(poly.Facet_nomals && poly.Facet_nomals->n == 8, 4)) return rc;
    if(int rc = require(poly.Facets && poly.Facets->n == 8, 5)) return rc;
    if(int rc = require(poly.Facets_to_faces && poly.Facets_to_faces->n == 8, 6)) return rc;

    if(int rc = require(near(poly.vertices->edgelength, 1.0), 7)) return rc;
    if(int rc = require(near((*poly.vertices)[0][0], -0.5), 8)) return rc;
    if(int rc = require(near((*poly.vertices)[15][3], 0.5), 9)) return rc;

    for(int i = 0; i < poly.faces->n; ++i) {
        if((*poly.faces)[i].n != 4) return 10;
        for(int j = 0; j < (*poly.faces)[i].n; ++j) {
            int index = (*poly.faces)[i][j];
            if(index < 0 || index >= poly.vertices->n) return 11;
        }
    }

    for(int i = 0; i < poly.Facets->n; ++i) {
        if((*poly.Facets)[i].n != 8) return 12;
        for(int j = 0; j < (*poly.Facets)[i].n; ++j) {
            int index = (*poly.Facets)[i][j];
            if(index < 0 || index >= poly.vertices->n) return 13;
        }
    }

    for(int i = 0; i < poly.Facets_to_faces->n; ++i) {
        if((*poly.Facets_to_faces)[i].n != 6) return 14;
        for(int j = 0; j < (*poly.Facets_to_faces)[i].n; ++j) {
            int index = (*poly.Facets_to_faces)[i][j];
            if(index < 0 || index >= poly.faces->n) return 15;
        }
    }

    for(int i = 0; i < poly.Facet_nomals->n; ++i) {
        if(!near((*poly.Facet_nomals)[i].norm(), 1.0)) return 16;
    }

    return 0;
}
