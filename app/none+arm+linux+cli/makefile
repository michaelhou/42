library?=../../library
all:
	make -s -C $(library)/libboot0 none
	make -s -C $(library)/libboot1 gcc
	make -s -C $(library)/libhard0 arm
	make -s -C $(library)/libhard1 gcc
	make -s -C $(library)/libsoft0 linux
	make -s -C $(library)/libsoft1 gcc
	make -s -C $(library)/libui0 cli
	make -s -C $(library)/libui1 gcc
	make -s -C $(library)/visitor cli
	gcc -o a.out \
	$(library)/libboot0/*.o \
	$(library)/libboot1/*.o \
	$(library)/libhard0/*.o \
	$(library)/libhard1/*.o \
	$(library)/libsoft0/*.o \
	$(library)/libsoft1/*.o \
	$(library)/libui0/*.o \
	$(library)/libui1/*.o \
	$(library)/visitor/*.o \
	-lm
static:
	make -s -C $(library)/libboot0 none
	make -s -C $(library)/libboot1 gcc
	make -s -C $(library)/libhard0 arm
	make -s -C $(library)/libhard1 gcc
	make -s -C $(library)/libsoft0 linux
	make -s -C $(library)/libsoft1 gcc
	make -s -C $(library)/libui0 cli
	make -s -C $(library)/libui1 gcc
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
clean:
	rm -f *.o
