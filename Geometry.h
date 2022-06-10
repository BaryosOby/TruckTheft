#include <iostream>
#include <iomanip>


using namespace std;
// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);
double to_normal_directions(double theta_d);
// class declarations
typedef struct Point {
	double x;
	double y;
	Point(double x, double y);
	Point();
	void print() const;
	void setCord(double x0, double y0){
	    x = x0;
	    y = y0;
	}
	bool operator==(const Point& rhs) const;
} Point;

double distance(const Point& a, const Point& b);

struct Polar_vector;
typedef struct Cartesian_vector {
	Cartesian_vector(const struct Polar_vector & pv);
	Cartesian_vector();
	void operator=(const struct Polar_vector & pv);
	double delta_x;
	double delta_y;
} Cartesian_vector;
typedef struct Polar_vector {
	Polar_vector(const Cartesian_vector & cv);
	Polar_vector();
	void operator=(const Cartesian_vector & cv);
	double r;
	double theta;
} Polar_vector;