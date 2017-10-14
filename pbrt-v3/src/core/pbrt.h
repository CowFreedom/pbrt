/*
This code is inspired by "Physically Based Rendering: From Theory To Implementation"
by Matt Pharr, Greg Humphreys, and Wenzel Jakob.


*/

#pragma once
#ifndef PBRT_CORE_PBRT_H
#define PBRT_CORE_PBRT_H
#endif//PBRT_CORE_PBRT_H

#include <type_traits>
#include <algorithm>
#include <cinttypes>
#include <iostream> //um cout und cerr zu nutzen
#include<string>
#include<vector>
#include <memory>
#include <array>
#include "spdlog/spdlog.h" //Unser Logger
#include <ostream> //für unseren Logger-Wrapper

#include <iostream>
#include <sstream>

namespace pbrt {

	// Global Forward Declarations 
	class Scene;
	class Integrator;
	class SamplerIntegrator;


#ifdef PBRT_FLOAT_AS_DOUBLE
	using Float = double;
#else
	using Float = float;
#endif //PBRT_FLOAT_AS_DOUBLE

	//constants
	constexpr Float Pi = 3.141592653589793238462;
	constexpr Float InvPi = 0.318309886183790671537;
	constexpr Float Inv2Pi = 0.159154943091895335768;
	constexpr Float Inv4Pi = 0.079577471545947667884;
	constexpr Float PiOver2 = 1.570796326794896619231;
	constexpr Float PiOver4 = 0.7853981633974483096155;
	constexpr Float Sqrt2 = 1.414213562373095048801;

	/*Wrapper für den Logger*/
	constexpr int INFO = 0;
	constexpr int WARNING = 1;
	constexpr int CRITICAL = 2;

	//classes

	struct Options {
		size_t nThreads = 0;
		bool quickRender = false;
		bool quiet = false;
		bool cat = false;
		bool toPly = false;
		std::string imgeFile;

	};

	extern Options PbrtOptions;
	//global helper functions
	template<class T>
	inline T Mod(T a, T b) {
		T result = a - ((a / b)*b);
		return static_cast<T>((result >= 0) ? result : result + b);
	}

	inline Float Mod(Float a, Float b) {
		Float result = std::fmod(a, b);
		return static_cast<Float>((result >= 0) ? result : result + b);
	}

	template<class T>
	inline T Radians(T deg) {
		return deg*(Pi / 180);
	}

	template<class T>
	inline T Degrees(T rad) {
		return rad*(180 * (InvPi));
	}

	inline double Log2(double x) {
		return std::log2(x);
	}

	inline float Log2(float x) {
		return std::log2f(x); //evt. log2f
	}

	//Siehe Tutorial über enable_if: https://oopscenities.net/2012/06/02/c11-enable_if/
	//Akzeptiert nur integrale typen (aber auch char (was ein short int ist))
	template<class T>
	inline typename std::enable_if<std::is_integral<T>::value, T>::type Log2Int(T x) {
		unsigned long index;
		_BitScanReverse64(&index, x); //VCC Befehl
		return static_cast<T>(index); //GCC hat __builtin_clz 
	}

	template<class T>
	inline typename std::enable_if<std::is_integral<T>::value, bool>::type isPowerOf2(T x) {
		return x && !(x & (x - 1));
	}

	template<class T>
	inline uint32_t RoundUpPow2(uint32_t x) {
		x--;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		return x + 1;
	}

	template<class T>
	inline uint64_t RoundUpPow2(uint64_t x) {
		x--;
		x |= x >> 1;
		x |= x >> 2;
		x |= x >> 4;
		x |= x >> 8;
		x |= x >> 16;
		x |= x >> 32;
		return x + 1;
	}

	template<class T>
	inline typename std::enable_if<std::is_integral<T>::value, T>::type CountTrailingZeros(T x) {
		unsigned long index;
		_BitScanForward(&index, x);
		return index;
	}

	template<class T, class U, class V>
	inline T Clamp(T val, U low, V high) {
		if (val < low)
			return low;
		else if (val > high)
			return high;
		else
			return val;
	}

