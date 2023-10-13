SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

BIN := font-test

CXXFLAGS := $(shell pkg-config --cflags sfml-graphics) -Ientt/src -std=c++20
LDFLAGS := $(shell pkg-config --libs sfml-graphics) -lbox2d

ALL: $(BIN)
.PHONY: clean debug

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS)

debug: CXXFLAGS += -g -O0
debug: $(BIN)

clean:
	rm -f $(OBJ) $(BIN)
