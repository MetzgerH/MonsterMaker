#pragma once

#include <iostream>

enum class abilityScore :char //we inherit from char for memory reasons
{
	strength=0, dexterity, constitution, intelligence, wisdom, charisma, max
};

enum class skillName : char //we inherit from char for memory reasons
{
	min = 0, acrobatics, animalHandling, arcana, athletics, deception, history, insight, intimidation, investigation, medicine, nature, perception, performance, persuasion,
	religion, sleightOfHand, stealth, survival, savingThrow, max
};



class Skill //this also works with saving throws
{
private:
	skillName name;
	abilityScore associatedAbility;
	bool proficient;
	bool expertise;
public:
	Skill(skillName newName, abilityScore ability, bool isProf, bool isExpert);
	Skill(abilityScore ability, bool isProf= true); //this is for saves
	Skill();
	/*skillName getName();
	void setName(skillName newName);*/
	bool isProficient();
	void setProficiency(bool prof);
	bool isExpert();
	void setExpertise(bool expert);
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

abilityScore defaultAbility(skillName skill);

std::ostream& operator<< (std::ostream& lhs, skillName rhs);

std::ostream& operator<< (std::ostream& lhs, abilityScore rhs);