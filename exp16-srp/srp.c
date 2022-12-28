#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char input[10],ip_prod[3][10];
char stack[100];
int top=-1,ip_c;
char checkstring[10];
char* getSubstring(char string[10],int start)
{
   char *substring=malloc(sizeof(char)*10);
   int k=0;
   for(int i=start;i<strlen(string);i++)
   {
     substring[k]=string[i];
     k++;
   }
   substring[k]='\0';
   return substring;
}

void reducestack()
{
  //check top,{top,top-1},.....{top,top-1,,,,$}

  memset(checkstring,0,strlen(checkstring));
  for(int i=top;i>0;i--)
  {
    strncat(checkstring,&(stack[i]),1);
    //printf("\n stack: %s checkstring: %s",stack,checkstring );
    char *substring=malloc(sizeof(char)*10);
    for(int k=0;k<3;k++)
    {
      memset(substring,0,strlen(substring));
      strcat(substring,getSubstring(ip_prod[k],3));
      if(strcmp(substring,checkstring)==0)
      {
      //  printf("substring: %s checkstring:%s",substring,checkstring );
        printf("\n %s\t%s ",stack,getSubstring(input,ip_c));
        printf("\treduced by %s",ip_prod[k] );
        int len=strlen(substring);
        for(int n=len;n>0;n--)
         stack[top--]='\0';
        stack[++top]=ip_prod[k][0];
        stack[top+1]='\0';
        reducestack();
      }
    }
  }
}

void main()
{
  printf("\n The grammar is E->E+E\n E->E*E\n E->i");
  printf("\n Enter the input string : ");
  scanf("%s",input);
  strcat(ip_prod[0],"E->E+E");
  strcat(ip_prod[1],"E->E*E");
  strcat(ip_prod[2],"E->i");

  memset(stack,0,strlen(stack));
  stack[++top]='$';
  strcat(input,"$");

  printf("\n Stack\t Input\t Action");
  for( ip_c=0;ip_c<strlen(input);)
  {

    printf("\n %s\t%s ",stack,getSubstring(input,ip_c));
    if(input[ip_c]=='$')
    {
      //printf("\n Content:%s",stack );
      if(strcmp(stack,"$E")==0)
       printf(" Accepted");
      else
      printf("Rejected");
      ip_c++;
    }
    else
    {
      printf("\tShift ");
      stack[++top]=input[ip_c];
      ip_c++;
      reducestack();
    }
  }
}
