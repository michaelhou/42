library?=../../library
res?=../../res
all:
	make -s -C $(library)/libboot0 wincmd
	make -s -C $(library)/libboot1 mingw
	make -s -C $(library)/libhard0 winx64
	make -s -C $(library)/libhard1 mingw
	make -s -C $(library)/libsoft0 win
	make -s -C $(library)/libsoft1 mingw
	make -s -C $(library)/libui0 winapi
	make -s -C $(library)/libui1 mingw
	make -s -C $(library)/visitor gui
	gcc -mwindows \
	$(library)/libboot0/*.o \
	$(library)/libboot1/*.o \
	$(library)/libhard0/*.o \
	$(library)/libhard1/*.o \
	$(library)/libsoft0/*.o \
	$(library)/libsoft1/*.o \
	$(library)/libui0/*.o \
	$(library)/libui1/*.o \
	$(library)/visitor/*.o \
	-lgdi32
static:
	make -s -C $(library)/libboot0 wincmd
	make -s -C $(library)/libboot1 mingw
	make -s -C $(library)/libhard0 winx64
	make -s -C $(library)/libhard1 mingw
	make -s -C $(library)/libsoft0 win
	make -s -C $(library)/libsoft1 mingw
	make -s -C $(library)/libui0 winapi
	make -s -C $(library)/libui1 mingw
	ar crs library.a \
	$(library)/libboot0/*.o \
	$(library)/libboot1/*.o \
	$(library)/libhard0/*.o \
	$(library)/libhard1/*.o \
	$(library)/libsoft0/*.o \
	$(library)/libsoft1/*.o \
	$(library)/libui0/*.o \
	$(library)/libui1/*.o
shared:
	make -s -C $(library)/libboot0 wincmd
	make -s -C $(library)/libboot1 mingw
	make -s -C $(library)/libhard0 winx64
	make -s -C $(library)/libhard1 mingw
	make -s -C $(library)/libsoft0 win
	make -s -C $(library)/libsoft1 mingw
	make -s -C $(library)/libui0 winapi
	make -s -C $(library)/libui1 mingw
	make -s -C $(library)/visitor winshared
	gcc -shared -o library.dll \
	$(library)/libboot0/*.o \
	$(library)/libboot1/*.o \
	$(library)/libhard0/*.o \
	$(library)/libhard1/*.o \
	$(library)/libsoft0/*.o \
	$(library)/libsoft1/*.o \
	$(library)/libui0/*.o \
	$(library)/libui1/*.o \
	$(library)/visitor/temple.*.o -lgdi32
clean:
	rm -f *.o
