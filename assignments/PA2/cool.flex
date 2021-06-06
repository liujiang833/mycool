/*
 *  The scanner definition for COOL.
 */
%{

#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>
#include <string>
#include <fstream>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex
/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;
extern int curr_lineno;
extern int verbose_flag;
extern YYSTYPE cool_yylval;
std::string curr_str;
int open_com_count;
%}
%x IN_COMMENT
%x IN_SINGLE_LINE_COMMENT
%x COMMENT_ESCAPE
%x IN_STR
%x STR_NULL
%x STR_ESCAPE

DARROW          =>
/*
  string and comments
*/

INT_CONST       [0-9]+
TYPEID          [A-Z]+[a-zA-z0-9_]*
OBJECTID        [a-z]+[a-zA-z0-9_]*

/*
  keyword 
*/
CLASS           (c|C)(l|L)(a|A)(s|S)(s|S)
ELSE            (e|E)(l|L)(s|S)(e|E)
FI              (f|F)(i|I)
IF              (i|I)(f|F)
IN              (i|I)(n|N)
ISVOID          (i|I)(S|s)(V|v)(O|o)(I|i)(D|d)
NOT             (N|n)(O|o)(T|t)
INHERITS        (i|I)(N|n)(H|h)(E|e)(r|R)(I|i)(T|t)(S|s)
LET             (l|L)(E|e)(T|t)
LOOP            (L|l)(O|o)(O|o)(P|p)
POOL            (p|P)(O|o)(O|o)(L|l)
THEN            (t|T)(H|h)(E|e)(N|n)
WHILE           (w|W)(H|h)(I|i)(L|l)(E|e)
CASE            (C|c)(A|a)(S|s)(E|e)
ESAC            (e|E)(s|S)(a|A)(c|C)
OF              (o|O)(f|F) 
NEW             (n|N)(e|E)(w|W)
BOOL_CONST      (t(r|R)(u|U)(e|E))|(f(a|A)(l|L)(s|S)(e|E))



/*
  binary and unary operations
*/
DOT           "."
AT            "@"
NEGATE        "~"
MULTIPLY      "*"
DIVIDE        "/"
PLUS          "+"
MINUS         "-"
LE            <=
LESSTHAN      "<"
EQUAL         "="
ASSIGN        <-

/* 
  other
*/
LEFT_PAREN    "("
RIGHT_PARENT  ")"
COLUNM        ":"
SEMICOLUNM    ";"
OPEN_CURLY    "{"
CLOSE_CURLY   "}"
COMMA         ","

%%


{DARROW}		{ return (DARROW); }
{CLASS}     { return CLASS;}
{ELSE}      { return ELSE;}
{FI}        { return FI;}
{IF}        { return IF;}
{IN}        { return IN;}
{ISVOID}    { return ISVOID;}
{NOT}       { return NOT;}
{INHERITS}  { return INHERITS;}
{LET}       { return LET;}
{LOOP}      { return LOOP;}
{POOL}      { return POOL;}
{THEN}      { return THEN;}
{WHILE}     { return WHILE;}
{CASE}      { return CASE;}
{ESAC}      { return ESAC;}
{OF}        { return OF;}
{NEW}       { return NEW;}

{DOT}       { return '.';}
{AT}        { return '@';}
{NEGATE}    { return '~';}
{MULTIPLY}  { return '*';}
{DIVIDE}    { return '/';}
{PLUS}      { return '+';}
{MINUS}     { return '-';}
{LE}        { return LE;}
{LESSTHAN}  { return '<';}
{EQUAL}     { return '=';}
{ASSIGN}    { return ASSIGN;}

{LEFT_PAREN}  { return '(';}
{RIGHT_PARENT}  { return ')';}
{COLUNM}      { return ':';}
{SEMICOLUNM}  { return ';';}
{OPEN_CURLY}  { return '{';}
{CLOSE_CURLY} { return '}';} 
{COMMA}       { return ',';}

