#pragma once

#include "polytope.h"
#include <string>

extern polytope poly;
extern std::string data_dir;

int ReadPolytope(char* pname);
int ReadPolytopeJson(char* pname);
