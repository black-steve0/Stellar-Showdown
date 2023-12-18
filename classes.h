#pragma once

#include "stvlib.h"
#include "raylib.h"
#include <chrono>
#include <ctime>

struct Window {
	Vector2 size;
	std::string title;
	int fps;

	Window(Vector2 p_size, std::string p_title, int p_fps = 60) {
		size = p_size;
		title = p_title;
		fps = p_fps;
	}

	void Init(void);

	bool ProcessPerFrame(void);

	bool ProcessPerTick(void);

};

struct Player {
	Vector2 position;
	Vector2 size;
	int speed = 10;
	int health = 10;

	Player(Vector2 p_size);

	void draw(void);
	void move(Vector2 vector);
};

struct Asteroid {
	int health;
	Vector2 size;
	Vector2 position;
	Vector2 vector;
	int speed;
	int type;
	bool reflective;

	Asteroid(){};
	Asteroid(Vector2 p_position, Vector2 p_size, int p_type, int p_speed, int p_health, bool p_reflective);

	void draw(void);
	void update(void);
	void collided(int type);

};

struct Bullet {

	Vector2 position;
	Vector2 velocity;
	int size;
	int speed;
	int type;
	int id;
	float damage;
	stv::Vector2 target;

	Bullet(int p_id, Vector2 p_position, int p_type, float p_damage, int p_speed = 20, int p_size = 25) {
		position = p_position;
		type = p_type;
		damage = p_damage;
		speed = p_speed;
		size = p_size;
		id = p_id;
	}

	void update(void);
	void draw(void);
};

struct Button {
	Vector2 position;
	std::string text;
	Vector2 size;
	int fontSize;
	int border;
	Color color;
	Color textColor;
	Color borderColor;

	Button(Vector2 p_position, std::string p_text, Vector2 p_size, int p_fontSize, int p_border, Color p_color, Color p_textColor, Color p_borderColor) {
		position = p_position;
		text = p_text;
		size = p_size;
		fontSize = p_fontSize;
		border = p_border;
		color = p_color;
		textColor = p_textColor;
		borderColor = p_borderColor;
	}

	bool update(void);
	void draw(void);
	bool hovered(void);
	bool clicked(int key);
};

struct ImageButton {
	Vector2 position;
	Texture texture;
	Vector2 size;
	Vector2 imageSize;
	int border;
	Color color;
	Color imageTint;
	Color borderColor;

	ImageButton(Vector2 p_position, Texture p_texture, Vector2 p_size, Vector2 p_imageSize, int p_border, Color p_color, Color p_borderColor, Color p_imageTint = WHITE) {
		position = p_position;
		texture = p_texture;
		size = p_size;
		imageSize = p_imageSize;
		border = p_border;
		color = p_color;
		borderColor = p_borderColor;
		imageTint = p_imageTint;
	}

	bool update(void);
	void draw(void);
	bool hovered(void);
	bool clicked(int key);
};

struct PowerUP {
	int id;
	int type;
	float strength;
	Vector2 position;
	Vector2 size = Vector2(75,40);

	PowerUP(int p_id, int p_type, float p_strength);
	void update(void);
	void draw(void);
};

struct Shield {
	int duration = 0;
	int active = 0;
	int size = 200;

	Shield() {
		duration = 0;
		active = 0;
	}

	void draw(void);
	void update(void);
};

struct Rocket {
	int damage;
	Vector2 position;
	Vector2 size;
	float rotation;

	Rocket(Vector2 p_position) {
		position = p_position;
	}
};

struct Gear {
	Vector2 position;
	Vector2 size = Vector2(125, 125);
	float rotation;
	int id;

	Gear(int p_id);

	void draw(void);
	void update(void);
};

struct MiniBullet {
	int damage;
	Vector2 position;
	Vector2 directionVector;
	Vector2 size = Vector2(125, 125);
	int id;
	int speed = 1;

	MiniBullet(int p_id, Vector2 p_position, Vector2 directionVector);

	void draw(void);
	void update(void);
};