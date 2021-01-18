TARGET = AudioFreq
OBJS = main.o sceAudio_driver371.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

LIBS = -lpspaudio_driver

USE_KERNEL_LIBC = 1
USE_KERNEL_LIBS = 1

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

