CXX=g++
CXXFLAGS=-pthread -std=c++11 -m64 -g -I./include -L/usr/lib/CAEN -I/usr/include/CAEN -Wall
LDFLAGS=-m64
LDLIBS=-pthread -lm -ldl -rdynamic -lCAENVME
SRCDIR=./src
SOURCES=$(SRCDIR)/sethv.cpp $(SRCDIR)/V6521N.cpp $(SRCDIR)/V6521P.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sethv

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS) 
	cp -f sethv ~/bin/

.cc.o:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) -W -Wall -c $<

clean:
	rm -f ./*~ $(OBJECTS) ./sethv



