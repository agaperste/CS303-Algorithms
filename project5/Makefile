CPP      = g++
CPPFLAGS = -c -g -Wall -pedantic -std=c++11

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -DWEAK="" -o $@ $<

# unifdef returns 1 if its output does not match its input; this is ok but make interprets
# this as an error.  the leading '-' tells make to ignore the nonzero return code.
%_stub.cpp: %.cpp
	-unifdef -DSTUB -o $@ $<

SRC = edge.cpp graph.cpp mst.cpp union_find.cpp 
H   = edge.hpp graph.hpp mst.hpp union_find.hpp

all: dependencies foo

dependencies: $(SRC) $(H)
	 rm -f dependencies
	 $(CC) $(CPPFLAGS) -MM $(SRC) >> dependencies

include dependencies

foo: main.o edge.o graph.o mst.o union_find.o 
ifeq ($(shell uname -s), Darwin)
	g++ -o foo -g -std=c++11 main.o edge.o graph.o mst.o union_find.o foo_macosx.a
else
	g++ -o foo -g -std=c++11 main.o edge.o graph.o mst.o union_find.o foo_linux.a
endif

foo_linux.a: $(SRC) $(H)
ifeq ($(shell uname -s), Darwin)
	echo "You're on a Mac, you dolt!"
else
	$(CPP) $(CPPFLAGS) -DWEAK="__attribute__ ((weak))" $(SRC)
	ar vr $@ edge.o graph.o mst.o union_find.o
	ranlib $@
	rm edge.o graph.o mst.o union_find.o
endif

foo_macosx.a: $(SRC) $(H)
ifeq ($(shell uname -s), Darwin)
	$(CPP) $(CPPFLAGS) -DWEAK="__attribute__ ((weak))" $(SRC)
	ar vr $@ edge.o graph.o mst.o union_find.o
	ranlib $@
	rm edge.o graph.o mst.o union_find.o
else
	echo "You're on a Linux system, you dolt!"
endif

stubs: graph_stub.cpp mst_stub.cpp union_find_stub.cpp

clean: 
	rm main.o edge.o graph.o mst.o union_find.o