#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

#include "skill.h"
#include "attack.h"

extern std::pair<double, int> g_CRProfBonus[34];

enum class creatureType
{
	min = 0, aberration, beast, celestial, construct, dragon, elemental, fey, fiend, giant, humanoid, monstrosity, ooze, plant, undead, max
};

std::ostream& operator<< (std::ostream& lhs, creatureType rhs);
std::istream& operator>> (std::istream& lhs, creatureType &rhs);

enum class creatureSize
{
	min = 0, tiny, small, medium, large, huge, gargantuan, max
};

std::ostream& operator<< (std::ostream& lhs, creatureSize rhs);
std::istream& operator>> (std::istream& lhs, creatureSize& rhs);
//std::ifstream& operator>> (std::ifstream& lhs, creatureSize rhs);

enum class armorType
{
	min =0, padded, leather, studded, hide, chainShirt, scale, breastplate, halfPlate, ring, chain, splint, plate, natural, max
};



std::ostream& operator<< (std::ostream& lhs, armorType rhs);
std::istream& operator>> (std::istream& lhs, armorType &rhs);

enum class language
{
	min = 0, abyssal, aquan, auran, celestial, common, deepSpeech, draconic, druidic, dwarvish, elvish, giant, gnomish, goblin, gnoll, halfling, ignan, 
	infernal, orc, primordial, sylvan, terran, undercommon, thievesCant, max
};

std::ostream& operator<< (std::ostream& lhs, language rhs);
std::istream& operator>> (std::istream& lhs, language& rhs);

int armorToAC(armorType armor, int dex);
int hitdiceToHitpoints(int hitdieSize, int hitdiceCount);

class Monster
{
	
public:
	int scores[(int)abilityScore::max];
	Skill saves[(int)abilityScore::max];
	std::string name;
	unsigned short int hitdieSize;
	unsigned short int hitdice;
	unsigned short int hitpoints;
	double cr;
	unsigned short int speed;
	unsigned short int ac;
	unsigned short int profBonus;
	unsigned short int climb;//0 if doesn't have
	unsigned short int burrowing;//0 if doesn't have
	unsigned short int swim;//0 if doesn't have
	unsigned short int flying; //0 if doesn't have
	unsigned short int legendaryResistances; //0 if doesn't have
	unsigned short int darkvision;
	unsigned short int blindsight;
	unsigned short int tremorsense;
	unsigned short int truesight;
	creatureType type;
	creatureSize size;
	armorType armor;
	std::vector<language> langs;
	std::vector<Skill> skills;

	std::vector<Feature> features;
	std::vector<Attack> attacks;
	std::vector<LegendaryAction> legendaryActions; 
	std::vector<damageType> resistances;
	std::vector<damageType> immunities;

	int effectiveAC();
	int pickBestAttack(); //gives the vector pos of the attack that does the most damage





	Monster(std::string newName = "", creatureType newType = creatureType::min, creatureSize newSize = creatureSize::min, int newHitdice = 0, int newHitdieSize = 0, double newCR = 0.125, int newSpeed = 0,
		int newScores[(int)abilityScore::max] = NULL, armorType newArmor = armorType::min, int newAC = -1, int newHitpoints = -1)
	{
		name = newName;
		type = newType;
		size = newSize;
		hitdice = newHitdice;
		hitdieSize = newHitdieSize;
		cr = newCR;
		speed = newSpeed;
		flying = 0;
		burrowing = 0;
		swim = 0;
		climb = 0;
		legendaryResistances = 0;

		for (int count = 0; count < (int)abilityScore::max; count++)
		{
			if (newScores == NULL)
				scores[count] = 0;
			else
				scores[count] = newScores[count];
		}
		armor = newArmor;
		if (newAC < 0)
			ac = armorToAC(armor, scores[(int)abilityScore::dexterity]);
		else
			ac = newAC;
		if (newHitpoints < 0)
			hitpoints = hitdiceToHitpoints(hitdieSize, hitdice);
		else
			hitpoints = newHitpoints;

		for (int count = 0; count < (int)abilityScore::max; count++)
		{
			saves[count] = Skill((abilityScore)count, false);
		}

		profBonus = estimatePB();

		darkvision = 0;
		truesight = 0;
		blindsight = 0;
		tremorsense = 0;
	}
	void addSave(abilityScore saveToAdd);
	int getBestAttackBonus();
	int getBestSaveDC();
	int getBestDamage();
	bool usesSave();
	double estimatePB();


	

};



double calculateCR(Monster* monster);