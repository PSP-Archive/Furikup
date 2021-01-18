TARGET = vidsend
OBJS = rtpvidsend.o

INCDIR = /usr/local/pspdev/psp/include ../../include
CFLAGS = -O2 -G0 -g -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lortp -lpspusb -lpsputility -lpspusbcam

BUILD_PRX = 1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = eRTP sample application

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
