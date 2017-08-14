/*
This code is inspired by "Physically Based Rendering: From Theory To Implementation"
by Matt Pharr, Greg Humphreys, and Wenzel Jakob. 


*/
#include <pbrt.h>
#include<iostream> //remove

using pbrt::Options;

template<class T, std::size_t N>
static void usage(const T(&msg)[N] = nullptr) {
	if (msg)
		std::cerr << "pbrt: " << msg << "\n\n";

	std::cerr << R"(usage: pbrt[<options>] <filename.pbrt...>
Rendering options:
   --help                  Print this help text.
   --nthreads <num>        Use specified number of threads for rendering.
   --outfile <filename>    Write the final image to the given filename.

Logging options:
   --logdir <dir>          Specify directory that log files should be written to.
                           Default: system temp directory (e.g. $TMPDIR or /tmp).
   --logtostderr           Print all logging messages to stderr.
   --minloglevel <num>     Log messages at or above this level (0 -> INFO,
                           1 -> WARNING, 2 -> ERROR, 3-> FATAL). Default: 0
   --v <verbosity>         Set VLOG verbosity.

Reformatting options:
   --cat                   Print a reformatted version of the input file(s) to
                           standard output. Does not render an image.
   --toply                 Print a reformatted version of the input file(s) to
                           standard output and convert all triangle meshes to 
                           PLY files. Does not render an image.

)";	
		
	//std::cout << msg;
}


int main(int agrc, char* argv[]){
	Options options;

	std::array<std::string, agrc> commandLine;

	for (size_t i = 0; i < agrc; i++) {
		std::cout << argv[i] << "\t HAHA"<<"\n";
	}

	std::ios::sync_with_stdio(false);
	std::vector<std::string> filenames;
	char msg[] = "msg";
	//usage("Hey");
	std::cin.get(); //remove
}