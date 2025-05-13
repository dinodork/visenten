#!/bin/bash

tags_file=TAGS

rm $tags_file
git ls-files '*.cpp' '*.hpp' '*.ypp' | xargs ctags -a -e -f$tags_file --langmap=YACC:.ypp
