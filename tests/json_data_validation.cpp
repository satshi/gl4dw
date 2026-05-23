#include "polytope_loader.h"

#include <filesystem>
#include <string>

namespace {

int require_loaded_polytope()
{
    if(!poly.vertices || poly.vertices->n <= 0) return 10;
    if(!poly.faces || poly.faces->n <= 0) return 11;
    if(!poly.Facet_normals || poly.Facet_normals->n <= 0) return 12;
    if(!poly.Facets || poly.Facets->n <= 0) return 13;
    if(!poly.Facets_to_faces || poly.Facets_to_faces->n <= 0) return 14;

    for(int i = 0; i < poly.faces->n; ++i) {
        if((*poly.faces)[i].n < 3) return 20;
        for(int j = 0; j < (*poly.faces)[i].n; ++j) {
            int index = (*poly.faces)[i][j];
            if(index < 0 || index >= poly.vertices->n) return 21;
        }
    }

    for(int i = 0; i < poly.Facets->n; ++i) {
        if((*poly.Facets)[i].n < 4) return 30;
        for(int j = 0; j < (*poly.Facets)[i].n; ++j) {
            int index = (*poly.Facets)[i][j];
            if(index < 0 || index >= poly.vertices->n) return 31;
        }
    }

    for(int i = 0; i < poly.Facets_to_faces->n; ++i) {
        for(int j = 0; j < (*poly.Facets_to_faces)[i].n; ++j) {
            int index = (*poly.Facets_to_faces)[i][j];
            if(index < 0 || index >= poly.faces->n) return 41;
        }
    }

    return 0;
}

} // namespace

int main()
{
    data_dir = "../data_json";
    std::filesystem::path dir(data_dir);
    if(!std::filesystem::is_directory(dir)) return 1;

    int loaded = 0;
    for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(dir)) {
        if(entry.path().extension() != ".json") continue;
        std::string name = entry.path().stem().string();
        if(!ReadPolytopeJson(&name[0])) return 2;
        if(int rc = require_loaded_polytope()) return rc;
        ++loaded;
    }

    return loaded > 0 ? 0 : 3;
}
