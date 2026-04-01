#NIGGAAAAAAAAAAAAAA
PATH_DKP := C:/devkitPro
PREFIX  := $(PATH_DKP)/devkitPPC/bin/powerpc-eabi-
CC      := $(PREFIX)gcc
CXX     := $(PREFIX)g++
LD      := $(PREFIX)g++
OBJCOPY := $(PREFIX)objcopy

LIBOGC_INC := $(PATH_DKP)/libogc/include
LIBOGC_LIB := $(PATH_DKP)/libogc/lib/wii

TARGET  := boot
MACHDEP := -mrvl -mcpu=750 -meabi -mhard-float
INCLUDES:= -I$(LIBOGC_INC)
LIBS    := -L$(LIBOGC_LIB) -lwiiuse -lbte -logc -lm

CXXFLAGS := $(MACHDEP) -O2 -Wall $(INCLUDES)
LDFLAGS  := $(MACHDEP) -Wl,-Map,$(TARGET).map

all: $(TARGET).dol

$(TARGET).dol: $(TARGET).elf
	$(PATH_DKP)/tools/bin/elf2dol $< $@

$(TARGET).elf: main.o
	$(LD) $(LDFLAGS) main.o $(LIBS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm -f *.o *.elf *.dol *.map