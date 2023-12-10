#pragma once

#include "game.h"

void Button::update(int button) {
	if (hovered()) {
		borderColor = GOLD;
	}
	else {
		borderColor = GRAY;
	}
	if (clicked(ray::MOUSE_LEFT_BUTTON)) {
		if (button == 1) {
			gameStart();
		}
		if (button == 2) {
			page = 2;
		}
		if (button == 3) {
			page = 3;
		}
	}
}

void Button::draw() {
	ray::DrawRectangle(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y, borderColor);
	ray::DrawRectangle(position.x - size.x / 2 + border, position.y - size.y / 2 + border, size.x - 2 * border, size.y - 2 * border, color);
	ray::DrawText(text, position.x - ray::MeasureText(text, fontSize) / 2, position.y - fontSize / 2, fontSize, textColor);
}

bool Button::clicked(int key) {
	return ray::IsMouseButtonReleased(key) and ray::CheckCollisionRecs(ray::Rectangle(ray::GetMouseX(), ray::GetMouseY(), 1, 1), ray::Rectangle(position - size / 2, size));
}

bool Button::hovered() {
	return ray::CheckCollisionRecs(ray::Rectangle(ray::GetMouseX(), ray::GetMouseY(), 1, 1), ray::Rectangle(position - size / 2, size));
}

void menu() {
	Button play(ray::Vector2(window_size.x, window_size.y) / 2, "PLAY", ray::Vector2(500, 150), 80, 10, WHITE, GRAY, GRAY);
	Button shop(ray::Vector2(window_size.x / 2 + 200-7, window_size.y + 325) / 2, "Shop", ray::Vector2(250-7, 150), 60, 10, WHITE, GRAY, GRAY);
	Button settings(ray::Vector2(window_size.x / 2 + 700+7, window_size.y + 325) / 2, "Help", ray::Vector2(250-7, 150), 60, 10, WHITE, GRAY, GRAY);

	std::string scoreText = "Score: ";
	ray::DrawText((scoreText + std::to_string(score)).c_str(), window_size.x / 2 - ray::MeasureText((scoreText + std::to_string(score)).c_str(), 128) / 2, window_size.y / 4.5 - 128 / 2, 128, WHITE);
	scoreText = "Highscore: ";
	ray::DrawText((scoreText + std::to_string(highscore)).c_str(), window_size.x / 2 - ray::MeasureText((scoreText + std::to_string(highscore)).c_str(), 100) / 2, window_size.y / 3 - 100 / 2, 100, WHITE);
	
	play.update(1);
	settings.update(3);
	shop.update(2);

	play.draw();
	settings.draw();
	shop.draw();
}

void shop() {

}