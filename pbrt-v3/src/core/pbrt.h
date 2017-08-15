/*
This code is inspired by "Physically Based Rendering: From Theory To Implementation"
by Matt Pharr, Greg Humphreys, and Wenzel Jakob. 


*/

#include <type_traits>
#include <algorithm>
#include <cinttypes>
#include <iostream> //um cout und cerr zu nutzen
#include<string>
#include<vector>
#include <memory>
#include <array>



namespace pbrt {

	struct Options {
		size_t nThreads = 0;
		bool quickRender =  false;
		bool quiet = false;
		bool cat = false;
		bool toPly = false;
		std::string imgeFile;

	};

//forward declarations

}