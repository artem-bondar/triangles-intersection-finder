#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "segment.h"

class Triangle : Segment {
public:

	Triangle();
	Triangle(Dot a, Dot b, Dot c);

	friend
		std::ostream& operator <<(std::ostream& ostream, const Triangle &triangle);

	bool
		checkExistence() const,
		checkIntersectionWith(const Triangle &anotherTriangle) const;

private:

	bool
		checkTriangleInequality(const double a, const double b, const double c) const,
		checkSegmentsIntersectionWith(const Triangle &anotherTriangle) const,
		checkIfOneOfSegmentsIsStretchedIn(const Triangle &anotherTriangle) const,
		checkIfIn(const Triangle &anotherTriangle) const;

	Dot A, B, C;
	Segment AB, BC, AC;
	bool isExist;

};

#endif