# File: Make file (bare.mk)
# Date: 13/06/25

# Tools
CC 		= gcc
OBJDUMP = objdump


# Compiler and Linker Flags
CFLAGS = -ggdb -Wall -Wextra

# Source Files
src = hello.c
OBJ = $(src:.c=.o)

# Final exe name
OUT = Final

all: $(OUT).exe $(OUT).i $(OUT).s $(OUT).lst

$(OUT).exe: $(OBJ)
	$(CC) $(OBJ) -o $@ $(CFLAGS)

$(OBJ): $(src)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT).i: $(src)
	$(CC) -E $< -o $@

$(OUT).s: $(src)
	$(CC) -S $< -o $@

$(OUT).lst: $(OBJ)
	$(OBJDUMP) -dS $< > $@

clean:
	rm -rf $(OUT).exe $(OUT).s $(OUT).lst $(OUT).i $(OBJ)

# Use command: " make -f bare.mk "