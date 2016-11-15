all: test client server

%: %.cc
	g++ -std=c++11 $< -w -o $@

%: %.c
	gcc $< -w -o $@

