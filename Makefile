CXXFLAGS = -Wall -O2
MAGICKFLAGS = `Magick++-config --cxxflags --cppflags --ldflags --libs`
LDFLAGS = -lstdc++fs

SRC_DIR := src
OBJ_DIR := obj
EXE := patterns
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(MAGICKFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(MAGICKFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rvf $(EXE) $(OBJ_DIR)
