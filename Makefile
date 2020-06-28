main: main.cpp
	g++ $< -o $@

run:
	./main

.PHONY: run
