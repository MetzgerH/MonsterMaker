#pragma once

#include <iostream>
#include <math.h>
#include "strManip.h"

enum class abilityScore : unsigned char //we inherit from char for memory reasons
{
	strength=0, dexterity, constitution, intelligence, wisdom, charisma, max
};

enum class skillName : unsigned char //we inherit from char for memory reasons
{
	min = 0, acrobatics, animalHandling, arcana, athletics, deception, history, insight, intimidation, investigation, medicine, nature, perception, performance, persuasion,
	religion, sleightOfHand, stealth, survival, savingThrow, max
};

abilityScore defaultAbility(skillName skill);

class Skill //this also works with saving throws
{
private:
	skillName name;
	abilityScore associatedAbility;
	bool proficient;
	bool expertise;
public:
	Skill(skillName newName, abilityScore ability = abilityScore::max, bool isProf = true, bool isExpert = false)
	{
		this->name = newName;
		if (ability == abilityScore::max)
			this->associatedAbility = defaultAbility(newName);
		else
			this->associatedAbility = ability;
		this->proficient = isProf;
		this->expertise = isExpert;
	}
	Skill(abilityScore ability, bool isProf = true) //this is for saves
	{
		this->name = skillName::savingThrow;
		this->associatedAbility = ability;
		this->proficient = isProf;
		this->expertise = false;
	}
	Skill(std::string csvEntry)
	{
		name = (skillName)csvEntry[0];
		associatedAbility = (abilityScore)csvEntry[1];
		proficient = (bool)csvEntry[2];
		expertise = (bool)csvEntry[3];
	}
	Skill()
	{
		this->name = skillName::min;
		this->associatedAbility = abilityScore::max;
		this->proficient = false;
		this->expertise = false;
	}
	skillName getName();
	void setName(skillName newName);
	bool isProficient();
	void setProficiency(bool prof);
	bool isExpert();
	void setExpertise(bool expert);
	std::string createCSVEntry(); //does not include the comma
	abilityScore getAbility();
};

class SkillNode
{
public:
	Skill data;
	SkillNode* pNext;
	SkillNode(skillName newName, abilityScore ability = abilityScore::max, bool isProf = true, bool isExpert = false)
	{
		data = Skill(newName, ability, isProf, isExpert);
		pNext = NULL;
	}
	SkillNode(abilityScore abilty)
	{
		data = Skill(abilty);
		pNext = NULL;
	}
};

int scoreToMod(int score);



std::ostream& operator<< (std::ostream& lhs, skillName rhs);
std::istream& operator>> (std::istream& lhs, skillName &rhs);

std::ostream& operator<< (std::ostream& lhs, abilityScore rhs);