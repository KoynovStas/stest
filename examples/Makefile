CFLAGS   += -std=c99 -O2 -s  -Wall -Wextra -pedantic
CFLAGS   += -D__USE_MINGW_ANSI_STDIO=1
CFLAGS   += -I..

CC       ?= gcc



# list of tests for build
TESTS  = one_test    \
         many_tests  \
         one_case    \
         many_cases



.PHONY: all
all: clean $(TESTS)



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(TESTS)



.PHONY: $(TESTS)
$(TESTS):
	$(CC) $@.c -o $@  $(CFLAGS)
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
