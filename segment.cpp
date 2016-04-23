#include "segment.h"
#include "text.h"
#include "implements.h"

Segment::Segment() {
	isExist = false;
}

Segment::Segment(Dot a, Dot b) {
	Line line(a, b);
	if (a != b)
	{
		isExist = true;
		A = line.getCoefficient(Ax);
		B = line.getCoefficient(By);
		C = line.getCoefficient(C0);
		if (a.getCoordinates(x) < b.getCoordinates(x) || (a.getCoordinates(x) == b.getCoordinates(x) && a.getCoordinates(y) < b.getCoordinates(y)))
		{
			start = a;
			end = b;
		}
		else
		{
			start = b;
			end = a;
		}
	}
	else
		isExist = false;
}

ostream& operator<<(ostream& ostream, const Segment &segment) {
	if (segment.isExist)
	{
		Line line(segment.start, segment.end);
		ostream << line << text.geometry[10] << segment.start << text.geometry[12] << segment.end << text.geometry[11];
	}
	else
		ostream << text.geometry[0] << text.geometry[3];
	return ostream;
}

bool Segment::isDotInSegment(const Dot &dot) const {
	return isDotOnLine(dot) && ((dot > start && dot < end && start < end) ||
								(dot < (start + end) && dot > (start - end) && (start - end) < (start + end)));
}

bool Segment::isDotOnSegment(const Dot &dot) const {
	return dot == start || dot == end || isDotInSegment(dot);
}

Dot Segment::getCrossingWith(const Segment & anotherSegment) const
{
	Dot crossing = findCrossing(anotherSegment);
	return crossing;
}

Dot Segment::getEnd() const
{
	return end;
}

Dot Segment::getStart() const
{
	return start;
}

bool Segment::isCrossedBy(const Segment &anotherSegment) const {
	Dot crossing = getCrossingWith(anotherSegment);
	return isDotInSegment(crossing) && anotherSegment.isDotInSegment(crossing);
}

bool Segment::isTouchedBy(const Segment &anotherSegment) const {
	Dot crossing = getCrossingWith(anotherSegment);
	return (crossing == start || crossing == end) && anotherSegment.isDotOnSegment(crossing) ||
		   (crossing == anotherSegment.start || crossing == anotherSegment.end) && isDotOnSegment(crossing);
}
bool Segment::isIn(const Segment &anotherSegment) const {
	return *this == anotherSegment && ((anotherSegment.start <= start && end <= anotherSegment.end && start < end) ||
									  ((anotherSegment.start - anotherSegment.end) <= (start - end) &&
									   (start + end) <= (anotherSegment.start + anotherSegment.end) &&
									   (start - end) < (start + end)));
}