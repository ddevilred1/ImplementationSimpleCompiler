#include <bits/stdc++.h>

using namespace std;

struct symbol
{
    int tid;
    char nm[50], idType[50], dType[50], sc[50];
}tbl[1000];

char tempScope[50], Scope[50];

bool isKeyWord(char s[])
{
    int i;
    char keywords[][10] = {"int", "void", "bool", "float", "double", "char"};
    for(i=0; i<6; i++)if(!strcmp(s,keywords[i]))return true;
    return false;
}

int whichID2(char s[], int n)
{
    int i;
    for(i=0; i<n; i++)if(!strcmp(tbl[i].nm,s))return i;
}

int whichID(char s[], int n)
{
    int i;
    for(i=0; i<n; i++)if(!strcmp(tbl[i].nm,s) && (!strcmp(tbl[i].sc,Scope) || !strcmp(tbl[i].idType,"func")))break;
    if(!strcmp(tbl[i].idType, "func"))strcpy(tempScope, tbl[i].nm);
    if(i==n)i=whichID2(s, n);
    return tbl[i].tid;
}


int main()
{
    char temp[50], iddt[50], c, s[50], idn[50];
    int i, n;
    FILE* p1 = fopen("input.txt", "r");
    FILE* p2 = fopen("output1.txt", "w");

    while(fscanf(p1, "%s", &s)!=EOF)
    {
        if(!strcmp(s, "[id"))
        {
            fprintf(p2, "%s", s);
            fscanf(p1, "%s", &s);
            fprintf(p2," %s", s);
        }
        else
        {
            fscanf(p1, "%s", &s);
            fprintf(p2, "[%s", s);
        }
    }
    fclose(p1);
    fclose(p2);
    p1 = fopen("output1.txt", "r");
    while((c=fgetc(p1))!=EOF)
    {
        printf("%c", c);
    }
    fclose(p1);
    printf("\n\n");

    p1 = fopen("output1.txt", "r");
    n=0;
    strcpy(temp, "global");

    while((c=fgetc(p1))!=EOF)
    {
        if(c=='[')
        {
            memset(iddt, '\0', sizeof(iddt));

            i=0;
            while((c=fgetc(p1))!=']' && c!=' ')
            {
                iddt[i++]=c;
            }
            iddt[i]='\0';
            if(isKeyWord(iddt))
            {
                strcpy(tbl[n].dType, iddt);
                fscanf(p1, "%s", &s);
                fgetc(p1);
                i=0;
                while((c=fgetc(p1))!=']')
                {
                    tbl[n].nm[i++]=c;
                }
                tbl[n].nm[i]='\0';
                c=fgetc(p1);
                c=fgetc(p1);
                strcpy(tbl[n].sc, temp);
                if(c=='=' || c==';' || c==')')strcpy(tbl[n].idType, "var");
                else if(c=='(')
                {
                    strcpy(tbl[n].idType, "func");
                    strcpy(temp, tbl[n].nm);
                }
                tbl[n].tid=n+1;
                n++;
            }
            else if(!strcmp("}", iddt))strcpy(temp, "global");
        }
    }
    printf("ID\tName\tType\tData Type\tScope\n");
    printf("-------------------------------------------------\n");
    for(i=0; i<n; i++)
    {
        printf("%d\t%s\t%s\t%s\t\t%s\n", tbl[i].tid, tbl[i].nm, tbl[i].idType, tbl[i].dType, tbl[i].sc);
    }
    printf("\n\n");
    p1 = fopen("output1.txt", "r");
    p2 = fopen("output2.txt", "w");
    strcpy(Scope, "global");
    while((c=fgetc(p1))!=EOF)
    {
        if(c=='i')
        {
            fputc(c, p2);
            c=fgetc(p1);
            if(c=='d')
            {
                fputc(c, p2);
                c=fgetc(p1);
                if(c==' ')
                {
                    fputc(c, p2);
                    memset(idn, '\0', sizeof(idn));
                    i=0;
                    while((c=fgetc(p1))!=']')
                    {
                        idn[i++]=c;
                    }
                    idn[i]='\0';
                    int xx = whichID(idn, n);
                    fprintf(p2, "%d]", xx);
                }
                else fputc(c, p2);
            }
            else fputc(c, p2);
        }
        else if(c=='{')
        {
            fputc(c, p2);
            strcpy(Scope,tempScope);
        }
        else if(c=='}')
        {
            fputc(c, p2);
            strcpy(Scope,"global");
        }
        else fputc(c, p2);
    }
    fclose(p1);
    fclose(p2);
    p1 = fopen("output2.txt", "r");
    while((c=fgetc(p1))!=EOF)
    {
        printf("%c", c);
    }
    fclose(p1);
    printf("\n\n");
    return 0;
}
