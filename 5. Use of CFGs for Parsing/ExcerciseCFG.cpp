#include <bits/stdc++.h>

using namespace std;

int A(int i, int l);
int X_1(int i, int l);
int X_2(int i, int l);

char s[1000];

int main()
{
    int i, l;
    printf("CFG:\n\n");
    printf("\tA -> aXd\n");
    printf("\tX -> bbX\n");
    printf("\tX -> bcX\n");
    printf("\tX -> NULL\n\n");
    printf("Enter the string: ");
    scanf("%s", &s);
    l=strlen(s);
    if(l>1)i=A(0,l);
    else printf("String is invalid\n\n\n");
    if(i==l)printf("String is valid\n\n\n");
    else printf("String is invalid\n\n\n");
    return 0;
}

int A(int i, int l)
{
    if(s[i]=='a')
    {
        i=X_1(i+1, l);
        if(s[i]=='d')
        {
            return i+1;
        }
        else return i;
    }
    else
    {
        return i;
    }
}

int X_1(int i, int l)
{
    int check;
    if(i<=l-3)
    {
        if(s[i]=='b' && s[i+1]=='b')
        {
            if(i+3==l)return i+2;
            else X_1(i+2, l);
        }
        else
        {
            check=i;
            i=X_2(i, l);
            if(i==l-2)return i+1;
            else if(check!=i) X_1(i, l);
        }
    }
    else return i;
}

int X_2(int i, int l)
{
    if(i<=l-3)
    {
        if(s[i]=='b' && s[i+1]=='c')
        {
            if(i+3==l)return i+2;
            else X_1(i+2, l);
        }
        else return i;
    }
    else return i;
}

