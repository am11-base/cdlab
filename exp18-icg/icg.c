// find highest op at each stage
// write a function to find its left and right ops
// substitue the expr with t[1]
//repeat above steps
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int varc=0;

int findhighprio(char expr[50])
{
  /* start from left and assign priority for * and + first
  then in another loop assign prio for + and - */
  for(int i=0;i<strlen(expr);i++)
  {
    if(expr[i]=='*'||expr[i]=='/')
     return i;
  }
  for(int i=0;i<strlen(expr);i++)
  {
    if(expr[i]=='+'||expr[i]=='-')
     return i;
  }
  return -1;

}

void generate(char expr[50])
{
  int a=findhighprio(expr);
  while(a!=-1){

  //printf("\n highprio:%d",a );
  char left[50],right[50];
  memset(left,0,strlen(left));
  memset(right,0,strlen(right));

  int lptr=a-1;
  while(expr[lptr]!='*'&&expr[lptr]!='+'&&expr[lptr]!='/'&&expr[lptr]!='-'&&lptr!=-1)
   lptr--;

  lptr++;

  for(int i=lptr;i!=a;i++)
   strncat(left,&(expr[i]),1);

   int rptr=a+1;
   while(expr[rptr]!='*'&&expr[rptr]!='+'&&expr[rptr]!='/'&&expr[rptr]!='-'&&rptr!=strlen(expr))
    rptr++;
   rptr--;

   for(int i=a+1;i<=rptr;i++)
    strncat(right,&(expr[i]),1);

  printf("\n t%d = ",++varc);
  for(int i=lptr;i<=rptr;i++)
    printf("%c",expr[i] );

  char temp[50];
  strcpy(temp,expr);
  expr[lptr]='t';
  expr[lptr+1]=(varc) + '0';
   int count=(rptr-lptr-2+1);
   while(count>0)
   {
     int i;
     for(i=lptr+2;i<(strlen(expr))-1;i++)
     {
       expr[i]=expr[i+1];
     }
     expr[i]='\0';
      //printf("\n%s",expr );
     count--;
   }

 //printf("\n%s",expr );
  a=findhighprio(expr);
 }
 printf("\n T = t%d\n",varc );

}

void main()
{
  char input[50];
  printf("\n Enter the expression : ");
  scanf("%s",input);
  generate(input);
}
