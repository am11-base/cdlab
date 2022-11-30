%{
   #include<stdio.h>
   int vowel_c=0;
   int cons_c=0;

%}

%%
[aeiouAEIOU] {vowel_c++;}
[a-zA-Z] {cons_c++;}
%%
void main()
{

 FILE *ptr;
 ptr=fopen("input.txt","r");
 yyin=ptr;
 while(yylex())
 {
 fclose(ptr);
 }
 printf("\n Vowel count is %d",vowel_c);
 printf("\n Consonant count is %d",cons_c);

}
int yywrap()
{
 return 1;
}
