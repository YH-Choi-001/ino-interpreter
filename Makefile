# Makefile to compile, build example sketches and test.
# 
# Copyright (c) 2026 YH Choi. All rights reserved.
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

ARDUINO_CLI ?= arduino-cli

LIB_NAME ?= $(shell basename $(PWD))

FQBN ?= arduino:avr:nano
PROGRAMMER ?= arduinoasisp
ARDUINO_CLI_FLAGS = --library ./ --clean --fqbn $(FQBN)
BOARD_FLAGS = --port $(PORT)

COMPILE_CMD = $(ARDUINO_CLI) compile $(ARDUINO_CLI_FLAGS)

SKETCH_FILES := $(shell find examples -type f -name "*.ino")

VERIFY_FILES := $(SKETCH_FILES:.ino=.ino.verify)
ELF_FILES := $(SKETCH_FILES:.ino=.ino.elf)
HEX_FILES := $(SKETCH_FILES:.ino=.ino.hex)
BIN_W_BTLD_FILES := $(SKETCH_FILES:.ino=.ino.with_bootloader.bin)
HEX_W_BTLD_FILES := $(SKETCH_FILES:.ino=.ino.with_bootloader.hex)

all: $(ELF_FILES)

verify: $(VERIFY_FILES)

test:
	cd .tests && make | grep -E "(Testing|All passed|failed)" && make clean

%.ino.verify: %.ino
	$(COMPILE_CMD) $<

%.ino.elf: %.ino
	$(COMPILE_CMD) $< --output-dir $(shell dirname $<)

%.ino.hex: %.ino
	$(COMPILE_CMD) $< --output-dir $(shell dirname $<)

%.ino.with_bootloader.bin: %.ino
	$(COMPILE_CMD) $< --output-dir $(shell dirname $<)

%.ino.with_bootloader.hex: %.ino
	$(COMPILE_CMD) $< --output-dir $(shell dirname $<)

board_details:
	$(ARDUINO_CLI) board details --fqbn $(FQBN)

list_ports:
	$(ARDUINO_CLI) board list

burn_bootloader:
	$(ARDUINO_CLI) burn-bootloader --fqbn $(FQBN) $(BOARD_FLAGS) --programmer $(PROGRAMMER) --verify

upload:
	$(COMPILE_CMD) examples/$(SKETCH)/$(SKETCH).ino $(BOARD_FLAGS) --upload --verify

clean:
	find examples -type f -name "*.elf" -exec rm {} \; || true
	find examples -type f -name "*.hex" -exec rm {} \; || true
	find examples -type f -name "*.bin" -exec rm {} \; || true
	find examples -type f -name "*.eep" -exec rm {} \; || true
