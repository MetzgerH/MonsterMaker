#include "skill.h"


std::string Skill::createCSVEntry()
{
	std::string output = "";
	output += (char)name;
	output += (char)associatedAbility;
	output += (char)proficient;
	output += (char)expertise;
	return output;
}

skillName Skill::getName()
{
	return this->name;
}
void Skill::setName(skillName newName)
{
	this->name = newName;
}

bool Skill::isProficient()
{
	return this->proficient;
}

bool Skill::isExpert()
{
	return this->expertise;
}

abilityScore Skill::getAbility()
{
	return associatedAbility;
}

void Skill::setProficiency(bool prof)
{
	proficient = prof;
	return;
}

void Skill::setExpertise(bool expert)
{
	expertise = expert;
	return;
}


int scoreToMod(int score)
{
	return (int) std::floor((double)(score / 2) - 5);
}

abilityScore defaultAbility(skillName skill)
{
	switch (skill)
	{
	case skillName::acrobatics:
		return abilityScore::dexterity;
	case skillName::animalHandling:
		return abilityScore::wisdom;
	case skillName::arcana:
		return abilityScore::intelligence;
	case skillName::athletics:
		return abilityScore::strength;
	case skillName::deception:
		return abilityScore::charisma;
	case skillName::history:
		return abilityScore::intelligence;
	case skillName::insight:
		return abilityScore::wisdom;
	case skillName::intimidation:
		return abilityScore::charisma;
	case skillName::investigation:
		return abilityScore::intelligence;
	case skillName::medicine:
		return abilityScore::wisdom;
	case skillName::nature:
		return abilityScore::intelligence;
	case skillName::perception:
		return abilityScore::wisdom;
	case skillName::performance:
		return abilityScore::charisma;
	case skillName::persuasion:
		return abilityScore::charisma;
	case skillName::religion:
		return abilityScore::intelligence;
	case skillName::sleightOfHand:
		return abilityScore::dexterity;
	case skillName::stealth:
		return abilityScore::dexterity;
	case skillName::survival:
		return abilityScore::wisdom;
	default:
		return abilityScore::max;
	}
}


std::ostream& operator<< (std::ostream& lhs, skillName rhs)
{
	switch (rhs)
	{
	case skillName::acrobatics:
		return lhs << "acrobatics";
	case skillName::animalHandling:
		return lhs << "animal handling";
	case skillName::arcana:
		return lhs << "arcana";
	case skillName::athletics:
		return lhs << "athletics";
	case skillName::deception :
		return lhs << "deception";
	case skillName::history:
		return lhs << "history";
	case skillName::insight:
		return lhs << "insight";
	case skillName::intimidation:
		return lhs << "intimidation";
	case skillName::investigation:
		return lhs << "investigation";
	case skillName::medicine:
		return lhs << "medicine";
	case skillName::nature:
		return lhs << "nature";
	case skillName::perception:
		return lhs << "perception";
	case skillName::performance:
		return lhs << "performance";
	case skillName::persuasion:
		return lhs << "persuasion";
	case skillName::religion:
		return lhs << "religion";
	case skillName::sleightOfHand:
		return lhs << "sleight of hand";
	case skillName::stealth:
		return lhs << "stealth";
	case skillName::survival:
		return lhs << "survival";
	default:
		return lhs;
	}
}

std::istream& operator>> (std::istream& lhs, skillName& rhs)
{
	std::string skill;
	lhs >> skill;

	shaveAstrerisks(skill);

	if (skill == "acrobatics" || skill == "Acrobatics")
	{
		rhs = skillName::acrobatics;
		return lhs;
	}
	if (skill == "animal handling" || skill == "Animal Handling")
	{
		rhs = skillName::animalHandling;
		return lhs;
	}
	if (skill == "arcana" || skill == "Arcana")
	{
		rhs = skillName::arcana;
		return lhs;
	}
	if (skill == "athletics" || skill == "Athletics")
	{
		rhs = skillName::athletics;
		return lhs;
	}
	if (skill == "deception" || skill == "Deception")
	{
		rhs = skillName::deception;
		return lhs;
	}
	if (skill == "history" || skill == "History")
	{
		rhs = skillName::history;
		return lhs;
	}
	if (skill == "insight" || skill == "Insight")
	{
		rhs = skillName::insight;
		return lhs;
	}
	if (skill == "intimidation" || skill == "Intimidation")
	{
		rhs = skillName::intimidation;
		return lhs;
	}
	if (skill == "investigation" || skill == "Investigation")
	{
		rhs = skillName::investigation;
		return lhs;
	}
	if (skill == "medicine" || skill == "Medicine")
	{
		rhs = skillName::medicine;
		return lhs;
	}
	if (skill == "nature" || skill == "Nature")
	{
		rhs = skillName::nature;
		return lhs;
	}
	if (skill == "perception" || skill == "Perception")
	{
		rhs = skillName::perception;
		return lhs;
	}
	if (skill == "performance" || skill == "Performance")
	{
		rhs = skillName::performance;
		return lhs;
	}
	if (skill == "persuasion" || skill == "Persuasion")
	{
		rhs = skillName::persuasion;
		return lhs;
	}
	if (skill == "religion" || skill == "Religion")
	{
		rhs = skillName::religion;
		return lhs;
	}
	if (skill == "sleight of hand" || skill == "Sleight Of Hand")
	{
		rhs = skillName::sleightOfHand;
		return lhs;
	}
	if (skill == "stealth" || skill == "Stealth")
	{
		rhs = skillName::stealth;
		return lhs;
	}
	if (skill == "survival" || skill == "Survival")
	{
		rhs = skillName::survival;
		return lhs;
	}
	rhs = skillName::min;
	return lhs;
}

std::ostream& operator<< (std::ostream& lhs, abilityScore rhs)
{
	switch (rhs)
	{
	case abilityScore::strength:
		return lhs << "Strength";
	case abilityScore::dexterity:
		return lhs << "Dexterity";
	case abilityScore::constitution:
		return lhs << "Constitution";
	case abilityScore::charisma:
		return lhs << "Charisma";
	case abilityScore::intelligence:
		return lhs << "Intelligence";
	case abilityScore::wisdom:
		return lhs << "Wisdom";
	default:
		return lhs;
	}
}