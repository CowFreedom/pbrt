#include <ProgressReporter.h>

namespace pbrt {

	ProgressReporter::ProgressReporter(int64_t totalWork, const std::string&& title):
		totalWork(std::max(static_cast<int64_t>(1), totalWork)),
		title(title),
		startTime(std::chrono::system_clock::now()){

		//Launch thread to periodically update progress bar
	}

	void ProgressReporter::Update(int64_t num = 1) {
		if (num == 0 || PbrtOptions.quiet)
			workDone += num;
	}

	int64_t ProgressReporter::ElapsedMS() const {
		std::chrono::system_clock::time_point now = 
			std::chrono::system_clock::now();
		int64_t elapsedMS =
			std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();

		return elapsedMS;
	}

}