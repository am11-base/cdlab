#include<stdio.h>
#include<string.h>
#include <stdlib.h>

char ip_grammar[10][20],nonterminal[10],grammar[20][20],first[10][10],follow[10][10],startsym;
int ipg_c=0,pro_c=0;

int containnull(char array[10])
{
  for(int i=0;i<strlen(array);i++)
  {
    if(array[i]=='#')
     return 1;
  }
  return 0;
}

void removeduplicants(char array[10])
{
    for(int j=0;array[j]!='\0';j++)
    {
     for(int k=j+1;array[k]!='\0';k++)
     {
         if(array[j]==array[k])
         {

                 int l;
                 for(l=k;array[l]!='\0';l++)
                 {

                  array[l]=array[l+1];
                 }
                 k--;

                 array[l-1]='\0';
        }
    }
  }
}

int isTerminal(char sym)
{
  for(int i=0;i<ipg_c;i++)
  {
    if(nonterminal[i]==sym)
     return 0;

  }
  return 1;
}

char* findfirst(char nt)
{
   char *first=malloc(10*sizeof(char));
   for(int j=0;j<pro_c;j++)
   {
     if(nt==ip_grammar[j][0])
     {
       if(isTerminal(ip_grammar[j][1]))
        strncat(first,&(ip_grammar[j][1]),1);
       else
       {
        int len=strlen(ip_grammar[j]);
        int k=1;
        while(k<len)
        {
         char *temp=malloc(10*sizeof(char));
         strcat(temp,findfirst(ip_grammar[j][k]));
         strcat(first,temp);
         if(!containnull(temp))
           break;
         k++;
        }

        //remove dup in first
      }
     }
   }
   removeduplicants(first);
  // printf("%c : %s",nt,first);
   return first;

}

int checknull(char sym)
{
  for(int i=0;i<ipg_c;i++)
  {
    if(first[i][0]==sym)
    {
      for(int j=1;j<strlen(first[i]);j++)
      {
        if(first[i][j]=='#')
         return 1;
      }
      return 0;
    }
  }
}

char* retrievefirst(char sym)
{
  char *retfirst=malloc(sizeof(char)*10);
  for(int i=0;i<ipg_c;i++)
  {
    if(first[i][0]==sym)
    {
      for(int j=1;j<strlen(first[i]);j++)
      {
        if(first[i][j]!='#')
         strncat(retfirst,&(first[i][j]),1);
      }
      return retfirst;
    }
  }
}

char* findfollow(char sym)
{
  //printf("\n finding followers of :%c\n",sym );
  char *follow=malloc(sizeof(char)*100);
  if(sym==startsym)
  {
    strcat(follow,"$");
  }
  for(int i=0;i<pro_c;i++)
  {
    int len=strlen(ip_grammar[i]);
    for(int j=1;j<len;j++)
    {
      if(sym==ip_grammar[i][j]) /// replace a while until '\0'
      {
        int k=1;
        while(ip_grammar[i][j+k]!='\0')
        {
          //printf(" %c ",ip_grammar[i][j+k]);
          if(isTerminal(ip_grammar[i][j+k]))
          {
          //  printf("\n adding %c to follow of %c",ip_grammar[i][j+k],sym );
            strncat(follow,&(ip_grammar[i][j+k]),1);
            break;
          }
          else
          {
            char s[10];
            memset(s,0,strlen(s));
            strcat(s,retrievefirst(ip_grammar[i][j+k]));
            //printf("\n adding %s to follow of %c after %c",s,sym,ip_grammar[i][j+k] );

            strcat(follow,s);
           if(!checknull(ip_grammar[i][j+k]))
             break;
          }
          k++;
        }
        if(ip_grammar[i][j+k]=='\0')
        {
          if(ip_grammar[i][j+k-1]!=ip_grammar[i][0])
           strcat(follow,findfollow(ip_grammar[i][0]));
        }
      }
    }
  }
  removeduplicants(follow);
  return follow;
}


void main()
{
 printf("\n Enter the number of productions : ");
 scanf("%d",&ipg_c);
 printf("\n Enter the productions (use # for null): \n");
 for(int i=0;i<ipg_c;i++)
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

 startsym=ip_grammar[0][0];
 /*printf("\n Printing ip pros");
 for(int i=0;i<pro_c;i++)
 {
  printf("\n%s",ip_grammar[i]);
}*/
 for(int i=0;i<ipg_c;i++)
 {

  strncat(first[i],&(nonterminal[i]),1);
  char *firsti=findfirst(nonterminal[i]);
  //printf("\nfirst of %c is: {%s}",nonterminal[i],firsti);
  strcat(first[i],firsti);
 }
 printf("\n Printing first");
 for(int i=0;i<ipg_c;i++)
 {
   printf("\n First of %c : ",first[i][0] );
   int len=strlen(first[i]);
   for(int j=1;j<len;j++)
    printf(" %c ",first[i][j] );
 }

 for(int i=0;i<ipg_c;i++)
 {
   strncat(follow[i],&(nonterminal[i]),1);
   char *followi=findfollow(nonterminal[i]);
   strcat(follow[i],followi);
  // printf("\n follow of %c : %s",nonterminal[i],followi );

 }
 printf("\n Printing follow");
 for(int i=0;i<ipg_c;i++)
 {
   printf("\n Follow of %c : ",follow[i][0] );
   int len=strlen(follow[i]);
   for(int j=1;j<len;j++)
    printf(" %c ",follow[i][j] );
 }

}
