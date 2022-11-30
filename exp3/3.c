#include<stdio.h>
#include<string.h>
int states,transition_c=0,sym_c=0;
char transition[10][10],input[10],result[10][10],newtransition[10][10],symbol[10],final[10],nfinal[10];
int final_n=0,final_e=0,nc=0;



void findfinal()
{

 for(int i=0;i<states;i++)
 {
  for(int j=0;j<strlen(result[i]);j++)
  {
  
   for(int k=0;k<final_e;k++)
   {
      //printf("\n comparing %c %c",result[i][j],final[k]);
      if(result[i][j]==final[k])
      {
        nfinal[final_n++]=i+'0';
        
      }
   
   }
  }
 }
 nfinal[final_n]='\0';


}


void removeduplicants()
{
  for(int i=0;i<nc;i++)
  {
    for(int j=2;newtransition[i][j]!='\0';j++)
    {
    
     for(int k=j+1;newtransition[i][k]!='\0';k++)
     {
         
         if(newtransition[i][j]==newtransition[i][k])
         {
                 
                 //printf("\nbefore dup %s",newtransition[i]);
                 int l;
                 for(l=k;newtransition[i][l]!='\0';l++)
                 {
                 
                  newtransition[i][l]=newtransition[i][l+1];
                 }
                 k--;
                 
                 newtransition[i][l-1]='\0';
                 //printf("\nafter dup %s",newtransition[i]);
         }
     
     }
    
    }
  }


}


char checkstate(int source,char sym)
{
  int i=0;
  while(i<transition_c)
  {
  //  printf("\n%d %d",transition[i][0]-'0',source );
    if((transition[i][0]-'0')==source&&transition[i][1]==sym)
    {
      //printf("\nmatch%c%c%c",transition[i][0],transition[i][1],transition[i][2]);
      return transition[i][2];
    }
    i++;
  }
  return '/';
}
void newTransition(int st,char sym)
{
  char inter[10],count=0;
  //printf("\n Eclosure of %d for %c : ",st,sym );
  //sprintf("%d",strlen(result[st]));
  for(int i=0;i<strlen(result[st]);i++)
  {
  //  printf("\nchecking for %d",result[st][i]-'0' );
    int temp=result[st][i]-'0';

    char st=checkstate(temp,sym);
    if(st!='/')
    {
      inter[count]=st;
      count++;

    }

  }
  inter[count]='\0';
  //printf("printing%s\n%d",inter,strlen(inter));
  if(strlen(inter)!=0){
  newtransition[nc][0]=st+'0';
  newtransition[nc][1]=sym;

    //printf("[newTransition]%s",newtransition[nc] );
  for(int i=0;i<strlen(inter);i++)
  {
   int in=(inter[i]-'0');
   //printf("%s", result[in]);
    strcat(newtransition[nc],result[in]);
  }
  nc++;
}
}
void eClosure(char source,int add)
{
 int i=0;
 while(i<transition_c)
 {
   if(transition[i][0]==source&&transition[i][1]=='e')
   {
     char dest[2];
     dest[0]=transition[i][2];
     dest[1]='\0';
     //strcat(result[add],",");
     strcat(result[add],dest);
     eClosure(dest[0],add);
   }

  i++;
 }
}
void main()
{
 char sym;
 printf("\n States start from 0 to n-1. Enter e for epsilon moves");
 printf("\n Enter the number of states (n): ");
 scanf("%d",&states);
 printf("\n Enter the symbols (e to exit): ");
 scanf("%c",&sym);
 while(sym!='e')
 {

  symbol[sym_c++]=sym;
  scanf("%c",&sym);
 }
 symbol[sym_c]='\0';
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
 while(sym!='e')
 {

  final[final_e++]=sym;
  scanf("%c",&sym);
 }
 
 //for(int i=0;i<transition_c;i++)
  //printf("\n%s",transition[i] );

  for(int i=0;i<states;i++)
  {
    char st[2];
    st[0]=i+'0';
    st[1]='\0';
   //printf("st%s", st);
    strcat(result[i],st);
    eClosure(st[0],i);

  }

  for(int i=0;i<states;i++)
  {
  printf("\neclosure of %d is {%s}",i,result[i] );
  }
    printf("\nresult\n");

  for(int i=0;i<states;i++)
  {
    for(int j=0;j<sym_c;j++)
    {
      newTransition(i,symbol[j]);
    }
  }
  
  removeduplicants();
  findfinal();
 
  printf("\n Printing new transitions");
  printf("\n -------------------------");
  printf("\n State  Input    End State(s)");
  for(int i=0;i<nc;i++)
  {
    printf("\n   %c  ",newtransition[i][0] );
    printf("     %c  ",newtransition[i][1] );
    printf("      {");
    for(int j=2;newtransition[i][j]!='\0';j++)
    {
      printf(" %c ",newtransition[i][j] );

    }
    printf("}");

  }
  printf("\n\n Final States : ");
  for(int i=0;i<final_n;i++)
  {
   printf(" %c ",nfinal[i]);
  }
  printf("\n ");

}
