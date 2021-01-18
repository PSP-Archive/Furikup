TARGET = Furikup
OBJS = text_gui.o SIPEngine.o

PSP_EBOOT_ICON = pspphone.png

PSP_EBOOT_TITLE = Furikup v0.1.$(shell svnversion)

INCDIR = /usr/local/pspdev/psp/include
CFLAGS = -O2 -G0 -g -Wall -DBUILDVERSION=\"$(shell svnversion)\"
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DBUILDVERSION=\"$(shell svnversion)\"
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -lpspaudio -lpspgu

BUILD_PRX = 1

EXTRA_TARGETS = EBOOT.PBP

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
