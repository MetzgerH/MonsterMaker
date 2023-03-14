#include "attack.h"

#include <stdlib.h>

std::istream& operator>> (std::istream& lhs, damageType& rhs)
{
	std::string input;
	lhs >> input;
	if (input == "acid" || input == "Acid")
	{
		rhs = damageType::acid;
		return lhs;
	}
	if (input == "bludgeoning" || input == "Bludgeoning")
	{
		rhs = damageType::bludgeoning;
		return lhs;
	}
	if (input == "cold" || input == "Cold")
	{
		rhs = damageType::cold;
		return lhs;
	}
	if (input == "fire" || input == "Fire")
	{
		rhs = damageType::fire;
		return lhs;
	}
	if (input == "force" || input == "Force")
	{
		rhs = damageType::force;
		return lhs;
	}
	if (input == "lightning" || input == "Lightning")
	{
		rhs = damageType::lightning;
		return lhs;
	}
	if (input == "necrotic" || input == "Necrotic")
	{
		rhs = damageType::necrotic;
		return lhs;
	}
	if (input == "piercing" || input == "Piercing")
	{
		rhs = damageType::piercing;
		return lhs;
	}
	if (input == "poison" || input == "Poison")
	{
		rhs = damageType::poison;
		return lhs;
	}
	if (input == "psychic" || input == "Psychic")
	{
		rhs = damageType::psychic;
		return lhs;
	}
	if (input == "radiant" || input == "Radiant")
	{
		rhs = damageType::radiant;
		return lhs;
	}
	if (input == "slashing" || input == "Slashing")
	{
		rhs = damageType::slashing;
		return lhs;
	}
	rhs = damageType::min;
	return lhs;
}

double Attack::averageDamage(int scores[(int)abilityScore::max])
{
	double output = (((double)dieSize / 2) + 0.5) * dice;
	if (addModToDamage)
	{
		if (isMagic)
		{
			//add the greatest modifier out of the mental abilities
			output += scoreToMod(std::max(std::max(scores[(int)abilityScore::charisma],
				scores[(int)abilityScore::wisdom]), 
				scores[(int)abilityScore::intelligence]));
		}
		else
		{
			//add the greater modifier out of strength and dexterity
			output += scoreToMod(std::max(scores[(int)abilityScore::strength], 
				scores[(int)abilityScore::dexterity]));
		}
	}
	if (aoe)
		output *= 2;
	return output;
}

int Attack::attackBonus(int scores[(int)abilityScore::max])
{
	if (isMagic)
	{
		//return the greatest modifier out of the mental abilities
		return( scoreToMod(std::max(std::max(scores[(int)abilityScore::charisma],
			scores[(int)abilityScore::wisdom]),
			scores[(int)abilityScore::intelligence])));
	}
	
		//return the greater modifier out of strength and dexterity
	return (scoreToMod(std::max(scores[(int)abilityScore::strength],
		scores[(int)abilityScore::dexterity])));
}

int Attack::saveDC(int scores[(int)abilityScore::max], int profBonus)
{
	int output = 8 + profBonus;
	if (isMagic)
	{
		//return output + the greatest modifier out of the mental abilities
		return output+(scoreToMod(std::max(std::max(scores[(int)abilityScore::charisma],
			scores[(int)abilityScore::wisdom]),
			scores[(int)abilityScore::intelligence])));
	}

	//return output + the greater modifier out of strength and dexterity
	return output+(scoreToMod(std::max(scores[(int)abilityScore::strength],
		scores[(int)abilityScore::dexterity])));
}

std::string Feature::bodyWithoutCommas()
{
	std::string output = body;
	for (int count = 0; count < output.size(); count++)
	{
		if (output[count] == ',')
			output[count] = ';';
	}
	return output;
}

std::string Feature::restoreCommas(std::string input)
{
	std::string output = input;
	for (int count = 0; count < output.size(); count++)
	{
		if (output[count] == ',')
			output[count] = ';';
	}
	return output;
}

std::string Feature::createCSVEntry()
{
	std::string output = "";

	//character at 0: name's length (<256 length is assumed for names)
	output += (char)name.size();

	output += name;

	output += body;

	return output;
}

std::string LegendaryAction::createCSVEntry()
{
	std::string output = "";
	if (ptrAttack != nullptr)
	{
		output += (char)ptrAttack->name.size();
		output += ptrAttack->name;
	}
	else
		output += (char)254;

	//the rest of the chars are formatted as Feature's is except starting at 16
	output += this-> Feature::createCSVEntry();

	return output;

}

std::string Attack::createCSVEntry()
{
	std::string output = "";
	output += (char) isMagic;
	output += (char)useSave;
	output += (char)aoe;
	output += (char)addModToDamage;
	output += (char)type;
	output += (char)dieSize;
	output += (char)dice;
	output += (char)reach; 
	output += (char)shortRange; 
	//output += (char) longRange; //longRange can be higher than 256
	output += (char)(longRange / 256);
	output += (char)(longRange % 256);
	return output;
}