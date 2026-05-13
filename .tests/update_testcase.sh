#!/bin/bash

# @file update_testcase.sh A unix-like shell script used to update the list of test cases in a test file.
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
