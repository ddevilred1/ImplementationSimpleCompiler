#include <bits/stdc++.h>

using namespace std;

struct symbol
{
    int tid;
    char nm[50], idType[50], dType[50], sc[50];
}tbl[1000];

struct error
{
    int ln;
    char des[1000];
}err[1000];

char tempScope[50], Scope[50];

bool isKeyword(char s[])
{
    int i;
    char kw[][15] = {"int", "float", "double", "char", "void", "if", "else", "for", "return", "bool"};
    for(i=0; i<10; i++)
    {
        if(!strcmp(s,kw[i]))
        {
            return true;
        }
    }
    return false;
}

bool isId(char s[])
{
    int i, l;
    l=strlen(s);
    if(!isalpha(s[0]) && s[0]!='_')return false;
    for(i=1; i<l; i++)
    {
        if(!isalnum(s[i]) && s[i]!='_')return false;
    }
    return true;
}

bool isOperator(char s[])
{
    int l;
    l=strlen(s);
    if(l==1 && (s[0]=='>' || s[0]=='+' || s[0]=='-' || s[0]=='*' || s[0]=='/' || s[0]=='<' || s[0]=='='))return true;
    else if(l==2 && (s[0]=='>' || s[0]=='<'|| s[0]=='=' || s[0]=='!') && s[1]=='=')return true;
    else return false;
}

bool isSeparator(char s[])
{
    int i, l;
    l=strlen(s);
    if(l==1 && (s[0]==',' || s[0]==39 || s[0]==';' || s[0]=='"'))return 1;
    else return 0;
}

bool isParenthesis(char s[])
{
    int l = strlen(s);
    if(l==1 && (s[0]=='(' || s[0]==')' || s[0]=='{' || s[0]=='}' || s[0]=='[' || s[0]==']'))return true;
    else return false;
}

bool isDatatype(char s[])
{
    int i;
    char keywords[][10] = {"int", "void", "bool", "float", "double", "char"};
    for(i=0; i<6; i++)if(!strcmp(s,keywords[i]))return true;
    return false;
}

int whichID2(char s[], int n)
{
    int i;
    for(i=0; i<n; i++)if(!strcmp(tbl[i].nm,s))break;
    return i;
}

int whichID(char s[], int n)
{
    int i;
    for(i=0; i<n; i++)if(!strcmp(tbl[i].nm,s) && (!strcmp(tbl[i].sc,Scope) || !strcmp(tbl[i].idType,"func")))break;
    if(!strcmp(tbl[i].idType, "func"))strcpy(tempScope, tbl[i].nm);
    if(i==n)i=whichID2(s, n);
    if(i==n)return 1000;
    else return tbl[i].tid;
}

