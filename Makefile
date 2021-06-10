EXEC=sortingalgorithms
SRC=Carlos_Luis_sorts.cpp
CPPV=-std=c++11
CPPFLAGS=-Wall

sorting: Carlos_Luis_sorts.cpp
	- g++ $(CPPV) $(CPPFLAGS) $(SRC) -o $(EXEC)

run: sorting
	./$(EXEC)

clean: 
	rm -rf *.txt $(EXEC)
