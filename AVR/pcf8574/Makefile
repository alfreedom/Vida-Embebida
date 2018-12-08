# Name: Makefile
# Author:    <insert your name here>
# Copyright: <insert your copyright message here>
# License:   <insert your license reference here>

PROJECT_NAME = pcf8574
DEVICE       = atmega32
CLOCK        = 16000000
PROGRAMMER   = -c usbtiny -P usb
FUSES        = -U hfuse:w:0xD9:m -U lfuse:w:0xDE:m #-U efuse:w:0xFF:m
AVRDUDE      = avrdude $(PROGRAMMER) -p $(DEVICE)

OBJECT_FILES = main.o
OBJECT_FILES += ./src/i2c_master.o
OBJECT_FILES += ./src/pcf8574.o

INCLUDEPATHS =  -I ./include
#INCLUDEPATHS += -I ./include/myFolder

CFLAGS = -ffunction-sections -fpermissive -std=c++11
LDFLAGS = -Wl,-gc-sections

COMPILE = avr-g++ $(CFLAGS) $(LDFLAGS) -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(INCLUDEPATHS)

# symbolic targets:
all: $(PROJECT_NAME).hex

.c.o:
	$(COMPILE) -c $< -o $@

.cpp.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

.cpp.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:$(PROJECT_NAME).hex:i

fuse:
	$(AVRDUDE) $(FUSES)

erase:
	$(AVRDUDE) -e

reset:
	$(AVRDUDE)

install: flash fuse

clean:
	rm -f $(PROJECT_NAME).hex $(PROJECT_NAME).elf $(OBJECT_FILES)

$(PROJECT_NAME).elf: $(OBJECT_FILES)
	$(COMPILE) -o $(PROJECT_NAME).elf $(OBJECT_FILES)

$(PROJECT_NAME).hex: $(PROJECT_NAME).elf
	rm -f $(PROJECT_NAME).hex
	avr-objcopy -j .text -j .data -O ihex $(PROJECT_NAME).elf $(PROJECT_NAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(PROJECT_NAME).elf

disasm:	$(PROJECT_NAME).elf
	avr-objdump -d $(PROJECT_NAME).elf

cpp:
	$(COMPILE) -E main.c
