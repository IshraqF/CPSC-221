CXX = clang++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++14 -g -Og $(WARNINGS) -MMD -MP -c
LD = clang++
LDFLAGS = -std=c++14 -lpthread

OBJS_DIR = .objs

CC_EXE = charcount
CC_OBJS = hashes.o textfile.o charcount.o

WC_EXE = wordcount
WC_OBJS = hashes.o textfile.o wordcount.o

ANAGRAM_EXE = anagramtest
ANAGRAM_OBJS = hashes.o textfile.o anagramtest.o

TEST_EXE = test
TEST_OBJS = hashes.o textfile.o test.o

all: nonasan
nonasan: $(CC_EXE) $(WC_EXE) $(ANAGRAM_EXE) $(TEST_EXE)

# Pattern rules for object files
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Rules for executables... we can use a pattern for the -asan versions, but, unfortunately, we can't use a pattern for the normal executables
$(CC_EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(WC_EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(ANAGRAM_EXE):
	$(LD) $^ $(LDFLAGS) -o $@
$(TEST_EXE):
	$(LD) $^ $(LDFLAGS) -o $@

# Executable dependencies
$(CC_EXE):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(CC_OBJS))
$(WC_EXE):           $(patsubst %.o, $(OBJS_DIR)/%.o,      $(WC_OBJS))
$(ANAGRAM_EXE):      $(patsubst %.o, $(OBJS_DIR)/%.o,      $(ANAGRAM_OBJS))
$(TEST_EXE):         $(patsubst %.o, $(OBJS_DIR)/%.o,      $(TEST_OBJS))

# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d

clean:
	-rm -rf doc *.o $(CC_EXE) $(WC_EXE) $(ANAGRAM_EXE) $(TEST_EXE) $(OBJS_DIR)

tidy:
	-rm -f anagrams.txt

.PHONY: all doc clean tidy nonasan asan
