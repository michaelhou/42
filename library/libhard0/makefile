.PHONY:arm
arm:
	gcc -c -O2 arm/arm.platform.c
.PHONY:x86
x86:
	gcc -c -O2 x86/x86.endian.c
	gcc -c -O2 x86/x86.fp.c
	gcc -c -O2 x86/x86.platform.c
	gcc -c -O2 x86/x86.port.c
clean:
	rm -f *.o *.a