#include<stdio.h>
//We are using this Single line comment for the testing purpose
/*We are using this
multiple line comment for the testing
purpose*/
int main()
{
    FILE *p1, *p2;
    char c, next;

    p1 = fopen("assignment.c", "r");
    p2 = fopen("output.txt", "w");

    if(!p1)
        printf("File is not found!!!");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if((c==' ') || (c=='\n') || (c=='\t'))
                continue;
            else if(c=='/')
            {
                next=fgetc(p1);
                if(next=='/')
                {
                    while((next=fgetc(p1))!='\n' && next!=EOF)
                        continue;
                }
                else if(next=='*')
                {
                    do
                    {
                        while ((c = fgetc(p1)) != '*')
                            continue;
                        next = fgetc(p1);
                    }
                    while (next != '/' && next != EOF);
                }
                else
                {
                    //fputc(c, p2);
                    fputc(next, p2);
                }
            }
            else
            {
                fputc(c, p2);
            }

        }
    }

    fclose(p1);
    fclose(p2);

    printf("Display of input C file:\n\n");
    p1 = fopen("assignment.c", "r");
    while((c=fgetc(p1))!=EOF)
        printf("%c", c);
    fclose(p1);

    printf("\n\nDisplay of Output txt file:\n\n");
    p2 = fopen("output.txt", "r");
    while((c=fgetc(p2))!=EOF)
        printf("%c", c);
    fclose(p2);


    return 0;
}
