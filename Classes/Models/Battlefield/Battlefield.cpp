#include "Battlefield.h"
#include "UI/GameUI.h"
#include "Models/Character/Character.h"
#include "Views/Character/CharacterView.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Battlefield::Battlefield(cocos2d::Node* root, std::unordered_map<int, std::vector<cocos2d::Vec3>> map)
	: _root(root), _spawnPositionsByTeam(std::move(map))
{
	_paused = true;
}

void Battlefield::start(std::vector<CharacterView> prefabs)
{
	auto ui = GameUI::create();
	ui->setName("GameUI");

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	ui->setContentSize(winSize);

	_root->getScene()->addChild(ui, 1000);

	_prefabs = std::move(prefabs);

	ui->onContinue = [this, ui]()
	{
		ui->setVisible(false);
		this->startBattle();
	};

	ui->onRestart = [this, ui]()
	{
		this->resetBattlefield();
		ui->showContinue();
	};
}

void Battlefield::startBattle()
{
	_paused = false;
	_charactersByTeam.clear();

	std::vector<CharacterView> availablePrefabs = _prefabs;
	std::random_device rd;
	std::mt19937 rng(rd());

	for (auto& positionsPair : _spawnPositionsByTeam)
	{
		std::vector<Vec3>& positions = positionsPair.second;
		std::vector<std::shared_ptr<Character>> characters;
		int i = 0;
		while (i < positions.size() && !availablePrefabs.empty())
		{
			std::uniform_int_distribution<int> uni(0, availablePrefabs.size() - 1);
			int index = uni(rng);
			characters.push_back(createCharacterAt(availablePrefabs[index], *this, positions[i]));
			std::swap(availablePrefabs[index], availablePrefabs.back());
			availablePrefabs.pop_back();
			i++;
		}
		_charactersByTeam[positionsPair.first] = characters;
	}
}

void Battlefield::update(float delta)
{
	if (!_paused)
	{
		for (auto& team : _charactersByTeam)
		{
			for (auto& character : team.second)
			{
				character->update(delta);
			}
		}
	}
}

std::shared_ptr<Character> Battlefield::createCharacterAt(
	const CharacterView& prefab,
	Battlefield& battlefield,
	const cocos2d::Vec3& position)
{
	Sprite3D* sprite3d = Sprite3D::create(prefab.model, prefab.texture);
	auto weapon = std::make_shared<Weapon>(prefab.weaponDescriptor, sprite3d, _root);
	auto character = std::make_shared<Character>(sprite3d, prefab.characterDescriptor, weapon, &battlefield);

	_root->addChild(sprite3d);

	character->onDeath = [this]() {
		if (this->getWinnerTeam() != -1)
		{
			_paused = true;

			auto ui = dynamic_cast<GameUI*>(_root->getScene()->getChildByName("GameUI"));
			if (ui)
			{
				ui->setVisible(true);
				ui->showRestart();
			}
		}
	};

	sprite3d->setPosition3D(position);
	sprite3d->setScale(0.3);

	return character;
}

void Battlefield::resetBattlefield()
{
	for (auto& teamPair : _charactersByTeam)
	{
		for (auto& character : teamPair.second)
		{
			if (character)
			{
				auto sprite = character->getSprite3D();
				if (sprite && sprite->getParent())
				{
					sprite->removeFromParentAndCleanup(true);
				}
			}
		}
	}

	_charactersByTeam.clear();
}

int Battlefield::getWinnerTeam() const
{
	int aliveTeamId = -1;

	for (const auto& team : _charactersByTeam)
	{
		bool teamAlive = false;
		for (const auto& ch : team.second)
		{
			if (ch && ch->isAlive())
			{
				teamAlive = true;
				break;
			}
		}

		if (teamAlive)
		{
			if (aliveTeamId == -1)
			{
				aliveTeamId = team.first;
			}
			else
			{
				// Both teams alive
				return -1;
			}
		}
	}

	return aliveTeamId;
}

std::shared_ptr<Character> Battlefield::getNearestAliveTarget(const std::shared_ptr<Character>& character)
{
	int team = getTeam(character.get());
	if (team == -1)
	{
		return nullptr;
	}

	std::shared_ptr<Character> nearestEnemy = nullptr;
	float nearestDistance = FLT_MAX;

	for (auto& charactersPair : _charactersByTeam)
	{
		if (charactersPair.first == team)
		{
			continue;
		}

		for (const auto& enemy : charactersPair.second)
		{
			if (enemy && enemy->isAlive())
			{
				float distance = (character->getPosition() - enemy->getPosition()).length();
				if (distance < nearestDistance)
				{
					nearestDistance = distance;
					nearestEnemy = enemy;
				}
			}
		}
	}
	return nearestEnemy;
}

int Battlefield::getTeam(const Character* target)
{
	for (auto& charactersPair : _charactersByTeam)
	{
		for (auto& character : charactersPair.second)
		{
			if (character.get() == target)
			{
				return charactersPair.first;
			}
		}
	}
	return -1;
}