APPNAME = ascent

LIBS = `sdl2-config --libs` -lSDL2_gfx `byteimage-config --libs`
CFLAGS = -Wno-unused-result `byteimage-config --cflags`
CXXFLAGS = -std=c++11
EXT =

APP = $(APPNAME)$(EXT)

all: debug

debug: CFLAGS += -g -DDEBUG
debug: $(APP)

release: CFLAGS += -O2
release: $(APP)

gray.o: gray.h gray.cpp
	$(CXX) gray.cpp -c $(CFLAGS) $(CXXFLAGS)

color.o: gray.h color.h color.cpp
	$(CXX) color.cpp -c $(CFLAGS) $(CXXFLAGS)

poly.o: gray.h color.h poly.h poly.cpp
	$(CXX) poly.cpp -c $(CFLAGS) $(CXXFLAGS)

genome.o: gray.h color.h poly.h genome.h genome.cpp
	$(CXX) genome.cpp -c $(CFLAGS) $(CXXFLAGS)

population.o: gray.h color.h poly.h genome.h population.h population.cpp
	$(CXX) population.cpp -c $(CFLAGS) $(CXXFLAGS)

main.o: gray.h color.h poly.h genome.h population.h main.cpp
	$(CXX) main.cpp -c $(CFLAGS) $(CXXFLAGS)

$(APP): gray.o color.o poly.o genome.o population.o main.o
	$(CXX) gray.o color.o poly.o genome.o population.o main.o -o $@ $(LDFLAGS) $(LIBS)

run: debug test.jpg
	./$(APP) test.jpg

clean:
	rm -f *~ *.o $(APP) Thumbs.db
