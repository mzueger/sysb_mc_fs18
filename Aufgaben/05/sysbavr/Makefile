MCU = atmega16u4
F_OSC = 8000000
TARGET = libsysbavr
SRC = string.c button.c led.c usart.c pwm.c
OPT = s
CSTANDARD = -std=c99

# ---------------------------------------------------------------------------

CFLAGS = -O$(OPT)
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -Wall -Wstrict-prototypes
CFLAGS += -Wa,-adhlns=$(<:.c=.lst)
CFLAGS += $(CSTANDARD)
CFLAGS += -DF_OSC=$(F_OSC)

# ---------------------------------------------------------------------------

DIRAVR = /usr/lib/avr
DIRAVRBIN = $(DIRAVR)/bin
DIRAVRUTILS = $(DIRAVR)/bin
DIRINC = .
DIRLIB = $(DIRAVR)/lib

CC = avr-gcc
AR = avr-ar
REMOVE = rm -f
COPY = cp

# ---------------------------------------------------------------------------

OBJ = $(SRC:.c=.o)
LST = $(SRC:.c=.lst)

GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(GENDEPFLAGS)

# ---------------------------------------------------------------------------

# Default target.
build: lib

# Create static library
lib: $(TARGET).a

.SECONDARY : $(TARGET).a
.PRECIOUS : $(OBJ)
%.a: $(OBJ)
	$(AR) rcs $(TARGET).a $(OBJ)

# Compile: create object files from C source files.
%.o : %.c
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 

# Clean project.
clean:
	$(REMOVE) *.o *.a *.sym *.obj .dep/* *.lst

# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
	
# Listing of phony targets.
.PHONY : clean

