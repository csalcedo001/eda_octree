CXX = g++
CXXFLAGS = -std=c++17 -L/opt/X11/lib -I /opt/X11/include -I include -o $@ -lX11
TARGET = bin/main
DIRS = bin build

SRCFILES = $(shell find src -type f -name '*.cpp')
APPFILES = $(shell find app -type f -name '*.cpp')


OBJFILES = $(patsubst src/%.cpp, build/%.o, $(SRCFILES))
BINFILES = $(patsubst app/%.cpp, bin/%, $(APPFILES))

.PRECIOUS: $(OBJFILES)

all: $(BINFILES)

bin/%: app/%.cpp $(OBJFILES)
	mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) $^

build/%.o: src/%.cpp include/%.hpp
	mkdir -p "$(@D)"
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(DIRS)
