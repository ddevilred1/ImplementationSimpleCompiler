#include <bits/stdc++.h>

using namespace std;

bool isNumber(char s[])
{
    int i, l;
    bool b=true;
    if(!isdigit(s[0]) && s[0]!='.' && s[0]!='-')return false;
    for(i=1; i<l; i++)
    {
        if(s[i]=='.')break;
        else if(!isdigit(s[i]))return false;
    }
    for( ; i<l; i++)
    {
        if(!isdigit(s[i]))return false;
    }
    return true;
}

bool isKeyword(char s[])
{
    int i;
    char kw[][15] = {"int", "float", "double", "char", "void", "if", "else", "for", "return"};
    for(i=0; i<9; i++)
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

int main()
{
    char c, prev;
    int i=0;
    FILE* fp1 = fopen("A2_in.txt", "r");

    while((c=fgetc(fp1))!=EOF)
    {
        printf("%c", c);
    }
    fclose(fp1);
    printf("\n\n");

    FILE* fp2 = fopen("A2_out1.txt", "w");
    fp1 = fopen("A2_in.txt", "r");

    while((c=fgetc(fp1))!=EOF)
    {
        if(i==0)
        {
            fputc(c, fp2);
            prev = c;
            i++;
            continue;
        }
        if(c=='=' && (prev=='>' || prev=='<' || prev=='=' || prev=='!'))
        {
            fputc(c, fp2);
            prev = c;
        }
        else if((!isalnum(c) && c!=' ' && c!='_' && c!='.') && prev!=' ')
        {
            fputc(' ', fp2);
            fputc(c, fp2);
            prev = c;
        }
        else if(c==' ' && prev==' ')continue;
        else if(isalnum(c) && (!isalnum(prev) && prev!=' ' && prev!='.' && prev!='_'))
        {
            fputc(' ', fp2);
            fputc(c, fp2);
            prev = c;
        }
        else
        {
            fputc(c, fp2);
            prev = c;
        }
        if(c==39)
        {
            fputc(' ', fp2);
            prev = ' ';
        }
    }
    fclose(fp1);
    fclose(fp2);
    fp1 = fopen("A2_out1.txt", "r");

    while((c=fgetc(fp1))!=EOF)
    {
        printf("%c", c);
    }
    fclose(fp1);
    printf("\n\n");

    fp2 = fopen("A2_out2.txt", "w");
    fp1 = fopen("A2_out1.txt", "r");
    char s[20];
    while(fscanf(fp1, "%s", &s)!=EOF)
    {
        if(isKeyword(s))fprintf(fp2, "[kw %s] ", s);
        else if(isOperator(s))fprintf(fp2, "[op  %s] ", s);
        else if(isParenthesis(s))fprintf(fp2, "[par  %s] ", s);
        else if(isSeparator(s))fprintf(fp2, "[Sep  %s] ", s);
        else if(isId(s))fprintf(fp2, "[id  %s] ", s);
        else if(isNumber(s))fprintf(fp2, "[num  %s]", s);
        else fprintf(fp2, "[unkn  %s]", s);
    }
    fclose(fp1);
    fclose(fp2);

    fp1 = fopen("A2_out2.txt", "r");

    while((c=fgetc(fp1))!=EOF)
    {
        printf("%c", c);
    }
    fclose(fp1);
    printf("\n");
    return 0;
}