{BOOL_CONST}  {
                cool_yylval.boolean= yytext[0] == 't'; 
                return BOOL_CONST;
              }

{INT_CONST}   {
                cool_yylval.symbol = inttable.add_string(yytext);
                return INT_CONST;
              }

{TYPEID}      {
                cool_yylval.symbol = idtable.add_string(yytext);
                return TYPEID;
              }
{OBJECTID}      {
                cool_yylval.symbol = idtable.add_string(yytext);
                return OBJECTID;
              }
[ \t\v\f\r]        ;
\n     {curr_lineno++;};

<INITIAL>\(\*       {
                      BEGIN(IN_COMMENT);
                      open_com_count = 1;}
<IN_COMMENT>\(\*    {
                      open_com_count++;
                    }

<IN_COMMENT>\\[\(\)\*]  ;
<IN_COMMENT>\*\)    { 
                      open_com_count--; 
                      if(open_com_count == 0)
                        BEGIN(INITIAL); 
                      }
<IN_COMMENT>.  ;   
<IN_COMMENT>\n  {curr_lineno++;}   
\*\)             {
                  cool_yylval.error_msg = "Unmatched *)";
                  return ERROR;
                }
<INITIAL>\-\- {BEGIN(IN_SINGLE_LINE_COMMENT);}
<IN_SINGLE_LINE_COMMENT>.  ;   
<IN_SINGLE_LINE_COMMENT>\n  {
                              curr_lineno++;
                              BEGIN(INITIAL);}   
<INITIAL>\"       { 
                    BEGIN(IN_STR);
                    curr_str.clear();
                  }
                  
<IN_STR>\\      {
                    BEGIN(STR_ESCAPE);
                }

<STR_ESCAPE>.  {
                            if(yytext[0]=='\0'){
                                BEGIN(STR_NULL);
                            }else{
                                switch(yytext[0]){
                                    case 'b': curr_str.push_back('\b'); break;
                                    case 't': curr_str.push_back('\t'); break;
                                    case 'n': curr_str.push_back('\n'); break;
                                    case 'f': curr_str.push_back('\f'); break;
                                    default : curr_str.push_back(yytext[0]); break;
                                } 
                                BEGIN(IN_STR);
                            }
                        }
<STR_ESCAPE>\n  {
                  curr_str.push_back(yytext[0]);
                  curr_lineno++;
                  BEGIN(IN_STR);
                }

<IN_STR>\"      { 
                    BEGIN(INITIAL);
                    if(curr_str.size() >= MAX_STR_CONST){
                      cool_yylval.error_msg = "String constant too long";
                      return ERROR;
                    } 
                    string_buf_ptr = (char*)curr_str.c_str();
                    cool_yylval.symbol = stringtable.add_string(string_buf_ptr);
                    return STR_CONST;
                }
<IN_STR>.            {
                                if(yytext[0]=='\0'){
                                    BEGIN(STR_NULL);
                                }else{
                                    curr_str.push_back(yytext[0]);
                                }
                            }   

                  
<IN_STR>\n      {
                    BEGIN(INITIAL);
                    curr_lineno++;
                    cool_yylval.error_msg = "Unterminated string constant";
                    return ERROR;
                }
<STR_NULL>\n|\"   {
                    BEGIN(INITIAL);
                    if(yytext[0] == '\n')
                      curr_lineno++;
                    cool_yylval.error_msg = "String contains null character";
                    return ERROR;
                  }
<STR_NULL>.       ;


<IN_COMMENT><<EOF>>   {
                      BEGIN(INITIAL);
                      cool_yylval.error_msg = "EOF in comment";
                      return ERROR;
                    }

<IN_STR,STR_ESCAPE><<EOF>>   {
                      BEGIN(INITIAL);
                      cool_yylval.error_msg = "EOF in string constant";
                      return ERROR;
                    }
<INITIAL,IN_SINGLE_LINE_COMMENT><<EOF>>  {
                    yyterminate();
                  }
.             {
                cool_yylval.error_msg = yytext;
                return ERROR;
              }

%%