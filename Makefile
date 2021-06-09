default: visenten sql.png sql.automaton

visenten: sql.ypp ast.h sql.l
	bison -d sql.ypp -g -v -t --report-file=sql.automaton -rstat
	flex sql.l
	g++ -o visenten sql.tab.cpp lex.yy.c -g

sql.automaton: visenten

sql.png: sql.dot
#	dot -Tpng sql.dot > sql.png
