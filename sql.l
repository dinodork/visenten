%{
#include "ast.h"
#include "sql.tab.hpp"
#include <iostream>
using namespace std;
%}

%option noyywrap

%%

[0-9]+   { yylval.val = atoi(yytext); return NUM; }
[a-z][a-z0-9]* { yylval.word = new string(yytext); return ALPHANUM; }
[\+|\-]  { yylval.sym = yytext[0]; return OPA; }
[\*|/]   { yylval.sym = yytext[0]; return OPM; }
"("      { return '('; }
")"      { return ')'; }
","      { return ','; }
";"      { return STOP; }
"="      { return '='; }
<<EOF>>  { return 0; }
[ \t\n]+ { }
.        { cerr << "Unrecognized token!" << endl; exit(1); }
AS       { return AS; }
SELECT   { return SELECT; }
FROM     { return FROM; }
UNION    { return UNION; }
JOIN     { return JOIN; }
ON       { return ON; }
USING    { return USING; }
INTO     { return INTO; }
ORDER    { return ORDER; }
BY       { return BY; }
LIMIT    { return LIMIT; }
WITH     { return WITH; }
%%
