#pragma once

#include "stvlib.h"
#include "raylib.h"

struct Window {
	ray::Vector2 size;
	std::string title;
	int fps;

	Window(ray::Vector2 p_size, std::string p_title, int p_fps = 60) {
		size = p_size;
		title = p_title;
		fps = p_fps;
	}

	void Init(void);

	void ProcessPerFrame(void);

	void ProcessPerTick(void);

};

struct Player {
	ray::Vector2 position;
	ray::Vector2 size;
	int speed = 10;

	Player(ray::Vector2 p_size);

	void draw(void);
	void move(ray::Vector2 vector);
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

	void update(double deltatime);
	void exitScreen(void);
	void hit(void);
	void explode(void);
	void reflect(void);

};


struct Bullet {

	ray::Vector2 position;
	ray::Vector2 velocity;
	ray::Vector2 size;
	int speed;
	int type;
	float damage;
	stv::Vector2 target;

	Bullet(ray::Vector2 p_position, stv::Vector2 p_target, int p_type, float p_damage, int p_speed = 10) {
		position = p_position;
		target = p_target;
		type = p_type;
		damage = p_damage;
		speed = p_speed;
	}
};