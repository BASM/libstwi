#CC=avr-gcc

LIBA=libstwi.a

OBJS_LIB=twi_sw.o
OBJS_TEST=main.o
OBJS_MODEL=twi_model.o

OBJS_LIB:=$(OBJS_LIB:%=obj/%)


OBJS+=$(OBJS_TEST)
OBJS+=$(OBJS_MODEL)

OBJS:=$(OBJS:%=obj/%)
OBJS+=$(OBJS_LIB)

DEFAULT=all

CFLAGS+=-Iinclude
CFLAGS+=-Imodel
CFLAGS+=-Wall -Werror -Wmissing-declarations -Wdeclaration-after-statement

all: dirs $(LIBA) dirs prgtest
	#./prgtest

$(LIBA): $(OBJS_LIB)
	ar rvs $@ $(OBJS_LIB)

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

obj/%.o: test/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

dirs:
	mkdir -p obj

prgtest: $(OBJS)
	echo $@ 
	$(CC) -o $@ $^

clean:
	rm -Rf obj prgtest $(LIBA)
############################
# MODEL

obj/%.o: model/%.c
	$(CC) -c $(CFLAGS) -o $@ $<


#all: dirs $(OBJS) main
	#gcc main.c

