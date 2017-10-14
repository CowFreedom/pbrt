//#include <error.h>
#include <mutex>
namespace pbrt {

	template<class T>
	std::unique_ptr<T> errorFactory() {
		return new T;
	}

	static std::string StringVaCout(std::string arg) {
		return arg;
	}

	template<class... Args>
	static std::string StringVaCout(std::string format, Args... args) {
		return format + StringVaCout(args...);
	}
	
	template<class... Args>
	static void ProcessError(std::string format, std::string errortype, Args... args) {
		std::string errorString;
		//std::string errortype = "Warnig";
		
		//Print line and position in input file, if available
		
		extern int line_num;
		/*
		if (line_num != 0) {
			extern std::string current_file;
			errorString += current_file;
			errorString += line_num+": ";
		}
		Obiges unbedingt hinzufügen sobald die externals definiert sind.
		*/

		errorString +=StringVaCout(format, args...);
	
		//Print the error message no more than once
		static std::string lastError;
		static std::mutex mutex;
		std::lock_guard<std::mutex> guard(mutex);

		if (errorString != lastError) {
			if (errortype == "Warning") 
				LOG(WARNING) << errorString;			
			else
				LOG(CRITICAL) << errorString;
		}

	}

	template<class ...Args>
	void Warning(std::string format, Args... args) {
		ProcessError(format, "Warning", args...);
	}

	template<class... Args>
	void Error(std::string format, Args... args) {
		ProcessError(format,"Error", args...);
	}


}