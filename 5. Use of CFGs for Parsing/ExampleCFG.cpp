#include <bits/stdc++.h>

using namespace std;

int S(int, int);
int A(int, int);
int B(int, int);

int f;
char s[1000];

int main()
{
    int i, l;
    printf("CFG:\n\n");
    printf("\tS -> b | AB\n");
    printf("\tA -> a | aA\n");
    printf("\tB -> b\n\n");
    printf("Enter the string: ");
    scanf("%s", &s);
    l=strlen(s);
    if(l>=1)i=S(0, l);
    else printf("\n\nString is invalid\n");
    if(l==i && f)printf("\n\nString is valid\n");
    else printf("\n\nString is invalid\n");
    return 0;
}

int S(int i, int l)
{
    if(s[i]=='b')
    {
        i++;
        f=1;
        return i;
    }
    else
    {
        i=A(i,l);
        if(f!=0)
        {
            i=B(i,l);
            return i;
        }
    }
}

int A(int i, int l)
{
    if(s[i]=='a')
    {
        i++;
        f=1;
    }
    else
    {
        f=0;
        return i;
    }
    if(i<l-1) i=A(i,l);
    return i;
}

int B(int i, int l)
{
    if(s[i]=='b')
    {
        i++;
        f=1;
        return i;
    }
    else
    {
        f=0;
        return i;
    }
}
