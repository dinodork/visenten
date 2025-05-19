#!/bin/bash

top_dir=`git rev-parse --show-toplevel`
bad_sql="$top_dir/test/bad.sql"
good_sql="$top_dir/test/good.sql"

if [ "$1" == "" ]
then
  executable=$top_dir/build/src/visenten
else
  executable="$1"
fi

# Test the bad SQL
while read line
do
  rm -f error.log
  echo "${line}" | $executable 2>> error.log
  status="$?"
  if [ "$status" == 0 ]
  then
    echo "This passed and it shouldn't: $line"
    exit 1
  fi
done < ${bad_sql}

# Test the good SQL
while read line
do
  if [ "${line}" != "" ]
  then
    echo "${line}" | $executable > /dev/null
    if [ $? != 0 ]
    then
      echo "This didn't pass and it should: $line"
      exit 1
    fi
  fi
done < ${good_sql}

if [ "$?" == "0" ]
then
  echo All tests passed.
fi
