EXE = treefun
TEST = test

MAIN_FILE = main.cpp
TEST_FILE = test.cpp

OBJS_DIR = .objs

OBJS_STUDENT = main.o
OBJS_TEST = test.o
OBJS_PROVIDED = coloredout.o

CXX = clang++
LD = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++14 -g -O0 $(WARNINGS) -MMD -MP -c
LDFLAGS = -std=c++14 -lpthread

all: $(EXE) $(TEST)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... unfortunately, we can't use a pattern for the normal executables
$(EXE):
	$(LD) $^ $(LDFLAGS) -o $@

$(TEST):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_STUDENT)) $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_PROVIDED))

$(TEST):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(OBJS_TEST))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	rm -rf $(EXE) $(TEST) $(OBJS_DIR)

tidy: clean
	rm -rf doc

.PHONY: all tidy clean