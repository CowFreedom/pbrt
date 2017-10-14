#pragma once

#ifndef PBRT_CORE_PROGRESS_REPORTER_H
#define PBRT_CORE_PROGRESS_REPORTER_H

#include <pbrt.h>
#include<atomic>
#include<chrono>
#include<thread>

namespace pbrt {

	class ProgressReporter {
	public:
		ProgressReporter() = delete;
		ProgressReporter(int64_t totalWork, const std::string&& title);

		void Update(int64_t num = 1);

		int64_t ElapsedMS() const;

		void Done();
		
		~ProgressReporter();

	private:
		void PrintBar();

		const int64_t totalWork;
		const std::string title;
		const std::chrono::system_clock::time_point startTime;
		std::atomic<int64_t> workDone=0;
		std::atomic<bool> exitThread=false;
		std::thread updateThread;
	};

}

#endif