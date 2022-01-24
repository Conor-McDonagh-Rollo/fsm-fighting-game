#include <Events.h>

#include <RunLeftPlayerState.h>

#include <AttackPlayerState.h>
#include <ThrowAttackPlayerState.h>
#include <IdlePlayerState.h>
#include <AccendLadderPlayerState.h>
#include <DecendLadderPlayerState.h>
#include <JumpPlayerState.h>
#include <DiedPlayerState.h>
#include <SlidePlayerState.h>

PlayerState* RunLeftPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("RunLeftPlayerState -> AttackPlayerState");
		return new AttackPlayerState();
	}
	if (input.getCurrent() == gpp::Events::Event::THROW_START_EVENT)
	{
		DEBUG_MSG("RunLeftPlayerState -> ThrowAttackPlayerState");
		return new ThrowAttackPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_WALL_EVENT || input.getCurrent() == gpp::Events::Event::RUN_LEFT_STOP_EVENT)
	{
		DEBUG_MSG("RunLeftPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT)
	{
		DEBUG_MSG("RunLeftPlayerState -> AccendLadderPlayerState");
		return new AccendLadderPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::HIT_LADDER_TOP_EVENT)
	{
		DEBUG_MSG("RunLeftPlayerState -> DecendLadderPlayerState");
		return new DecendLadderPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::JUMP_UP_EVENT) {
		DEBUG_MSG("IdlePlayerState -> JumpPlayerState");
		return new JumpPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::SLIDE_EVENT) {
		DEBUG_MSG("RunLeftPlayerState -> SlidePlayerState");
		return new SlidePlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("RunLeftPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void RunLeftPlayerState::update(Player& player) {
	DEBUG_MSG("RunLeftPlayerState::update");
	DEBUG_MSG(typeid(player).name());
	if (!player.isFlipped()) player.flipSprite();
	player.move(-0.1f,0.f);
}
void RunLeftPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering RunLeftPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(4986, 3556, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5349, 3556, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5712, 3556, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(4986, 4014, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5349, 4014, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5712, 4014, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(4986, 4472, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5349, 4472, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(5712, 4472, 363, 458));
	player.getAnimatedSprite().addFrame(sf::IntRect(4986, 4930, 363, 458));

	player.getAnimatedSpriteFrame().setTime(seconds(0.05f));
}
void RunLeftPlayerState::exit(Player& player) 
{
	DEBUG_MSG("Exiting RunLeftPlayerState");
	DEBUG_MSG(typeid(player).name());
}