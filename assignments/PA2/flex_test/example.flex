%{
    #include <stdio.h>    
    void printhello(){
        printf("hello world\n");
        }
%}

%%
\"/\\   {printf("escaped quote\n");}
\"      {printf("quote\n");}
%%

