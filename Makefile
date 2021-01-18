PSP=/cygdrive/f/
TARGET_DIR=$(PSP)/psp/game/Furikup

info:
	echo "First make and install the libs, if you haven't already."
	echo "Do this with:  make libs"
	echo "Then make the application:  make engine ui."

libs:
	bash ./config_libs.sh
	make -C libosip2-3.0.3-2/src SUBDIRS="osipparser2 osip2" install
	make -C libosip2-3.0.3-2/include install
	make -C libeXosip2-3.0.3-3/src install
	make -C ortp-0.13.1/src SUBDIRS=. install
	make -C ortp-0.13.1/include SUBDIRS=. install

engine:
	make -C SIPEngine

ui:
	make -C SIPTextGUI

audio:
	make -C AudioFreq
	
install:
	cp SIPTextGUI/EBOOT.PBP $(TARGET_DIR)/
	cp SIPEngine/SIPEngine.prx $(TARGET_DIR)/
	cp AudioFreq/AudioFreq.prx $(TARGET_DIR)/
	eject $(PSP)

all:  engine ui audio install

clean:
	make -C SIPEngine clean
	make -C SIPTextGUI clean
	make -C AudioFreq clean

release:  engine ui audio
	rm -rf release
	mkdir release
	mkdir -p release/MS_ROOT/psp/game/Furikup
	cp SIPTextGUI/EBOOT.PBP release/MS_ROOT/psp/game/Furikup/
	cp SIPEngine/SIPEngine.prx release/MS_ROOT/psp/game/Furikup/
	cp AudioFreq/AudioFreq.prx release/MS_ROOT/psp/game/Furikup/
	cp release_materials/* release/MS_ROOT/psp/game/Furikup/
	cp docs/* release/
	svn export . release/src
#	find release -name \*~ -print0 | xargs -0 /bin/rm
	find release -name .svn -print0 | xargs -0 /bin/rm -rf
