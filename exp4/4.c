#include<stdio.h>
#include<string.h>
int states,transition_c=0,dfatrans_c=0,sym_c=0;
char nfa_transition[10][10],input_sym[10],dfa_transition[20][10],dfastates[20][10],queue[10][10],nfafinal[10],dfafinal[10][10];
int queue_c=0,nfinal_c=0,dfinal_c=0;


void stateprint()
{
  printf("\n DFA States : ");
  for(int i=0;i<queue_c;i++)
  {
    printf(" %s ",queue[i]);
  }
}


void findfinal()
{
  for(int i=0;i<queue_c;i++)
  {
    int flag=0;
    int len=strlen(queue[i]);
    for(int j=0;j<len;j++)
    {
      for(int k=0;k<nfinal_c;k++)
      {
        if(nfafinal[k]==queue[i][j])
        {
          strcat(dfafinal[dfinal_c++],queue[i]);
          flag=1;
          break;
        }
      }
      if(flag==1)
      {
        break;
      }
    }
  }

  printf("\n\n final states:");
  for(int i=0;i<dfinal_c;i++)
  {
    printf(" %s ",dfafinal[i]);
  }
}

void sort(char transition[10])
{
  int len=strlen(transition);
  for(int i=0;i<len-1;i++)
  {
    for(int j=i+1;j<len;j++)
    {
      if(transition[i]>transition[j])
      {
        char temp=transition[i];
        transition[i]=transition[j];
        transition[j]=temp;
      }
    }
  }

}
void removeduplicants(char transition[10])
{

    for(int j=0;transition[j]!='\0';j++)
    {

     for(int k=j+1;transition[k]!='\0';k++)
     {

         if(transition[j]==transition[k])
         {

                 //printf("\nbefore dup %s",newtransition[i]);
                 int l;
                 for(l=k;transition[l]!='\0';l++)
                 {

                  transition[l]=transition[l+1];
                 }
                 k--;

                 transition[l-1]='\0';
                 //printf("\nafter dup %s",newtransition[i]);
         }

     }

    }



}



int checkifalready(char state[10])
{
 for(int i=0;i<queue_c;i++)
 {
  if(strcmp(queue[i],state)==0)
   return 1;
 }
 return 0;
}

void finalprint()
{
 printf("\n\n transitions ");
 for(int i=0;i<dfatrans_c;i++)
 {
  printf("\n %s",dfa_transition[i]);

 }


}

void findtransition(char currstate,char sym,char trans[10])
{
 int i=0;
 while(i<transition_c)
 {
  if(nfa_transition[i][0]==currstate&&nfa_transition[i][1]==sym)
  {
   char temp[2];
   temp[0]=nfa_transition[i][2];
   temp[1]='\0';
   strcat(trans,temp);
  }
  i++;
 }

}


void converttodfa()
{
 memset(queue[0],0,strlen(queue[0]));
 strcat(queue[queue_c++],"0");
 //printf("\nstate:%s\n",queue[0]);

 int ptr=0;
 while(ptr!=queue_c)
 {
   printf("\nptr:%d,queue_c:%d",ptr,queue_c);
  char state[10];
  memset(state,0,strlen(state));
  strcat(state,queue[ptr]);
   printf("\nstate:%s\n",state);
  int len=strlen(state);
  printf("len:%d\n",len);
  for(int i=0;i<sym_c;i++)
  {
   char finaltrans[10]={'\0'};
   for(int j=0;j<len;j++)
   {
     char currstate=state[j];
     char trans[10]="";
     findtransition(currstate,input_sym[i],trans);
     strcat(finaltrans,trans);
    }
     char temp[10]={'\0'};//doing it in the safe way
     strcat(temp,state);
     char temp2[2];
     temp2[0]=input_sym[i];
     temp2[1]='\0';
     printf("\n inputsymbl :%s",temp2);
     strcat(temp,temp2);
     removeduplicants(finaltrans);
     sort(finaltrans);
     strcat(temp,finaltrans);

     printf("\nnewtrans:%s",temp);
     if(checkifalready(finaltrans)==0)
      strcat(queue[queue_c++],finaltrans);
     strcat(dfa_transition[dfatrans_c++],temp);
      printf("\nptr:%d,queue_c:%d",ptr,queue_c);
       printf("\ndfatrans_c:%d",dfatrans_c);
   }

//apply remove duplicants from finaltrans


  ptr++;
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

   strcat(nfa_transition[transition_c],input);
   transition_c++;
   scanf("%s",input);
 }
 printf("\n Enter the final states(e to exit): ");
 scanf("%c",&sym);
 while(sym!='e')
 {

  nfafinal[nfinal_c++]=sym;
  scanf("%c",&sym);
 }
 //for(int i=0;i<sym_c;i++)
  //printf("sym:%c",input_sym[i]);
 converttodfa();
 stateprint();
 finalprint();
 findfinal();
}
