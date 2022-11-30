%{
 #include<stdio.h>
 int num_w,num_l,num_c;


%}

%%
[\n] {num_l++;num_c+=yyleng; }
[^ \n]+ {num_w++;num_c+=yyleng;}
. {num_c++;}

%%
void main()
{
 num_c=0;
 num_l=0;
 num_w=0;
 FILE *ptr;
 ptr=fopen("input.txt","r");
 yyin=ptr;
 while(yylex())
 {
  fclose(ptr);
 }
 printf("\n Number of characters : %d",num_c);
 printf("\n Number of lines :%d",num_l);
 printf("\nNumber of words :%d",num_w);
}

int yywrap()
{
 return 1;
}
