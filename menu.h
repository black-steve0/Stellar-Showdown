#pragma once

#include "game.h"

bool Button::update(void) {
	if (clicked(ray::MOUSE_LEFT_BUTTON)) {
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
	ray::DrawRectangle(position.x, position.y, size.x, size.y, borderColor);
	ray::DrawRectangle(position.x + border, position.y + border, size.x - 2 * border, size.y - 2 * border, color);
	ray::DrawText(text, (position.x + size.x / 2) - ray::MeasureText(text, fontSize) / 2, (position.y + size.y / 2) - fontSize / 2, fontSize, textColor);
}

bool Button::clicked(int key) {
	return ray::IsMouseButtonReleased(key) and ray::CheckCollisionRecs(ray::Rectangle(ray::GetMouseX(), ray::GetMouseY(), 1, 1), ray::Rectangle(position, size));
}

bool Button::hovered() {
	return ray::CheckCollisionRecs(ray::Rectangle(ray::GetMouseX(), ray::GetMouseY(), 1, 1), ray::Rectangle(position, size));
}

void menu() {
	Button play(ray::Vector2(window_size.x/2, window_size.y) / 2, "PLAY", ray::Vector2(500, 150), 80, 10, WHITE, GRAY, GRAY);
	Button shop(ray::Vector2(window_size.x / 2, window_size.y + 325) / 2, "Shop", ray::Vector2(250-7, 150), 60, 10, WHITE, GRAY, GRAY);
	Button settings(ray::Vector2(window_size.x / 2 + 515, window_size.y + 325) / 2, "Help", ray::Vector2(250-7, 150), 60, 10, WHITE, GRAY, GRAY);

	std::string scoreText = "Score: ";
	ray::DrawText((scoreText + std::to_string(score)).c_str(), window_size.x / 2 - ray::MeasureText((scoreText + std::to_string(score)).c_str(), 128) / 2, window_size.y / 4.5 - 128 / 2, 128, WHITE);
	scoreText = "Highscore: ";
	ray::DrawText((scoreText + std::to_string(highscore)).c_str(), window_size.x / 2 - ray::MeasureText((scoreText + std::to_string(highscore)).c_str(), 100) / 2, window_size.y / 3 - 100 / 2, 100, WHITE);


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
	Button ship     (ray::Vector2(25 , 86), "Ship"     , ray::Vector2(275, 100), 64, 5, WHITE, GRAY, GRAY);
	Button equipment(ray::Vector2(315, 86), "Equipment", ray::Vector2(275, 100), 48, 5, WHITE, GRAY, GRAY);
	Button secondary(ray::Vector2(605, 86), "Secondary", ray::Vector2(275, 100), 48, 5, WHITE, GRAY, GRAY);

	ray::DrawRectangle(25, 200, 855, 775, GRAY);
	ray::DrawRectangle(30, 205, 845, 765, WHITE);

	std::string string = std::to_string((int)totalcoins);
	
	using namespace std::literals::string_literals;
	ray::DrawText((string + "c"s).c_str(), 865-ray::MeasureText((string + "c"s).c_str(), 48), 215, 48, GOLD);
	ray::DrawCircle(25+75/2, 5 + 75/2, 75 / 2, WHITE);
	if (ray::CheckCollisionPointCircle(ray::Vector2(ray::GetMouseX(), ray::GetMouseY()), ray::Vector2(25,5)+75/2, 75/2)) {
		printf("C");
	}

	ray::DrawTexture(backButton, 25, 5, WHITE);

	if (shopPage == 3) {
		ray::DrawText("Secondary", 50, 215, 64, GRAY);
	}
	else if (shopPage == 2) {
		ray::DrawText("Equipment", 50, 215, 64, GRAY);
	}
	else if (shopPage == 1) {
		ray::DrawText("Ships", 50, 215, 64, GRAY);
	}

	ray::DrawRectangle(50, 285, 200, 5, GRAY);

	if (ship.update() + equipment.update() + secondary.update()) 
		shopPage = (ship.update()) + (equipment.update()*2) + (secondary.update()*3);
	
	ship.draw();
	equipment.draw();
	secondary.draw();
}