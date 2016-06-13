CFLAGS = -fPIC -O3 -Wall -std=c99 -pedantic
CFLAGS += $(INC)

INC = -Isrc

ifdef LUAPATH
	INC += -I$(LUAPATH)
endif

LFLAGS = -shared

NEWT_SRC = src/luanewt.c src/luanewt.h
NEWT_SO = newt.so
NEWT_LIB = -lnewt


all: $(NEWT_SO)

$(NEWT_SO): $(NEWT_SRC)
	$(CC) $(LFLAGS) -o $@ $(CFLAGS) $< $(NEWT_LIB)

clean:
	$(RM) $(NEWT_SO)

test:
	./test/test1.lua

.PHONY: all clean test
