#ifndef SEGMENT_H
#define SEGMENT_H

#include "line.h"

class Segment : protected Line {
public:

	Segment();
	Segment(Dot a, Dot b);

	friend
		std::ostream& operator <<(std::ostream& ostream, const Segment &segment);

	bool
		isDotOnSegment(const Dot &dot) const,
		isCrossedBy(const Segment &anotherSegment) const,
		isTouchedBy(const Segment &anotherSegment) const,
		isIn(const Segment &anotherSegment) const;
	Dot
		getStart() const,
		getEnd() const,
		getCrossingWith(const Segment &anotherSegment) const;

private:

	bool
		isDotInSegment(const Dot &dot) const;

	Dot start, end;
	bool isExist;

};

#endif