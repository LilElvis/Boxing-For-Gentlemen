#pragma once
#include <iostream>
#include <string>

class Vector
{
public:
	Vector(float, float, std::string);
	float dotProduct(const Vector&);
	float distance(const Vector&);
	void setX(float);
	void setY(float);
	void setName(std::string);
	float getX();
	float getY();
	std::string getName();
	void printVector();
	Vector operator=(Vector&);
private:
	float xCoord;
	float yCoord;
	std::string name;
};