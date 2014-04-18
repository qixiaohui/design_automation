parprog: tc_rev4.cpp
	g++ -O3 -march=native -Wall -o parprog tc_rev4.cpp
clean:
	rm -f $(binaries) *.out
