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
queue: main.o queue.o
	$(CC) $(COPTFLAGS) -o $@ $^

# Mergesort driver
list: main2.o list.o
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ queue list

# eof
