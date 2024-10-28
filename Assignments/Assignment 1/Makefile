# Define variables
CXX := g++

# Define the targets
TARGETS := merge bucket quicksort heapsort radix counting insertion

# Rule for all targets
all: $(TARGETS)

# Rule to build 'merge'
merge: merge.cpp generatearrays.cpp
	$(CXX)  .\merge.cpp .\generatearrays.cpp -o merge

# Rule to build 'insertion'
insertion: insertion.cpp generatearrays.cpp
	$(CXX) .\insertion.cpp .\generatearrays.cpp -o insertion

#rule to build 'bucket'
bucket: bucket.cpp generatearrays.cpp
	$(CXX) .\bucket.cpp .\generatearrays.cpp -o bucket

#rule to build 'quicksort'
quicksort: quicksort.cpp generatearrays.cpp
	$(CXX) .\quicksort.cpp .\generatearrays.cpp -o quicksort

#rule to build 'heapsort'
heapsort: heapsort.cpp generatearrays.cpp
	$(CXX) .\heapsort.cpp .\generatearrays.cpp -o heapsort

#rule to build 'radix'
radix: radix.cpp generatearrays.cpp
	$(CXX) .\radix.cpp .\generatearrays.cpp -o radix

#rule to build 'counting'
counting: counting.cpp generatearrays.cpp
	$(CXX) .\counting.cpp .\generatearrays.cpp -o counting

run: $(TARGETS)
	.\merge
	.\bucket
	.\quicksort
	.\heapsort
	.\radix
	.\counting
	.\insertion

# Clean up object files and executables
clean:
	del -f merge.exe bucket.exe quicksort.exe heapsort.exe radix.exe counting.exe insertion.exe

# PHONY targets to avoid conflicts with files named 'all' or 'clean'
.PHONY: all clean
