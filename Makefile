

OBJS_TEST=main.o
OBJS_MODEL=twi_model.o


OBJS=twi_sw.o 
OBJS+=$(OBJS_TEST)
OBJS+=$(OBJS_MODEL)

OBJS:=$(OBJS:%=obj/%)

DEFAULT=all

CFLAGS+=-Iinclude
CFLAGS+=-Imodel
CFLAGS+=-Wall -Werror -Wmissing-declarations -Wdeclaration-after-statement

all: dirs prgtest
	./prgtest


obj/%.o: src/%.c
	gcc -c $(CFLAGS) -o $@ $<

obj/%.o: test/%.c
	gcc -c $(CFLAGS) -o $@ $<

dirs:
	mkdir -p obj

prgtest: $(OBJS)
	echo $@ 
	gcc -o $@ $^

clean:
	rm -Rf obj prgtest
############################
# MODEL

obj/%.o: model/%.c
	gcc -c $(CFLAGS) -o $@ $<


#all: dirs $(OBJS) main
	#gcc main.c

