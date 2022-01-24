#include <Player.h>
#include <cmath>

Player::Player(const AnimatedSprite& sprite) : m_animated_sprite(sprite)
{
	// Set the Player to Default to IdlePlayer State 
	// and Enter that State
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

void Player::handleInput(gpp::Events input) {
	PlayerState * state = m_state->handleInput(input);

	if (state != NULL) {
		m_state->exit(*this);
		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Player::update() {
	m_animated_sprite.update();
	m_state->update(*this);
}

AnimatedSprite& Player::getAnimatedSprite() {
	return m_animated_sprite;
}

AnimatedSprite& Player::getAnimatedSpriteFrame() {
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void Player::setAnimatedSprite(AnimatedSprite& animated_sprite) {
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Player::getPlayerState() { return this->m_state; }

void Player::setPlayerState(PlayerState* state) { this->m_state = state; }

void Player::move(float x, float y)
{
	getAnimatedSpriteFrame().move(x,y);
	m_pos.x = x;
	m_pos.y = y;
}

void Player::flipSprite()
{
	if (!isFlipped()) 
		getAnimatedSpriteFrame().setScale(-0.5f,0.5f);
	else
		getAnimatedSpriteFrame().setScale(0.5f,0.5f);
}

bool Player::isFlipped()
{
	if (getAnimatedSpriteFrame().getScale().x < 0)
		return true;
	else
		return false;
}

bool Player::isColliding(Player& other)
{
	float dx = (getAnimatedSpriteFrame().getPosition().x - HIT_CIRCLE) - (other.getAnimatedSpriteFrame().getPosition().x - other.HIT_CIRCLE);
    float dy = (getAnimatedSpriteFrame().getPosition().y + HIT_CIRCLE) - (other.getAnimatedSpriteFrame().getPosition().y + other.HIT_CIRCLE);
    float distance = sqrt(dx * dx + dy * dy);
	if (distance < other.HIT_CIRCLE + other.HIT_CIRCLE)
	{
		return true;
	}
	return false;
}

bool Player::isCollidingAttack(Player& other, float range)
{
	float dx = (getAnimatedSpriteFrame().getPosition().x - HIT_CIRCLE) - (other.getAnimatedSpriteFrame().getPosition().x - other.HIT_CIRCLE);
    float dy = (getAnimatedSpriteFrame().getPosition().y + HIT_CIRCLE) - (other.getAnimatedSpriteFrame().getPosition().y + other.HIT_CIRCLE);
    float distance = sqrt(dx * dx + dy * dy);
	if (distance + range < other.HIT_CIRCLE + other.HIT_CIRCLE)
	{
		return true;
	}
	return false;
}