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

namespace stv {

	struct Vector3 {
		double x = 0;
		double y = 0;
		double z = 0;

		void operator += (float n) { x += n; y += n; z += n; }
		void operator += (Vector3 n) { x += n.x; y += n.y; z += n.z; }

		void operator -= (float n) { x -= n; y -= n; z -= n; }
		void operator -= (Vector3 n) { x -= n.x; y -= n.y; z -= n.z; }

		void operator *= (unsigned n) { x *= n; y *= n; z *= n; }
		void operator *= (Vector3 n) { x *= n.x; y *= n.y; z *= n.z; }

		void operator /= (float n) { x /= n; y /= n; z /= n; }
		void operator /= (Vector3 n) { x /= n.x; y /= n.y; z /= n.z; }

		void operator = (std::vector<int> vector3) { x = vector3[0]; y = vector3[1]; z = vector3[2]; }
		void operator = (std::vector<float> vector3) { x = vector3[0]; y = vector3[1]; z = vector3[2]; }
		void operator = (std::vector<double> vector3) { x = vector3[0]; y = vector3[1]; z = vector3[2]; }

		bool operator == (Vector3 var) { return (var.x == x and var.y == y and var.z == z); }

		bool operator != (Vector3 var) { return !(var.x == x and var.y == y and var.z == z); }

		Vector3 operator + (float n) { return Vector3(x + n, y + n, z + n); }
		Vector3 operator + (Vector3 n) { return Vector3(x + n.x, y + n.y, z + n.z); }
		Vector3 operator - (float n) { return Vector3(x - n, y - n, z - n); }
		Vector3 operator - (Vector3 n) { return Vector3(x - n.x, y - n.y, z - n.z); }
		Vector3 operator * (float n) { return Vector3(x * n, y * n, z * n); }
		Vector3 operator * (Vector3 n) { return Vector3(x * n.x, y * n.y, z * n.z); }
		Vector3 operator / (float n) { return Vector3(x / n, y / n, z / n); }
		Vector3 operator / (Vector3 n) { return Vector3(x / n.x, y / n.y, z / n.z); }

		friend std::ostream& operator << (std::ostream& os, const Vector3 vector3)
		{
			os << "(" << vector3.x << ", " << vector3.y << ", " << vector3.z << ")";
			return os;
		};

		Vector3() { x = 0; y = 0; z = 0; }

		Vector3(double p_x, double p_y, double p_z) { x = p_x; y = p_y; z = p_z; }

		Vector3(std::vector<int> vector3) { x = vector3[0]; y = vector3[1]; z = vector3[2]; }
		Vector3(std::vector<float> vector3) { x = vector3[0]; y = vector3[1]; z = vector3[2]; }
		Vector3(std::vector<double> vector3) { x = vector3[0]; y = vector3[1]; z = vector3[2]; }
	};

	struct Vector2 {
		double x = 0;
		double y = 0;

		void operator += (float n) { x += n; y += n; }
		void operator += (Vector2 n) { x += n.x; y += n.y; }

		void operator -= (float n) { x -= n; y -= n; }
		void operator -= (Vector2 n) { x -= n.x; y -= n.y; }

		void operator *= (unsigned n) { x *= n; y *= n; }
		void operator *= (Vector2 n) { x *= n.x; y *= n.y; }

		void operator /= (float n) { x /= n; y /= n; }
		void operator /= (Vector2 n) { x /= n.x; y /= n.y; }

		void operator = (std::vector<int> vector2) { x = vector2[0]; y = vector2[1]; }
		void operator = (std::vector<float> vector2) { x = vector2[0]; y = vector2[1]; }
		void operator = (std::vector<double> vector2) { x = vector2[0]; y = vector2[1]; }

		bool operator == (Vector2 var) { return (var.x == x and var.y == y); }

		bool operator != (Vector2 var) { return !(var.x == x and var.y == y); }

		bool operator >= (Vector2 var) { return (sqrt(pow(var.x, 2) + pow(var.y, 2)) <= sqrt(pow(x, 2) + pow(y, 2))); }

		bool operator <= (Vector2 var) { return (sqrt(pow(var.x, 2) + pow(var.y, 2)) >= sqrt(pow(x, 2) + pow(y, 2))); }

		bool operator < (Vector2 var) { return (sqrt(pow(var.x, 2) + pow(var.y, 2)) > sqrt(pow(x, 2) + pow(y, 2))); }

		bool operator > (Vector2 var) { return (sqrt(pow(var.x, 2) + pow(var.y, 2)) < sqrt(pow(x, 2) + pow(y, 2))); }

