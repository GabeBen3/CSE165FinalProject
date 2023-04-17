//Header file for vector operations to use in TransformComponent.h
#ifndef VECTOR2D
#define VECTOR2D

#include <iostream>

#pragma once


class Vector2D {

public: 

	float x;
	float y;

	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float _x, float _y) {
		this->x = _x;
		this->y = _y;
	}

	//return reference to a vector 
	Vector2D& Add(const Vector2D& v1) {
		this->x += v1.x;
		this->y += v1.y;

		return *this;
	}

	Vector2D& Subtract(const Vector2D& v1) {
		this->x -= v1.x;
		this->y -= v1.y;

		return *this;
	}

	Vector2D& Multi(const Vector2D& v1) {
		this->x *= v1.x;
		this->y *= v1.y;

		return *this;
	}
	Vector2D& Div(const Vector2D& v1) {
		this->x /= v1.x;
		this->y /= v1.y;

		return *this;
	}

	//operator overloads
	// Create friend reference to a Vector2D obj 
	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
		return v1.Add(v2);
	}
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
		return v1.Subtract(v2);
	}
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
		return v1.Multi(v2);
	}
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
		return v1.Div(v2);
	}

	Vector2D& operator+=(Vector2D& v1) {
		return this->Add(v1);
	}
	Vector2D& operator-=(Vector2D& v1) {
		return this->Subtract(v1);
	}
	Vector2D& operator*=(Vector2D& v1) {
		return this->Multi(v1);
	}
	Vector2D& operator/=(Vector2D& v1) {
		return this->Div(v1);
	}

	//Multiply vector by given int
	Vector2D& operator*(const int& i) {
		this->x *= i;
		this->y *= i;

		return *this;
	}

	//Zero out the vectors
	Vector2D& zero() {
		this->x = 0.0f;
		this->y = 0.0f;

		return *this;
	}
};


#endif // !VECTOR2D







