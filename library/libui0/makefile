.PHONY:linuxcli
linuxcli:
	rm -f fb.*.o xlib.*.o winapi.*.o sdl.*.o
	gcc -c -fPIC -O2 cli/cli.cli.c
	gcc -c -fPIC -O2 window.c
.PHONY:maccli
maccli:
	rm -f fb.*.o xlib.*.o winapi.*.o sdl.*.o
	gcc -c -fPIC -O2 cli/cli.cli.c
	gcc -c -fPIC -O2 window.c
.PHONY:wincli
wincli:
	rm -f fb.*.o xlib.*.o winapi.*.o sdl.*.o
	gcc -c -O2 cli/cli.cli.c
	gcc -c -O2 window.c

.PHONY:linuxsdl
linuxsdl:
	rm -f cli.*.o fb.*.o xlib.*.o winapi.*.o
	clang -c -O2 sdl/sdl.c -I /usr/local/Cellar/sdl2/2.0.3/include
	gcc -c -O2 window.c
.PHONY:macsdl
macsdl:
	rm -f cli.*.o fb.*.o xlib.*.o winapi.*.o
	clang -c -O2 sdl/sdl.c -I /usr/local/Cellar/sdl2/2.0.3/include
	gcc -c -O2 window.c
.PHONY:winsdl
winsdl:
	rm -f cli.*.o fb.*.o xlib.*.o winapi.*.o
	gcc -c -O2 sdl2/sdl.c -I /opt/SDL2-2.0.3/x86_64-w64-mingw32/include
	gcc -c -O2 window.c

.PHONY:cocoa
cocoa:
	rm -f cli.*.o xlib.*.o winapi.*.o sdl.*.o
	clang -c -fPIC -O2 cocoa/cocoa.cocoa.c
	clang -c -fPIC -O2 window.c
.PHONY:fb
fb:
	rm -f cli.*.o xlib.*.o winapi.*.o sdl.*.o
	gcc -c -fPIC -O2 fb/fb.fb.c
	gcc -c -fPIC -O2 window.c
.PHONY:wayland
wayland:
	rm -f cli.*.o xlib.*.o winapi.*.o sdl.*.o
	gcc -c -fPIC -O2 wayland/wayland.wayland.c
	gcc -c -fPIC -O2 window.c
.PHONY:winapi
winapi:
	rm -f cli.*.o fb.*.o xlib.*.o sdl.*.o
	gcc -c -O2 winapi/winapi.winapi.c
	gcc -c -O2 window.c
.PHONY:xlib
xlib:
	rm -f cli.*.o fb.*.o winapi.*.o sdl.*.o
	gcc -c -fPIC -O2 xlib/xlib.xlib.c
	gcc -c -fPIC -O2 window.c

clean:
	rm -f *.o *.a
