# Makefile wrapping the CMake build of the GoogleTest unit tests.
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

# Usage:
#   make test    configure, build and run all tests (GoogleTest is fetched on the first run)
#   make clean   remove every build artefact, including the GoogleTest download
#
# Run a subset of tests with TEST_FILTER, a regex over "Suite.test" names, e.g.
#   make test TEST_FILTER="SubstringTest\."

CMAKE ?= cmake
CTEST ?= ctest

BUILD_DIR := build
BUILD_TYPE ?= Debug
JOBS ?= $(shell getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)

CTEST_FLAGS := --test-dir $(BUILD_DIR) --output-on-failure --parallel $(JOBS)
ifdef TEST_FILTER
CTEST_FLAGS += --tests-regex "$(TEST_FILTER)"
endif

.PHONY: all build test clean

all: build

$(BUILD_DIR)/CMakeCache.txt: CMakeLists.txt
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: $(BUILD_DIR)/CMakeCache.txt
	$(CMAKE) --build $(BUILD_DIR) --parallel $(JOBS)

test: build
	$(CTEST) $(CTEST_FLAGS)

clean:
	rm -rf $(BUILD_DIR)
