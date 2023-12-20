#pragma once

#include "stvlib.h"
#include <chrono>
#include <ctime>
#include <random>

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
	int rotation = 0;

	Player(Vector2f p_size);

	void draw(void);
	void move(Vector2f vector);

	std::vector<Vector2f> vertexies() {
		return { 
			Vector2f(position.x + size.x / 2, position.y), 
			Vector2f(position.x, position.y + size.y - 10), 
			Vector2f(position.x + size.x, position.y + size.y - 10)
		};
	}
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
	int rotation;
	Vector2f target;
	Vector2f VectorDirection;

	Bullet(int p_id, Vector2f p_position, int p_type, float p_damage, int p_speed = 20, int p_size = 25);

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
	int active = 0;
	Vector2f size = Vector2f(200,200);
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;

	Shield() {
		start = std::chrono::high_resolution_clock::now();
		end = std::chrono::high_resolution_clock::now();
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
	int rotation = 0;
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
	Vector2f size = Vector2f(125, 125);
	int id;

	RogueEnemy(int p_id, int x) {
		position = Vector2f(x, -size.y);
		id = p_id;
	}

	void draw(void);
	void update(void);
};

struct Explosion {
	Vector2f position;
	Vector2f size = Vector2f(150, 150);
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> end;
	bool hit = 0;
	int id;
	int textureId = 0;

	Explosion(int p_id, Vector2f p_position) {
		position = p_position;
		id = p_id;
		start = std::chrono::high_resolution_clock::now();
		end = std::chrono::high_resolution_clock::now();
	}

	void draw(void);
	void update(void);
};