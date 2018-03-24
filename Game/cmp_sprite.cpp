#include "cmp_sprite.h"
#include "SystemRenderer.h"
#include <iostream>
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

SpriteComponent::SpriteComponent(Entity *p) : Component(p), _sprite(std::make_shared<sf::Sprite>())
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

void SpriteComponent::update(double dt) 
{
	
	AnimationCounter -= dt;
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
	
	_sprite->setPosition(_parent->getPosition());
}

void SpriteComponent::render() {
	Renderer::queue(_sprite.get());
}
sf::Sprite& SpriteComponent::getSprite() const {
	return *_sprite;
}

