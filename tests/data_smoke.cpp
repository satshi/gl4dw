#include "polytope_loader.h"

int main()
{
    char name[] = "c8";
    return ReadPolytope(name) ? 0 : 1;
}
