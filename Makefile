CC=g++-9
CFLAGS=-Wall --std=c++17

build: utilities.so compare_dirs.o
	$(CC) $(CFLAGS) -o compare_dirs compare_dirs.o -lutilities -L. -Wl,-rpath=$(PWD)

utilities.so:
	$(CC) $(CFLAGS) -fPIC -c utilities.cpp -o utilities.o
	$(CC) $(CFLAGS) -shared utilities.o -o libutilities.so

compare_dirs.o:
	$(CC) $(CFLAGS) -c compare_dirs.cpp -o $@

clean:
	rm -rf *.o *.so compare_dirs a_only b_only common

write-all: clean build
	./compare_dirs test/$@/dir_a test/$@/dir_b
	diff a_only test/$@/answers/a_only
	diff b_only test/$@/answers/b_only
	diff common test/$@/answers/common

write-a-only-and-common: clean build
	./compare_dirs test/$@/dir_a test/$@/dir_b
	diff a_only test/$@/answers/a_only
	diff b_only test/$@/answers/b_only
	diff common test/$@/answers/common

write-b-only-and-common: clean build
	./compare_dirs test/$@/dir_a test/$@/dir_b
	diff a_only test/$@/answers/a_only
	diff b_only test/$@/answers/b_only
	diff common test/$@/answers/common

write-common-only: clean build
	./compare_dirs test/$@/dir_a test/$@/dir_b
	diff a_only test/$@/answers/a_only
	diff b_only test/$@/answers/b_only
	diff common test/$@/answers/common

test: clean build write-all write-a-only-and-common write-b-only-and-common write-common-only

run: build
	./compare_dirs test/write-all/dir_a test/write-all/dir_b
