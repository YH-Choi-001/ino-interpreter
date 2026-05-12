#!/bin/bash

TARGETCPP=$1

if [ ! -f "$TARGETCPP" ]
then
    echo "$0: file not found:" "$TARGETCPP"
    exit 1
fi

ENDLINE_STR=$(grep -n "const testfunc_t functions \[\] \=" "$TARGETCPP")

if [ $? -ne 0 ]
then
    echo "$0: file does not have the testcases collection array: $TARGETCPP"
    exit 0
fi

ENDLINE=$(echo "$ENDLINE_STR" | cut -f1 -d:)

head -n $ENDLINE "$TARGETCPP" > "$TARGETCPP.target"
chmod u+x ./get_testcase.sh
./get_testcase.sh "$TARGETCPP" | sed 's/^/    /g' | sed 's/$/,/g' >> "$TARGETCPP.target"
printf "};\n\nMAIN();\n" >> "$TARGETCPP.target"
cat "$TARGETCPP.target" > $TARGETCPP
rm "$TARGETCPP.target"

echo "$0: done: $TARGETCPP"
