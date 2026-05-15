#include "polytope.h"

int main()
{
    Vector4 v(1.0, 2.0, 3.0, 4.0);
    projector p;
    Vector3 projected = p.projection(v);
    return projected.norm() > 0.0 ? 0 : 1;
}

