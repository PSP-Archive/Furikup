TARGET = SIPEngine
OBJS = sipengine.o config.o config_file.o codec.o call_api.o video.o audio.o sound_conv.o sound_resample.o presence.o addressbook.o sceUsbMic.o exports.o

INCDIR = /usr/local/pspdev/psp/include
CFLAGS = -O2 -G0 -g -Wall -Werror -fno-pic -DBUILDVERSION=\"$(shell svnversion)\"
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -DBUILDVERSION=\"$(shell svnversion)\"
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =
LIBS = -leXosip2 -losipparser2 -losip2 -lortp -lpsprtc -lpspaudio -lpspusb -lpspusbcam

PRX_EXPORTS = exports.exp

BUILD_PRX = 1

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

