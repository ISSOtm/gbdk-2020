# gbcompress makefile

ifndef TARGETDIR
TARGETDIR = /opt/gbdk
endif

ifeq ($(OS),Windows_NT)
	BUILD_OS := Windows_NT
else
	BUILD_OS := $(shell uname -s)
endif

# Target older macOS version than whatever build OS is for better compatibility
ifeq ($(BUILD_OS),Darwin)
	export MACOSX_DEPLOYMENT_TARGET=10.10
endif

CC = $(TOOLSPREFIX)gcc
CFLAGS = -ggdb -O -Wno-incompatible-pointer-types -DGBDKLIBDIR=\"$(TARGETDIR)\"
OBJ = main.o gbcompress.o rlecompress.o files.o files_c_source.o
BIN = gbcompress

all: $(BIN)

$(BIN): $(OBJ)

clean:
	rm -f *.o $(BIN) *~
	rm -f tmp.*
	rm -f *.exe

# round trip the executable through compression and de-compression as a brief test
test:
	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress -v tmp.in tmp.cmp; ./gbcompress -v -d tmp.cmp tmp.dcmp; diff -s tmp.in tmp.dcmp
	rm -f tmp.cmp.c; rm -f tmp.dcmp.c; 	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress -v --cout --varname=some_array tmp.in tmp.cmp.c; ./gbcompress -v -d --cin tmp.cmp.c tmp.dcmp; diff -s tmp.in tmp.dcmp
	rm tmp.*
	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress --alg=rle -v tmp.in tmp.cmp; ./gbcompress  --alg=rle -v -d tmp.cmp tmp.dcmp; diff -s tmp.in tmp.dcmp
	rm -f tmp.cmp.c; rm -f tmp.dcmp.c; 	rm -f tmp.cmp; rm -f tmp.dcmp
	cp $(BIN) tmp.in; ./gbcompress  --alg=rle -v --cout --varname=some_array tmp.in tmp.cmp.c; ./gbcompress --alg=rle -v -d --cin tmp.cmp.c tmp.dcmp; diff -s tmp.in tmp.dcmp
	rm tmp.*
