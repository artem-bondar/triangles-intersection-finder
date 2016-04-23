#include "triangle.h"
#include "text.h"
#include <iostream>

Triangle::Triangle() {
	isExist = false;
}

Triangle::Triangle(Dot a, Dot b, Dot c) {
	if (checkTriangleInequality(getSquareNormBetweenTwoDots(a,b), getSquareNormBetweenTwoDots(b,c), getSquareNormBetweenTwoDots(a,c)))
	{
		isExist = true;
		AB = Segment(a, b);
		BC = Segment(b, c);
		AC = Segment(a, c);
		A = a;
		B = b;
		C = c;
	}
	else
		isExist = false;
}

std::ostream& operator <<(std::ostream& ostream, const Triangle &triangle) {
	if (triangle.isExist)
		ostream << text.geometry[8] << triangle.A << text.geometry[7] << triangle.B << text.geometry[7] << triangle.C << text.geometry[9];
	else
		ostream << text.geometry[0] << text.geometry[4];
	return ostream;
}

bool Triangle::checkExistence() const {
	return isExist;
}

bool Triangle::checkTriangleInequality(const double a, const double b, const double c) const {
	return a < (b + c) && b < (a + c) && c < (a + b);
}

bool Triangle::checkSegmentsIntersectionWith(const Triangle &anotherTriangle) const {
	return AB.isCrossedBy(anotherTriangle.AB) || AB.isCrossedBy(anotherTriangle.BC) || AB.isCrossedBy(anotherTriangle.AC) ||
		   BC.isCrossedBy(anotherTriangle.AB) || BC.isCrossedBy(anotherTriangle.BC) || BC.isCrossedBy(anotherTriangle.AC) ||
		   AC.isCrossedBy(anotherTriangle.AB) || AC.isCrossedBy(anotherTriangle.BC) || AC.isCrossedBy(anotherTriangle.AC);
}

bool Triangle::checkIfOneOfSegmentsIsStretchedIn(const Triangle &anotherTriangle) const {
	Segment segments[3] = { AB, BC, AC };
	Segment anotherTriangleSegments[3] = { anotherTriangle.AB, anotherTriangle.BC, anotherTriangle.AC };
	Dot anotherTriangleDots[3] = { anotherTriangle.A, anotherTriangle.B, anotherTriangle.C };
	for (Segment i : segments)
	{
		int end = 0, start = 0;
		for (int j = 0; j < 3; j++)
		{
			if (anotherTriangleSegments[j].isDotOnSegment(i.getStart()))
				start = j++;
			if (anotherTriangleSegments[j].isDotOnSegment(i.getEnd()))
				end = j++;
			if (end && start && end == start)
				end = start = 0;
		}
		if (end && start)
			return true;
	}
	return false;
}

bool Triangle::checkIfIn(const Triangle &anotherTriangle) const {
	Dot triangleDots[3] = { A, B, C };
	Dot anotherTriangleDots[3] = { anotherTriangle.A, anotherTriangle.B, anotherTriangle.C };
	Segment anotherTriangleSegments[3] = { anotherTriangle.AB, anotherTriangle.BC, anotherTriangle.AC };
	for (Dot i : triangleDots)
	{
		for (Dot j : anotherTriangleDots)
		{
			if (i == j) break;
			Segment segment(i, j);
			for (Segment k : anotherTriangleSegments)
			{
				Dot dot = segment.getCrossingWith(k);
				if ((!segment.isIn(anotherTriangle.AB) && !segment.isIn(anotherTriangle.BC) && !segment.isIn(anotherTriangle.AC)) &&
				    (!anotherTriangle.AB.isDotOnSegment(dot) && !anotherTriangle.BC.isDotOnSegment(dot) && !anotherTriangle.AC.isDotOnSegment(dot)))
					return false;
			}
		}
	}
	return true;
}

bool Triangle::checkIntersectionWith(const Triangle &anotherTriangle) const {
	return checkSegmentsIntersectionWith(anotherTriangle) || checkIfIn(anotherTriangle) || anotherTriangle.checkIfIn(*this) ||
		   checkIfOneOfSegmentsIsStretchedIn(anotherTriangle) || anotherTriangle.checkIfOneOfSegmentsIsStretchedIn(*this);
}