#include <stdio.h>
#include <string.h>
void main()
{
        char in_code[10][20],input[20];
        int ip_c=0;
        printf("\n Enter the set of intermediate code ( type exit for exit):\n");
        scanf("%s",input);
        while(strcmp(input,"exit")!=0)
        {
          strcpy(in_code[ip_c++],input);
          scanf("%s",input);
        }

        char str[20],opr[10];
        for(int i=0;i<ip_c;i++)
        {
                memset(str,0,strlen(str));
                memset(str,0,strlen(opr));
                strcpy(str,in_code[i]);
                if(str[3]=='+')
                  strcpy(opr,"ADD");
                else if(str[3]=='-')
                  strcpy(opr,"SUB");
                else if(str[3]=='*')
                  strcpy(opr,"MUL");
                else if(str[3]=='/')
                  strcpy(opr,"DIV");
                printf("\n Mov R%d,%c",i,str[2]);
                printf("\n %s R%d,%c",opr,i,str[4]);
                printf("\n Mov %c,R%d\n",str[0],i);
        }
}