int main()
{
    FILE *p1, *p2;
    char c, prev;
    char temp[50], iddt[50], s[50], idn[50];
    char pst[50], nst[50];
    int i, n;
    int x=0, ifc=0, opsec=0, opf=0, flag=0, ln=1;

    p1 = fopen("Input.txt", "r");
    p2 = fopen("CommentDeleted.txt", "w");

    while((c=fgetc(p1))!=EOF)
    {
        if(c=='/')
        {
            if((c=fgetc(p1))=='/')
            {
                while((c=fgetc(p1))!='\n'){}
            }
            else if(c=='*')
            {
                while((c=fgetc(p1))!='*'){}
                c=fgetc(p1);
                continue;
            }
            else
            {
                fputc('/',p2);
            }
        }
        fputc(c,p2);
    }

    fclose(p1);
    fclose(p2);

    p1 = fopen("CommentDeleted.txt", "r");
    p2 = fopen("OneLiner.txt", "w");

    while((c=fgetc(p1))!=EOF)
    {
        if(c=='\n')fputc(' ', p2);
        else fputc(c, p2);
    }

    fclose(p1);
    fclose(p2);

    p1 = fopen("OneLiner.txt", "r");
    p2 = fopen("Formating1.txt", "w");

    i=0;
    while((c=fgetc(p1))!=EOF)
    {
        if(i==0 && (c==' ' || c=='\t'))
        {
            i++;
            continue;
        }
        if((c==' ') || (c=='\t'))
        {
            fputc(' ', p2);
            c=fgetc(p1);
            while(c==' ' || c=='\t'){c=fgetc(p1);}
            if(c!=EOF)fputc(c, p2);
        }
        else fputc(c, p2);
    }

    fclose(p1);
    fclose(p2);

    p1 = fopen("Formating1.txt", "r");
    p2 = fopen("SpaceSeparated.txt", "w");

    i=0;
    while((c=fgetc(p1))!=EOF)
    {
        if(i==0)
        {
            fputc(c, p2);
            prev = c;
            i++;
            continue;
        }
        if(c=='=' && (prev=='>' || prev=='<' || prev=='=' || prev=='!'))
        {
            fputc(c, p2);
            prev = c;
        }
        else if((!isalnum(c) && c!=' ' && c!='_' && c!='.') && prev!=' ')
        {
            fputc(' ', p2);
            fputc(c, p2);
            prev = c;
        }
        else if(c==' ' && prev==' ')continue;
        else if(isalnum(c) && (!isalnum(prev) && prev!=' ' && prev!='.' && prev!='_'))
        {
            fputc(' ', p2);
            fputc(c, p2);
            prev = c;
        }
        else
        {
            fputc(c, p2);
            prev = c;
        }
        if(c==39)
        {
            fputc(' ', p2);
            prev = ' ';
        }
    }

    fclose(p1);
    fclose(p2);

    p2 = fopen("Lexer.txt", "w");
    p1 = fopen("SpaceSeparated.txt", "r");
    while(fscanf(p1, "%s", &s)!=EOF)
    {
        if(isKeyword(s))fprintf(p2, "[kw %s] ", s);
        else if(isOperator(s))fprintf(p2, "[op %s] ", s);
        else if(isParenthesis(s))fprintf(p2, "[par %s] ", s);
        else if(isSeparator(s))fprintf(p2, "[Sep %s] ", s);
        else if(isId(s))fprintf(p2, "[id %s] ", s);
        else fprintf(p2, "[num %s] ", s);
    }
    fclose(p1);
    fclose(p2);

    p1 = fopen("Lexer.txt", "r");
    p2 = fopen("Format2.txt", "w");

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

    p1 = fopen("Format2.txt", "r");
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
            if(isDatatype(iddt))
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

    p1 = fopen("CommentDeleted.txt", "r");
    p2 = fopen("SpaceSeparated2.txt", "w");
    i=0;
    while((c=fgetc(p1))!=EOF)
    {
        if(i==0)
        {
            fputc(c, p2);
            prev = c;
            i++;
            continue;
        }
        if(c=='=' && (prev=='>' || prev=='<' || prev=='=' || prev=='!'))
        {
            fputc(c, p2);
            prev = c;
        }
        else if((!isalnum(c) && c!=' ' && c!='_' && c!='.') && prev!=' ')
        {
            fputc(' ', p2);
            fputc(c, p2);
            prev = c;
        }
        else if(c==' ' && prev==' ')continue;
        else if(isalnum(c) && (!isalnum(prev) && prev!=' ' && prev!='.' && prev!='_'))
        {
            fputc(' ',p2);
            fputc(c, p2);
            prev = c;
        }
        else
        {
            fputc(c, p2);
            prev = c;
        }
        if(c==39)
        {
            fputc(' ', p2);
            prev = ' ';
        }
    }
    fclose(p1);
    fclose(p2);

    p1 = fopen("SpaceSeparated2.txt", "r");
    p2 = fopen("Format3.txt", "w");

    while((c=fgetc(p1))!=EOF)
    {
        if((c==' ') || (c=='\t'))
        {
            fputc(' ', p2);
            c=fgetc(p1);
            while(c==' ' || c=='\t'){c=fgetc(p1);}
            if(c!=EOF)fputc(c, p2);
        }
        else fputc(c, p2);
    }

    fclose(p1);
    fclose(p2);

    p1 = fopen("Format3.txt", "r");
    p2 = fopen("LineNumbering.txt", "w");
    i=1;
    fprintf(p2, "%d.", i++);
    while((c=fgetc(p1))!=EOF)
    {
        if(c=='\n')
        {
            fputc(c, p2);
            fprintf(p2, "%d.", i++);
        }
        else fputc(c, p2);
    }

    fclose(p1);
    fclose(p2);

    p1 = fopen("LineNumbering.txt", "r");
    p2 = fopen("Tokenized.txt", "w");

    while((c=fgetc(p1))!=EOF)
    {
        memset(temp, '\0', sizeof(temp));
        i=0;
        while(c!=EOF && c!=' ')
        {
            temp[i]=c;
            i++;
            c=fgetc(p1);
        }
        temp[i]='\0';
        i=whichID(temp, n);
        if(!strcmp(temp, "{"))strcpy(Scope, tempScope);
        else if(!strcmp(temp, "}"))strcpy(Scope, "global");
        if(i==1000)fprintf(p2, "%s ", temp);
        else fprintf(p2, "id %d ", i);
    }

    fclose(p1);
    fclose(p2);

    p1 = fopen("Tokenized.txt", "r");

    while((c=fgetc(p1))!=EOF)
    {
        if(c=='\n')ln++;
        else if(c=='{')opsec++;
        else if(c=='(')opf++;
        else if(c=='}')
        {
            opsec--;
            if(opsec<0)
            {
                opsec=0;
                err[x].ln=ln;
                strcpy(err[x].des, "Missing '{' for '}'");
                x++;
            }
        }
        else if(c=='}')
        {
            opf--;
            if(opf<0)
            {
                opf=0;
                err[x].ln=ln+1;
                strcpy(err[x].des, "Missing '(' for ')'");
                x++;
            }
        }
        else if(c!=' ')
        {
            memset(nst, '\0', sizeof(nst));
            i=0;
            while(c!=' ' && c!=EOF)
            {
                nst[i]=c;
                i++;
                c=fgetc(p1);
            }
            nst[i]='\0';
            if(!flag){strcpy(pst,nst);flag=1;}
            else
            {
                if(!strcmp(pst, nst) && strcmp(nst, "{") && strcmp(nst, "}") && strcmp(nst, "(") && strcmp(nst, ")"))
                {
                    err[x].ln=ln+1;
                    strcpy(err[x].des, "Duplicate token");
                    x++;
                }
                else strcpy(pst,nst);
                if(!strcmp(nst, "if"))ifc++;
                else if(!strcmp(nst, "else"))
                {
                    ifc--;
                    if(ifc<0)
                    {
                        ifc=0;
                        err[x].ln=ln+1;
                        strcpy(err[x].des, "Missing 'if' for 'else'");
                        x++;
                    }
                }
            }
        }
    }

    fclose(p1);

    p1 = fopen("Tokenized.txt", "r");
    while((c=fgetc(p1))!=EOF)printf("%c", c);
    fclose(p1);
    printf("\n\n");

    for(i=0; i<x; i++)
    {
        printf("%s at line %d\n", err[i].des, err[i].ln);
    }
    return 0;
}
