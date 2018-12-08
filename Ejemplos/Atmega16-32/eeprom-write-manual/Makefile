# Name: Makefile
# Author:    <insert your name here>
# Copyright: <insert your copyright message here>
# License:   <insert your license reference here>

PROJECT_NAME = eeprom-write-manual
DEVICE       = atmega32
CLOCK        = 16000000
PROGRAMMER   = -c usbtiny -P usb
FUSES        = -U hfuse:w:0xD1:m -U lfuse:w:0xDE:m #-U efuse:w:0xFF:m
AVRDUDE      = avrdude $(PROGRAMMER) -p $(DEVICE) -B 2

OBJECT_FILES = main.o
#OBJECT_FILES += ./src/mySource.o

INCLUDEPATHS =  -I .
INCLUDEPATHS += -I ./include
#INCLUDEPATHS += -I ./include/myFolder

CFLAGS = -ffunction-sections -fpermissive -std=c++11
LDFLAGS = -Wl,-gc-sections

COMPILE = avr-g++ $(CFLAGS) $(LDFLAGS) -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(INCLUDEPATHS)

# symbolic targets:
all: $(PROJECT_NAME).hex $(PROJECT_NAME).eep

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

flash:	$(PROJECT_NAME).hex
	$(AVRDUDE) -U flash:w:$(PROJECT_NAME).hex:i

fuse:
	$(AVRDUDE) $(FUSES)

erase:
	$(AVRDUDE) -e

reset:
	$(AVRDUDE)

eeprom:	$(PROJECT_NAME).eep
	$(AVRDUDE) -U eeprom:w:$(PROJECT_NAME).eep:i

read_eeprom:
	$(AVRDUDE) -U eeprom:r:$(PROJECT_NAME)_eeprom.bin:r

read_flash:
	$(AVRDUDE) -U flash:r:$(PROJECT_NAME).bin:r

install: flash flash_eeprom fuse

clean:
	rm -f $(PROJECT_NAME).hex $(PROJECT_NAME).eep $(PROJECT_NAME).elf $(OBJECT_FILES)

$(PROJECT_NAME).elf: $(OBJECT_FILES)
	$(COMPILE) -o $(PROJECT_NAME).elf $(OBJECT_FILES)

$(PROJECT_NAME).hex: $(PROJECT_NAME).elf
	rm -f $(PROJECT_NAME).hex
	avr-objcopy -j .text -j .data -O ihex $(PROJECT_NAME).elf $(PROJECT_NAME).hex
	
$(PROJECT_NAME).eep: $(PROJECT_NAME).elf
	avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex $(PROJECT_NAME).elf $(PROJECT_NAME).eep
	avr-size --format=avr --mcu=$(DEVICE) $(PROJECT_NAME).elf
	
disasm:	$(PROJECT_NAME).elf
	avr-objdump -d $(PROJECT_NAME).elf

cpp:
	$(COMPILE) -E main.c
