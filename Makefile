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
