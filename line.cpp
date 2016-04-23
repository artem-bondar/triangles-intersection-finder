#include "line.h"
#include "text.h"
#include "implements.h"

Line::Line() {
	isExist = false;
}

Line::Line(Dot a, Dot b) {
	if (a != b)
	{
		isExist = true;
		if (a.getCoordinates(x) != b.getCoordinates(x))
			A = roundToFive(b.getCoordinates(y) - a.getCoordinates(y));
		else {
			A = 1;
			B = 0;
			C = -a.getCoordinates(x);
		}
		if (a.getCoordinates(y) != b.getCoordinates(y))
			B = roundToFive(a.getCoordinates(x) - b.getCoordinates(x));
		else {
			A = 0;
			B = 1;
			C = -a.getCoordinates(y);
		}
		if (A && B)
			C = -roundToFive(a.getCoordinates(y)*B + a.getCoordinates(x)*A);
	}
	else
		isExist = false;
}

const bool Line::operator==(const Line &anotherLine) const {
	return roundToFive(A * anotherLine.B) == roundToFive(B * anotherLine.A) && roundToFive(B * anotherLine.C) == roundToFive(C * anotherLine.B);
}

const bool Line::operator||(const Line &anotherLine) const {
	return roundToFive(A * anotherLine.B) == roundToFive(B * anotherLine.A) && roundToFive(B * anotherLine.C) != roundToFive(C * anotherLine.B);;
}

ostream& operator<<(ostream& ostream, const Line &line) {
	if (line.isExist)
	{
		if (line.A)
		{
			if (line.A > 0)
			{
				if (line.A != 1)
					ostream << line.A;
				ostream << text.geometry[15];
			}
			if (line.A < 0)
			{
				ostream << text.geometry[12];
				if (line.A != -1)
					ostream << -line.A;
				ostream << text.geometry[15];
			}
		}
		if (line.B)
		{
			if (line.B > 0)
			{
				if (line.A)
					ostream << text.geometry[14];
				if (line.B != 1)
					ostream << line.B;
				ostream << text.geometry[16];
			}
			if (line.B < 0)
			{
				ostream << text.geometry[13];
				if (line.B != -1)
					ostream << -line.B;
				ostream << text.geometry[16];
			}
		}
		if (line.C)
		{
			if (line.C > 0)
				ostream << text.geometry[14] << line.C;
			else
				ostream << text.geometry[13] << -line.C;
		}
		ostream << text.geometry[17];
	}
	else ostream << text.geometry[0] << text.geometry[2];
	return ostream;
}

Dot Line::findCrossing(const Line &anotherLine) const {
	Dot crossing;
	if ((*this || anotherLine) || (*this == anotherLine)) crossing.setNonExistent();
	else {
		if (A && B && anotherLine.A && anotherLine.B)
		{
			crossing.setCoordinates(y, roundToFive((anotherLine.A*C - A*anotherLine.C) / (A*anotherLine.B - anotherLine.A*B)));
			crossing.setCoordinates(x, roundToFive(-(crossing.getCoordinates(y)*B + C) / A));
		}
		else
		{
			if (!A)
			{
				crossing.setCoordinates(y, roundToFive(-C / B));
				if (!anotherLine.B)
					crossing.setCoordinates(x, roundToFive(-anotherLine.C / anotherLine.A));
				else
					crossing.setCoordinates(x, roundToFive((anotherLine.B*C / B - anotherLine.C) / anotherLine.A));
			}
			if (!B)
			{
				crossing.setCoordinates(x, roundToFive(-C / A));
				if (!anotherLine.A)
					crossing.setCoordinates(y, roundToFive(-anotherLine.C / anotherLine.B));
				else
					crossing.setCoordinates(y, roundToFive((anotherLine.A*C / A - anotherLine.C) / anotherLine.B));
			}
			if (A && B)
			{
				if (!anotherLine.A)
				{
					crossing.setCoordinates(y, roundToFive(-anotherLine.C / anotherLine.B));
					crossing.setCoordinates(x, roundToFive((B*anotherLine.C / anotherLine.B - C) / A));
				}
				if (!anotherLine.B)
				{
					crossing.setCoordinates(x, roundToFive(-anotherLine.C / anotherLine.A));
					crossing.setCoordinates(y, roundToFive((A*anotherLine.C / anotherLine.A - C) / B));
				}
			}
		}
	} 
	return crossing;
}

double Line::getCoefficient(int mode) const {
	switch (mode)
	{
	case Ax: return A;
	case By: return B;
	case C0: return C;
	default: return 0;
	}
}

bool Line::isDotOnLine(const Dot &dot) const {
	return roundToTwo((A*dot.getCoordinates(x) + B*dot.getCoordinates(y) + C)) == 0;
}