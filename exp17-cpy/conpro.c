#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char symtable[50][10];
int sym_c=0;
char seperator[10][3]={" ","+","-","*","/","%",";",","};
FILE *optr;

int isSeperator(char sym)
{
        char temp[2];
        memset(temp,0,strlen(temp));
        strncat(temp,&sym,1);
        for(int i=0; i<8; i++)
        {
                if(strcmp(seperator[i],temp)==0)
                        return 1;
        }
        return 0;
}

char* checkTable(char input[10])
{
  char *value=malloc(sizeof(char)*10);
  memset(value,0,strlen(value));
  for(int i=0;i<sym_c;i++)
  {
    int len=strlen(symtable[i]);
    int pos=strcspn(symtable[i],"|");
    int flag=1;
    for(int j=0;j<pos;j++)
    {
      if(symtable[i][j]!=input[j])
      {
        flag=0;
        break;
      }
    }
    if(flag==1)
    {
      for(int j=pos+1;j<len;j++)
       strncat(value,&(symtable[i][j]),1);

      return value;
    }
  }
  strcat(value,"none");
  return value;
}


void lineAnalyser(char parastring[50])
{
        char string[50];
        strcat(string,parastring);
        char *ltoken,*ch=string;
        while((ltoken=strtok_r(ch," ",&ch)))
        {
                //char *wtoken,*ptr=ltoken;
                if(strchr(ltoken,'=')!=NULL)
                {
                        printf("\n%s",ltoken );
                        printf("%s",parastring );
                        int pos=strcspn(parastring,"=");
                        printf(" %d\n",pos );

                        int inputflag=0;
                        int tempptr=1;
                        while(parastring[pos+tempptr]==' ')
                                tempptr++;
                        if(isdigit(parastring[pos+tempptr]))
                                inputflag=1;
                        if(inputflag==1)
                        {
                                fprintf(optr, "%s",parastring );
                                 char tableen[10];
                                memset(tableen,0,strlen(tableen));
                                int enc=0,iptr,fptr;
                                if(parastring[pos-1]==' ')
                                {
                                        iptr=pos-2;
                                        fptr=pos-2;
                                }
                                else
                                {
                                        iptr=pos-1;
                                        fptr=pos-1;
                                }
                                while(!isSeperator(parastring[iptr])&&iptr>=0)
                                {
                                        iptr--;
                                }
                                for(int j=iptr+1; j<=fptr; j++)
                                        tableen[enc++]=parastring[j];

                                tableen[enc++]='|';

                                int ilit,flit;
                                if(parastring[pos+1]==' ')
                                {
                                        ilit=pos+2;
                                        flit=pos+2;
                                }
                                else
                                {
                                        ilit=pos+1;
                                        flit=pos+1;
                                }
                                while(!isSeperator(parastring[flit]))
                                        flit++;

                                for(int j=ilit; j<flit; j++)
                                        tableen[enc++]=parastring[j];

                                tableen[enc]='\0';
                                printf(" %s ",tableen );
                                strcat(symtable[sym_c++],tableen);
                        }
                        else
                        {
                          //do the substitution part
                          //start from = and initialise two pointer.for every
                          //seperator check if value within ptr is available in
                          //symtable if there substitute using strcat
                          for(int i=0;i<=pos;i++)
                           fprintf(optr, "%c",parastring[i] );
                         char var[10];
                         for(int i=pos+1;parastring[i]!=';';i++)
                         {
                          if(!isSeperator(parastring[i]))
                           strncat(var,&(parastring[i]),1);
                          else
                          {
                            char *value=checkTable(var);
                            printf("\n ip:%s",var );
                            if(strcmp(value,"none")!=0)
                            {
                              printf(" value : %s",value );
                              fprintf(optr, "%s",value );
                            }
                            else
                            {
                              fprintf(optr, "%s",var );
                            }
                            fprintf(optr, "%c",parastring[i] );
                            memset(var,0,strlen(var));
                          }
                         }
                         char *value=checkTable(var);
                         printf("\n ip:%s",var );
                         if(strcmp(value,"none")!=0)
                         {
                           printf(" value : %s",value );
                           fprintf(optr, "%s",value );
                         }
                         else
                         {
                           fprintf(optr, "%s",var );
                         }
                         fprintf(optr, ";\n");

                        }
                }

        }
}
void main()
{
        FILE *ptr;
        char ch[50];
        ptr=fopen("input.txt","r");
        optr=fopen("output.txt","w");
        while(fgets(ch,50,ptr))
        {
                if(strchr(ch,'=')==NULL)
                  fprintf(optr,"%s",ch);
                lineAnalyser(ch);
        }
        fclose(ptr);
        fclose(optr);
        for(int i=0;i<sym_c;i++)
         printf("\n %s",symtable[i] );
}
