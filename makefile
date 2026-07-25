run: main.c stdmine.c stdmine.h hashtable.c hashtable.h circularlist.c circularlist.h tries.c tries.h
	clang -o run main.c stdmine.c hashtable.c circularlist.c tries.c

clean:
	rm -f run
