
OBJS=main.o twi_sw.o

OBJS:=$(OBJS:%=obj/%)

DEFAULT=all

CFLAGS+=-Iinclude

all: prgtest
	echo "OK"

obj/%.o: src/%.c
	gcc -c $(CFLAGS) -o $@ $<

obj/%.o: test/%.c
	gcc -c $(CFLAGS) -o $@ $<

dirs:
	mkdir -p obj

prgtest: $(OBJS)
	echo $@ 
	gcc -o $@ $^

#all: dirs $(OBJS) main
	#gcc main.c

