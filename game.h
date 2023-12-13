#pragma once

#include "data.h"

void rocketLaunch() {

}

void summonShield() {

}

void endGame() {
	totalcoins += score/10;
	gameRunning = 0;
	asteroids.clear();
	page = 0;
}

void Shield::draw() {
	ray::DrawTexture(shieldTexture, player.position.x - size/2, player.position.y - size/2, WHITE);
}

Player::Player(ray::Vector2 p_size) {
	size = p_size;
	position = ray::Vector2(window_size.x / 2 - size.x / 2, window_size.y - size.y - 10);
}

void Player::draw() {
	spaceship1.width = size.x;
	spaceship1.height = size.y;
	ray::DrawTexture(spaceship1, position.x, position.y, WHITE);
}

void Player::move(ray::Vector2 vector) {
	if (position.x + (vector.x * speed) > 0 and position.x + (vector.x * speed) < window_size.x - size.x and position.y + (vector.y * speed) > 0 and position.y + (vector.y * speed) < window_size.y - size.y) {
		position += vector * speed;
	}
}

Asteroid::Asteroid(ray::Vector2 p_position, ray::Vector2 p_size, int p_type, int p_speed, int p_health = 10, bool p_reflective = 0) {
	position = p_position;
	size = p_size;
	type = p_type;
	health = p_health;
	reflective = p_reflective;
	speed = p_speed;

	vector += ray::Vector2(((double)(rand() % 10) - (rand() % 10))/10, 1);
}

void Asteroid::update() {
	int x = window_size.x;
	if (position.x < -size.x or position.x > window_size.x or position.y > window_size.y) {
		
		position = ray::Vector2(rand() % x, -size.y);
	}
	if (ray::CheckCollisionRecs(ray::Rectangle(position.x, position.y, size.x, size.y), ray::Rectangle(player.position.x, player.position.y, player.size.x, player.size.y))) {
		
		player.health -= (int)size.x / 75;

		if (type == 2) {
			ray::DrawCircle(position.x, position.y, size.x, RED);
			if (ray::CheckCollisionCircleRec(position, size.x, ray::Rectangle(player.position.x, player.position.y, player.size.x, player.size.y))) {
				player.health -= 3;
			}
		}

		position = ray::Vector2(rand() % x, rand() % 100 - size.y);
		type = rand() % 3;
		health = 10;

		if (player.health <= 0) {
			endGame();
		}
	}

	position += vector * speed;
}

void Asteroid::collided(int type) {
	position = ray::Vector2(rand() % x, -(rand() % 100) - size.y);
	type = rand() % 3;
	health = 10;
	score++;
}

void Asteroid::draw() {
	asteroid.width = size.x;
	asteroid.height = size.y;
	if (type == 2) {
		ray::DrawTexture(asteroid, position.x, position.y, RED);
	}
	else {
		ray::DrawTexture(asteroid, position.x, position.y, WHITE);
	}
}

Asteroid asteroidSpawn() {
	Asteroid ast = Asteroid(ray::Vector2(rand() % x, -(rand() % 300)), ray::Vector2(asteroidsize, asteroidsize), rand() % 3, 10);
	return ast;
}

void Bullet::update() {
	bool collided = 0;

	if (position.y < 0) {
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i].id == id) {
				bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
				break;
			}
		}
	}

	for (Asteroid& object : asteroids) {
		if (ray::CheckCollisionRecs(ray::Rectangle(position.x, position.y, size, size), ray::Rectangle(object.position.x, object.position.y, object.size.x, object.size.y))) {
			collided = 1;
			object.collided(type);
		}
	}

	if (collided) {
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i].id == id) {
				bullets.erase(bullets.begin() + i, bullets.begin() + i + 1);
				break;
			}
		}
	}

	position.y -= speed;

}

void Bullet::draw() {
	bulletTextures[type].width = size;
	bulletTextures[type].height = size*1.75;
	ray::DrawTexture(bulletTextures[type], position.x, position.y, WHITE);
}

PowerUP::PowerUP(int p_id, int p_type, float p_strength) {
	id = p_id;
	position = ray::Vector2(rand() % x, -size.y/2);
	type = p_type;
	strength = p_strength;
}

void PowerUP::update() {
	position += ray::Vector2(0, 10);
	bool collided = 0;

	if (ray::CheckCollisionRecs(ray::Rectangle(position.x, position.y, size.x, size.y), ray::Rectangle(player.position.x, player.position.y, player.size.x, player.size.y))) {
		if (type == 0) {
			damage += 5 * strength;
		}
		else if (type == 1) {
			firespeed += 1 * strength;
		}
		else if (type == 2) {
			player.health += 10 * strength;
		}
		else if (type == 3) {
			rocketLaunch();
		}
		else if (type == 4) {
			summonShield();
		}
		collided++;
	}

	if (position.y > window_size.y or collided) {
		for (int i = 0; i < powerUPs.size(); i++) {
			if (powerUPs[i].id == id) {
				powerUPs.erase(powerUPs.begin() + i, powerUPs.begin() + i + 1);
				break;
			}
		}
	}
}

void PowerUP::draw() {
	ray::DrawTexture(powerUPTextures[type], position.x, position.y, WHITE);
}

void gameStart() {
	page = 1;
	damage = 5;
	gameRunning = 1;
	score = 0;
	for (int i = 0; i < 10; i++) asteroids.push_back(asteroidSpawn());
	player.health = 10;
	bullets = {};
	player.position = ray::Vector2(window_size.x / 2 - player.size.x / 2, window_size.y - player.size.y - 10);
}