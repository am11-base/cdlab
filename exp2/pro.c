#include<stdio.h>
#include<string.h>
int states,transition_c=0;
char transition[10][10],input[10],result[10][10];

void checkstate(char source,int add)
{
 int i=0;
 while(i<transition_c)
 {
   if(transition[i][0]==source&&transition[i][1]=='e')
   {
     char dest[2];
     dest[0]=transition[i][2];
     dest[1]='\0';

      //add a condition to check if already present
     strcat(result[add],dest);
     checkstate(dest[0],add);
   }

  i++;
 }
}
void main()
{

 printf("\n Enter the number of states : ");
 scanf("%d",&states);
 printf("\nEnter the transition table(state1-input-state2) //enter exit to stop input\n");
 scanf("%s",input);
 while(strcmp(input,"exit")!=0)
 {

   strcat(transition[transition_c],input);
   transition_c++;
   scanf("%s",input);
 }
 for(int i=0;i<transition_c;i++)
  printf("\n%s",transition[i] );

  for(int i=0;i<states;i++)
  {
    char st[2];
    st[0]=i+'0';
    st[1]='\0';
    printf("st%s", st);
    strcat(result[i],st);
    checkstate(st[0],i);

  }
  printf("result\n");
  for(int i=0;i<states;i++)
  {
    printf("\neclosure of %d is {%s}",i,result[i] );
  }

}
