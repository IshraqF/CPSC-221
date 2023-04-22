EXE = maze
EXETESTSQ = testStackQueue
EXETESTMAZE = testMaze

OBJS_DIR = .objs

OBJS_MAZE = main.o DrawMaze.o HexBoard.o HexBoard_given.o HexCell.o
OBJS_TESTSQ = testStackQueue.o catch_config.o
OBJS_TESTMAZE = testMaze.o DrawMaze.o HexBoard.o HexBoard_given.o HexCell.o catch_config.o
OBJS_PROVIDED = PNG.o RGBAPixel.o lodepng.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++14 -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++14 -lpthread

# Rules
all: $(EXE) $(EXETESTSQ) $(EXETESTMAZE)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Pattern rules for cs221util
$(OBJS_DIR)/%.o: cs221util/%.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJS_DIR)/%.o: cs221util/lodepng/%.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR) $(OUT_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXETESTSQ):
	$(LD) $^ $(LDFLAGS) -o $@
$(EXETESTMAZE):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(EXE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_MAZE)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))
$(EXETESTSQ): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TESTSQ))
$(EXETESTMAZE): $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TESTMAZE)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE) $(EXETESTSQ) $(EXETESTMAZE) $(OBJS_DIR)

.PHONY: all clean
