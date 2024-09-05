.PHONY: all run clean

all: _build/main.exe

_build/main.exe: ./source/main.cpp ./source/GraphMinHeap.h
	mkdir -p _build
	g++ -o _build/main.exe ./source/main.cpp

run:
	_build/main.exe

clean:
	rm -rf _build
