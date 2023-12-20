#pragma once

#include "classes.h"

#define window_size Vector2f(900, 1000)

int stage;
int difficulty;
int x = window_size.x;
int run;

std::chrono::time_point<std::chrono::steady_clock> upgradeEnd;
std::chrono::time_point<std::chrono::steady_clock> upgradeStart;
std::chrono::time_point<std::chrono::steady_clock> end;
std::chrono::time_point<std::chrono::steady_clock> start;
std::chrono::time_point<std::chrono::steady_clock> pstart;
std::chrono::time_point<std::chrono::steady_clock> tick;

Texture spaceship1;
Texture spaceship2;
Texture asteroid;
Font font;
Texture background;
Texture menuUI;
Texture shieldTexture;
Texture backButton;
Texture miniBulletTexture;
Texture logo;
Texture gearTexture;
std::vector<Texture> powerUPTextures;
std::vector<Texture> bulletTextures;
std::vector<Texture> healthTextures;

Player player(Vector2f(125, 125));
Window window(window_size, "Stellar Showdown", 60);

int BulletIdCount = 1;
int PowerUPIdCount = 1;
int GearIdCount = 1;
int MiniBulletIdCount = 1;

std::vector<Bullet> bullets = {};
std::vector<Asteroid> asteroids = {};
std::vector<Button> buttons;
std::vector<PowerUP> powerUPs;
std::vector<MiniBullet> miniBullets;
std::vector<Gear> gears;

int score = 0;
int bulletsize = 25;
int asteroidsize = 100;
int bulletType = 1;

/* Upgrades list:
* Red spaceship  : bought | reinforced | golden |
* Blue spaceship : bought | reinforced | golden |
* Ship health    : 10     | 11         | 12     |
* **************************************************
* No. Bullets    :                     1    | 2     | 3
* Bullet damage	 : type one damage   : 5    | 7.5   | 10
*				 : type two damage   : 2.5  | 3.75  | 5
*				 : type three damage : 1.25 | 1.875 | 2.5
* Fire rate		 :                     5b/s | 10b/s | 20b/s
* **************************************************
* Shield uptime  : 7s        | 10s       | 15s       |
* Rockets        : 2 rockets | 20 damage | 4 rockets | 30 damage
* Side turret    : 1 turret  | 3 damage  | 4 damage  | 2 turrets
*/

std::vector<int> upgrades{ 1, 0, 1, 1, 1, 1, 1, 1, 0};
bool shipSelected = 0;
float maxHealth = 10;
float firespeed = 5;
float damage = 5;
int shieldUptime = 7;
int rockets = 2;
int rocketDamage = 10;
int sideTurret = 0;
int TurretDamage = 2;

bool gameRunning;
int shopPage = 1;
int page = 0;

int highscore = 0;
float totalcoins = 99999;
