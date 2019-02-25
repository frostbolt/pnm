class Solution
{

public:
	Solution(double S, double t)
		: s_area(S)
		, s_duration(t)
	{}

	inline double area() const { return s_area; }

	inline double duration() const { return s_duration; }

private:
	double s_area, s_duration;
};