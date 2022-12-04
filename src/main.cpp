// system 
#include <iostream>
#include <string>
// SFML
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>   
#include <SFML/Audio.hpp>
// Project
#include "sound.h"


#define MAX_FRAMERATE 500

enum max_values { MAX_X = 1280, MAX_Y = 720 };
float frametime = 0;

class DeadScene {
public:
	float time = 0;
	sf::Clock clock;
	enum Status { idle, start };
	Status status = idle;
	bool run(void)
	{
		bool answer = false;
		if (status == idle)
		{
			status = start;
			clock.restart();
		}
		if (status == start)
		{
			if (clock.getElapsedTime().asSeconds() > 2)
			{
				status = idle;
				answer = true;
			}
		}
		return answer;
	}
};

class Game {
public:
	enum Status { Alive, Dead };
	Status status;
	Game() {
		status = Status::Alive;
	};
};

class Ball {
public:
	float x;
	float y;
	float vx;
	float vy;
	sf::CircleShape shape;
	float timeElapsed = 1;
	const int size = 30;
	Ball() {
		x = rand() % (MAX_X - 4 * size) + 2 * size;
		y = rand() % (MAX_Y - 4 * size) + 2 * size;
		vx = 300 * ((float)rand() / RAND_MAX * 2 - 1);
		vy = 300 * ((float)rand() / RAND_MAX * 2 - 1);
		shape.setRadius(size);
		//shape.setFillColor(sf::Color::rand()%15);
		int temp = rand() % 3;
		sf::Color fillColor;
		if (temp == 1)
			fillColor = sf::Color(255, 0, 0, 155);
		else if (temp == 2)
			fillColor = sf::Color(0, 255, 0, 155);
		else
			fillColor = sf::Color(0, 0, 255, 155);
		shape.setFillColor(fillColor);
		//sf::Color
		shape.setPosition(x, y);
	}
	void calculate(void) {
		x += vx * frametime / 1000000;
		y += vy * frametime / 1000000;
		if ((x > MAX_X - 2 * size) || (x < 0)) vx = -vx;
		if ((y > MAX_Y - 2 * size) || (y < 0)) vy = -vy;
		shape.setPosition(x, y);
	}

};

class Player {
public:
	float x;
	float y;
	float vx;
	float vy;
	float life = 100;
	sf::RectangleShape shape;
	float timeElapsed = 1;
	const int size = 10;
	const int nominalSpeed = 100;
	const float damageRate = 2;
	bool gettingDamaged = 0;
	Player() {
		x = MAX_X / 2;
		y = MAX_Y / 2;
		vx = 0;
		vy = 0;
		shape.setFillColor(sf::Color::White);
		shape.setSize(sf::Vector2f(size, size));
		shape.setPosition(x - size / 2, y - size / 2);
	}
	void restart(void) {
		x = MAX_X / 2;
		y = MAX_Y / 2;
		vx = 0;
		vy = 0;
		life = 100;
		gettingDamaged = 0;
	}
	void calculate(void) {
		x += vx * frametime / 1000000;
		y += vy * frametime / 1000000;
		if ((x > MAX_X - 2 * size) || (x < 0)) vx = -vx;
		if ((y > MAX_Y - 2 * size) || (y < 0)) vy = -vy;
		shape.setPosition(x, y);
	}

};




int main(void)
{
	const int QTY_BALLS = 20;
	srand(time(NULL));
	float framerate = 0;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(MAX_X, MAX_Y), "Bouncing balls");
	sf::Keyboard kb;
	Game game;

	std::vector<Ball> ball(QTY_BALLS);
	Player player;

	sf::Font font;
	font.loadFromFile("C:/Temp/arial.ttf");
	sf::Text text1("hello", font);
	text1.setPosition(5, 5);
	text1.setCharacterSize(30);

	sf::RectangleShape background;

	SoundEffect sounds;
	sounds.add("electricity");

	sf::Music music;
	if (!music.openFromFile("c:/Temp/background.wav"))
		return -1; // error
	music.play();

	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string temp = "c:/Temp/electricity.wav";
	buffer.loadFromFile(temp);
	sound.setBuffer(buffer);
	//sound.play();


	//sound_start.play();

	DeadScene deadScene;

restart:
	game.status = Game::Alive;
	player.restart();
	clock.restart();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (game.status == Game::Alive) {
			// 1) Process input & apply physics
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			{
				player.vx -= player.nominalSpeed;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				player.vx += player.nominalSpeed;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				player.vx = 0;
			}
			// Check collisions
			player.gettingDamaged = false;
			for (int i = 0; i < QTY_BALLS; i++) {
				if (player.shape.getGlobalBounds().intersects(ball[i].shape.getGlobalBounds()))
				{
					player.life -= player.damageRate;
					player.gettingDamaged = true;
					if (player.life <= 0)
						game.status = Game::Dead;
				}
			}

			// Play sounds
			if (player.gettingDamaged == true)
				sounds.play("electricity");
			else
				sounds.stop("electricity");

			// 2) Draw the screen
			window.clear();
			background.setFillColor(sf::Color::Blue);
			background.setSize(sf::Vector2f(MAX_X, MAX_Y));
			background.setPosition(0, 0);
			if (game.status == Game::Alive) {
				if (player.gettingDamaged == true) {
					if ((rand() % 10) < 5) {
						window.draw(background);
					}
				}
				//text1.setString("Framerate: " + std::to_string(framerate));
				text1.setString("LIFE: " + std::to_string(player.life) + " %");
				for (int i = 0; i < QTY_BALLS; i++) {
					ball[i].calculate();
					window.draw(ball[i].shape);
				}
				player.calculate();
				window.draw(player.shape);
				window.draw(text1);
			}
		}
		else
		{
			player.gettingDamaged == false;
			sounds.stop("electricity");
			background.setFillColor(sf::Color::Red);
			window.draw(background);
			text1.setString("DEAD");
			if (deadScene.run() == true)
				goto restart;
		}

		window.display();

		// 3) Delay for max framerate
		do
		{
			framerate = 10E6 / clock.getElapsedTime().asMicroseconds();

		} while (framerate > MAX_FRAMERATE);
		frametime = clock.getElapsedTime().asMicroseconds();
		clock.restart();

	}
	return 0;
}