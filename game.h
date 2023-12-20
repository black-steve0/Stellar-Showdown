#pragma once

#include "data.h"
#include <cmath>

void rocketLaunch() {

}

void summonShield() {
	
}

void applyShop() {
	maxHealth = upgrades[2] + 9;
	damage = 2.5 + upgrades[2] * 2.5;
}

void shoot() {
	if ((end - start).count() / (1000000000 / ((float)(upgrades[5]) * 2.5 + 2.5)) >= 1) {
		if (upgrades[3] % 2 == 1) {
			bullets.emplace_back(Bullet(BulletIdCount++,
				Vector2f(player.position.x + player.size.x / 2 - bulletsize / 2 - 3,
					player.position.y - bulletsize / 2),
				bulletType,
				damage));
		}

		if (upgrades[3] > 1) {
			bullets.emplace_back(Bullet(BulletIdCount++,
				Vector2f(player.position.x + player.size.x / 4 - bulletsize / 2 - 3,
					player.position.y - bulletsize / 2 + player.size.y / 2),
				bulletType,
				damage));
			bullets.emplace_back(Bullet(BulletIdCount++,
				Vector2f(player.position.x + (player.size.x - player.size.x / 4) - bulletsize / 2 - 3,
					player.position.y - bulletsize / 2 + player.size.y / 2),
				bulletType,
				damage));
		}
		start = std::chrono::high_resolution_clock::now();
	}
}

bool sCheckCollisionCircles(Vector2f center, int radius, Vector2f center2, int radius2) {
	int a = center.x - center2.x;
	int b = center.y - center2.y;
	int c = a * a + b * b;
	float radii = radius + radius2;
	return radii * radii >= c;
}

bool sCheckCollisionCircleTriangle(Vector2f center, int radius, std::vector<Vector2f> vertexes) {
	
	for (auto vertex : vertexes) {
		double distance = sqrt(pow(center.x - vertex.x, 2) + pow(center.y - vertex.y, 2));
		if (distance <= radius) {
			return true;
		}
	}
	return false;
}

void endGame() {
	totalcoins += score/10;
	gameRunning = 0;
	asteroids.clear();
	page = 0;
}

void Shield::draw() {
	DrawTexture(shieldTexture, player.position.x - size/2, player.position.y - size/2, WHITE);
}

Player::Player(Vector2f p_size) {
	size = p_size;
	position = Vector2f(window_size.x / 2 - size.x / 2, window_size.y - size.y - 10);
}

void Player::draw() {
	DrawTexturePro(spaceship1, Rectanglef(0,0, spaceship1.width, spaceship1.height), Rectanglef(position.x+size.x/2, position.y+size.y/2, size.x, size.y), Vector2f(size.x/2, size.y/2), 0, WHITE);
}

void Player::move(Vector2f vector) {
	if (position.x + (vector.x * speed) > 0 and position.x + (vector.x * speed) < window_size.x - size.x and position.y + (vector.y * speed) > 0 and position.y + (vector.y * speed) < window_size.y - size.y) {
		position += vector * speed;
	}
}

Asteroid::Asteroid(Vector2f p_position, Vector2f p_size, int p_type, int p_speed, int p_health = 10, bool p_reflective = 0) {
	position = p_position;
	size = p_size;
	type = p_type;
	health = p_health;
	reflective = p_reflective;
	speed = p_speed;

	vector = Vector2f(((double)(rand() % 10) - (rand() % 10)) / 10, 1);
}

void Asteroid::update() {
	int x = window_size.x;
	if (position.x < -size.x or position.x > window_size.x or position.y > window_size.y) {
		position = Vector2f(rand() % x, -size.y);
	}

	std::vector<Vector2f> playerVertex = { Vector2f(player.position.x + player.size.x / 2, player.position.y), Vector2f(player.position.x, player.position.y + player.size.y - 10), Vector2f(player.position.x + player.size.x, player.position.y + player.size.y - 10) };

	if (sCheckCollisionCircleTriangle(position + size/2, size.x/2, playerVertex)) {
		player.health -= (int)size.x / 75;

		if (type == 2) {
			DrawCircle(position.x, position.y, size.x, RED);
			if (CheckCollisionCircleRec(position, size.x, Rectanglef(player.position.x, player.position.y, player.size.x, player.size.y))) {
				player.health -= 3;
			}
		}

		position = Vector2f(rand() % x, rand() % 100 - size.y);
		vector = Vector2f(((double)(rand() % 10) - (rand() % 10)) / 10, 1);
		type = rand() % 3;
		health = 10;

		if (player.health <= 0) {
			player.health = 0;
			endGame();
		}
	}

	position += vector * speed;
}

void Asteroid::collided(int type) {
	health -= damage / (type + 1);
	if (health < 1) {
		position = Vector2f(rand() % x, -(rand() % 100) - size.y);
		type = rand() % 3;
		health = 10;
		score++;
	}
}

