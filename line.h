#ifndef LINE_H
#define LINE_H

#include "dot.h"

class Line : public Dot {
public:

	Line();
	Line(Dot a, Dot b);

	const bool
		operator==(const Line &anotherLine) const,
		operator||(const Line &anotherLine) const;

	friend
		std::ostream& operator<<(std::ostream& ostream, const Line &line);

	double
		getCoefficient(int mode) const;

protected:

	bool
		isDotOnLine(const Dot &dot) const;
	Dot
		findCrossing(const Line &anotherLine) const;

	double A, B, C;

private:

	bool isExist;

};

#endif