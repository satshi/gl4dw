extern int ReadPolytope(char* pname);

int main()
{
    char name[] = "__missing_polytope__";
    return ReadPolytope(name) ? 1 : 0;
}
