#pragma once

#include "game.h"

bool Button::update() {
	if (clicked(MOUSE_LEFT_BUTTON)) {
		borderColor = GOLD;
		return 1;
	}
	if (hovered()) {
		borderColor = GOLD;
		return false;
	}
	else {
		if (!(text == "MAX")) borderColor = GRAY;
		return false;
	}
}

void Button::draw() {
	DrawRectangle(position.x, position.y, size.x, size.y, borderColor);
	DrawRectangle(position.x + border, position.y + border, size.x - 2 * border, size.y - 2 * border, color);
	DrawText(text.c_str(), (position.x + size.x / 2) - MeasureText(text.c_str(), fontSize) / 2, (position.y + size.y / 2) - fontSize / 2, fontSize, textColor);
}

bool Button::clicked(int key) {
	return IsMouseButtonReleased(key) and CheckCollisionRecs(Rectanglef(GetMouseX(), GetMouseY(), 1, 1), Rectanglef(position, size));
}

bool Button::hovered() {
	return CheckCollisionRecs(Rectanglef(GetMouseX(), GetMouseY(), 1, 1), Rectanglef(position, size));
}

bool ImageButton::update() {
	if (clicked(MOUSE_LEFT_BUTTON)) {
		borderColor = GOLD;
		color = LIGHTGRAY;
		return 1;
	}
	if (hovered()) {
		borderColor = GOLD;
		return false;
	}
	else {
		borderColor = GRAY;
		return false;
	}
}

void ImageButton::draw() {
	DrawRectangle(position.x, position.y, size.x, size.y, borderColor);
	DrawRectangle(position.x + border, position.y + border, size.x - 2 * border, size.y - 2 * border, color);
	texture.width = imageSize.x;
	texture.height = imageSize.y;
	DrawTexture(texture, position.x + size.x / 2 - texture.width/2, position.y + size.y / 2 - texture.height/2, WHITE);
}

bool ImageButton::clicked(int key) {
	return IsMouseButtonDown(key) and CheckCollisionRecs(Rectanglef(GetMouseX(), GetMouseY(), 1, 1), Rectanglef(position, size));
}

bool ImageButton::hovered() {
	return CheckCollisionRecs(Rectanglef(GetMouseX(), GetMouseY(), 1, 1), Rectanglef(position, size));
}

void menu() {
	Button play(Vector2f(window_size.x/2, window_size.y) / 2, "PLAY", Vector2f(500, 150), 80, 10, WHITE, GRAY, GRAY);
	Button shop(Vector2f(window_size.x / 2, window_size.y + 325) / 2, "Shop", Vector2f(250-7, 150), 60, 10, WHITE, GRAY, GRAY);
	Button settings(Vector2f(window_size.x / 2 + 515, window_size.y + 325) / 2, "Help", Vector2f(250-7, 150), 60, 10, WHITE, GRAY, GRAY);

	DrawTexture(logo, window_size.x / 4, 0, WHITE);

	if (play.update()) {
		gameStart();
	}
	if (settings.update()) {
		page = 3;
	}
	if (shop.update()) {
		page = 2;
	}

	play.draw();
	settings.draw();
	shop.draw();
}

