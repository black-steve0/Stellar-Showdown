#pragma once

#include "data.h"
#include <cmath>

void rocketLaunch() {

}

void summonShield() {
	shield.active = 1;
	shield.start = std::chrono::high_resolution_clock::now();
}

void applyShop() {
	maxHealth = upgrades[2] + 9;
	damage = 2.5 + upgrades[2] * 2.5;
}

void shoot() {
	if ((uend - ustart).count() / (1000000000 / ((float)(upgrades[5]) * 2.5 + 2.5)) >= 1) {
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
		ustart = std::chrono::high_resolution_clock::now();
	}
}

bool sCheckCollisionCircles(Vector2f center, int radius, Vector2f center2, int radius2) {
	int a = center.x - center2.x;
	int b = center.y - center2.y;
	int c = a * a + b * b;
	float radii = radius + radius2;
	return radii * radii >= c;
}

int min(int x, int y) {
	return x * (x <= y) + y * (y < x);
}

float bearing(Vector2f position, Vector2f position2) {
	Vector2f distance = position - position2;

	return atan2(distance.x, distance.y) * 57.2957795;
}

bool sCheckCollisionTriangleRec(Vector2f start, Vector2f end, Rectf rect) {
	return 0;
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
	page = 0;
	
	asteroids = {};
	bullets = {};
	miniBullets = {};
	rogueEnemies = {};
	gears = {};
	powerUPs = {};
	explosions = {};
}

Player::Player(Vector2f p_size) {
	size = p_size;
	position = Vector2f(window_size.x / 2 - size.x / 2, window_size.y - size.y - 10);
}

void Player::draw() {
	rotation = bearing(position + size / 2, Vector2f(GetMouseX(), GetMouseY())) *-1;
	DrawTexturePro(spaceship1, Rectanglef(0,0, spaceship1.width, spaceship1.height), Rectanglef(position.x+size.x/2, position.y+size.y/2, size.x, size.y), Vector2f(size.x/2, size.y/2), rotation, WHITE);
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

	vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
}

void Asteroid::update() {
	if (position.x < -size.x or position.x > window_size.x or position.y > window_size.y) {
		position = Vector2f(dis(gen), -size.y);
	}

	if (sCheckCollisionCircles(player.position + size / 2, shield.size.x / 2, position + size / 2, size.x / 2) && shield.active) {
		position = Vector2f(dis(gen), -(dis(gen) % 100) - size.y);
		type = dis(gen) % 3;
		health = 10 + stage * 2;
		vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
	}

	if (sCheckCollisionCircleTriangle(position + size/2, size.x/2, player.vertexies())) {
		player.health -= (int)size.x / 75;

		if (type == 2) {
			explosions.push_back(Explosion(ExplosionIdCount++, position));
		}

		position = Vector2f(dis(gen), dis(gen) % 100 - size.y);
		vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
		type = dis(gen) % 3;
		health = 10+stage*2;
	}

	position += vector * speed;
}

void Asteroid::collided(int p_damage) {
	health -= p_damage;
	if (health < 1) {
		position = Vector2f(dis(gen), -(dis(gen) % 100) - size.y);
		vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
		type = dis(gen) % 3;
		health = 10 + stage * 2;
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
	Asteroid ast = Asteroid(Vector2f(dis(gen), -(dis(gen) % 300)), Vector2f(asteroidsize, asteroidsize), dis(gen) % 3, 10);
	return ast;
}

Bullet::Bullet(int p_id, Vector2f p_position, int p_type, float p_damage, int p_speed, int p_size) {
	position = p_position;
	type = p_type;
	damage = p_damage;
	speed = p_speed;
	size = p_size;
	id = p_id;

	rotation = player.rotation;
	VectorDirection = Vector2f(cos((rotation-90) / 57.2957795), sin((rotation - 90) / 57.2957795));
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
			object.collided(damage/(type+1));
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
	position += (VectorDirection)*speed;
}

void Bullet::draw() {
	bulletTextures[type].width = size;
	bulletTextures[type].height = size*1.75;
	DrawTexturePro(
		bulletTextures[type],
		Rectanglef(0,0, bulletTextures[type].width, bulletTextures[type].height), 
		Rectanglef(position.x, position.y, bulletTextures[type].width, bulletTextures[type].height), 
		Vector2f(bulletTextures[type].width, bulletTextures[type].height), 
		rotation, 
		WHITE);
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
		else if (type == 5) {
			gears.push_back(Gear(GearIdCount++));
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

void Shield::update() {
	end = std::chrono::high_resolution_clock::now();
	if ((end - start).count() / 10000000 > (100)*(4+3*upgrades[6])) {
		active = 0;
	}
}

void Shield::draw() {
	std::cout << sin(GetTime()) << std::endl;
	DrawTexture(shieldTexture, 
		player.position.x + player.size.x / 2 - size.x / 2, 
		player.position.y + player.size.y / 2 - size.y / 2, 
		Colorf(255, 255, 255, 100 * abs(sin(GetTime()))+50));
}

Gear::Gear(int p_id) {
	id = p_id;
	position = Vector2f(window_size.x/2-size.x/2, window_size.y + size.y / 2);
}

void Gear::draw() {
	int rot = floor(rotation / 10);
	gearTexture.width = size.x;
	gearTexture.height = size.y;
	DrawTexturePro(gearTexture, Rectanglef(0, 0, gearTexture.width, gearTexture.height), Rectanglef(position.x, position.y, size.x, size.y), Vector2f(size.x / 2, size.y / 2), rotation, WHITE);

}

void Gear::update() {
	position.y -= 2;
	rotation += 1;

	if (!(rotation % 10)) {
		for (int i : {0, 1, 2, 3, 4, 5, 6, 7}) {
			Vector2f dirVec = Vector2f(cos((i * 45 + rotation) * PI / 180.0), sin((i * 45 + rotation) * PI / 180.0));
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
			object.collided(10);
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

void RogueEnemy::update() {
	position.y += 15;



	if (position.y - size.y > window_size.y) {
		for (int i = 0; i < rogueEnemies.size(); i++) {
			if (rogueEnemies[i].id == id) {
				rogueEnemies.erase(rogueEnemies.begin() + i, rogueEnemies.begin() + i + 1);
				break;
			}
		}
	}
}

void RogueEnemy::draw() {
	rogueEnemyTexture.width = size.x;
	rogueEnemyTexture.height = size.y;

	DrawTexture(rogueEnemyTexture, position.x, position.y, WHITE);
}

void Explosion::update() {
	if (sCheckCollisionCircleTriangle(position + size.x / 2, size.x / 2, player.vertexies()) && !hit) {
		hit++;
		player.health -= 3;
	}

	end = std::chrono::high_resolution_clock::now();
	if ((end - start).count() / 1000000) {
		textureId++;
		if (textureId > 7) {
			for (int i = 0; i < explosions.size(); i++) {
				if (explosions[i].id == id) {
					explosions.erase(explosions.begin() + i, explosions.begin() + i + 1);
					break;
				}
			}
		}
		start = std::chrono::high_resolution_clock::now();
	}
}

void Explosion::draw() {
	DrawTexture(explosionTextures[textureId], position.x, position.y, WHITE);
}

void gameStart() {
	stage = 1;
	page = 1;
	gameRunning = 1;
	score = 0;
	for (int i = 0; i < 5; i++) asteroids.push_back(asteroidSpawn());
	player.health = maxHealth;

	player.position = Vector2f(window_size.x / 2 - player.size.x / 2, window_size.y - player.size.y - 10);
}