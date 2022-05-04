#@copyright : Omar
CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3 -mthumb -gdwarf-2
INCS= -I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
project_name = learn-in-depth_cortex-m3

all: $(project_name).bin
	@echo "<<=====================Build is Done=====================>>"


%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@
#startup.o: startup.s
#	$(CC)as.exe  $(CFLAGS) $< -o $@
$(project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linkerscript.ld $(LIBS) $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
$(project_name).bin: $(project_name).elf 
	$(CC)objcopy.exe -O binary $< $@
clean_all:
	rm *.o *.elf *.bin
clean:
	rm  *.elf *.bin