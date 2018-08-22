#include <bits/stdc++.h>

using namespace std;

int main()
{
    FILE *p1, *p2;
    char c;

    p2 = fopen("Assign_1_in.txt", "r");
    while((c=fgetc(p2))!=EOF)
    {
        printf("%c", c);
    }
    fclose(p2);

    //PART 1 -> Single line comment delete

    p1 = fopen("Assign_1_in.txt", "r");
    p2 = fopen("Assign_1_out1.txt", "w");

    if(!p1)printf("\nFile can't be opened!");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='/')
            {
                if((c=fgetc(p1))=='/')
                {
                    while((c=fgetc(p1))!='\n'){}
                }
                else
                {
                    fputc('/',p2);
                }
            }
            fputc(c,p2);

        }
    }
    printf("\n\n");
    fclose(p1);
    fclose(p2);
    p2 = fopen("Assign_1_out1.txt", "r");
    while((c=fgetc(p2))!=EOF)
    {
        printf("%c", c);
    }
    fclose(p2);

    //PART 2 -> \n delete

    p1 = fopen("Assign_1_out1.txt", "r");
    p2 = fopen("Assign_1_out2.txt", "w");

    if(!p1)printf("\nFile can't be opened!");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='\n')fputc(' ', p2);
            else fputc(c, p2);
        }
    }
    fclose(p1);
    fclose(p2);
    p2 = fopen("Assign_1_out2.txt", "r");
    while((c=fgetc(p2))!=EOF)
    {
        printf("%c", c);
    }
    fclose(p2);
    printf("\n\n");

    //PART 3 -> Multiple line comment delete

    p1 = fopen("Assign_1_out2.txt", "r");
    p2 = fopen("Assign_1_out3.txt", "w");

    if(!p1)printf("\nFile can't be opened!");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='/')
            {
                if((c=fgetc(p1))=='*')
                {
                    while((c=fgetc(p1))!='*'){}
                    c=fgetc(p1);
                    continue;
                }
            }
            fputc(c,p2);

        }
    }
    printf("\n\n");
    fclose(p1);
    fclose(p2);
    p2 = fopen("Assign_1_out3.txt", "r");
    while((c=fgetc(p2))!=EOF)
    {
        printf("%c", c);
    }
    fclose(p2);

    //PART 4 -> Extra space delete if available

    printf("\n\n");
    p1 = fopen("Assign_1_out3.txt", "r");
    p2 = fopen("Assign_1_out4.txt", "w");

    if(!p1)printf("\nFile can't be opened!");
    else
    {
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
    }
    fclose(p1);
    fclose(p2);
    p2 = fopen("Assign_1_out4.txt", "r");
    while((c=fgetc(p2))!=EOF)
    {
        printf("%c", c);
    }
    fclose(p2);
    printf("\n\n");

    return 0;
}
