extern int ReadPolytope(char* pname);

int main()
{
    char name[] = "c8";
    return ReadPolytope(name) ? 0 : 1;
}

