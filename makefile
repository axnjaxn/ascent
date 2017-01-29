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

color.o: color.h color.cpp
	$(CXX) color.cpp -c $(CFLAGS) $(CXXFLAGS)

poly.o: color.h poly.h poly.cpp
	$(CXX) poly.cpp -c $(CFLAGS) $(CXXFLAGS)

random.o: random.h random.cpp
	$(CXX) random.cpp -c $(CFLAGS) $(CXXFLAGS)

genome.o: color.h poly.h random.h genome.h genome.cpp
	$(CXX) genome.cpp -c $(CFLAGS) $(CXXFLAGS)

population.o: color.h poly.h random.h genome.h population.h population.cpp
	$(CXX) population.cpp -c $(CFLAGS) $(CXXFLAGS)

main.o: color.h poly.h random.h genome.h population.h main.cpp
	$(CXX) main.cpp -c $(CFLAGS) $(CXXFLAGS)

$(APP): color.o poly.o random.o genome.o population.o main.o
	$(CXX) color.o poly.o random.o genome.o population.o main.o -o $@ $(LDFLAGS) $(LIBS)

run: debug test.jpg
	./$(APP) test.jpg

clean:
	rm -f *~ *.o $(APP) Thumbs.db
