#include <iostream>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// note: a Sprite represents an image on screen. A sprite knows and remembers its own position
// ship.move(offsetX, offsetY) adds offsetX, offsetY to 
// the current position of the ship. 
// x is horizontal, y is vertical. 
// 0,0 is in the UPPER LEFT of the screen, y increases DOWN the screen
void moveShip(Sprite& ship)
{
	const float DISTANCE = 5.0f;

	Vector2f pos = ship.getPosition();
	Vector2f nextPos;
	const Texture *craft = ship.getTexture();
	Vector2u shipSize = craft->getSize();

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		// left arrow is pressed: move our ship left 5 pixels
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		ship.move(-DISTANCE, 0);
		nextPos = ship.getPosition();
		if (nextPos.x < 0)
		{
			ship.setPosition(pos);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		// right arrow is pressed: move our ship right 5 pixels

		ship.move(DISTANCE, 0);
		nextPos = ship.getPosition();
		if (nextPos.x > (WINDOW_WIDTH - shipSize.x))
		{
			ship.setPosition(pos);
		}
	}
	// *** add code to move ship up/down
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		// up arrow is pressed: move our ship up 5 pixels
		ship.move(0, -DISTANCE);
		nextPos = ship.getPosition();
		if (nextPos.y < (0.8 * WINDOW_HEIGHT))
		{
			ship.setPosition(pos);
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		// down arrow is pressed: move our ship down 5 pixels
		ship.move(0, DISTANCE);
		nextPos = ship.getPosition();
		if (nextPos.y > (WINDOW_HEIGHT - shipSize.y))
		{
			ship.setPosition(pos);
		}
	}
}

int main()
{

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "aliens!");
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.
	Texture shipTexture;
	if (!shipTexture.loadFromFile("ship.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture missileTexture;
	if (!missileTexture.loadFromFile("email.png"))
	{
		cout << "Unable to load missile texture!" << endl;
		exit(EXIT_FAILURE);
	}
	Texture enemyTexture;
	if (!enemyTexture.loadFromFile("enemy.png"))
	{
		cout << "Unable to load enemy texture!" << endl;
		exit(EXIT_FAILURE);
	}

	// A sprite is a thing we can draw and manipulate on the screen.
	// We have to give it a "texture" to specify what it looks like

	Sprite background;
	background.setTexture(starsTexture);
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale(1.5, 1.5);

	// create sprite and texture it
	Sprite ship;
	ship.setTexture(shipTexture);

	// *** add code to set texture for the missile
	Sprite missile;
	missile.setTexture(missileTexture);

	Sprite enemy;
	enemy.setTexture(enemyTexture);


	// initial position of the ship will be approx middle of screen
	float shipX = window.getSize().x / 2.0f;
	float shipY = window.getSize().y / 1.5f;
	ship.setPosition(shipX, shipY);

	float enemyX = window.getSize().x / 4.0f;
	float enemyY = window.getSize().y / 5.0f;
	enemy.setPosition(enemyX, enemyY);

	bool isMissileInFlight = false;

	int hitCount = 0;

	const float DISTANCE = 5.0f;

	int numCount = 0;

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		// For now, we just need this so we can click on the window and close it
		Event event;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Space)
				{
					isMissileInFlight = true;
					// ***Add code to initialize missile position 

					Vector2f pos = ship.getPosition();
					pos.x += 10;
					pos.y += 10;
					missile.setPosition(pos.x, pos.y);

				}
			}
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);

		//detect key presses to update the position of the ship. 
		//See moveShip() function above.
		moveShip(ship);

		// draw the ship on top of background 
		// (the ship from previous frame was erased when we drew background)
		window.draw(ship);

		if (numCount % 2 == 0)
		{
			Vector2f pos = enemy.getPosition();
			Vector2f nextPos;

			enemy.move(-DISTANCE, 0);
			nextPos = enemy.getPosition();
			if (nextPos.x < 0)
			{
				enemy.setPosition(pos);
				numCount = 1;
			}
		}
		else if (numCount % 2 == 1)
		{
			Vector2f pos = enemy.getPosition();
			Vector2f nextPos;

			enemy.move(DISTANCE, 0);
			nextPos = enemy.getPosition();
			if (nextPos.x > WINDOW_WIDTH - enemyTexture.getSize().x)
			{
				enemy.setPosition(pos);
				numCount = 0;
			}
		}


		window.draw(enemy);


		if (isMissileInFlight)
		{
			const float DISTANCE = 5.0f;
			window.draw(missile);
			missile.move(0, -DISTANCE);
			Vector2f pos = missile.getPosition();
			if (pos.y <= 0)
			{
				isMissileInFlight = false;
			}
			FloatRect missileBounds = missile.getGlobalBounds();
			FloatRect enemyBounds = enemy.getGlobalBounds();
			if (missileBounds.intersects(enemyBounds))
			{
				cout << "Nous avons detruit l'ennemi" << endl;
				isMissileInFlight = false;
				hitCount++;
				cout << "Hit count: " << hitCount << endl;
			}
		}



		// end the current frame; this makes everything that we have 
		// already "drawn" actually show up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	} // end body of animation loop

	return 0;
}

