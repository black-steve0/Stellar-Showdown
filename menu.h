#pragma once

#include "game.h"

bool Button::update(void) {
	if (clicked(MOUSE_LEFT_BUTTON)) {
		borderColor = GOLD;
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

void Button::draw() {
	DrawRectangle(position.x, position.y, size.x, size.y, borderColor);
	DrawRectangle(position.x + border, position.y + border, size.x - 2 * border, size.y - 2 * border, color);
	DrawText(text, (position.x + size.x / 2) - MeasureText(text, fontSize) / 2, (position.y + size.y / 2) - fontSize / 2, fontSize, textColor);
}

bool Button::clicked(int key) {
	return IsMouseButtonReleased(key) and CheckCollisionRecs(Rectangle(GetMouseX(), GetMouseY(), 1, 1), Rectangle(position, size));
}

bool Button::hovered() {
	return CheckCollisionRecs(Rectangle(GetMouseX(), GetMouseY(), 1, 1), Rectangle(position, size));
}

void menu() {
	Button play(Vector2(window_size.x/2, window_size.y) / 2, "PLAY", Vector2(500, 150), 80, 10, WHITE, GRAY, GRAY);
	Button shop(Vector2(window_size.x / 2, window_size.y + 325) / 2, "Shop", Vector2(250-7, 150), 60, 10, WHITE, GRAY, GRAY);
	Button settings(Vector2(window_size.x / 2 + 515, window_size.y + 325) / 2, "Help", Vector2(250-7, 150), 60, 10, WHITE, GRAY, GRAY);

	std::string scoreText = "Score: ";
	DrawText((scoreText + std::to_string(score)).c_str(), window_size.x / 2 - MeasureText((scoreText + std::to_string(score)).c_str(), 128) / 2, window_size.y / 4.5 - 128 / 2, 128, WHITE);
	scoreText = "Highscore: ";
	DrawText((scoreText + std::to_string(highscore)).c_str(), window_size.x / 2 - MeasureText((scoreText + std::to_string(highscore)).c_str(), 100) / 2, window_size.y / 3 - 100 / 2, 100, WHITE);


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
	Button ship     (Vector2(25 , 86), "Ship"     , Vector2(275, 100), 64, 5, WHITE, GRAY, GRAY);
	Button equipment(Vector2(315, 86), "Equipment", Vector2(275, 100), 48, 5, WHITE, GRAY, GRAY);
	Button secondary(Vector2(605, 86), "Secondary", Vector2(275, 100), 48, 5, WHITE, GRAY, GRAY);

	DrawRectangle(25, 200, 855, 775, GRAY);
	DrawRectangle(30, 205, 845, 765, WHITE);

	std::string string = std::to_string((int)totalcoins);
	
	using namespace std::literals::string_literals;
	DrawText((string + "c"s).c_str(), 865-MeasureText((string + "c"s).c_str(), 48), 215, 48, GOLD);
	if (CheckCollisionCircles(Vector2(GetMouseX(), GetMouseY()), 1, Vector2(25 + 75 / 2, 5 + 75 / 2), (int)75 / 2) and IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		page = 0;
	}

	DrawTexture(backButton, 25, 5, WHITE);

	if (shopPage == 3) {
		DrawText("Secondary", 50, 215, 64, GRAY);
	}
	else if (shopPage == 2) {
		DrawText("Equipment", 50, 215, 64, GRAY);
	}
	else if (shopPage == 1) {
		DrawText("Ships", 50, 215, 64, GRAY);
	}

	DrawRectangle(50, 285, 200, 5, GRAY);

	if (ship.update() + equipment.update() + secondary.update()) 
		shopPage = (ship.update()) + (equipment.update()*2) + (secondary.update()*3);
	
	ship.draw();
	equipment.draw();
	secondary.draw();
}