void Asteroid::draw() {
	asteroid.width = size.x;
	asteroid.height = size.y;
	if (type == 2) {
		DrawTexture(asteroid, position.x, position.y, RED);
	}
	else {
		DrawTexture(asteroid, position.x, position.y, WHITE);
	}
}

Asteroid asteroidSpawn() {
	Asteroid ast = Asteroid(Vector2f(rand() % x, -(rand() % 300)), Vector2f(asteroidsize, asteroidsize), rand() % 3, 10);
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
		if (CheckCollisionRecs(Rectanglef(position.x, position.y, size, size), Rectanglef(object.position.x, object.position.y, object.size.x, object.size.y))) {
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
	DrawTexture(bulletTextures[type], position.x, position.y, WHITE);
}

PowerUP::PowerUP(int p_id, int p_type, float p_strength) {
	id = p_id;
	position = Vector2f(rand() % x, -size.y/2);
	type = p_type;
	strength = p_strength;
}

void PowerUP::update() {
	position += Vector2f(0, 10);
	bool collided = 0;

	if (CheckCollisionRecs(Rectanglef(position.x, position.y, size.x, size.y), Rectanglef(player.position.x, player.position.y, player.size.x, player.size.y))) {
		if (type == 0) {
			damage += 5 * strength;
			upgradeStart = std::chrono::high_resolution_clock::now();
		}
		else if (type == 1) {
			firespeed += 2.5 * strength;
			upgradeStart = std::chrono::high_resolution_clock::now();
		}
		else if (type == 2) {
			player.health += 10 * strength;
		}
		else if (type == 3) {
			rocketLaunch();
		}
		else if (type == 4) {
			summonShield();
			upgradeStart = std::chrono::high_resolution_clock::now();
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
	DrawTexture(powerUPTextures[type], position.x, position.y, WHITE);
}


Gear::Gear(int p_id) {
	id = p_id;
	position = Vector2f(player.position.x + player.size.x/2, window_size.y + size.y / 2);
}

void Gear::draw() {
	int rot = floor(rotation / 10);
	gearTexture.width = size.x;
	gearTexture.height = size.y;
	DrawTexturePro(gearTexture, Rectanglef(0, 0, gearTexture.width, gearTexture.height), Rectanglef(position.x, position.y, size.x, size.y), Vector2f(size.x / 2, size.y / 2), 0, WHITE);

}

void Gear::update() {
	position.y -= 2;
	rotation += 1;

	if (rotation / 10 == floor(rotation / 10)) {
		for (int i : {0, 1, 2, 3, 4, 5, 6, 7}) {
			Vector2f dirVec = Vector2f(cos(i * 45 * PI / 180.0) , sin(i * 45 * PI / 180.0));
			miniBullets.push_back(MiniBullet(MiniBulletIdCount++, position + (dirVec * size / 2)*0.9, dirVec));
		}
	}

	if (position.y + size.y / 2 < 0) {
		for (int i = 0; i < gears.size(); i++) {
			if (gears[i].id == id) {
				gears.erase(gears.begin() + i, gears.begin() + i + 1);
				break;
			}
		}
	}
}

MiniBullet::MiniBullet(int p_id, Vector2f p_position, Vector2f p_directionVector) {
	id = p_id;
	directionVector = p_directionVector;
	position = p_position+size/4;
}

void MiniBullet::draw() {
	DrawTexture(miniBulletTexture, position.x - size.x / 2, position.y - size.y / 2, WHITE);
}

void MiniBullet::update() {
	position += directionVector*speed;
	if (position.x < -size.x or position.x > window_size.x or position.y - size.y > window_size.y) {
		for (int i = 0; i < miniBullets.size(); i++) {
			if (miniBullets[i].id == id) {
				miniBullets.erase(miniBullets.begin() + i, miniBullets.begin() + i + 1);
				break;
			}
		}
	}
	int collided = 0;
	for (Asteroid& object : asteroids) {
		if (sCheckCollisionCircles(position+size/2, size.x/2, object.position+object.size/2, object.size.x/2)) {
			collided = 1;
			object.collided(0);
		}
	}

	if (collided) {
		for (int i = 0; i < miniBullets.size(); i++) {
			if (miniBullets[i].id == id) {
				miniBullets.erase(miniBullets.begin() + i, miniBullets.begin() + i + 1);
				break;
			}
		}
	}
}

void gameStart() {
	page = 1;
	gameRunning = 1;
	score = 0;
	for (int i = 0; i < 10; i++) asteroids.push_back(asteroidSpawn());
	player.health = maxHealth;
	bullets = {};
	player.position = Vector2f(window_size.x / 2 - player.size.x / 2, window_size.y - player.size.y - 10);
}