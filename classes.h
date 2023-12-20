#pragma once

#include "stvlib.h"
#include <chrono>
#include <ctime>

struct Window {
	Vector2f size;
	std::string title;
	int fps;

	Window(Vector2f p_size, std::string p_title, int p_fps = 60) {
		size = p_size;
		title = p_title;
		fps = p_fps;
	}

	void Init(void);

	bool ProcessPerFrame(void);

	bool ProcessPerTick(void);

};

struct Player {
	Vector2f position;
	Vector2f size;
	int speed = 10;
	int health = 10;

	Player(Vector2f p_size);

	void draw(void);
	void move(Vector2f vector);
};

struct Asteroid {
	int health;
	Vector2f size;
	Vector2f position;
	Vector2f vector;
	int speed;
	int type;
	bool reflective;

	Asteroid(){};
	Asteroid(Vector2f p_position, Vector2f p_size, int p_type, int p_speed, int p_health, bool p_reflective);

	void draw(void);
	void update(void);
	void collided(int type);

};

struct Bullet {

	Vector2f position;
	Vector2f velocity;
	int size;
	int speed;
	int type;
	int id;
	float damage;
	Vector2f target;

	Bullet(int p_id, Vector2f p_position, int p_type, float p_damage, int p_speed = 20, int p_size = 25) {
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
	Vector2f position;
	std::string text;
	Vector2f size;
	int fontSize;
	int border;
	Color color;
	Color textColor;
	Color borderColor;

	Button(Vector2f p_position, std::string p_text, Vector2f p_size, int p_fontSize, int p_border, Color p_color, Color p_textColor, Color p_borderColor) {
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
	Vector2f position;
	Texture texture;
	Vector2f size;
	Vector2f imageSize;
	int border;
	Color color;
	Color borderColor;

	ImageButton(Vector2f p_position, Texture p_texture, Vector2f p_size, Vector2f p_imageSize, int p_border, Color p_color, Color p_borderColor) {
		position = p_position;
		texture = p_texture;
		size = p_size;
		imageSize = p_imageSize;
		border = p_border;
		color = p_color;
		borderColor = p_borderColor;
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
	Vector2f position;
	Vector2f size = Vector2f(75,40);

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
	Vector2f position;
	Vector2f size;
	float rotation;

	Rocket(Vector2f p_position) {
		position = p_position;
	}
};

struct Gear {
	Vector2f position;
	Vector2f size = Vector2f(100, 100);
	float rotation = 0;
	int id;

	Gear(int p_id);

	void draw(void);
	void update(void);
};

struct MiniBullet {
	int damage = 2;
	Vector2f position;
	Vector2f directionVector;
	Vector2f size = Vector2f(10, 10);
	int id;
	int speed = 10;

	MiniBullet(int p_id, Vector2f p_position, Vector2f directionVector);

	void draw(void);
	void update(void);
};

struct RogueEnemy {
	Vector2f position;
	Vector2f size;


	RogueEnemy();
};