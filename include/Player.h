#ifndef PLAYER_H
#define PLAYER_H
#include <Events.h>
#include <PlayerState.h>
#include <AnimatedSprite.h>
#include <stdio.h>
#include <IdlePlayerState.h>

struct Position
{
	float x = 0;
	float y = 0;
};

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;
	
public:
	Player(const AnimatedSprite&);
	virtual void handleInput(gpp::Events);
	virtual void update();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
	void move(float x, float y);
	void flipSprite();
	bool isFlipped();
	bool isColliding(Player&);
	bool isCollidingAttack(Player&, float);
	Position m_pos;
	float health = 100.f;
	const float HIT_CIRCLE = 50.f;
};
#endif

