#pragma once

#include <iostream>
#include <algorithm>

#include "skill.h"

enum class creatureType
{
	min = 0, aberration, beast, celestial, construct, dragon, elemental, fey, fiend, giant, humanoid, monstrosity, ooze, plant, undead, max
};

std::ostream& operator<< (std::ostream& lhs, creatureType rhs);

enum class creatureSize
{
	min = 0, tiny, small, medium, large, huge, gargantuan, max
};

std::ostream& operator<< (std::ostream& lhs, creatureSize rhs);

enum class armorType
{
	min =0, padded, leather, studded, hide, chainShirt, scale, breastplate, halfPlate, ring, chain, splint, plate
};

std::ostream& operator<< (std::ostream& lhs, armorType rhs);

int armorToAC(armorType armor, int dex);

class Monster
{
private:
	int scores[(int)abilityScore::max];
	Skill saves[(int)abilityScore::max];
	std::string name;
	int hitpoints;
	int hitdieSize;
	int hitdice;
	int profBonus;
	double cr;
	int speed;
	int ac;
	creatureType type;
	creatureSize size;
	SkillNode* pHeadSkill;
	armorType armor;
public:
	Monster(std::string newName = "", creatureType newType = creatureType::min, creatureSize newSize = creatureSize::min, int newHitdice = 0, int newHitdieSize = 0, double newCR = 0.125, int newSpeed = 0,
		int newScores[(int)abilityScore::max]=NULL, armorType newArmor = armorType::min, int newAC=-1, int newHitpoints = -1)
	{
		name = newName;
		type = newType;
		size = newSize;
		hitdice = newHitdice;
		hitdieSize = newHitdieSize;
		cr = newCR;
		speed = newSpeed;
		
		for (int count = 0; count < (int)abilityScore::max; count++)
		{
			if (newScores == NULL)
				scores[count] = 0;
			else
				scores[count] = newScores[count];
		}
		armor = newArmor;
		if (newAC <0)
			ac = armorToAC(armor, scores[(int)abilityScore::dexterity]);
		else
			ac = newAC;
		if (newHitpoints < 0)
			hitpoints = hitdiceToHitpoints(hitdieSize, hitdice);
		else
			hitpoints = newHitpoints;

		for (int count = 0; count < (int)abilityScore::max; count++)
		{
			saves[count] = Skill((abilityScore)count,false);
		}
		

	}
	void addSkill(skillName skillToAdd, bool isExpert = false); // theta(n) where n is num of skills already on monster
	void addSave(abilityScore saveToAdd);
};

int hitdiceToHitpoints(int hitdieSize, int hitdiceCount);