%{
  #include<stdio.h>
  char outtext[100];
  int i;
%}

%%
[a-zA-Z]* {
for(i=0;i<=yyleng;i++){
if((yytext[i]=='a')&&(yytext[i+1]=='b')&&(yytext[i+2]=='c'))
{
 
 outtext[i]='A';
 outtext[i+1]='B';
 outtext[i+2]='C';
 i+=2;
}
else
 outtext[i]=yytext[i];
}
outtext[i]='\0';
printf("%s",outtext);
}
%%
void main()
{
 FILE *ptr;
 ptr=fopen("input.txt","r");
 yyin=ptr;

 while(yylex())
 {

 fclose(ptr);}
}
int yywrap()
{ return 1;}
