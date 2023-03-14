#include <vector>

#include "skill.h"

enum class damageType
{
	min=0, acid, bludgeoning, cold, fire, force, lightning, necrotic, piercing, poison, psychic, radiant, slashing, thunder, max
};

std::istream& operator>> (std::istream& lhs, damageType& rhs);

class Attack
{
private:
	

public:
	bool isMagic; //if isMagic then use best of wis/int/cha, if !isMagic then use best of str/dex
	bool useSave;
	bool aoe; //area of effects are treated as if they always hit 2 creatures
	bool addModToDamage;
	damageType type;
	unsigned int dieSize;
	unsigned int dice;
	unsigned int reach; //0 if ranged
	unsigned int shortRange; //0 if melee
	unsigned int longRange; //0 if melee

	std::string name;
	Attack(std::string newName, unsigned int die, unsigned int diceCount, bool magic = false, bool areaOfEffect = false, bool save = false, bool addMod = false,
		damageType newType = damageType::bludgeoning, unsigned int newReach = 0, unsigned int lowRange=0, unsigned int highRange=0)
	{
		name = newName;
		dieSize = die;
		dice = diceCount;
		isMagic = magic;
		aoe = areaOfEffect;
		useSave = save;
		addModToDamage = addMod;
		reach = newReach;
		shortRange = lowRange;
		longRange = highRange;
		type = newType;
	}
	Attack(const std::string & csvEntry)
	{
		isMagic = (bool)csvEntry[0];
		useSave = (bool)csvEntry[1];
		aoe = (bool)csvEntry[2];
		addModToDamage = (bool)csvEntry[3];
		type = (damageType)csvEntry[4];
		dieSize = (unsigned int)csvEntry[5];
		dice = (unsigned int)csvEntry[6];
		reach = (unsigned int)csvEntry[7]; 
		shortRange = (unsigned int)csvEntry[8]; 
		//longRange = (unsigned int)csvEntry[9]; 
		longRange = (unsigned int)((int)csvEntry[9] * 256 + (int)csvEntry[10]);

		name = csvEntry.substr(11);
	}

	double averageDamage(int scores[(int)abilityScore::max]);
	int attackBonus(int scores[(int)abilityScore::max]);
	int saveDC(int scores[(int)abilityScore::max], int profBonus);
	 std::string createCSVEntry();
};

class Feature
{
	std::string bodyWithoutCommas(); //turns commas into semicolons
	std::string restoreCommas(std::string input);
public:
	std::string name;
	std::string body;
	Feature()
	{
		name = "";
		body = "";
	}
	Feature(std::string newName, std::string newBody)
	{
		name = newName;
		body = newBody;
	}
	Feature(std::string csvEntry)
	{
		if (csvEntry.size() < 1) //if the csv entry is too small
		{
			name = "";
			body = "";
			std::cout << "feature failed to read a csv entry" << std::endl;
			return;
		}
		

		//now read in name's size
		int nameLength = (int)csvEntry[0];
		name = csvEntry.substr(1, nameLength);

		//now read in body
		body = csvEntry.substr(nameLength);
	}
	
	virtual std::string createCSVEntry();
};


class LegendaryAction : public Feature
{
public:
	Attack* ptrAttack; //legendary features that allow an attack will have a corresponding attack on the monster's statblock that can be pointed to, instead of stored as a different object
	//using ptr could become a huge problem when it comes to copying

	LegendaryAction(std::string csvEntry, Attack* ptr = nullptr) : Feature(csvEntry)
	{
		ptrAttack = ptr;
	};

	std::string createCSVEntry();
};
