CC = g++
CFLAGS =
COPTFLAGS = -O0 -g
LDFLAGS =

default:
	@echo "=================================================="
	@echo "To build your sorting code, use:"
	@echo "  make insertion-sort    # For Insertion sort"
	@echo "  make mergesort    	 # For Mergesort"
	@echo ""
	@echo "To clean this subdirectory (remove object files"
	@echo "and other junk), use:"
	@echo "  make clean"
	@echo "=================================================="

# Insertion sort driver

distance0: main0.o dist2.o list.o
	$(CC) $(COPTFLAGS) -o $@ $^

distance: main.o dist.o list.o
	$(CC) $(COPTFLAGS) -o $@ $^

distance2: main2.o dist.o list.o
	$(CC) $(COPTFLAGS) -o $@ $^

distance3: main3.o dist.o list.o
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ queue list

# eof
