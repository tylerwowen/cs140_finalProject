CC=gcc
CILK=cilk++
AR=ar
TESTFILE= /scratch/6.884/kkt_power.bin
RUNTESTS= $(CURDIR)/runtests.pl
PROCS=8
LDFLAGS= -L$(CURDIR)
LIBS = -lmiser -lcilkutil 


CFLAGS = -Wall -Werror
ifeq ($(DEBUG),1)
CFLAGS := -DDEBUG -g -O0 $(CFLAGS)
else
CFLAGS := -O3 $(CFLAGS)
endif
CILKFLAGS= $(CFLAGS)


.PHONY: clean runtest

TARGETS = bag_test bfs_driver libtrivial.a

# Add variants of the bag implementation to this list.
BAG_VARIANTS = bag_list bag_parallel bag_opt
BAG_FILES = $(BAG_VARIANTS:%=%.cpp)


all: $(TARGETS)


bag_test : bag_test.cilk bag.h $(BAG_FILES)
	$(CILK) $(CILKFLAGS) $@.cilk $(LDFLAGS) $(LIBS) -o $@

bfs_driver : bfs_driver.cilk graph.cilk graph.h libtrivial.a
	$(CILK) $(CILKFLAGS) $@.cilk $(LDFLAGS) $(LIBS) -ltrivial -o $@

libtrivial.a : trivial.o
	$(AR) rcs $@ trivial.o

.o:
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f *.o $(TARGETS) *.plt *.out *.csv

runtest : bfs_driver $(TESTFILE)
	$(CURDIR)/bfs_driver 5 $(TESTFILE) -cilk_set_worker_count=$(PROCS)

