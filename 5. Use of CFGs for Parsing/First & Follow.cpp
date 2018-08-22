#include<bits/stdc++.h>

using namespace std;

char a[100][100];

struct Table
{
    int n;
    char firT[100], folT[100];
}ff[100];

int col, n;
void findFirst(char,char);
void findFollow(char,char);
void folTabOperation(char,char);
void firTabOperation(char,char);

int main()
{
    int i, j, c=0, cnt=0;
    char ip;
    char b[100];
    FILE* fp=fopen("input.txt", "r");
    printf("CFG:\n\n");
    i=0;
    while(fscanf(fp, "%s", &a[i])!=EOF)
    {
        printf("\t%s\n", a[i]);
        i++;
    }
    fclose(fp);
    n=i;
    for(i=0; i<n; i++)
    {
        c=0;
        for(j=0; j<i+1; j++)
        {
            if(a[i][0] == b[j])
            {
                c=1;
                break;
            }
        }
        if(c!=1)
        {
            b[cnt] = a[i][0];
            cnt++;
        }
    }
    printf("\n");
    for(i=0;i<cnt;i++)
    {
        col=1;
        ff[i].firT[0] = b[i];
        ff[i].n=0;
        findFirst(b[i],i);
    }
    for(i=0;i<cnt;i++)
    {
        col=1;
        ff[i].folT[0] = b[i];
        ff[i].n=0;
        findFollow(b[i],i);
    }
    printf("\n");
    for(i=0;i<cnt;i++)
    {
        for(j=0;j<=ff[i].n;j++)
        {
            if(j==0)
            {
                printf("First(%c) : {",ff[i].firT[j]);
            }
            else
            {
                printf(" %c",ff[i].firT[j]);
            }
        }
        printf(" }\n");
    }
    printf("\n");
    for(i=0;i<cnt;i++)
    {
        for(j=0;j<=ff[i].n;j++)
        {
            if(j==0)
            {
                printf("Follow(%c) : {",ff[i].folT[j]);
            }
            else
            {
                printf(" %c",ff[i].folT[j]);
            }
        }
    printf(" }\n");
    }
}

void findFirst(char ip,char pos)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(ip == a[i][0])
        {
            if(isupper(a[i][3]))
            {
                findFirst(a[i][3],pos);
            }
            else
            {
            ff[pos].firT[col]=a[i][3];
            ff[pos].n++;
            col++;
            }
        }
    }
}

void findFollow(char ip,char row)
{   int i,j;
    if(row==0 && col==1)
    {
        ff[row].folT[col]= '$';
        col++;
        ff[row].n++;
    }
    for(i=0;i<n;i++)
    {
        for(j=3;j<n-1;j++)
        {
            if(a[i][j] == ip)
            {
                if(a[i][j+1] == '\0')
                {
                    if(a[i][j] != a[i][0])
                    {
                        folTabOperation(a[i][0],row);
                    }
                }
                else if(isupper(a[i][j+1]))
                {
                    if(a[i][j+1] != a[i][0])
                    {
                        firTabOperation(a[i][j+1],row);
                    }
                }
                else
                {
                    ff[row].folT[col] = a[i][j+1];
                    col++;
                    ff[row].n++;
                }
            }
        }
    }
}

void folTabOperation(char ip,char row)
{   int i,j;
    for(i=0;i<n-3;i++)
    {
        if(ip == ff[i].folT[0])
        {
            for(j=1;j<=ff[i].n;j++)
            {
                ff[row].folT[col] = ff[i].folT[j];
                col++;
                ff[row].n++;
            }
        }
    }
}

void firTabOperation(char ip,char row)
{
    int i,j;
    for(i=0;i<n-3;i++)
    {
        if(ip == ff[i].firT[0])
        {
            for(j=1;j<=ff[i].n;j++)
            {
                if(ff[i].firT[j] != '0')
                {
                    ff[row].folT[col] = ff[i].firT[j];
                    ff[row].n++;
                    col++;
                }
                else
                {
                    folTabOperation(ip,row);
                }
            }
        }
    }

}
