target: main

output = cppcounter
ofile = src/file_tree.o src/file_node.o src/file_utils.o

CC = g++
CFLAGS = 
main: src/main.cc src/file_tree.cc src/file_node.cc src/file_utils.cc
	$(CC) $(CFLAGS) -o cppcounter \
		src/main.cc \
		src/file_tree.cc \
		src/file_utils.cc \
		src/file_node.cc

clean:
	rm -rf $(output) $(ofile) 
