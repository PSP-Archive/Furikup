#!/bin/bash

cd libosip2-3.0.3-2
CPPFLAGS="-I$(psp-config --pspsdk-path)/include -G0" \
LDFLAGS="-L$(psp-config --psp-prefix)/lib -L$(psp-config --pspsdk-path)/lib" \
LIBS="-lc -lpspnet_inet -lpspnet_resolver -lpspuser" \
bash ./configure --host=psp --disable-tools --disable-shared \
--prefix=$(psp-config --psp-prefix)

cd ../libeXosip2-3.0.3-3
CPPFLAGS="-I$(psp-config --pspsdk-path)/include -G0" \
LDFLAGS="-L$(psp-config --psp-prefix)/lib -L$(psp-config --pspsdk-path)/lib" \
LIBS="-lc -lpspnet_inet -lpspnet_resolver -lpspuser" \
bash ./configure --host=psp --disable-shared --prefix=$(psp-config --psp-prefix)

cd ../ortp-0.13.1
CPPFLAGS="-I$(psp-config --pspsdk-path)/include -G0" \
LDFLAGS="-L$(psp-config --pspsdk-path)/lib -lc -lpspnet_inet -lpspnet_resolver \
-lpspuser" \
bash ./configure --enable-ipv6=no --enable-strict=no --host psp --prefix=$(psp-config --psp-prefix)

