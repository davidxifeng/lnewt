INC = -Isrc

ifdef LUAPATH
	INC += -I$(LUAPATH)
endif

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	INC += -I/usr/local/include
	NEWT_LIB = -L/usr/local/lib -lnewt
	SHARED_LIB = -dynamiclib -Wl,-undefined,dynamic_lookup
else
	NEWT_LIB = -lnewt
	SHARED_LIB = -shared
endif

CFLAGS = -fPIC -O3 -Wall -std=c99 -pedantic
CFLAGS += $(INC)

NEWT_SO = newt.so

all: $(NEWT_SO)

$(NEWT_SO): src/luanewt.c src/luanewt.h
	$(CC) $(SHARED_LIB) -o $@ $(CFLAGS) $< $(NEWT_LIB)

clean:
	$(RM) $(NEWT_SO)

test:
	./test/test1.lua

.PHONY: all clean test
