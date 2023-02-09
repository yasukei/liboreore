#pragma once

#include <chrono>

class Clock {
public:
	Clock() :
		ref_(std::chrono::steady_clock::now())
	{
		//setlocale(LC_NUMERIC,"ja_JP.utf8");
	}

	void reset() {
		ref_ = std::chrono::steady_clock::now();
	}

	std::uint64_t getElapsedTimeMillisec() const {
		return getElapsedTime<std::chrono::milliseconds>();
	}
	std::uint64_t getElapsedTimeMicrosec() const {
		return getElapsedTime<std::chrono::microseconds>();
	}
	std::uint64_t getElapsedTimeNanosec() const {
		return getElapsedTime<std::chrono::nanoseconds>();
	}

private:
	std::chrono::steady_clock::time_point ref_;

	template<typename T>
	std::uint64_t getElapsedTime() const {
		using namespace std::chrono;
		T elapsed = duration_cast<T>(steady_clock::now() - ref_);
		return elapsed.count();
	}
};


