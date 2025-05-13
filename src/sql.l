%{

// For some reason the parser's header file doesn't become self-sufficient; it
// doesn't contain the #include's from the Bison definition section. This causes
// the %union to get compiler errors as the parse tree types aren't defined.
// Fixing it by including their header first.
#include "parse_tree.hpp"

#include "sql_tab.hpp"


#include <iostream>
using std::string;
%}

%option noyywrap case-insensitive

%s COMMENT

%%

--              BEGIN(COMMENT);
<COMMENT>[^\n]*
<COMMENT>\n     BEGIN(INITIAL);

AS       { return AS; }
BY       { return BY; }
FROM     { return FROM; }
INTO     { return INTO; }
JOIN     { return JOIN; }
LIMIT    { return LIMIT; }
ON       { return ON; }
ORDER    { return ORDER; }
SELECT   { return SELECT; }
UNION    { return UNION; }
USING    { return USING; }
WITH     { return WITH; }
CREATE   { return CREATE; }
TABLE    { return TABLE; }


[0-9]+   { yylval.val = atoi(yytext); return NUM; }

[\+|\-]  { yylval.sym = yytext[0]; return OPA; }
[\*|/]   { yylval.sym = yytext[0]; return OPM; }
"("      { return '('; }
")"      { return ')'; }
","      { return ','; }
";"      { return STOP; }
"="      { return '='; }
<<EOF>>  { return YYEOF; }
[ \t\n]+ { }

[a-zA-Z][a-z0-9]* { yylval.word = new string(yytext); return ALPHANUM; }
%%
