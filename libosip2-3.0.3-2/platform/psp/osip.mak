TARGET = libosip2
OBJS = main.o exports.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall -fshort-wchar -fno-pic -mno-check-zero-division
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PRX_EXPORTS = exports.exp

LIBDIR =
LIBS = -losip2 -losipparser2

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

LIBS += -lpspnet_inet
