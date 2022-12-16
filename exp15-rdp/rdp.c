#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int nc=0,count=0,pc=0,pro_c,ipg_c;
char *ip;
char nonterminal[10],ip_grammar[10][10],grammar[10][10],processed[10];

int checkprocessed(char sym)
{
        for(int i=0; i<pc; i++)
        {
                if(processed[i]==sym)
                        return 1;
        }
        return 0;
}

char* findcomplete(char sym)
{
        char *s=malloc(sizeof(char)*10);
        for(int i=0; i<pro_c; i++)
        {
                if(ip_grammar[i][0]==sym&&ip_grammar[i][1]==sym)
                {
                        for(int j=2; j<strlen(ip_grammar[i]); j++)
                                strncat(s,&(ip_grammar[i][j]),1);

                        return s;
                }
        }

}

char* findother(char sym)
{
        char *s=malloc(sizeof(char)*10);
        for(int i=0; i<pro_c; i++)
        {
                if(ip_grammar[i][0]==sym&&ip_grammar[i][1]!=sym)
                {
                        for(int j=1; j<strlen(ip_grammar[i]); j++)
                                strncat(s,&(ip_grammar[i][j]),1);

                        return s;
                }
        }

}
void eliminateLR()
{
        for(int i=0; i<pro_c; i++)
        {
                if(ip_grammar[i][0]==ip_grammar[i][1])
                {
                        char *s=malloc(sizeof(char)*10);
                        strcat(s,findother(ip_grammar[i][0]));

                        char *s1=malloc(sizeof(char)*10);
                        strcat(s1,findcomplete(ip_grammar[i][0]));

                        char newnt='A'+nc;

                        char newpro[10];
                        memset(newpro,0,strlen(newpro));
                        strncat(newpro,&(ip_grammar[i][0]),1);
                        strcat(newpro,s);
                        strncat(newpro,&(newnt),1);

                        strcat(grammar[count++],newpro);

                        char newpro1[10];
                        memset(newpro1,0,strlen(newpro1));
                        strncat(newpro1,&(newnt),1);
                        strcat(newpro1,s1);
                        strncat(newpro1,&(newnt),1);

                        strcat(grammar[count++],newpro1);

                        char newpro2[10];
                        memset(newpro2,0,strlen(newpro2));
                        strncat(newpro2,&(newnt),1);
                        strcat(newpro2,"#");

                        strcat(grammar[count++],newpro2);

                        processed[pc++]=ip_grammar[i][0];
                        nc++;
                }
                else
                {
                        int flag;
                        flag=checkprocessed(ip_grammar[i][0]);
                        if(flag==0)
                        {
                                strcat(grammar[count++],ip_grammar[i]);
                        }
                }
        }

}

int E();
int T();
int Edash();
int Tdash();
int F();

int E()
{
        if(T())
        {
                if(Edash())
                        return 1;
                else
                        return 0;
        }
        else
                return 0;

}

int F()
{
        if(*ip=='(')
        {
                ip++;
                if(E())
                {
                        if(*ip==')')
                        {
                                ip++;
                                return 1;
                        }
                        else
                                return 0;
                }
                else
                        return 0;
        }
        else
        {
                if(islower(*ip))
                {
                        ip++;
                        return 1;
                }
                else
                        return 0;
        }
}

int Tdash()
{
        if(*ip=='*')
        {
                ip++;
                if(F())
                        if(Tdash())
                                return 1;
                        else
                                return 0;
                else
                        return 0;
        }
        else
                return 1;
}

int T()
{
        if(F())
                if(Tdash())
                        return 1;
                else
                        return 0;
        else
                return 0;
}

int Edash()
{
        if(*ip=='+')
        {
                ip++;
                if(T())
                {
                        if(Edash())
                                return 1;
                        else
                                return 0;
                }
                else
                        return 0;
        }
        else
                return 1;
}


void main()
{
        int choice;
        printf("\n 1.EliminateLR 2.RDP");
        printf("\n Enter the choice: ");
        scanf("%d",&choice);
        if(choice==1)
        {
                printf("\n Enter the number of productions : ");
                scanf("%d",&ipg_c);
                printf("\n Enter the productions (use # for null): \n");
                for(int i=0; i<ipg_c; i++)
                {
                        char nt,nts[2],pro[20];
                        scanf("\n");
                        scanf("%c=%s",&nt,pro);

                        nonterminal[i]=nt;
                        nts[0]=nt;
                        nts[1]='\0';
                        //seperate
                        char* token=strtok(pro,"|");

                        while(token!=NULL)
                        {
                                strcat(ip_grammar[pro_c],nts);
                                strcat(ip_grammar[pro_c],token);
                                pro_c++;
                                token=strtok(NULL,"|");
                        }

                }

                //startsym=ip_grammar[0][0];
                printf("\n printing final");
                eliminateLR();
                for(int i=0; i<count; i++)
                {
                        printf("\n %c -> ",grammar[i][0] );
                        for(int j=1; j<strlen(grammar[i]); j++)
                                printf("%c",grammar[i][j] );
                }
                printf("\n");
        }
        else
        {
                char input[10];
                printf("\n Enter the input: ");
                scanf("%s",input);
                strcat(input,"#");
                ip=input;
                if(E() && *ip=='#')
                        printf("\n %s successfully parsed\n",input);
                else
                        printf("\n%s parsing failed\n",input);

        }

}
