
#include "SpellCaster.h"
#include "cmp_char_sheet.h"
#include "cmp_health.h"
#include "cmp_actor_movement.h"
#include "cmp_projectile.h"
#include "cmp_sprite.h"

SpellCaster* SpellCaster::instance;
SpellCaster::SpellCaster()
{
	cooldowns.push_back(0.5f);//////////fireball cooldown
	cooldowns.push_back(0.5f);//////////water gun cooldown
	cooldowns.push_back(0.5f);//////////sonic boom cooldown
	cooldowns.push_back(0.5f);//////////earth spike cooldown
	cooldowns.push_back(0.25f);////////////////////////////////SWORD ATTACK cooldown
}
SpellCaster* SpellCaster::getInstance()
{
	if (instance == 0)
	{
		instance = new SpellCaster();
	}

	return instance;
}
void SpellCaster::setEntities(std::vector <std::shared_ptr<Entity>>& e) {
	_entities = e;
}
void SpellCaster::cast_spell_id(int id, sf::Vector2f location)
{
	switch (id)
	{
	case 0:
		cast_fire_ball(location);
		break;
	case 1:
		cast_water_gun(location);
		break;
	case 2:
		cast_sonic_boom(location);
		break;
	case 3:
		cast_earth_spike(location);
		break;
	case 4:
		cast_sword_swing(location);
		break;
	default:
		break;
	}
}
void SpellCaster::cast_fire_ball(sf::Vector2f location)
{////////////////////spell ID: 0//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana()>=15)
	{
		health_mana->reduceMana(15);

		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelFire()*8.0f) + 20.0f);
		c2->setType(1);
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->addSpin();
		s->getSprite().setTextureRect({ 0,0,30,30 });
		s->getSprite().setScale({ 1.0f, 1.0f });
		s->getSprite().setOrigin({ 17.0f, 19.0f });

		activeScene->getEnts().push_back(bullet);
	}
}

void SpellCaster::cast_water_gun(sf::Vector2f location)
{////////////////////spell ID: 1//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana()>=15)
	{
		health_mana->reduceMana(15);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelWater()*8.0f) + 20.0f);
		c2->setType(2);
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->addSpin();
		s->getSprite().setTextureRect({ 30,0,30,30 });
		s->getSprite().setScale({ 1.0f, 1.0f });
		s->getSprite().setOrigin({ 15.0f, 15.0f });

		activeScene->getEnts().push_back(bullet);
	}
}
void SpellCaster::cast_sonic_boom(sf::Vector2f location)
{////////////////////spell ID: 2//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana()>=15)
	{
		health_mana->reduceMana(15);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->addKnockback();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelWind()*7.0f) + 15.0f);
		c2->setType(3);
		auto s = bullet->addComponent<StaticSpriteComponent>();
		s->getSprite().setTexture(spellsTexture);
		s->addSpin();
		s->getSprite().setTextureRect({ 60,0,30,30 });
		s->getSprite().setScale({ 1.0f, 1.0f });
		s->getSprite().setOrigin({ 15.0f, 15.0f });

		activeScene->getEnts().push_back(bullet);
	}

}
void SpellCaster::cast_earth_spike(sf::Vector2f location)
{////////////////////spell ID: 3//////////////////////////////////////
	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getMana()>=15)
	{
		health_mana->reduceMana(15);
		auto bullet = std::make_shared<Entity>();
		bullet->setPosition(player->getPosition());
		auto pr = bullet->addComponent<ProjectileMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->addBlind();
		c2->setEntities(_entities);
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage((dmg->getLevelEarth()*8.0f) + 20.0f);
		c2->setType(4);
		auto s = bullet->addComponent<AnimatedSpriteComponent>();
		s->getSprite().setTexture(animatedSpellsTexture);
		s->getSprite().setScale({ 1.0f, 1.0f });
		s->getSprite().setOrigin({ 15.0f, 15.0f });
		s->getSprite().setTextureRect({ 0,0,30,30 });
		s->setDelay(0.1f);
		s->addFrame(sf::IntRect(0, 0, 30, 30));
		s->addFrame(sf::IntRect(0, 0, 30, 30));
		s->addFrame(sf::IntRect(30, 0, 30, 30));
		s->addFrame(sf::IntRect(60, 0, 30, 30));
		s->addFrame(sf::IntRect(90, 0, 30, 30));
		s->addFrame(sf::IntRect(120, 0, 30, 30));

		activeScene->getEnts().push_back(bullet);
	}

}
void SpellCaster::cast_sword_swing(sf::Vector2f location)
{////////////////////spell ID: 4//////////////////////////////////////

	auto health_mana = player->GetComponent<HealthComponent>();
	if (health_mana->getStamina() >= 4)
	{
		health_mana->reduceStamina(4);
		auto bullet = std::make_shared<Entity>();
		auto pr = bullet->addComponent<PlayerMovementComponent>();
		bullet->setFace(player->getFace());
		auto c2 = bullet->addComponent<ProjectileComponent>();
		c2->finishAnimationFirst();
		c2->setEntities(_entities);
		c2->addKnockback();
		auto dmg = player->GetComponent<CharacterSheetComponent>();
		c2->setDamage(dmg->getStatAttack());
		c2->setType(0);
		auto s = bullet->addComponent<AnimatedSpriteComponent>();
		s->getSprite().setTexture(swordSwingTexture);
		s->getSprite().setScale({ 1.0f, 1.0f });
		s->getSprite().setOrigin({ 60, 35 });
		c2->setTimer(0.35f);
		s->setDelay(0.05f);
		s->playOnce();
		s->addFrame(sf::IntRect(0, 0, 100, 70));
		s->addFrame(sf::IntRect(100, 0, 100, 70));
		s->addFrame(sf::IntRect(200, 0, 100, 70));
		s->addFrame(sf::IntRect(300, 0, 100, 70));
		s->addFrame(sf::IntRect(400, 0, 100, 70));
		s->addFrame(sf::IntRect(500, 0, 100, 70));
		s->addFrame(sf::IntRect(600, 0, 100, 70));
		s->getSprite().setTextureRect({ 0, 0, 100, 70 });
		if (player->getFace() == 1)
		{
			bullet->setPosition(player->getPosition() + sf::Vector2f(0, -15.0 *WY / 720));
			s->getSprite().rotate(-90);
		}
		else if (player->getFace() == 2)
		{
			bullet->setPosition(player->getPosition() + sf::Vector2f(15 * WX / 1280, 0));
		}
		else if (player->getFace() == 3)
		{
			s->setPriority(1);
			bullet->setPosition(player->getPosition() + sf::Vector2f(0, 15.0 *WY / 720));
			s->getSprite().rotate(90);
		}
		else if (player->getFace() == 4)
		{
			bullet->setPosition(player->getPosition() + sf::Vector2f(-15 * WX / 1280, 0));
			s->getSprite().rotate(180);
		}
		activeScene->getEnts().push_back(bullet);

	}
}