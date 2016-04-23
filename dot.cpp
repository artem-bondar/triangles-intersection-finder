#include "dot.h"
#include "text.h"
#include "implements.h"
#include "interface.h"

Dot::Dot() {
	isExist = false;
}

Dot::Dot(double x, double y) {
	setCoordinates(x,y);
}

const bool Dot::operator==(const Dot &anotherDot) const {
	return roundToFive(X) == roundToFive(anotherDot.X) && roundToFive(Y) == roundToFive(anotherDot.Y);
}

const bool Dot::operator!=(const Dot &anotherDot) const {
	return roundToFive(X) != roundToFive(anotherDot.X) || roundToFive(Y) != roundToFive(anotherDot.Y);
}

const bool Dot::operator<=(const Dot &anotherDot) const {
	return roundToFive(X) <= roundToFive(anotherDot.X) && roundToFive(Y) <= roundToFive(anotherDot.Y);
}

const bool Dot::operator>=(const Dot &anotherDot) const {
	return roundToFive(X) >= roundToFive(anotherDot.X) && roundToFive(Y) >= roundToFive(anotherDot.Y);
}

const bool Dot::operator<(const Dot &anotherDot) const {
	return (roundToFive(X) < roundToFive(anotherDot.X) && Y <= roundToFive(anotherDot.Y)) || (Y < roundToFive(anotherDot.Y) && X <= roundToFive(anotherDot.X));
}

const bool Dot::operator>(const Dot &anotherDot) const {
	return (roundToFive(X) > roundToFive(anotherDot.X) && Y >= roundToFive(anotherDot.Y)) || (Y > roundToFive(anotherDot.Y) && X >= roundToFive(anotherDot.X));
}

Dot Dot::operator+(const Dot &anotherDot) const {
	Dot resultDot;
	resultDot.setCoordinates(anotherDot.X, Y);
	return resultDot;
}

Dot Dot::operator-(const Dot &anotherDot) const {
	return anotherDot + *this;
}

ostream& operator<<(ostream& ostream, const Dot &dot) {
	if (dot.isExist)
	{
		ostream << text.geometry[5];
		UI.outputNumber(dot.X, 5);
		cout << text.geometry[7];
		UI.outputNumber(dot.Y, 5); 
		cout << text.geometry[6];
	}
	else
		ostream << text.geometry[0] << text.geometry[1];
	return ostream;
}

void Dot::setCoordinates(double x, double y) {
	isExist = true;
	X = x;
	Y = y;
}

void Dot::setCoordinates(int mode, double number) { 
	isExist = true;
	switch (mode)
	{
	case x: { X = number; break; }
	case y: { Y = number; }
	}
}

void Dot::setNonExistent() {
	isExist = false;
}

double Dot::getCoordinates(int mode) const {
	if (isExist) {
		switch (mode)
		{
		case x: return X;
		case y: return Y;
		default: return 0;
		}
	}
	else return false;
}

double getSquareNormBetweenTwoDots(const Dot &dot, const Dot &anotherDot) {
	return sqrt(pow(dot.X - anotherDot.X, 2) + pow(dot.Y - anotherDot.Y, 2));
}