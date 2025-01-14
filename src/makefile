CCFLAGS=-std=gnu90 -I. -DDEBUG
CC=gcc

.PHONY: build
build : analyze
	@echo Build
%.o : %.c
	$(CC) $(CCFLAGS) -c -o $@ $<
	@echo MAKING $@

analyze : processP.o processQ.o common.o
	$(CC) $(CCFLAGS) -o $@ $@.c $^
	#$^ indica tutte le dipendenze, separate da spazio
	if [ ! -d "../bin" ]; then mkdir ../bin; fi
	mv analyze ../bin/
	@echo MAKING $@

.PHONY : clean
clean : 
	@echo Clean
	rm *.o