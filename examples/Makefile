CFLAGS   += -O2  -s  -Wall
CFLAGS   += -D__USE_MINGW_ANSI_STDIO=1  #-DWITHOUT_COLOR_COLOR
CFLAGS   += -I..

GCC       = gcc



# list of tests for build
TESTS  = one_test    \
         many_tests



.PHONY: all
all: clean $(TESTS)



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(TESTS)



.PHONY: $(TESTS)
$(TESTS):
	$(GCC) $@.c -o $@  $(CFLAGS)
	@echo "  ---- Compiled $@ ----"
	-@ ./$@



.PHONY: debug
debug: CFLAGS  += -DDEBUG
debug: all



.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   debug   -  build in debug mode (#define DEBUG 1)"
	@echo "   help    -  This help"
