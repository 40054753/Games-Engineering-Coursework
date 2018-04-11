#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include <iostream>
#include "cmp_actor_movement.h"
#include "Game.h"
#include "cmp_health.h"
#include "cmp_status.h"
using namespace sf;
ShapeComponent::ShapeComponent(Entity *p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}

void ShapeComponent::update(double dt) 
{
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render() {
	Renderer::queue(_shape.get());
}

sf::Shape& ShapeComponent::getShape() const {
	return *_shape;
}

CharacterSpriteComponent::CharacterSpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{
	frame = 0;
	walkingAnimationDown.push_back(sf::IntRect(0, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(16, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(32, 0, 16, 21));
	walkingAnimationDown.push_back(sf::IntRect(48, 0, 16, 21));

	walkingAnimationUp.push_back(sf::IntRect(0, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(16, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(32, 42, 16, 21));
	walkingAnimationUp.push_back(sf::IntRect(48, 42, 16, 21));
	
	walkingAnimationRight.push_back(sf::IntRect(0, 22, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(16, 22, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(32, 22, 16, 21));
	walkingAnimationRight.push_back(sf::IntRect(48, 22, 16, 21));

	walkingAnimationLeft.push_back(sf::IntRect(0, 65, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(16, 65, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(32, 65, 16, 21));
	walkingAnimationLeft.push_back(sf::IntRect(48, 65, 16, 21));
}

void CharacterSpriteComponent::update(double dt)
{
	
	AnimationCounter -= dt;
	if (!_parent->isPlayer())
	{
		if (frame > 3) frame = 0;

		if (_parent->getFace() == 1 && AnimationCounter <= 0.0f)
		{
			_sprite->setTextureRect(walkingAnimationUp[frame]);
			frame++;
			AnimationCounter = AnimationDelay;
		}
		else if (_parent->getFace() == 2 && AnimationCounter <= 0.0f)
		{
			_sprite->setTextureRect(walkingAnimationRight[frame]);
			frame++;
			AnimationCounter = AnimationDelay;
		}
		else if (_parent->getFace() == 3 && AnimationCounter <= 0.0f)
		{
			_sprite->setTextureRect(walkingAnimationDown[frame]);
			frame++;
			AnimationCounter = AnimationDelay;
		}
		else if (_parent->getFace() == 4 && AnimationCounter <= 0.0f)
		{
			_sprite->setTextureRect(walkingAnimationLeft[frame]);
			frame++;
			AnimationCounter = AnimationDelay;
		}

	}
	else
	{
		if (Keyboard::isKeyPressed(controls[0]))
		{
			facing = 1;
			if (frame > 3) frame = 0;
			if (AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationUp[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		}
		else if (Keyboard::isKeyPressed(controls[1]))
		{
			facing = 3;
			if (frame > 3) frame = 0;
			if (AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationDown[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		}
		else if (Keyboard::isKeyPressed(controls[3]))
		{
			facing = 4;
			if (frame > 3) frame = 0;
			if (AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationLeft[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		}
		else if (Keyboard::isKeyPressed(controls[2]))
		{
			facing = 2;
			if (frame > 3) frame = 0;
			if (AnimationCounter <= 0.0f)
			{
				_sprite->setTextureRect(walkingAnimationRight[frame]);
				frame++;
				AnimationCounter = AnimationDelay;
			}
		}

		else
		{
			frame = 0;
			switch (facing)
			{
			case 1:
				_sprite->setTextureRect(walkingAnimationUp[frame]);
				break;
			case 2:
				_sprite->setTextureRect(walkingAnimationRight[frame]);
				break;
			case 3:
				_sprite->setTextureRect(walkingAnimationDown[frame]);
				break;
			case 4:
				_sprite->setTextureRect(walkingAnimationLeft[frame]);
				break;
			}
		}
	}
	
	_sprite->setPosition(_parent->getPosition());
}
void CharacterSpriteComponent::setScale()
{
	_sprite->setScale(WX / 1280, WY / 720);
}
void CharacterSpriteComponent::render() {
	Renderer::queue(1,_sprite.get());
}
sf::Sprite& CharacterSpriteComponent::getSprite() const {
	return *_sprite;
}

DamageTextComponent::DamageTextComponent(Entity *p) : Component(p) 
{
	damageText.setFont(font);
	damageText.setCharacterSize(15);
	damageText.setScale(WX/1280,WY/720);
	damageText.setColor(sf::Color::Red);
	

}
void DamageTextComponent::setText(int x)
{
	damageText.setString(std::to_string(x));
}
void DamageTextComponent::update(double dt)
{
	textTime -= dt;
	damageText.setPosition(_parent->getPosition()+Vector2f(-14.0f*WX/1280,-50.0f*WY/720));
	if (textTime < 0)
		_parent->setForDelete();
	
}
void DamageTextComponent::render()
{
	Renderer::queue(&damageText);
}

StatusTextComponent::StatusTextComponent(Entity *p) : Component(p)
{
	statusText.setFont(font);
	statusText.setCharacterSize(15);
	statusText.setScale(WX / 1280, WY / 720);
	statusText.setColor(sf::Color::Red);


}
void StatusTextComponent::setText(std::string x)
{
	statusText.setString(x);
}
void StatusTextComponent::update(double dt)
{
	auto status = _parent->GetComponent<StatusComponent>();
	statusText.setPosition(_parent->getPosition() + Vector2f(-39.0f*WX / 1280, -50.0f*WY / 720));
	auto blinded = "Blinded";
	setText(blinded);
	blindTextTime -= dt;
	if (blindTextTime < 0) {
		_parent->setForDelete();
	}

}
void StatusTextComponent::render()
{
	Renderer::queue(&statusText);
}
	
sf::Sprite& StaticSpriteComponent::getSprite() const {
	return *_sprite;
}

StaticSpriteComponent::StaticSpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{
	
}

void StaticSpriteComponent::setScale()
{
	_sprite->setScale(WX / 1280, WY / 720);
}
void StaticSpriteComponent::update(double dt)
{
	if(spin)
	_sprite->rotate(-360.0f*dt*5.0f);
	_sprite->setPosition(_parent->getPosition());
}

void StaticSpriteComponent::render()
{
	Renderer::queue(2,_sprite.get());
}
EnemyHealthBarComponent::EnemyHealthBarComponent(Entity *p) : Component(p) 
{
	
	hp.setFillColor(sf::Color::Red);
	hp.setSize({31.0f, 4.0f});
}
void EnemyHealthBarComponent::update(double dt)
{
	auto health = _parent->GetComponent<HealthComponent>();
	float scaleX = health->getHealth() / health->getMaxHealth();
	hp.setScale(scaleX * (WX / 1280) , WY / 720);
	hp.setPosition(_parent->getPosition() + Vector2f(-15.0*WX/1280, -30.0f*WY/720));
}
void EnemyHealthBarComponent::render()
{
	Renderer::queue(&hp);
}
AnimatedSpriteComponent::AnimatedSpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{

}

void AnimatedSpriteComponent::setScale()
{
	_sprite->setScale(WX / 1280, WY / 720);
}
void AnimatedSpriteComponent::update(double dt)
{
	AnimationCounter -= dt;

	if (frame >= max_frames)
	{
		animationDirection = false;
		if (singularPlay)
			_parent->setForDelete();
	}
	else if (frame <= 0)
		animationDirection = true;
	if(!_parent->is_forDeletion())
	if ( AnimationCounter <= 0.0f)
	{
		if (animationDirection)
			frame++;
		else
			frame--;
		_sprite->setTextureRect(animationFrames[frame]);		
		AnimationCounter = AnimationDelay;
	}
	_sprite->setPosition(_parent->getPosition());

	
}
sf::Sprite& AnimatedSpriteComponent::getSprite() const {
	return *_sprite;
}

void AnimatedSpriteComponent::render()
{
	Renderer::queue(priority, _sprite.get());
}