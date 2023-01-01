#include <stdio.h>
#include <string.h>
#include <ctype.h>
int multiflag=0;
int strflag=0;
int chrcount=0;
int isNum(char a)
{
        if(a=='0'||a=='1'||a=='2'||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9')
                return 1;
        else
                return 0;

}
int check_seperator(char ch[10])
{

        char seperator[8][10]={
                ",","{","[","(",")","]","}",";",
        };

        for(int i=0; i<8; i++)
        {

                if(strcmp(seperator[i],ch)==0)
                        return 1;

        }
        return 0;
}
int check_operator(char ch[10])
{

        char operator[25][10]={
                "+","-","*","/","%","=","+=","-=","/=","%=","==",">","<","!=",">=","<=","&&","||","!","&","|","^","~","<<",">>"
        };

        for(int i=0; i<25; i++)
        {

                if(strcmp(operator[i],ch)==0)
                        return 1;

        }
        return 0;
}
int check_keyword(char ch[10])
{

        char keyword[32][10]={
                "auto","double","int","struct","break","else","long",
                "switch","case","enum","register","typedef","char",
                "extern","return","union","const","float","short",
                "unsigned","continue","for","signed","void","default",
                "goto","sizeof","voltile","do","if","static","while"
        };

        for(int i=0; i<32; i++)
        {

                if(strcmp(keyword[i],ch)==0)
                        return 1;

        }
        return 0;
}
void lexanal(char ch[50])
{

        FILE *ptr;
        ptr=fopen("output.txt","a");
        char a=ch[0];

        if(a== '#')
        {
                fprintf(ptr,"<%s,preprocessor>\n",ch);
        }

        else
        {
                char *token;
                char *rest = ch;

                while((token=strtok_r(rest," ",&rest)))
                {
                        int flag=1,j;
                        printf("\ntoken is :%s",token);
                        int len=strlen(token);
                        if(token[0]=='/' && token[1]=='/')
                                break;
                        //printf("%s\n",token);

                        if(token[0]=='/' && token[1]=='*')
                        {
                                printf("mf turn on");
                                multiflag=1;

                        }
                        if(token[len-1]=='/' && token[len-2]=='*')
                        {
                                printf("mf turn off");
                                multiflag=0;
                                continue;

                        }
                        if(multiflag!=1)
                        {

                                printf("\n%s token inside mf",token);
                                int st_key,st_op;
                                if((st_key=(check_keyword(token)))==1)
                                {
                                        printf("%s is keyword\n",token);
                                        fprintf(ptr,"<%s,keyword>\n",token);
                                }
                                else if((st_op=(check_operator(token)))==1)
                                {
                                        printf("%s is operator\n",token);
                                        fprintf(ptr,"<%s,operator>\n",token);
                                }
                                else if((st_op=(check_seperator(token)))==1)
                                {
                                        printf("%s is seperator\n",token);
                                        fprintf(ptr,"<%s,seperator>\n",token);
                                }

                                else if(isNum(token[0]))
                                {
                                        int sepflag=0;
                                        int len=strlen(token);
                                        if(token[len-1]==';')
                                                sepflag=1;
                                        char *checknum=strtok_r(token,";",&token);
                                        printf("%s",checknum);
                                        int clen=strlen(checknum);
                                        for(int i=1; i<clen; i++)
                                        {
                                                if(!isNum(checknum[i]))
                                                {
                                                        flag=0;
                                                        break;
                                                }
                                        }
                                        if(flag==1)
                                        {
                                                printf("%s is integer\n",checknum);
                                                printf("%s is ptoken",token);
                                                fprintf(ptr,"<%s,integer>\n",checknum);
                                        }
                                        if(sepflag==1)
                                                fprintf(ptr,"<;,separator>\n");

                                }
                                else
                                //if(isalpha(token[0])||token[])
                                {
                                        int len=strlen(token),k=0,nk=-1;
                                        char s[10];
                                        s[k]=token[0];
                                        char n[10];
                                        char str[50]; int sc;

                                        printf("\n checking");
                                        int i=0;
                                        while(i<len)
                                        {
                                                char stoken[10];
                                                stoken[0]=token[i];
                                                stoken[1]='\0';

                                                if(token[i]=='\"'||strflag==1)
                                                {
                                                        printf("\n inside lcheck");
                                                        if(strflag==0)
                                                        {
                                                                strflag=1;
                                                                sc=0;
                                                                str[sc]=token[i];
                                                        }
                                                        else
                                                        {
                                                                if(token[i]=='\"')
                                                                {
                                                                        strflag=0;
                                                                        str[++sc]='\"';
                                                                        str[++sc]='\0';
                                                                        fprintf(ptr,"<%s,literal>\n",str);
                                                                        memset(str,0,sizeof(str));
                                                                }
                                                                else
                                                                        str[++sc]=token[i];
                                                        }



                                                }
                                                else if(token[i]=='\'')
                                                {
                                                        if(chrcount%2==0)
                                                        {
                                                                fprintf(ptr,"<'%c',literal>\n",token[i+1]);
                                                                i++;
                                                        }

                                                        chrcount++;
                                                }
                                                else if(check_operator(stoken)||check_seperator(stoken))
                                                {

                                                        //printf("%c inside opcheck",token[i]);
                                                        if(k!=-1)
                                                        {
                                                                s[++k]='\0';
                                                                if(check_keyword(s)==1)
                                                                        fprintf(ptr,"<%s,keyword>\n",s);
                                                                else
                                                                        fprintf(ptr,"<%s,identifier>\n",s);
                                                                k=-1;
                                                                memset(s,0,strlen(s));

                                                        }
                                                        if(nk!=-1)
                                                        {
                                                                n[++nk]='\0';
                                                                fprintf(ptr,"<%s,integer>\n",n);
                                                                nk=-1;
                                                                memset(n,0,strlen(n));
                                                        }



                                                        if(check_operator(stoken))
                                                        {
                                                                char nextcheck[3];
                                                                nextcheck[0]=stoken[0];
                                                                nextcheck[1]=token[i+1];
                                                                nextcheck[2]='\0';
                                                                if(check_operator(nextcheck))
                                                                {
                                                                        printf("double op");
                                                                        fprintf(ptr,"<%s,operator>\n",nextcheck);
                                                                        i++;
                                                                }
                                                                else
                                                                        fprintf(ptr,"<%c,operator>\n",token[i]);
                                                        }
                                                        if(check_seperator(stoken))
                                                                fprintf(ptr,"<%c,seperator>\n",token[i]);
                                                }

                                                else if(isalnum(token[i]))
                                                {
                                                        if(k==-1)
                                                        {
                                                                if(isalpha(token[i]))
                                                                {
                                                                        k++;
                                                                        s[k]=token[i];
                                                                        //printf("%c appended",token[i]);
                                                                }

                                                        }
                                                        else
                                                        {
                                                                k++;
                                                                s[k]=token[i];
                                                                //printf("%c appended",token[i]);
                                                        }


                                                        if(isNum(token[i]))
                                                        {
                                                                n[++nk]=token[i];
                                                        }
                                                }

                                                i++;
                                        }
                                        if(k!=-1) {
                                                s[++k]='\0';
                                                if(check_keyword(s)==1)
                                                        fprintf(ptr,"<%s,keyword>\n",s);
                                                else
                                                        fprintf(ptr,"<%s,identifier>\n",s);
                                        }
                                }
                                /**/
                        }
                }
        }
        fclose(ptr);
}
void main()
{
        FILE *ptr;
        char ch[50];
        ptr=fopen("sample1.txt","r");
        FILE *ptr1;
        ptr1=fopen("output.txt","w");
        fclose(ptr1);

        while(fgets(ch,50,ptr))
        {
                ch[strcspn(ch,"\n")]=0;
                //printf("%s",ch);
                lexanal(ch);

        };
        fclose(ptr);
}
