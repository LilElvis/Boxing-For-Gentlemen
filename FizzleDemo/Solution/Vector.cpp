#include "Vector.h"

Vector::Vector(float XIn, float YIn, std::string nameIn)
{
	setX(XIn);
	setY(YIn);
	setName(nameIn);
}

float Vector::dotProduct(const Vector& anotherVector)
{
	float dp = ((xCoord*anotherVector.xCoord) + (yCoord*anotherVector.yCoord));
	return dp;
}

float Vector::distance(const Vector& anotherVector)
{
	float d = (sqrtf(((anotherVector.xCoord - xCoord)*(anotherVector.xCoord - xCoord)) + ((anotherVector.yCoord - yCoord)*(anotherVector.yCoord - yCoord))));
	return d;
}

void Vector::setX(float xIn)
{
	xCoord = xIn;
}

void Vector::setY(float yIn)
{
	yCoord = yIn;
}

void Vector::setName(std::string nameIn)
{
	name = nameIn;
}

float Vector::getX()
{
	return xCoord;
}

float Vector::getY()
{
	return yCoord;
}

std::string Vector::getName()
{
	return name;
}

void Vector::printVector()
{
	std::cout << "/nVector " << getName() << ": (" << getX() << "," << getY() << ")/n";
}

Vector Vector::operator=(Vector& anotherVector)
{
	setX(anotherVector.getX());
	setY(anotherVector.getY());
	return anotherVector;
}