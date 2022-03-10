CXXFLAGS = -Wall -O2 -lstdc++fs
MAGICKFLAGS = `Magick++-config --cxxflags --cppflags --ldflags --libs`

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

patterns: $(OBJ)
	$(CXX) $(CXXFLAGS) $(MAGICKFLAGS) $(OBJ) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(MAGICKFLAGS) -c $< -o $@

mandelbrot.o: mandelbrot.cpp mandelbrot.h
	$(CXX) $(CXXFLAGS) $(MAGICKFLAGS) -c $< -o $@

img.o: img.cpp img.h
	$(CXX) $(CXXFLAGS) $(MAGICKFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -vf $(OBJ)