void shop() {
	Button ship     (Vector2f(25 , 86), "Ship"     , Vector2f(275, 100), 64, 5, WHITE, GRAY, GRAY);
	Button equipment(Vector2f(315, 86), "Equipment", Vector2f(275, 100), 48, 5, WHITE, GRAY, GRAY);
	Button secondary(Vector2f(605, 86), "Secondary", Vector2f(275, 100), 48, 5, WHITE, GRAY, GRAY);

	ImageButton upgrade1(Vector2f(75, 350), Texture(), Vector2f(150, 150), Vector2f(125, 125), 5, WHITE, GRAY);
	ImageButton upgrade2(Vector2f(75, 550), Texture(), Vector2f(150, 150), Vector2f(125, 125), 5, WHITE, GRAY);
	ImageButton upgrade3(Vector2f(75, 750), Texture(), Vector2f(150, 150), Vector2f(125, 125), 5, WHITE, GRAY);

	std::string upgrade1Title = "";
	std::string upgrade2Title = "";
	std::string upgrade3Title = "";
	std::string upgrade1Description = "";
	std::string upgrade2Description = "";
	std::string upgrade3Description = "";
	std::string cost1 = "MAX";
	std::string cost2 = "MAX";
	std::string cost3 = "MAX";

	Button buy1(Vector2f(235, 450), "MAX", Vector2f(100, 50), 24, 4, WHITE, GOLD, GOLD);
	Button buy2(Vector2f(235, 650), "MAX", Vector2f(100, 50), 24, 4, WHITE, GOLD, GOLD);
	Button buy3(Vector2f(235, 850), "MAX", Vector2f(100, 50), 24, 4, WHITE, GOLD, GOLD);
	
	DrawRectangle(25, 200, 855, 775, GRAY);
	DrawRectangle(30, 205, 845, 765, WHITE);

	std::string string = std::to_string((int)totalcoins);
	
	using namespace std::literals::string_literals;
	DrawText((string + "c"s).c_str(), 865-MeasureText((string + "c"s).c_str(), 48), 215, 48, GOLD);
	if (sCheckCollisionCircles(Vector2f(GetMouseX(), GetMouseY()), 1, Vector2f(25 + 75 / 2, 5 + 75 / 2), (int)75 / 2) and IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		page = 0;
		applyShop();
	}

	DrawTexture(backButton, 25, 5, WHITE);

	if (shopPage == 3) {
		DrawText("Secondary", 50, 215, 64, GRAY);

		upgrade1.texture = spaceship1;
		upgrade2.texture = spaceship2;
		upgrade3.texture = powerUPTextures[2];

		upgrade1Title = "Shield duration";
		upgrade2Title = "Rockets";
		upgrade3Title = "Side turret";

		upgrade1Description = "Increase shield uptime.";
		upgrade2Description = "Improve rocket damage and count.";
		upgrade3Description = "Turrets that shoot independently";

		if (upgrades[6] < 3) {
			cost1 = std::to_string(upgrades[6] * 1250) + "c";
			if (buy1.update() && totalcoins >= upgrades[6] * 1250) {
				upgrades[6]++;
				totalcoins -= upgrades[6] * 1250;
			}
		}
		if (upgrades[7] < 3) {
			cost2 = std::to_string(upgrades[7] * 700) + "c";
			if (buy2.update() && totalcoins >= upgrades[7] * 700) {
				upgrades[7]++;
				totalcoins -= upgrades[7] * 700;
			}
		}
		if (upgrades[8] < 4) {
			cost3 = std::to_string(upgrades[8] * 300 + 300) + "c";
			if (buy3.update() && totalcoins >= upgrades[8] * 300 + 300) {
				upgrades[8]++;
				totalcoins -= upgrades[8] * 300 + 300;
			}
		}
	}
	else if (shopPage == 2) {
		DrawText("Equipment", 50, 215, 64, GRAY);

		upgrade1.texture = bulletTextures[0];
		upgrade1.imageSize = Vector2f(35, 75);
		upgrade2.texture = spaceship2;
		upgrade3.texture = powerUPTextures[2];

		upgrade1Title = "Number of bullets";
		upgrade2Title = "Bullet damage";
		upgrade3Title = "Fire speed";

		upgrade1Description = "Increase number of bullets per shot.";
		upgrade2Description = "Increase damage of bullets shot.";
		upgrade3Description = "Increase bullets per second.";

		if (upgrades[3] < 3) {
			cost1 = std::to_string(upgrades[3] * 1500) + "c";
			if (buy1.update() && totalcoins >= upgrades[3] * 1500) {
				upgrades[3]++; 
				totalcoins -= upgrades[3] * 1500;
			}
		}
		if (upgrades[4] < 3) {
			cost2 = std::to_string(upgrades[4] * 500) + "c";
			if (buy2.update() && totalcoins >= upgrades[4] * 500) {
				upgrades[4]++; 
				totalcoins -= upgrades[4] * 500;
			}
		}
		if (upgrades[5] < 3) {
			cost3 = std::to_string(upgrades[5] * 350) + "c";
			if (buy3.update() && totalcoins >= upgrades[5] * 350) {
				upgrades[5]++; 
				totalcoins -= upgrades[5] * 350;
			}
		}
	}
	else if (shopPage == 1) {
		DrawText("Ships", 50, 215, 64, GRAY);

		upgrade1.texture = spaceship1;
		upgrade2.texture = spaceship2;
		upgrade3.texture = powerUPTextures[2];
		upgrade3.imageSize = Vector2f(100, 65);

		upgrade1Title = "Red spaceship";
		upgrade2Title = "Blue spaceship";
		upgrade3Title = "Max health";

		upgrade1Description = "Default ship.";
		upgrade2Description = "Chance to do shock damage.";
		upgrade3Description = "Increase Maximuim health.";

		if (upgrades[0] < 3) {
			cost1 = std::to_string(upgrades[0] * 1000) + "c";
			if (buy1.update() && totalcoins >= upgrades[0] * 1000) {
				upgrades[0]++;
				totalcoins -= upgrades[0] * 1000;
			}
		}
		if (upgrades[1] < 3) {
			cost2 = std::to_string(upgrades[1] * 1000 + 500) + "c";
			if (buy2.update() && totalcoins >= upgrades[1] * 1000 + 500) {
				upgrades[1]++;
				totalcoins -= upgrades[1] * 1000 + 500;
			}
		}
		if (upgrades[2] < 3) {
			cost3 = std::to_string(upgrades[2] * 500) + "c";
			if (buy3.update() && totalcoins >= upgrades[2] * 500) {
				upgrades[2]++;
				totalcoins -= upgrades[2] * 500;
			}
		}
	}

	DrawText(upgrade1Title.c_str(), 235, 350, 48, GRAY);
	DrawText(upgrade2Title.c_str(), 235, 550, 48, GRAY);
	DrawText(upgrade3Title.c_str(), 235, 750, 48, GRAY);
	DrawText(upgrade1Description.c_str(), 235, 400, 32, LIGHTGRAY);
	DrawText(upgrade2Description.c_str(), 235, 600, 32, LIGHTGRAY);
	DrawText(upgrade3Description.c_str(), 235, 800, 32, LIGHTGRAY);

	buy1.text = (cost1);
	buy2.text = (cost2);
	buy3.text = (cost3);

	buy1.draw();
	buy2.draw();
	buy3.draw();

	DrawRectangle(50, 285, 200, 5, GRAY);

	if (ship.update() + equipment.update() + secondary.update()) 
		shopPage = (ship.update()) + (equipment.update()*2) + (secondary.update()*3);

	upgrade1.draw();
	upgrade2.draw();
	upgrade3.draw();
	ship.draw();
	equipment.draw();
	secondary.draw();
}