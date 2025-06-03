CC = g++
CFLAGS = --std=c++20 -Wall -Werror -pedantic -g

# Dependencies and program file creations
BIN = bin

DEP_GL = include/win64_gl/glad/glad.h include/win64_gl/GLFW/glfw3.h include/win64_gl/GLFW/glfw3native.h
DEP = include/market.hpp include/event.hpp include/lots.hpp include/player.hpp include/char.hpp include/core.hpp $(DEP_GL)
CHAR_C = src/char/marisa.cpp src/char/reimu.cpp src/char.cpp
MARK_C = src/markets/wriggle.cpp src/market.cpp
MAIN_C = src/event.cpp src/lots.cpp src/player.cpp src/core.cpp
GL_C = src/.gl/glad.c
ALL_C = $(CHAR_C) $(MARK_C) $(MAIN_C) $(GL_C)

CHAR_OBJ = $(BIN)/char.o $(BIN)/marisa.o $(BIN)/reimu.o
MARK_OBJ = $(BIN)/market.o $(BIN)/wriggle.o 
MAIN_OBJ = $(BIN)/event.o $(BIN)/lots.o $(BIN)/player.o $(BIN)/core.o $(BIN)/main.o
OBJ = $(CHAR_OBJ) $(MARK_OBJ) $(MAIN_OBJ) $(BIN)/glad.o

LIB = -lgdi32
LIB_A = 

LIB_F = lib

STATIC_LIB = $(LIB_F)/Touhou_RM.a
DYNAMIC_LIB_W = $(LIB_F)/Touhou_RM_Win.dll
PROG = Touhou_RM
PROGWIN = Touhou_RM_Win.exe

# /Program Use/

.PHONY: unix win unixr winr

unix: $(PROG)

win: $(PROGWIN)

unixr: $(PROG)
	./$(PROG)

winr: $(PROGWIN)
	exec $(PROGWIN)


# /Object Compilation/

$(BIN):
	mkdir -p bin

# For compiling all characters
$(BIN)/%.o: src/char/%.cpp include/char.hpp | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

# For compiling all markets
$(BIN)/%.o: src/markets/%.cpp include/market.hpp | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

# For compiling the core features
$(BIN)/%.o: src/%.cpp $(DEP) | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

# For GLAD
$(BIN)/glad.o: src/.gl/glad.c include/win64_gl/glad/glad.h | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

# For compiling the main
$(BIN)/main.o: main.cpp include/core.hpp $(DEP_GL) | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@


# /Static Library Compilation/

$(LIB_F):
	mkdir -p lib

# For the static library (linux)
$(STATIC_LIB): | $(LIB_F)
	ar rcs $(STATIC_LIB) $@ $^ $(OBJ)

# For the static library (windows)
$(DYNAMIC_LIB_W): $(ALL_C) | $(LIB_F)
	g++ -fpic -shared $(DEP) -o $@ $^


# //////Program Compilation/

# For the program creation (linux)
$(PROG): $(OBJ) $(STATIC_LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

# For the program creation (windows)
$(PROGWIN): $(OBJ) $(DYNAMIC_LIB_W) lib/libglfw3dll.a glfw3.dll
	$(CC) $(CFLAGS) -o $@ $^ -I $(LIB_A) -L../ $(LIB)

# For cleaning
clean:
	rm -rf $(BIN) $(PROG) $(PROGWIN) $(STATIC_LIB) $(DYNAMIC_LIB_W)

# For linting
lint:
	cpplint src/*.cpp src/*.hpp src/char/*.cpp src/markets/*.cpp
