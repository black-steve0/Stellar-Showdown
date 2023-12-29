#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "raylib.h"

struct Colorf {
	unsigned char r;        // Color red value
	unsigned char g;        // Color green value
	unsigned char b;        // Color blue value
	unsigned char a;        // Color alpha value

	Colorf() {
		r = 0; g = 0; b = 0; a = 255;
	}

	Colorf(unsigned char mr, unsigned char mg, unsigned char mb, unsigned char ma = 255) {
		r = mr;
		g = mg;
		b = mb;
		a = ma;
	}

	operator Color() const {
		Color color;
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
		return color;
	}
};

typedef struct Rectf {
	float x;                // Rectangle top-left corner position x
	float y;                // Rectangle top-left corner position y
	float width;            // Rectangle width
	float height;           // Rectangle height

	Rectf(float px, float py, float pwidth, float pheight) {
		x = px;
		y = py;
		width = pwidth;
		height = pheight;
	}

	Rectf(Vector2 vec1, Vector2 vec2) {
		x = vec1.x;
		y = vec1.y;
		width = vec2.x;
		height = vec2.y;
	}

	operator Rect() const {
		Rect rect;
		rect.x = x;
		rect.y = y;
		rect.width = width;
		rect.height = height;
		return rect;
	}
} Rectanglef;

struct Vector2f {
	float x;
	float y;

	void operator += (float n) { x += n; y += n; }
	void operator += (Vector2f n) { x += n.x; y += n.y; }

	void operator -= (float n) { x -= n; y -= n; }
	void operator -= (Vector2f n) { x -= n.x; y -= n.y; }

	void operator *= (unsigned n) { x *= n; y *= n; }
	void operator *= (Vector2f n) { x *= n.x; y *= n.y; }

	void operator /= (float n) { x /= n; y /= n; }
	void operator /= (Vector2f n) { x /= n.x; y /= n.y; }

	void operator = (std::vector<int> vector2) { x = vector2[0]; y = vector2[1]; }
	void operator = (std::vector<float> vector2) { x = vector2[0]; y = vector2[1]; }
	void operator = (std::vector<double> vector2) { x = vector2[0]; y = vector2[1]; }

	bool operator == (Vector2f var) { return (var.x == x and var.y == y); }

	bool operator != (Vector2f var) { return !(var.x == x and var.y == y); }

	bool operator >= (Vector2f var) { return (sqrt(pow(var.x, 2) + pow(var.y, 2)) <= sqrt(pow(x, 2) + pow(y, 2))); }

	bool operator <= (Vector2f var) { return (sqrt(pow(var.x, 2) + pow(var.y, 2)) >= sqrt(pow(x, 2) + pow(y, 2))); }

	bool operator < (Vector2f var) { return (sqrt(pow(var.x, 2) + pow(var.y, 2)) > sqrt(pow(x, 2) + pow(y, 2))); }

	bool operator > (Vector2f var) { return (sqrt(pow(var.x, 2) + pow(var.y, 2)) < sqrt(pow(x, 2) + pow(y, 2))); }

	Vector2f operator + (float n) { return Vector2f(x + n, y + n); }
	Vector2f operator + (Vector2f n) { return Vector2f(x + n.x, y + n.y); }
	Vector2f operator - (float n) { return Vector2f(x - n, y - n); }
	Vector2f operator - (Vector2f n) { return Vector2f(x - n.x, y - n.y); }
	Vector2f operator * (float n) { return Vector2f(x * n, y * n); }
	Vector2f operator * (Vector2f n) { return Vector2f(x * n.x, y * n.y); }
	Vector2f operator / (float n) { return Vector2f(x / n, y / n); }
	Vector2f operator / (Vector2f n) { return Vector2f(x / n.x, y / n.y); }

	std::string operator ! () {
		return std::to_string((int)x) + ";" + std::to_string((int)y);
	}

	friend std::ostream& operator << (std::ostream& os, const Vector2f vector2)
	{
		os << "(" << vector2.x << ", " << vector2.y << ")";
		return os;
	};

	Vector2f() { x = 0; y = 0; }

	Vector2f(double p_x, double p_y) { x = p_x; y = p_y; }

	Vector2f(std::vector<int> vector2) { x = vector2[0]; y = vector2[1]; }
	Vector2f(std::vector<float> vector2) { x = vector2[0]; y = vector2[1]; }
	Vector2f(std::vector<double> vector2) { x = vector2[0]; y = vector2[1]; }

	operator Vector2() const { 
		Vector2 vector;
		vector.x = x;
		vector.y = y;
		return vector;
	}
};