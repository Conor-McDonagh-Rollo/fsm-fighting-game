#include <Defines.h>

#include <iostream>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Events.h>
#include <Debug.h>

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Player Finite State Machine");

	// Load a sprite to display
	sf::Texture player_texture;
	if (!player_texture.loadFromFile(PLAYER_SPRITES))
	{
		DEBUG_MSG("Failed to load file");
		if (!player_texture.loadFromFile(ERROR_SPRITES))
		{
			return EXIT_FAILURE;
		}
	}
	sf::Texture background_texture;
	if (!background_texture.loadFromFile(BACKGROUND))
	{
		DEBUG_MSG("Failed to load file");
	}
	sf::RectangleShape bg(sf::Vector2f(800,600));
	bg.setTexture(&background_texture);

	// Setup Players Default Animated Sprite
	AnimatedSprite player_animated_sprite(player_texture);
	AnimatedSprite villain_animated_sprite(player_texture);

	Player player(player_animated_sprite);
	sf::CircleShape playerHitbox(player.HIT_CIRCLE);
	Player villain(villain_animated_sprite);
	sf::CircleShape villainHitbox(villain.HIT_CIRCLE);
	villain.move(150,0);
	villain.flipSprite();

	gpp::Events input;
	gpp::Events inputVillain;

	inputVillain.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
				// Deal with KeyPressed
			case sf::Event::KeyPressed:
				// Died Event
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
					input.setCurrent(gpp::Events::Event::DIED_EVENT);
				}
				// Revieved Event
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
					input.setCurrent(gpp::Events::Event::REVIVED_EVENT);
				}
				// Running attack
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
						 (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) ||
						  (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
						 (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Z)))
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_START");
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
				}
				// Attack
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
				}
				// Throw attack
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::X) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
						 (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::X)) ||
						  (sf::Keyboard::isKeyPressed(sf::Keyboard::X) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
						 (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::X)))
				{
					DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
				}
				// Throw Attack
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				{
					DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
				}
				// Run Right
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Run Left
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_LEFT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_LEFT_START_EVENT);
				}
				// Climb Up
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_UP_START_EVENT);
				}
				// Climb Down
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_START_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT);
				}
				// Hit Bottom of Ladder Event
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT);
				}
				// Hit Top of Ladder Event
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_LADDER_TOP_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT);
				}
				// Jump Run
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
					 sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
					(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
					 sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) ||
					 (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
					 sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
					(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
					 sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
				{
					DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
					input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				}
				// Jump Event
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
					input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
				}
				// Running Slide
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
						 (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
						  (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
						 (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
						  sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
				{
					DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
					input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
				}
				// Hit Ground Event
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}

				// Jump Attack Event
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}

				// Jump Throw Attack Event
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
				{
					DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
					input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
				}
				break;

				// Deal with KeyReleased
			case sf::Event::KeyReleased:
				// Run and Stop Attack
				if (event.key.code == sf::Keyboard::Z && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
					event.key.code == sf::Keyboard::Z && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Stop Attack
				else if (event.key.code == sf::Keyboard::Z)
				{
					DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
				}
				// Run and Stop Throw Attack
				else if (event.key.code == sf::Keyboard::X && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
						 event.key.code == sf::Keyboard::X && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Stop Throw Attack
				else if (event.key.code == sf::Keyboard::X)
				{
					DEBUG_MSG("gpp::Events::Event::THROW_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
				}
				// Stop Running Right
				else if (event.key.code == sf::Keyboard::Right)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT);
				}
				// Stop Running Left
				else if (event.key.code == sf::Keyboard::Left)
				{
					DEBUG_MSG("gpp::Events::Event::RUN_LEFT_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_LEFT_STOP_EVENT);
				}
				// Stop Slide
				else if (event.key.code == sf::Keyboard::Down &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
					input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
				}
				// Stop Moving Up
				else if (event.key.code == sf::Keyboard::Up)
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_UP_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_UP_STOP_EVENT);
				}
				// Stop Moving Down
				else if (event.key.code == sf::Keyboard::Down)
				{
					DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_STOP_EVENT");
					input.setCurrent(gpp::Events::Event::MOVE_DOWN_STOP_EVENT);
				}
				break;

			default:
				DEBUG_MSG("gpp::Events::Event::NONE");
				input.setCurrent(gpp::Events::Event::NONE);
				break;
			}
			// Handle input to Player
			player.handleInput(input);
		}

		//update game world
		bool Touching = player.isColliding(villain);
		
		playerHitbox.setPosition(player.getAnimatedSpriteFrame().getPosition() - sf::Vector2f(50.f,0.f));
		playerHitbox.setFillColor(sf::Color(0,255,0,125));
		villainHitbox.setPosition(villain.getAnimatedSpriteFrame().getPosition() - sf::Vector2f(50.f,0.f));
		villainHitbox.setFillColor(sf::Color(0,255,0,125));
		if (Touching)
		{
			playerHitbox.setFillColor(sf::Color(255,0,0,125));
			villainHitbox.setFillColor(sf::Color(255,0,0,125));
		}
		//player attack decreases health next

		
		//health stuff
		sf::RectangleShape playerHealth(sf::Vector2f(player.health * 3, 25.f));
		playerHealth.setFillColor(sf::Color::Red);
		sf::RectangleShape villainHealth(sf::Vector2f(villain.health * 3, 25.f));
		villainHealth.setFillColor(sf::Color::Red);
		villainHealth.setPosition(sf::Vector2f(800 - (villain.health * 3), 0));
		
		// Update the Player
		player.update();
		villain.update();

		villain.handleInput(inputVillain);

		// Clear screen
		window.clear();
		window.draw(bg);
		window.draw(playerHealth);
		window.draw(villainHealth);

		// Draw the Players Current Animated Sprite
		window.draw(player.getAnimatedSpriteFrame());
		window.draw(villain.getAnimatedSpriteFrame());
		window.draw(playerHitbox);
		window.draw(villainHitbox);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};