#pragma once

#include "game.h"

bool Button::update(bool style) {
	if (style) {
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
}

void Button::draw() {
	buttonTextures[5].width = size.x;
	buttonTextures[5].height = size.y;
	DrawTexture(buttonTextures[5], position.x, position.y, WHITE);
	DrawTextEx(font, text.c_str(), Vector2f((position.x + size.x / 2) - MeasureTextEx(font, text.c_str(), fontSize, 0).x/2, (position.y + size.y / 2) - MeasureTextEx(font, text.c_str(), fontSize, 0).y / 2), fontSize, 0, textColor);
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
	buttonTextures[4].width = size.x;
	buttonTextures[4].height = size.y;
	DrawTexture(buttonTextures[4], position.x, position.y, WHITE);
	texture.width = imageSize.x;
	texture.height = imageSize.y;
	DrawTexture(texture, position.x + size.x / 2 - texture.width/2, position.y + size.y / 2 - texture.height/2, tint);
}

bool ImageButton::clicked(int key) {
	return IsMouseButtonDown(key) and CheckCollisionRecs(Rectanglef(GetMouseX(), GetMouseY(), 1, 1), Rectanglef(position, size));
}

bool ImageButton::hovered() {
	return CheckCollisionRecs(Rectanglef(GetMouseX(), GetMouseY(), 1, 1), Rectanglef(position, size));
}

void menu() {

	DrawTexture(logo, window_size.x * 2 / 5, 0, WHITE);
	buttonTextures[0].width = 300;
	buttonTextures[0].height = 100;
	DrawTexture(buttonTextures[0], 20, 400, WHITE);
	Vector2f textSize = Vector2f(MeasureTextEx(font, "PLAY", 64, 0).x, MeasureTextEx(font, "PLAY", 64, 0).y);
	DrawTextEx(font, "PLAY", Vector2f(20, 400) + Vector2f(300, 100)/2 - Vector2f(textSize.x, textSize.y)/2, 64, 0, SKYBLUE);
	buttonTextures[0].width = 250;
	buttonTextures[0].height = 85;
	DrawTexture(buttonTextures[0], 20, 510, WHITE);
	textSize = Vector2f(MeasureTextEx(font, "Shop", 64, 0).x, MeasureTextEx(font, "Shop", 64, 0).y);
	DrawTextEx(font, "Shop", Vector2f(20, 510) + Vector2f(250, 85) / 2 - Vector2f(textSize.x, textSize.y) / 2, 64, 0, SKYBLUE);
	buttonTextures[0].width = 250;
	buttonTextures[0].height = 85;
	DrawTexture(buttonTextures[0], 20, 605, WHITE);
	textSize = Vector2f(MeasureTextEx(font, "Help", 64, 0).x, MeasureTextEx(font, "Help", 64, 0).y);
	DrawTextEx(font, "Help", Vector2f(20, 605) + Vector2f(250, 85) / 2 - Vector2f(textSize.x, textSize.y) / 2, 64, 0, SKYBLUE);
	buttonTextures[0].width = 200;
	buttonTextures[0].height = 80;
	DrawTexture(buttonTextures[0], 20, 700, WHITE);
	textSize = Vector2f(MeasureTextEx(font, "Quit", 64, 0).x, MeasureTextEx(font, "Quit", 64, 0).y);
	DrawTextEx(font, "Quit", Vector2f(20, 700) + Vector2f(200, 80) / 2 - Vector2f(textSize.x, textSize.y) / 2, 64, 0, SKYBLUE);

	if (CheckCollisionPointRec(GetMousePosition(), Rectf(20, 400, 300, 100)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		gameStart();
	}
	if (CheckCollisionPointRec(GetMousePosition(), Rectf(20, 510, 250, 85)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		page = 2;
	}
	if (CheckCollisionPointRec(GetMousePosition(), Rectf(20, 605, 250, 85)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		page = 3;
	}
	if (CheckCollisionPointRec(GetMousePosition(), Rectf(20, 700, 200, 80)) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		exit(0);
	}
}

void shop() {
	Button ship     (Vector2f(25 , 86), "Ship"     , Vector2f(275, 100), 64, 5, WHITE, SKYBLUE, GRAY);
	Button equipment(Vector2f(315, 86), "Equipment", Vector2f(275, 100), 48, 5, WHITE, SKYBLUE, GRAY);
	Button secondary(Vector2f(605, 86), "Secondary", Vector2f(275, 100), 48, 5, WHITE, SKYBLUE, GRAY);

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

	CheckCollisionPointRec(GetMousePosition(), Rectf(235, 850, 50, 50));
	
	DrawRectangle(25, 200, 855, 775, Colorf(56,64,73));
	DrawRectangle(30, 205, 845, 765, Colorf(8,72,107));

	inc++;

	for (int i = 0; i < 845/20; i++) {
		DrawRectangle(30, 205 + (inc + i * 20) % 765, 845, 5, Colorf(102,191,255,32));
	}

	buttonTextures[3].width = 50;
	buttonTextures[3].height = 50;

	DrawTexture(buttonTextures[3], 235, 450, WHITE);
	DrawTexture(buttonTextures[3], 235, 650, WHITE);
	DrawTexture(buttonTextures[3], 235, 850, WHITE);

	std::string string = std::to_string((int)totalcoins);
	
	using namespace std::literals::string_literals;
	DrawTextEx(font, (string + "c"s).c_str(), Vector2f(865-MeasureTextEx(font, (string + "c"s).c_str(), 64, 0).x, 215), 64, 0, GOLD);
	if (sCheckCollisionCircles(Vector2f(GetMouseX(), GetMouseY()), 1, Vector2f(25 + 75 / 2, 5 + 75 / 2), (int)75 / 2) and IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		page = 0;
		applyShop();
		inc = 0;
	}

	buttonTextures[1].width = 70;
	buttonTextures[1].height = 70;
	DrawTexture(buttonTextures[1], 25, 5, WHITE);

	if (shopPage == 3) {
		DrawText("Secondary", 50, 215, 64, GRAY);

		upgrade1.texture = powerUPTextures[4];
		upgrade2.texture = rocketTexture;
		upgrade3.texture = sideTurretTexture;
		upgrade1.imageSize = Vector2f(100, 65);
		upgrade2.imageSize = Vector2f(55, 100);
		upgrade3.imageSize = Vector2f(100, 125);

		upgrade1Title = "Shield duration";
		upgrade2Title = "Rockets";
		upgrade3Title = "Side turret";

		upgrade1Description = "Increase shield uptime.";
		upgrade2Description = "Improve rocket damage and count.";
		upgrade3Description = "Turrets that shoot independently";

		if (upgrades[6] < 3) {
			cost1 = std::to_string(upgrades[6] * 1250) + "c";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 450, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && totalcoins >= upgrades[6] * 1250) {
				totalcoins -= upgrades[6] * 1250;
				upgrades[6]++;
			}
		}
		if (upgrades[7] < 4) {
			cost2 = std::to_string(upgrades[7] * 700) + "c";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 650, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && totalcoins >= upgrades[7] * 700) {
				totalcoins -= upgrades[7] * 700;
				upgrades[7]++;
			}
		}
		if (upgrades[8] < 4) {
			cost3 = std::to_string(upgrades[8] * 300 + 300) + "c";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 850, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && totalcoins >= upgrades[8] * 300 + 300) {
				totalcoins -= upgrades[8] * 300 + 300;
				upgrades[8]++;
			}
		}
	}
	else if (shopPage == 2) {
		DrawText("Equipment", 50, 215, 64, GRAY);

		upgrade1.texture = bulletTextures[0];
		upgrade1.imageSize = Vector2f(35, 75);
		upgrade2.texture = explosionTextures[7];
		upgrade3.texture = fireSpeedIcon;
		upgrade3.imageSize = Vector2f(75, 75);

		upgrade1Title = "Number of bullets";
		upgrade2Title = "Bullet damage";
		upgrade3Title = "Fire speed";

		upgrade1Description = "Increase number of bullets per shot.";
		upgrade2Description = "Increase damage of bullets shot.";
		upgrade3Description = "Increase bullets per second.";

		if (upgrades[3] < 3) {
			cost1 = std::to_string(upgrades[3] * 1500) + "c";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 450, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && totalcoins >= upgrades[3] * 1500) {
				totalcoins -= upgrades[3] * 1500;
				upgrades[3]++;
			}
		}
		if (upgrades[4] < 3) {
			cost2 = std::to_string(upgrades[4] * 500) + "c";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 650, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && totalcoins >= upgrades[4] * 500) {
				totalcoins -= upgrades[4] * 500;
				upgrades[4]++;
			}
		}
		if (upgrades[5] < 3) {
			cost3 = std::to_string(upgrades[5] * 350) + "c";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 850, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && totalcoins >= upgrades[5] * 350) {
				totalcoins -= upgrades[5] * 350;
				upgrades[5]++;
			}
		}
	}
	else if (shopPage == 1) {
		DrawText("Ships", 50, 215, 64, GRAY);

		upgrade1.texture = spaceshipTexture[0];
		upgrade2.texture = spaceshipTexture[1];
		upgrade3.texture = powerUPTextures[2];
		upgrade3.imageSize = Vector2f(100, 65);

		upgrade1Title = "Red spaceship";
		upgrade2Title = "Blue spaceship";
		upgrade3Title = "Max health";

		upgrade1Description = "Default ship.";
		upgrade2Description = "Chance to do shock damage.";
		upgrade3Description = "Increase Maximuim health.";

		if (!shipSelected) {
			cost1 = "USED";
		}
		else {
			cost1 = "USE";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 450, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				shipSelected = 0;
			}
		}
		if (!upgrades[1]) {
			cost2 = std::to_string(upgrades[1] * 1000 + 500) + "c";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 650, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && totalcoins >= upgrades[1] * 1000 + 500) {
				totalcoins -= upgrades[1] * 1000 + 500;
				upgrades[1]++;
			}
		}
		else {
			if (shipSelected) {
				cost2 = "USED";
			}
			else {
				cost2 = "USE";
				if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 650, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					shipSelected = 1;
				}
			}
		}
		if (upgrades[2] < 3) {
			cost3 = std::to_string(upgrades[2] * 500) + "c";
			if (CheckCollisionPointRec(GetMousePosition(), Rectf(235, 850, 50, 50)) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && totalcoins >= upgrades[2] * 500) {
				totalcoins -= upgrades[2] * 500;
				upgrades[2]++;
			}
		}
	}

	DrawText(upgrade1Title.c_str(), 235, 350, 48, DARKBLUE);
	DrawText(upgrade2Title.c_str(), 235, 550, 48, BLUE);
	DrawText(upgrade3Title.c_str(), 235, 750, 48, SKYBLUE);
	DrawText(upgrade1Description.c_str(), 235, 400, 32, LIGHTGRAY);
	DrawText(upgrade2Description.c_str(), 235, 600, 32, LIGHTGRAY);
	DrawText(upgrade3Description.c_str(), 235, 800, 32, LIGHTGRAY);
	DrawTextEx(font, cost1.c_str(), Vector2f(290, 450), 48, 0, GOLD);
	DrawTextEx(font, cost2.c_str(), Vector2f(290, 650), 48, 0, GOLD);
	DrawTextEx(font, cost3.c_str(), Vector2f(290, 850), 48, 0, GOLD);

	DrawRectangle(50, 285, 200, 5, GRAY);

	if (ship.update(1) + equipment.update(1) + secondary.update(1)) 
		shopPage = (ship.update(1)) + (equipment.update(1)*2) + (secondary.update(1)*3);

	upgrade1.draw();
	upgrade2.draw();
	upgrade3.draw();
	ship.draw();
	equipment.draw();
	secondary.draw();
}

void help() {

}