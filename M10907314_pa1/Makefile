cc = g++
prom = bin/MR
LDFLAGS = -std=c++11
deps = src/*.h
source = src/*.cpp

$(prom): $(source)
	$(cc) $(LDFLAGS) $(deps) $(source) -o $(prom)
 
 clean:
	rm -rf *.o $(prom)
