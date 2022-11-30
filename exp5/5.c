#include<stdio.h>
#include<string.h>
int states,transition_c=0,sym_c=0,min_c=0,qc=0,mtransition_c=0,mfinal_c=0;
char input_sym[10],transition[10][10],final[10],mfinal[10][10],mintrans[20][20],mtransition[20][20];
int final_c=0,nfinal_c=0,table[10][10],queue[10];

const char* findstate(char sym)
{
  for(int i=0;i<min_c;i++)
  {
    int len=strlen(mintrans[i]);
    for(int j=0;j<len;j++)
    {
      if(mintrans[i][j]==sym)
       return mintrans[i];
    }
  }
}

int findtransition(int state,char sym)
{
  int cstate=state+'0';
  for(int i=0;i<transition_c;i++)
  {
    if(transition[i][0]==cstate&&transition[i][1]==sym)
    {
      char a=transition[i][2];
      int s2=a-'0';
      return s2;
    }
  }
}

int checkifalready(char string[10])
{
  for(int i=0;i<mfinal_c;i++)
  {
    if(strcmp(mfinal[i],string)==0)
     return 1;
  }
  return 0;
}

void findfinal()
{
  char fstate[10];
  for(int i=0;i<final_c;i++)
  {
    memset(fstate,0,strlen(fstate));
    char a=final[i];
    strcat(fstate,findstate(a));
    //printf(" %s ",fstate );

    if(checkifalready(fstate)==0)
      strcat(mfinal[mfinal_c++],fstate);
  }

  printf("\nFinal states : ");
  for(int i=0;i<mfinal_c;i++)
  {
    printf(" %s ",mfinal[i] );
  }
}

void mintransition()
{
  for(int i=0;i<min_c;i++)
  {
    char a=mintrans[i][0];
    for(int j=0;j<sym_c;j++)
    {
     char transition[10],finaltrans[10];
     int s=a-'0';
     int r=findtransition(s,input_sym[j]);
     char b=r+'0';
     strcpy(finaltrans,findstate(b));
     strcpy(transition,mintrans[i]);

     char temp[2];
     temp[0]=input_sym[j];
     temp[1]='\0';

     strcat(transition,temp);
     strcat(transition,finaltrans);

     strcat(mtransition[mtransition_c++],transition);
    }
  }

  printf("\n Transitions");
  for(int i=0;i<mtransition_c;i++)
  {
    printf(" %s ",mtransition[i] );
  }
}



void minimizedfa()
{
  for(int i=1;i<states;i++)
  {
    for(int j=0;j<i;j++)
    {
      if(table[i][j]==0)
      {
       for(int k=0;k<sym_c;k++)
       {
         int first=findtransition(i,input_sym[k]);
         int second=findtransition(j,input_sym[k]);
         if(second>first)
         {
           int temp=first;
           first=second;
           second=temp;
         }
         if(table[first][second]==1)
         {
           table[i][j]=1;
           minimizedfa();
         }
       }
      }
    }
  }
}
void minstates()
{//combining states
  for(int i=1;i<states;i++)
  {
    for(int j=0;j<i;j++)
    {
      if(table[i][j]==0)
      {
        queue[qc++]=i;
        queue[qc++]=j;
        char a=i+'0';
        char b=j+'0';
        char temp[2];
        temp[0]=a;
        temp[1]=b;
        strcat(mintrans[min_c++],temp);

      }

    }
  }

  //findrest
  for(int i=0;i<states;i++)
  {
    int flag=0;
    for(int j=0;j<qc;j++)
    {
      if(queue[j]==i)
      {
        flag=1;
        break;
      }
    }
    if(flag==0)
    {
      queue[qc++]=i;
      char temp=i+'0';
      char temp1[2];
      temp1[0]=temp;
      temp1[1]='\0';
      strcat(mintrans[min_c++],temp1);
    }
  }

  printf("\n Minimized States : ");
  for(int i=0;i<min_c;i++)
  {
    printf(" %s ",mintrans[i] );
  }
}


int isfinal(int state)
{
  char cstate=state+'0';
  for(int i=0;i<final_c;i++)
  {
   if(final[i]==cstate)
    return 1;
  }
  return 0;
}

void firstfill()
{
  for(int i=1;i<states;i++)
  {
    for(int j=0;j<i;j++)
    {
      if((isfinal(i)==1&&isfinal(j)==0)||(isfinal(i)==0&&isfinal(j)==1))
       table[i][j]=1;
      else
       table[i][j]=0;
    }
  }

  printf("\n Printing myhold table ");
  for(int i=1;i<states;i++)
  {
    for(int j=0;j<states;j++)
    {
      printf("\ni:%d,j:%d,con:%d",i,j,table[i][j]);
    }
  }
}



void main()
{
  char sym;
 printf("\n States start from 0 to n-1. Enter e for epsilon moves");
 printf("\n Enter the number of states (n): ");
 scanf("%d",&states);
 scanf("%c",&sym);
 printf("\n Enter the symbols (e to exit): ");
 scanf("%c",&sym);
 while(sym!='e')
 {
  input_sym[sym_c++]=sym;
  scanf("%c",&sym);
 }
 input_sym[sym_c]='\0';
 char input[10];
 printf("\nEnter the transition table(state1-input-state2) //enter exit to stop input\n");
 scanf("%s",input);
 while(strcmp(input,"exit")!=0)
 {

   strcat(transition[transition_c],input);
   transition_c++;
   scanf("%s",input);
 }
 printf("\n Enter the final states(e to exit): ");
 scanf("%c",&sym);
 scanf("%c",&sym);
 while(sym!='e')
 {

  final[final_c++]=sym;
  scanf("%c",&sym);
 }
 final[final_c]='\0';
 firstfill();
 minimizedfa();

 printf("\n Printing myhold table ");
 for(int i=1;i<states;i++)
 {
   for(int j=0;j<states;j++)
   {
     printf("\ni:%d,j:%d,con:%d",i,j,table[i][j]);
   }
 }

 minstates();
 mintransition();
 //printf("\nfinal:%s",final);
 findfinal();
}
