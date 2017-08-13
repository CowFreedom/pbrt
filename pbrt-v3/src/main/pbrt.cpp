/*
This code is inspired by "Physically Based Rendering: From Theory To Implementation"
by Matt Pharr, Greg Humphreys, and Wenzel Jakob. 


*/
#include <pbrt.h>
#include<iostream> //remove

template<class T, std::size_t N>
static void usage(const T(&msg)[N] = nullptr) {
	if (msg)
		fprintf(stderr, "pbrt: %s\n\n", msg);

	fprintf(stderr, R"(usage: pbrt [<options>] <filename.pbrt...>
		
		
		)");
}

int main(int agrc, char* argv[]){

	std::vector<std::string> filenames;
	char msg[] = "";
	usage(msg);
	std::cin.get(); //remove
}