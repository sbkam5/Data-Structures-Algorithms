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

# Hashtable program 
hashtable: main.o hashtable.o
	$(CC) $(COPTFLAGS) -o $@ $^

# MST program
mst: main2.o mst.o
	$(CC) $(COPTFLAGS) -o $@ $^

# MST program for dense graph
mst2: main3.o mst.o
	$(CC) $(COPTFLAGS) -o $@ $^

extra_credit: main4.o hashtable2.o
	$(CC) $(COPTFLAGS) -o $@ $^

shit: dijktra.o
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ queue list

# eof
