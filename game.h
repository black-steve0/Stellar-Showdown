#pragma once

#include "window.h"
#include "raylib.h"
#include "stvlib.h"

struct Player {
	ray::Vector2 position;
	ray::Vector2 size;

	Player(ray::Vector2 p_size) {
		size = p_size;
		position = ray::Vector2(window.size.x/2 - size.x/2, window.size.y - size.y - 10);
	}
	
	void draw() {
		ray::DrawRectangle(position.x, position.y, size.x, size.y, WHITE);
	}

	void move(ray::Vector2 vector) {

	}
};

struct Asteroid {
	int health;
	ray::Vector2 size;
	ray::Vector2 position;
	ray::Vector2 vector;
	int speed;
	int type;
	bool reflective;

	Asteroid(ray::Vector2 p_position, ray::Vector2 p_size, ray::Vector2 p_vector, int p_type, int p_speed, int p_health = 10, bool p_reflective = 0) {
		position = p_position;
		size = p_size;
		type = p_type;
		health = p_health;
		reflective = p_reflective;
		vector = p_vector;
		speed = p_speed;
	}

	void update(double deltatime) {

	}

	void exitScreen() {

	}

	void hit() {

	}

	void explode() {

	}

	void reflect() {

	}

};

struct Bullet {

	ray::Vector2 position;
	ray::Vector2 velocity;
	ray::Vector2 size;
	int speed;
	int type;
	float damage;

	Asteroid target;

	Bullet(ray::Vector2 position, int speed, ) {

	}
};

void Window::ProcessPerFrame() {

}

void Window::ProcessPerTick() {

}