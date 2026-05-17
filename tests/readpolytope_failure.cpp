#include "polytope_loader.h"

int main()
{
    char name[] = "__missing_polytope__";
    return ReadPolytope(name) ? 1 : 0;
}
