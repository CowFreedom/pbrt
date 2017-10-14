#pragma once
#ifndef PBRT_CORE_ERROR_H
#define PBRT_CORE_ERROR_H

#include <pbrt.h>

namespace pbrt {
	
	template<class... Args>
	void Warning(std::string, Args...);

	template<class... Args>
	void Error(std::string, Args...);
}

#include <error.tpp>

#endif
