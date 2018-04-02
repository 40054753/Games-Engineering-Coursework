#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include <iostream>
#include "cmp_actor_movement.h"
#include "Game.h"
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
		if (Keyboard::isKeyPressed(Keyboard::W))
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
		else if (Keyboard::isKeyPressed(Keyboard::S))
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
		else if (Keyboard::isKeyPressed(Keyboard::A))
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
		else if (Keyboard::isKeyPressed(Keyboard::D))
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

void CharacterSpriteComponent::render() {
	Renderer::queue(_sprite.get());
}
sf::Sprite& CharacterSpriteComponent::getSprite() const {
	return *_sprite;
}

DamageTextComponent::DamageTextComponent(Entity *p) : Component(p) 
{
	damageText.setString(std::to_string(30));
	damageText.setFont(font);
	damageText.setCharacterSize(20);
	damageText.setColor(sf::Color::Red);
	

}
void DamageTextComponent::update(double dt)
{
	textTime -= dt;
	damageText.setPosition(_parent->getPosition());
	if (textTime < 0)
		_parent->setForDelete();
	
}
void DamageTextComponent::render()
{
	Renderer::queue(&damageText);
}
	
sf::Sprite& StaticSpriteComponent::getSprite() const {
	return *_sprite;
}

StaticSpriteComponent::StaticSpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
{

}

void StaticSpriteComponent::update(double dt)
{
	_sprite->rotate(360.0f*dt*5.0f);
	_sprite->setPosition(_parent->getPosition());
}

void StaticSpriteComponent::render()
{
	Renderer::queue(_sprite.get());
}