#!/bin/bash

bad_sql=bad.sql
good_sql=good.sql
executable=build/src/visenten

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
