#ifndef DOT_H
#define DOT_H

#include <ostream>

class Dot 
{
public:
	
	Dot();
	Dot(double X, double Y);
	
	const bool
		operator==(const Dot &anotherDot) const,
		operator!=(const Dot &anotherDot) const,
		operator<=(const Dot &anotherDot) const,
		operator>=(const Dot &anotherDot) const,
		operator<(const Dot &anotherDot) const,
		operator>(const Dot &anotherDot) const;
	Dot
		operator+(const Dot &anotherDot) const,
		operator-(const Dot &anotherDot) const;

	friend
		double getSquareNormBetweenTwoDots(const Dot &dot, const Dot &anotherDot);
	friend
		std::ostream& operator <<(std::ostream& ostream, const Dot &dot);

	void
		setCoordinates(int mode, double number),
		setNonExistent();
	double
		getCoordinates(int mode) const;

private:

	void
		setCoordinates(double x, double y);

	double X, Y;
	bool isExist;

};

#endif