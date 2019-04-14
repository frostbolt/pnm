#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include <sstream>
#include <iostream>

struct Solution {
	size_t s_numThreads;
	double s_area;
	size_t s_steps;
	double s_error, s_duration;

	Solution(size_t num_threads, double area, size_t steps, double error, double duration)
		: s_numThreads(num_threads)
		, s_area(area)
		, s_steps(steps)
		, s_error(error)
		, s_duration(duration)
	{}

	inline double area() const { return s_area; }
	inline double error() const { return s_error; }
	inline double steps() const { return s_steps; }

	inline double duration() const { return s_duration; }

	inline std::string toString() const {
		std::stringstream ss;
		ss.precision(8);
    	std::cout.precision(8);
		ss.setf(std::cout.fixed);
		std::cout.setf(std::cout.fixed);

		ss << s_numThreads << "," << s_area << "," << s_steps << "," << s_error << "," << s_duration;
		return ss.str();
	}

	inline std::string toStringPretty() const {
		std::stringstream ss;
		ss.precision(8);
    	std::cout.precision(8);
		ss.setf(std::cout.fixed);
		std::cout.setf(std::cout.fixed);

		ss << "numThreads: " << s_numThreads << std::endl;
		ss << "area:       " << s_area << std::endl;
		ss << "steps:      " << s_steps << std::endl;
		ss << "error:      " << s_error << std::endl;
		ss << "duration:   " << s_duration << std::endl;
		return ss.str();
	}
};

#endif // __SOLUTION_H__