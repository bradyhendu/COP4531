# Define variables
CXX := g++

# Define the targets
TARGETS := merge insertion

# Rule for all targets
all: $(TARGETS)

# Rule to build 'merge'
merge: merge.cpp generatearrays.cpp
	$(CXX)  .\merge.cpp .\generatearrays.cpp -o merge

# Rule to build 'insertion'
insertion: insertion.cpp generatearrays.cpp
	$(CXX) .\insertion.cpp .\generatearrays.cpp -o insertion

run: $(TARGETS)
	.\merge
	.\insertion

# Clean up object files and executables
clean:
	rm -f $(TARGETS)

# PHONY targets to avoid conflicts with files named 'all' or 'clean'
.PHONY: all clean
