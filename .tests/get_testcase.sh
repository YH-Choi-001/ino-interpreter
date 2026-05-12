#!/bin/bash

TARGETCPP=$1

if [ ! -f "$TARGETCPP" ]
then
    echo "$0: file not found:" "$TARGETCPP" 1>&2
    exit 1
fi

TESTFUNC_IDENTIFIER_REGEX="test_[[:alnum:]_]*"
TESTFUNC_PARAM_STR="testing_framework::testcase_result_t &result, std::stringstream &reasonstream"
TESTFUNC_SIGNATURE_REGEX="void $TESTFUNC_IDENTIFIER_REGEX[\(]$TESTFUNC_PARAM_STR[\)]"
gcc -E "$TARGETCPP" | grep -o "$TESTFUNC_SIGNATURE_REGEX" | grep -o "$TESTFUNC_IDENTIFIER_REGEX"
