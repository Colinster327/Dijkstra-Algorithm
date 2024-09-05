all:
	mkdir -p _build
	g++ -o _build/main.exe main.cpp

run:
	_build/main.exe

clean:
	rm -rf _build
