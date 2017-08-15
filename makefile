scan: scan.o MyFile.o DictTree.o 
	g++  scan.o MyFile.o DictTree.o -o scan
scan.o: scan.cpp MyFile.h DictTree.h
	g++ -c scan.cpp
MyFile: MyFile.cpp MyFile.h
	g++ -c MyFile.cpp
DictTree: DictTree.cpp DictTree.h
	g++ -c DictTree.cpp

clean: 
	rm -rf *.o