	template <class Predicate>
	size_t FindInterval(size_t size, const Predicate &pred) {
		int first = 0;
		len = size;

		while (len > 0) {
			int half = len / 2;
			int middle = first + half;

			if (pred(middle)) {
				first = middle + 1;
				len -= half + 1;
			}
			else
				len = half;
		}
		return Clamp(first - 1, 0, size - 2);
	}



	/*
	class Logger : public std::ostream {
	private:
		class LogBuf : public std::stringbuf {
		private:
			// or whatever you need for your application
			std::vector<spdlog::sink_ptr> sinks;
			std::shared_ptr<spdlog::logger> combined_logger;
			std::string m_marker;
		public:
			LogBuf(const std::string& marker) : m_marker(marker) { }
			

			~LogBuf() { pubsync(); }
			int sync() {
				std::cout << m_marker << ": " << str();
				str("");
				return std::cout ? 0 : -1;
			}

		};

	public:
		// Other constructors could specify filename, etc
		// just remember to pass whatever you need to CLogBuf
		Logger(const std::string& marker) : std::ostream(new LogBuf(marker)) {}

		~Logger() { delete rdbuf(); }
	};
	*/

	class Logger : public std::ostream {
	private:

		std::vector<spdlog::sink_ptr> sinks;
		std::shared_ptr<spdlog::logger> combined_logger;
		int log_state = 0;
		enum class warning_levels { INFO=0, WARNING=1,CRITICAL=2 };


		class LogBuf : public std::stringbuf {
		private:
			// or whatever you need for your application
			std::shared_ptr<spdlog::logger> logvector;
			int buf_state;

		public:
			LogBuf(std::shared_ptr<spdlog::logger> loggers, const int& log_state) : buf_state(log_state), logvector(loggers) {
				std::cout << "Neuer Buffer erstellt!\n";
			}


			~LogBuf() { pubsync(); std::cout << "Buffer gelöscht!\n"; }
			int sync() {
				switch (buf_state) {
				case 0: {

					logvector->info(str());
					logvector->flush();
					break;
				}

				case 1: {
					logvector->warn(str());
					logvector->flush();
					break;
				}
				case 2: {
					logvector->critical(str());
					logvector->flush();
					break;
					}
				}
				str("");
				return std::cout ? 0 : -1;
			}

		};

		std::array<std::unique_ptr<LogBuf>, 3> buffers; //noch initialisieren!

	public:
		// Other constructors could specify filename, etc
		// just remember to pass whatever you need to CLogBuf
		Logger(const std::string& marker): std::ostream(new LogBuf(combined_logger, log_state)) {

			try {
				sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
				sinks.push_back(std::make_shared<spdlog::sinks::simple_file_sink_mt>("src/logs/log_"+marker, 3)); //Pfad, relativ zum Projektverzeichnis
				combined_logger = std::make_shared<spdlog::logger>(marker, std::begin(sinks), std::end(sinks));
				spdlog::register_logger(combined_logger);
				//(*this).set_rdbuf(new LogBuf(combined_logger, log_state));
				//std::unique_ptr<LogBuf> a1(new LogBuf(combined_logger, 0));
				//std::unique_ptr<LogBuf> a2(new LogBuf(combined_logger, 1));
				//std::unique_ptr<LogBuf> a3(new LogBuf(combined_logger, 2));
				buffers[INFO] = std::make_unique<LogBuf>(combined_logger, INFO);
				buffers[WARNING] = std::make_unique<LogBuf>(combined_logger, WARNING);
				buffers[CRITICAL] = std::make_unique<LogBuf>(combined_logger, CRITICAL);

			}
			catch (const spdlog::spdlog_ex& ex)
			{
				std::cout << "Log init failed: " << ex.what() << std::endl;
			}
		
		
		}

		~Logger() { delete rdbuf(); spdlog::drop_all(); std::cout << "Logger zerstört!\n"; }

		auto& operator() (int level) {
			log_state = level;
			//(*this).set_rdbuf(new LogBuf(combined_logger, log_state));
			//std::cout << "TypeiD:" << typeid(buffers[level]._Myptr()).name();
			(*this).set_rdbuf((buffers[level]._Myptr())); //Myptr Konversion notwendig, da unique_ptr nicht akzeptiert wird

			//(*this).rdbuf()->pubsetbuf(0, 0); //um Buffern zu vermeiden
			(*this).flush();
			return *this;
		}
	};

	Logger LOG("PBRT");
}