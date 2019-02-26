#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <sstream>

struct Solution {
	size_t s_numThreads;
	double s_area, s_error, s_duration;

	Solution(size_t num_threads, double area, double error, double duration)
		: s_numThreads(num_threads)
		, s_area(area)
		, s_error(error)
		, s_duration(duration)
	{}

	inline double area() const { return s_area; }

	inline double duration() const { return s_duration; }

	inline std::string toString() const {
		std:: stringstream ss;
		ss << s_numThreads << "," << s_area << "," << s_error << "," << s_duration << std::endl;
		return ss.str();
	}
};

#endif // __SOLUTION_H__