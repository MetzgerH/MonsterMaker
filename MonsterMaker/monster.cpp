#include "monster.h"

std::ostream& operator<< (std::ostream& lhs, creatureType rhs)
{
	switch (rhs)
	{
	case creatureType::aberration:
		return lhs << "aberration";
	case creatureType::beast:
		return lhs << "beast";
	case creatureType::celestial:
		return lhs << "celestial";
	case creatureType::construct:
		return lhs << "construct";
	case creatureType::dragon:
		return lhs << "dragon";
	case creatureType::elemental:
		return lhs << "elemental";
	case creatureType::fey:
		return lhs << "fey";
	case creatureType::fiend:
		return lhs << "fiend";
	case creatureType::giant:
		return lhs << "giant";
	case creatureType::humanoid:
		return lhs << "humanoid";
	case creatureType::monstrosity:
		return lhs << "monstrosity";
	case creatureType::ooze:
		return lhs << "ooze";
	case creatureType::plant:
		return lhs << "plant";
	case creatureType::undead:
		return lhs << "undead";
	default:
		return lhs;
	}
}

std::ostream& operator<< (std::ostream& lhs, creatureSize rhs)
{
	switch (rhs)
	{
	case creatureSize::tiny:
		return lhs << "tiny";
	case creatureSize::small:
		return lhs << "small";
	case creatureSize::medium:
		return lhs << "medium";
	case creatureSize::large:
		return lhs << "large";
	case creatureSize::huge:
		return lhs << "huge";
	case creatureSize::gargantuan:
		return lhs << "gargantuan";
	default:
		return lhs;
	}
}

std::ostream& operator<< (std::ostream& lhs, armorType rhs)
{
	switch (rhs)
	{
	case armorType::padded:
		return lhs << "padded leather";
	case armorType::leather:
		return lhs << "leather";
	case armorType::studded:
		return lhs << "studded leather";
	case armorType::hide:
		return lhs << "hide";
	case armorType::chainShirt:
		return lhs << "chain shirt";
	case armorType::scale:
		return lhs << "scale mail";
	case armorType::breastplate:
		return lhs << "breastplate";
	case armorType::halfPlate:
		return lhs << "half plate";
	case armorType::ring:
		return lhs << "ring mail";
	case armorType::chain:
		return lhs << "chain mail";
	case armorType::splint:
		return lhs << "splint";
	case armorType::plate:
		return lhs << "plate";
	default:
		return lhs;
	}
}

int armorToAC(armorType armor, int dex)
{
	switch (armor)
	{
	case armorType::padded:
		return 11 + scoreToMod(dex);
	case armorType::leather:
		return 11 + scoreToMod(dex);
	case armorType::studded:
		return 12 + scoreToMod(dex);
	case armorType::hide:
		return 12 + std::min(2, scoreToMod(dex));
	case armorType::chainShirt:
		return 13 + std::min(2, scoreToMod(dex));
	case armorType::scale:
		return 14 + std::min(2, scoreToMod(dex));
	case armorType::breastplate:
		return 14 + std::min(2, scoreToMod(dex));
	case armorType::halfPlate:
		return 15 + std::min(2, scoreToMod(dex));
	case armorType::ring:
		return 14;
	case armorType::chain:
		return 16;
	case armorType::splint:
		return 17;
	case armorType::plate:
		return 18;
	default:
		return 10 + scoreToMod(dex);
	}
}

int hitdiceToHitpoints(int hitdieSize, int hitdiceCount)
{
	return floor((((double)hitdieSize / 2) + 0.5) * hitdiceCount);
}

void Monster::addSkill(skillName skillToAdd, bool isExpert = false)
{
	if (pHeadSkill == NULL)
		pHeadSkill = new SkillNode(skillToAdd, defaultAbility(skillToAdd), true, isExpert);
	else
	{
		SkillNode* pCurrent = pHeadSkill;
		while (pCurrent->pNext == NULL)
			pCurrent = pCurrent->pNext;
		pCurrent->pNext = new SkillNode(skillToAdd, defaultAbility(skillToAdd), true, isExpert);
	}
}

void Monster::addSave(abilityScore saveToAdd)
{
	saves[(int)saveToAdd].setProficiency(true);
}