		Vector2 operator + (float n) { return Vector2(x + n, y + n); }
		Vector2 operator + (Vector2 n) { return Vector2(x + n.x, y + n.y); }
		Vector2 operator - (float n) { return Vector2(x - n, y - n); }
		Vector2 operator - (Vector2 n) { return Vector2(x - n.x, y - n.y); }
		Vector2 operator * (float n) { return Vector2(x * n, y * n); }
		Vector2 operator * (Vector2 n) { return Vector2(x * n.x, y * n.y); }
		Vector2 operator / (float n) { return Vector2(x / n, y / n); }
		Vector2 operator / (Vector2 n) { return Vector2(x / n.x, y / n.y); }

		std::string operator ! () {
			return std::to_string((int)x) + ";" + std::to_string((int)y);
		}

		friend std::ostream& operator << (std::ostream& os, const Vector2 vector2)
		{
			os << "(" << vector2.x << ", " << vector2.y << ")";
			return os;
		};

		Vector2() { x = 0; y = 0; }

		Vector2(double p_x, double p_y) { x = p_x; y = p_y; }

		Vector2(std::vector<int> vector2) { x = vector2[0]; y = vector2[1]; }
		Vector2(std::vector<float> vector2) { x = vector2[0]; y = vector2[1]; }
		Vector2(std::vector<double> vector2) { x = vector2[0]; y = vector2[1]; }
	};

	template <class _Ty, class _Alloc = std::allocator<_Ty>>
	struct Vector {
		std::vector<_Ty> data;

		Vector() {}

		Vector(std::vector<_Ty> vec) {
			data = vec;
		}

		Vector2 vector2(int i = 0) {
			i *= 2;
			if (data.size() < 2 + i) { return Vector2(0, 0); }
			return Vector2(data[0 + i], data[1 + i]);
		}

		Vector3 vector3(int i = 0) {
			i *= 3;
			if (data.size() < 3 + i) { return Vector3(data[0 + i], data[1 + i], 0); }
			return Vector3(data[0 + i], data[1 + i], data[2 + i]);
		}

		std::vector<_Ty> vector() {
			return data;
		}

		std::vector<_Ty> subVector(int start, int length) {
			auto vecstart = data.begin() + start;
			auto vecend = data.begin() + start + length;
			return std::vector<_Ty>(vecstart, vecend);
		}

		void append(_Ty n) {
			data.push_back(n);
		}
		void append(Vector n) {
			data.insert(data.end(), n.data.begin(), n.data.end());
		}
		void append(std::vector<_Ty> n) {
			data.insert(data.end(), n.begin(), n.end());
		}

		Vector<_Ty> operator + (_Ty n) {
			std::vector<_Ty> vec = data;
			vec.push_back(n);
			return vec;
		}
		std::vector<_Ty> operator + (std::vector<_Ty> n) {
			std::vector<_Ty> vec = data;
			vec.insert(vec.end(), n.begin(), n.end());
			return vec;
		}
		Vector operator + (Vector n) {
			Vector vec;
			vec.data = data;
			vec.data.insert(vec.data.end(), n.data.begin(), n.data.end());
			return vec;
		}

		_Ty operator [] (int i) { return data[i]; }

		friend std::ostream& operator << (std::ostream& os, const Vector vec)
		{
			if (!vec.data.size()) return os;
			os << "(";
			for (int i = 0; i < vec.data.size() - 1; i++) {
				os << vec.data[i] << ", ";
			}
			os << vec.data[vec.data.size() - 1] << ")";
			return os;
		};

		void operator += (_Ty n) {
			data.push_back(n);
		}
		void operator += (Vector n) {
			data.insert(data.end(), n.data.begin(), n.data.end());
		}
		void operator += (std::vector<_Ty> n) {
			data.insert(data.end(), n.begin(), n.end());
		}
	};

	struct rgb {
		int blue;
		int red;
		int green;

		rgb(int r, int g, int b) {
			blue = b;
			red = r;
			green = g;
		}
	};

	struct Color {
		int blue;
		int red;
		int green;
		int alpha;


		Color(int r, int g, int b, int a = 255) {
			blue = b;
			red = r;
			green = g;
			alpha = a;
		}
	};

	class matrix3d {
	public:
		std::vector<std::vector<std::vector<int>>> data;
		std::vector<stv::Vector3> renderOrder;
	public:
		matrix3d(int p_x = 1, int p_y = 1, int p_z = 1, int def = 0) {

			for (int k = 0; k < p_x; k++) {
				data.push_back(std::vector<std::vector<int>>{});
				for (int j = 0; j < p_y; j++) {
					data[k].push_back(std::vector<int> {});
					for (int i = 0; i < p_z; i++) {
						data[k][j].push_back(def);
					}
				}
			}
		}

		friend std::ostream& operator << (std::ostream& os, const matrix3d matrix) {
			for (const std::vector<std::vector<int>>& element1 : matrix.data) { for (const std::vector<int>& element2 : element1) { for (const int& element3 : element2) { os << element3 << " "; } os << std::endl; } os << std::endl; }
			return os;
		}

		void updateOrder(int chunkid, Vector3 playerPosition);

		std::vector<stv::Vector3> getOrder(int chunkid);

	};

}