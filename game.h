#pragma once

#include "data.h"
#include <cmath>

float _fmax(float n1, float n2) {
	return n1 > n2 ? n1 : n2;
}

float _fmin(float n1, float n2) {
	return n1 < n2 ? n1 : n2;
}

float normalize(float rotation, int n_min, int n_max) {
	return _fmin(_fmax(rotation, n_min), n_max);
}

void rocketLaunch() {
	if (rocketsAvailable) {
		rocketsAvailable -= 2;
		
		rockets.push_back(Rocket(RocketIdCount++, player.position - Vector2f(75,150)/2 + Vector2f(player.size.x/2,0), player.rotation));
		rockets.push_back(Rocket(RocketIdCount++, player.position - Vector2f(75, 150) / 2 + Vector2f(player.size.x - player.size.x/4, 0), player.rotation));
	}
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
			Vector2f VectorDirection = Vector2f(cos((player.rotation - 90) / 57.2957795), sin((player.rotation - 90) / 57.2957795)) * -1;
			bullets.emplace_back(Bullet(BulletIdCount++,
				Vector2f(
				player.position.x + player.size.x / 2 + bulletTextures[0].width  / 2 * VectorDirection.y,
				player.position.y + player.size.y / 2 - bulletTextures[0].height / 3 * VectorDirection.x) 
				- player.size/2.2 * VectorDirection,
				bulletType,
				damage));
		}

		if (upgrades[3] > 1) {
			Vector2f VectorDirection1 = Vector2f(cos((player.rotation - 210) / 57.2957795), sin((player.rotation - 210) / 57.2957795)) * -1;
			Vector2f VectorDirection2 = Vector2f(cos((player.rotation + 30) / 57.2957795), sin((player.rotation + 30) / 57.2957795)) * -1;
			bullets.emplace_back(Bullet(BulletIdCount++,
				Vector2f(
				player.position.x + player.size.x / 2 + bulletTextures[0].width / 2 * VectorDirection1.y,
				player.position.y + player.size.y / 2 - bulletTextures[0].height / 3 * VectorDirection1.x
				) - player.size / 8 * VectorDirection1,
				bulletType,
				damage));
			bullets.emplace_back(Bullet(BulletIdCount++,
				Vector2f
				(
				player.position.x + player.size.x / 2 + bulletTextures[0].width / 2 * VectorDirection2.y,
				player.position.y + player.size.y / 2 - bulletTextures[0].height / 3 * VectorDirection2.x
				) 
				- player.size / 2.4 * VectorDirection2,
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

	Vector2f c1 = vertexes[0] - center;
	Vector2f c2 = vertexes[1] - center;
	Vector2f c3 = vertexes[2] - center;

	c1.x = center.x - vertexes[0].x;
	c1.y = center.y - vertexes[0].y;

	float radiusSqr = radius * radius;
	float c1sqr = c1.x * c1.x + c1.y * c1.y - radiusSqr;

	if (c1sqr <= 0)
		return true;

	c2.x = center.x - vertexes[1].x;
	c2.y = center.y - vertexes[1].y;
	float c2sqr = c2.x * c2.x + c2.y * c2.y - radiusSqr;

	if (c2sqr <= 0)
		return true;

	c3.x = center.x - vertexes[2].x;
	c3.y = center.y - vertexes[2].y;

	float& c3sqr = radiusSqr;
	c3sqr = c3.x * c3.x + c3.y * c3.y - radiusSqr;

	if (c3sqr <= 0)
		return true;
	
	for (auto vertex : vertexes) {
		double distance = sqrt(pow(center.x - vertex.x, 2) + pow(center.y - vertex.y, 2));
		if (distance <= radius) {
			return true;
		}
	}
	return false;
}

void endGame() {
	totalcoins += score;
	gameRunning = 0;
	page = 0;
	
	rockets = {};
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
	DrawTexturePro(spaceshipTexture[shipSelected], Rectanglef(0, 0, 125, 125), Rectanglef(position.x + size.x / 2, position.y + size.y / 2, size.x, size.y), Vector2f(size.x / 2, size.y / 2), rotation, WHITE);
}

void Player::move(Vector2f vector) {
	if (position.x + (vector.x * speed) > 0 and position.x + (vector.x * speed) < window_size.x - size.x and position.y + (vector.y * speed) > 0 and position.y + (vector.y * speed) < window_size.y - size.y) {
		position += vector * speed;
	}
}

Asteroid::Asteroid(Vector2f p_position, Vector2f p_size, int p_type, int p_speed, int p_health = 10) {
	position = p_position;
	size = p_size;
	type = p_type;
	health = p_health;
	speed = p_speed;

	vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
}

void Asteroid::update() {
	if (position.x < -size.x or position.x > window_size.x or position.y > window_size.y) {
		position = Vector2f(dis(gen), -(dis(gen) % 100) - size.y);
		type = dis(gen) % 3;
		health = 10 + stage * 2;
		vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
		shock = 0;
		acid = 0;
	}

	end = std::chrono::high_resolution_clock::now();
	if ((acid or shock) and (end - start).count() / 10000000 > 50) {
		health -= acid + shock;
		start = std::chrono::high_resolution_clock::now();

		if (health < 1) {
			position = Vector2f(dis(gen), -(dis(gen) % 100) - size.y);
			vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
			type = dis(gen) % 3;
			health = 10 + stage * 2;
			score++;
			shock = 0;
			acid = 0;
		}
	}

	if (sCheckCollisionCircles(player.position + size / 2, shield.size.x / 2, position + size / 2, size.x / 2) && shield.active) {
		position = Vector2f(dis(gen), -(dis(gen) % 100) - size.y);
		type = dis(gen) % 3;
		health = 10 + stage * 2;
		vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
		shock = 0;
		acid = 0;
	}

	if (sCheckCollisionCircleTriangle(position + size/2, size.x/2, player.vertexies())) {
		player.health -= (int)size.x / 75;

		if (type == 2) {
			explosions.push_back(Explosion(ExplosionIdCount++, position-size/2, size));
		}

		shaking = 1;

		position = Vector2f(dis(gen), dis(gen) % 100 - size.y);
		vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
		type = dis(gen) % 3;
		health = 10+stage*2;
		shock = 0;
		acid = 0;
	}

	position += vector * speed;
}

void Asteroid::collided(float p_damage, bool p_acid, bool p_shock) {
	health -= p_damage;
	acid += p_acid;
	shock += p_shock;

	if (type == 2) {
		explosions.push_back(Explosion(ExplosionIdCount++, position-size/2, size));
	}

	if (health < 1) {
		position = Vector2f(dis(gen), -(dis(gen) % 100) - size.y);
		vector = Vector2f(((double)(dis(gen) % 10) - (dis(gen) % 10)) / 10, 1);
		type = dis(gen) % 3;
		health = 10 + stage * 2;
		score++;
		shock = 0;
		acid = 0;
	}

}

void Asteroid::draw() {
	asteroid.width = size.x;
	asteroid.height = size.y;
	DrawTexture(asteroid, position.x, position.y, shock ? BLUE : acid ? LIME : (type == 2) ? RED : WHITE);
}

Asteroid asteroidSpawn() {
	int random = dis(gen);
	Asteroid ast = Asteroid(Vector2f(dis(gen), -(dis(gen) % 300)), Vector2f(asteroidsize, asteroidsize) * ((random % 2) ? 1 : 1.25), random % 3, random % 2 ? 10 : 5, random % 2 ? 10 : 15);
	return ast;
}

Bullet::Bullet(int p_id, Vector2f p_position, int p_type, float p_damage, int p_speed, int p_size) {
	rotation = player.rotation;
	VectorDirection = Vector2f(cos((rotation - 90) / 57.2957795), sin((rotation - 90) / 57.2957795));

	position = p_position;
	type = p_type;
	damage = p_damage;
	speed = p_speed;
	size = p_size;
	id = p_id;
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
			object.collided(damage / ((type) ? 2 : 1), type == 1 ? rand() % 2 : 0, shipSelected ? rand() % 2 : 0);
		}
	}

	for (Explosion& explosion : explosions) {
		if (CheckCollisionRecs(Rectanglef(position.x, position.y, size, size), Rectanglef(explosion.position.x, explosion.position.y, explosion.size.x, explosion.size.y))) {
			collided = 1;
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

	if (type == 2) {
		rotation += normalize(bearing(position + size / 2, Vector2f(GetMouseX(), GetMouseY())), 10, -10);

		VectorDirection = Vector2f(cos(rotation * DEG2RAD), sin(rotation * DEG2RAD));
	}

	position += (VectorDirection)*speed;
}

void Bullet::draw() {

	DrawTexturePro(
		bulletTextures[type],
		Rectanglef(0,0, bulletTextures[0].width, bulletTextures[0].height),
		Rectanglef(position.x, position.y, bulletTextures[0].width, bulletTextures[0].height),
		Vector2f(bulletTextures[0].width, bulletTextures[0].height),
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
	if (active) {
		end = std::chrono::high_resolution_clock::now();
		if ((end - start).count() / 10000000 > (100) * (4 + 3 * upgrades[6])) {
			damage -= 5 * strength * (!type);
			firespeed -= 2.5 * strength * type;
			for (int i = 0; i < powerUPs.size(); i++) {
				if (powerUPs[i].id == id) {
					powerUPs.erase(powerUPs.begin() + i, powerUPs.begin() + i + 1);
					break;
				}
			}
		}
		
	}
	else {
		position += Vector2f(0, 10);

		if (CheckCollisionRecs(Rectanglef(position.x, position.y, size.x, size.y), Rectanglef(player.position.x, player.position.y, player.size.x, player.size.y))) {
			if (type == 0) {
				damage += 5 * strength;
				start = std::chrono::high_resolution_clock::now();
				end = std::chrono::high_resolution_clock::now();
			}
			else if (type == 1) {
				firespeed += 2.5 * strength;
				start = std::chrono::high_resolution_clock::now();
				end = std::chrono::high_resolution_clock::now();
			}
			else if (type == 2) {
				player.health += 10 * strength;
			}
			else if (type == 3) {
				rocketsAvailable += 2 * upgrades[3];
			}
			else if (type == 4) {
				summonShield();
			}
			else if (type == 5) {
				gears.push_back(Gear(GearIdCount++));
			}
			active++;
		}
	}
}

void PowerUP::draw() {
	if (!active) {
		DrawTexture(powerUPTextures[type], position.x, position.y, WHITE);
	}
}

void Shield::update() {
	end = std::chrono::high_resolution_clock::now();
	if ((end - start).count() / 10000000 > (100)*(4+3*upgrades[6])) {
		active = 0;
	}
}

void Shield::draw() {
	DrawTexture(shieldTexture, 
		player.position.x + player.size.x / 2 - size.x / 2, 
		player.position.y + player.size.y / 2 - size.y / 2, 
		Colorf(255, 255, 255, 100 * abs(sin(GetTime()))+50));
}

Gear::Gear(int p_id) {
	id = p_id;
	position = Vector2f(window_size.x/2, window_size.y + size.y / 2);
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

MiniBullet::MiniBullet(int p_id, Vector2f p_position, Vector2f p_directionVector, int p_damage, int p_speed) {
	id = p_id;
	directionVector = p_directionVector;
	position = p_position+size/4;
	speed = p_speed;
	damage = p_damage;
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

	if (CheckCollisionCircleRec(player.position + player.size / 2, player.size.x / 2, Rectf(position.x + size.x / 2 - 7, position.y, 14, size.y)) && !shield.active) {
		shaking = 1;
		player.health -= 3;
		for (int i = 0; i < rogueEnemies.size(); i++) {
			if (rogueEnemies[i].id == id) {
				rogueEnemies.erase(rogueEnemies.begin() + i, rogueEnemies.begin() + i + 1);
				break;
			}
		}
	}

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
	if (friendly) {
		for (Asteroid& astroid : asteroids) {
			if (sCheckCollisionCircleTriangle(position + size.x / 2, size.x / 2, player.vertexies()) && !hit) {
				astroid.collided(upgrades[7]);
			}
		}
	}
	else {
		if (sCheckCollisionCircleTriangle(position + size.x / 2, size.x / 2, player.vertexies()) && !hit) {
			hit++;
			player.health -= 3;
		}
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
	explosionTextures[textureId].width = size.x;
	explosionTextures[textureId].height = size.y;
	DrawTexture(explosionTextures[textureId], position.x, position.y, WHITE);
}

Rocket::Rocket(int p_id, Vector2f p_position, int p_rotation) {
	position = p_position;
	id = p_id;
	rotation = p_rotation;
	damage = 10 + (int)upgrades[7] / 2;
}

void Rocket::update() {
	rotation += normalize(bearing(position + size/2, Vector2f(GetMouseX(), GetMouseY())) * -1 - rotation, -2,2);

	for (Asteroid& asteroid : asteroids) {
		if (CheckCollisionCircleRec(asteroid.position + asteroid.size/2, asteroid.size.x / 2, Rectf(position.x, position.y, size.x, size.y))) {
			for (int i = 0; i < rockets.size(); i++) {
				if (rockets[i].id == id) {
					asteroid.collided((int)((upgrades[7]) / 2) * 10 + 10);
					explosions.push_back(Explosion(ExplosionIdCount++, position, Vector2f(150, 150), 1));
					rockets.erase(rockets.begin() + i, rockets.begin() + i + 1);
					break;
				}
			}
		}
	}

	position += Vector2f(sin(rotation * DEG2RAD), cos(rotation * DEG2RAD)*-1) * 10;
}

void Rocket::draw() {
	rocketTexture.width = size.x;
	rocketTexture.height = size.y;
	DrawTexturePro(rocketTexture, Rectf(0, 0, rocketTexture.width, rocketTexture.height), Rectf(position.x + size.x/2, position.y + size.y, size.x/2, size.y/2), Vector2f(size.x/2, size.y/2), rotation, WHITE);
}

void gameStart() {
	shaking = 0;
	shakeDegree = 0;
	inc = 0;
	stage = 0;
	page = 1;
	gameRunning = 1;
	rocketsAvailable = upgrades[7];
	score = 0;
	for (int i = 0; i < 5; i++) asteroids.push_back(asteroidSpawn());
	player.health = maxHealth;

	player.position = Vector2f(window_size.x / 2 - player.size.x / 2, window_size.y - player.size.y - 10);
}

void SideTurret::draw() {
	sideTurretTexture.width = size.x;
	sideTurretTexture.height = size.y;
	DrawTexturePro(sideTurretTexture, Rectf(0,0, sideTurretTexture.width, sideTurretTexture.height), Rectf(position.x, position.y, size.x, size.y), size/2, 180, WHITE);
}

void SideTurret::update() {
	position = player.position + Vector2f(((side == 0) ? -1 * player.size.x/2 : 1.5 * player.size.x), player.size.y/2);
	if ((end - start).count() / (1000000000 / ((float)(upgrades[5]) * 2.5 + 2.5)) >= 1) {
		miniBullets.push_back(MiniBullet(MiniBulletIdCount++, position + (Vector2f(0, 1) * size / 2) * 0.9 - Vector2f(0,size.y/2), Vector2f(0, -1), ((upgrades[8] == 1) ? 2 : (upgrades[8] == 2) ? 2 : 3), 20));
		start = std::chrono::high_resolution_clock::now();
	}
	end = std::chrono::high_resolution_clock::now();
}