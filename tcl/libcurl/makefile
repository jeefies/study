CC = gcc
CFLAGS = `curl-config --cflags --libs`
SRC = ./src
INC = ./include

all: $(SRC)/main.c buffer.o scurl.o
	$(CC) $^ -o curl $(CFLAGS) -I$(INC)

tcl-share: buffer.o scurl.o $(SRC)/tcl-apis.c
	$(CC) -shared $(SRC)/tcl-apis.c buffer.o scurl.o -o libScurl.so \
		-I$(INC) $(CFLAGS)
	echo "pkg_mkIndex . *.so" > mkIndex.tcl
	tclsh mkIndex.tcl
	rm mkIndex.tcl

scurl.o: $(SRC)/scurl.c $(INC)/scurl.h
	$(CC) -c $(SRC)/scurl.c -I$(INC) -o $@ -fPIC

buffer.o: $(SRC)/buffer.c $(INC)/buffer.h
	$(CC) -c $(SRC)/buffer.c -I$(INC) -o $@

clean:
	rm -rf *.o *.so \
		*.html \
		curl
