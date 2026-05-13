#!/bin/bash

# @file get_testcase.sh A unix-like shell script used to get the list of test cases in a test file.
# 
# @copyright Copyright (c) 2026 YH Choi. All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The copyright of Arduino API belongs to Arduino and their respective copyright holders.
# The copyright notice above only covers the contents of this file,
# which might not be applicable to Arduino API.

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
