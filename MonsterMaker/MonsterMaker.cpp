// MonsterMaker.cpp : Defines the entry point for the application.
//

#include "MonsterMaker.h"
#include <iostream>

using namespace std;

int main()
{
	std::string filename = "../../../../MonsterMaker/statblocks/goblin.txt";
	std::fstream goblinFile;
	goblinFile.open(filename, ios::in);
	/*std::string test;
	goblin >> test;
	std::cout<< test;
	goblin >> test;
	std::cout << test;
	goblin >> test;
	std::cout << test;*/
	Monster goblin = importMonster(&goblinFile);
	goblinFile.close();

	std::string csvName = "../../../../MonsterMaker/storedMonsters.csv";
	
	std::fstream testCSV;
	testCSV.open(csvName, ios::out);
	exportToCSV(&testCSV, &goblin);
	testCSV.close();

	testCSV.open(csvName, ios::in);
	Monster goblinInAndOut = importFromCSV(&testCSV);
	testCSV.close();

	testCSV.open(csvName, ios::out);
	exportToCSV(&testCSV, &goblin);
	exportToCSV(&testCSV, &goblinInAndOut);
	testCSV.close();


	return 0;
}

Monster importMonster(std::fstream* input)
{
	char nextChar = 'Q';
	while (nextChar != '#')
		*input >> nextChar;
	*input >> nextChar;
	std::string name;
	*input >> name;
	Monster output(name);

	for (int count = 0; count < 2; count++)
	{
		char eater;
		*input >> eater;
	}


	*input >> output.size;


	*input >> output.type;

	for (int asterisk = 0; asterisk < 5;)
	{
		char eater;
		*input >> eater;
		if (eater == '*')
			asterisk++;
	}

	int ac;
	*input >> ac;
	output.ac = ac;

	*input >> nextChar;
	if (nextChar == '(')
	{
		*input >> nextChar; //eat the asterisk
		*input >> output.armor;

	}

	while (nextChar != '-')
		*input >> nextChar;
	for (int asterisk = 0; asterisk < 4;)
	{
		char eater;
		*input >> eater;
		if (eater == '*')
			asterisk++;
	}

	*input >> output.hitpoints;
	*input >> nextChar; // eat the '('
	*input >> output.hitdice; 
	*input >> nextChar; //eat the 'd'
	*input >> output.hitdieSize;

	for (int asterisk = 0; asterisk < 4;)
	{
		char eater;
		*input >> eater;
		if (eater == '*')
			asterisk++;
	}
	*input >> output.speed;

	for (int count = 0; count < 4; count++)
		*input >> nextChar; //eat the "ft."
	while (nextChar == ',') //if its a list of speeds;
	{
		std::string movementType;
		*input >> movementType;
		if (movementType == "fly")
			*input >> output.flying;
		else if (movementType == "burrow")
			*input >> output.burrowing;
		else if (movementType == "swim")
			*input >> output.swim;
		for (int count = 0; count < 4; count++)
			*input >> nextChar; //eat the "ft." and potentially the ","
	}

	for (int colons = 0; colons < 12;) // eat chars until we eat the table's establishment row
	{
		char eater;
		*input >> eater;
		if (eater == ':')
			colons++;
	}
	*input >> nextChar;
	
	for (int count = (int)abilityScore::strength; count < (int)abilityScore::max; count++)
	{
		do
			*input >> nextChar;
		while (nextChar != '|');
		*input >> output.scores[count];
	}

	for (int count = 0; count < 10; count++)
		*input >> nextChar;

	while (nextChar != '_') //take in basic attributes
	{
		if (nextChar == '*')
		{
			*input >> nextChar; //eat next *
			std::string component;
			*input >> component;
			if (component == "Skills" || component == "Skills**") //this does not account for expertise yet
			{
				do
				{
					skillName newSkill;
					*input >> newSkill;
					if (newSkill == skillName::min)
						*input >> newSkill;
					Skill fullSkill(newSkill);
					output.skills.push_back(fullSkill);
					*input >> nextChar; //eat the '+'
					int eatInt;
					*input >> eatInt;
					*input >> nextChar;
				} while (nextChar == ',');
			}

			if (component == "Senses" || component == "Senses**")
			{
				do
				{
					std::string sense;
					*input >> sense;
					if (sense == "darkvision")
						*input >> output.darkvision;
					else if (sense == "blindsight")
						*input >> output.blindsight;
					else if (sense == "tremorsense")
						*input >> output.tremorsense;
					else if (sense == "truesight")
						*input >> output.truesight;
					*input >> nextChar;
					*input >> nextChar;
					*input >> nextChar;
					*input >> nextChar;
				} while (nextChar == ',');
			}
			
			if (component == "Languages" || component == "Languages**")
			{
				do
				{
					language lang;
					*input >> lang;
					if (lang == language::min)
					{
						break;
					}
					output.langs.push_back(lang);
				}while(nextChar != ' ');
			}

			if (component == "Challenge" || component == "Challenge**" || component == "CR" || component == "CR**")
			{
				double inCR;
				*input >> inCR;
				*input >> nextChar;
				if (nextChar == '/')
				{
					double denominator;
					*input >> denominator;
					inCR = inCR / denominator;
				}
				output.cr = inCR;
				output.profBonus = output.estimatePB();
			}
			
			if (component == "Proficiency" || component == "proficiency")
			{
				*input >> component; //eat the "Bonus**"
				*input >> nextChar;
				while (nextChar != '+')
					*input >> nextChar;
				*input >> output.profBonus;
			}
			
		}
		*input >> nextChar;
	}
	
	while (nextChar != '#') //take in traits/features
	{
		if (nextChar == '*')
		{
			std::string traitName;
			std::string traitAppender;
			*input >> traitName;
			if (traitName[traitName.size() - 1] != '*')
			{
				*input >> traitAppender;
				while (traitAppender[traitAppender.size() - 1] != '*')
				{
					traitName += " ";
					traitName += traitAppender;
					*input >> traitAppender;
				}
				traitName += " ";
				traitName += traitAppender;
			}
			shaveAstrerisks(traitName);
			std::string bodyText;
			std::string bodyAppender;
			*input >> bodyText;
			*input >> bodyAppender;
			while (bodyAppender != ">") 
			{
				bodyText += " ";
				bodyText += bodyAppender;
				*input >> bodyAppender;
			}
			Feature newFeature (traitName, bodyText);
			output.features.push_back(newFeature);
		}
		*input >> nextChar;
	}
	
	for (int count = 0; count < 10; count++)
		*input >> nextChar;

	while (nextChar != '#') //take in traits/features
	{
		if (nextChar == '*')
		{
			std::string traitName;
			std::string traitAppender;
			*input >> traitName;
			if (traitName[traitName.size() - 1] != '*')
			{
				*input >> traitAppender;
				while (traitAppender[traitAppender.size() - 1] != '*')
				{
					traitName += " ";
					traitName += traitAppender;
					*input >> traitAppender;
				}
				traitName += " ";
				traitName += traitAppender;
			}
			shaveAstrerisks(traitName);
			std::string bodyText;
			std::string bodyAppender;
			*input >> bodyText;
			shaveAstrerisks(bodyText);
			if (bodyText == "Melee" || bodyText == "melee" || bodyText == "Ranged" || bodyText == "Ranged")
			{
				bool isMelee = bodyText == "Melee" || bodyText == "melee";
				*input >> bodyText;
				shaveAstrerisks(bodyText);
				bool isMagic = bodyText == "Spell" || bodyText == "spell";
				while (bodyText != "hit," && bodyText != "hit.")
					*input >> bodyText;
				*input >> bodyText; //intake "reach" or "range"
				int reach;
				int lowRange;
				int highRange;
				if (isMelee)
				{
					*input >> reach;
					lowRange = 0;
					highRange = 0;
				}
				else
				{
					reach = 0;
					*input >> lowRange;
					*input >> nextChar; //intake the '/'
					*input >> highRange;
				}
				*input >> bodyText; //intake "ft."
				*input >> bodyText;
				bool isAOE = !(bodyText == "one" || bodyText == "One");
				while (nextChar != '(')
					*input >> nextChar;
				int numDice;
				*input >> numDice;
				*input >> nextChar; //intake 'd'
				int dieSize;
				*input >> dieSize;
				bool addModToDamage = false;
				while (nextChar != ')')
				{
					*input >> nextChar;
					if (nextChar == '+') //if there's an added modifier
						addModToDamage = true;
				}
				damageType type;
				*input >> type;
				Attack newAtk(traitName, dieSize, numDice, isMagic, isAOE, false, addModToDamage, type, reach, lowRange, highRange);
				output.attacks.push_back(newAtk);
			}
			else
			{
				*input >> bodyAppender;
				while (bodyAppender != ">")
				{
					bodyText += " ";
					bodyText += bodyAppender;
					*input >> bodyAppender;
				}
				Feature newFeature (traitName, bodyText);
				output.features.push_back(newFeature);
			}
		}
		*input >> nextChar;
	}
	*input >> nextChar;//take in next '#'
	*input >> nextChar;
	if (nextChar == '#') //if there are 3 #'s then there's more to the statblock, likely legendary actions
	{
		
	}
	return output;
}


void exportToCSV(std::fstream* output, Monster * monster)
{
	*output << monster->name;
	*output << ',';
	for (int count = 0; count < (int)abilityScore::max; count++)
	{
		*output << monster->scores[count];
		*output << ',';
	}
	for (int count = 0; count < (int)abilityScore::max; count++)
	{
		*output << monster->saves[count].createCSVEntry();
		*output << ',';
	}
	*output << monster->hitdieSize;
	*output << ',';
	*output << monster->hitdice;
	*output << ',';
	*output << monster->hitpoints;
	*output << ',';
	*output << monster->cr;
	*output << ',';
	*output << monster->speed;
	*output << ',';
	*output << monster->ac;
	*output << ',';
	*output << monster->profBonus;
	*output << ',';
	*output << monster->climb;
	*output << ',';
	*output << monster->burrowing;
	*output << ',';
	*output << monster->swim;
	*output << ',';
	*output << monster->flying;
	*output << ',';
	*output << monster->legendaryResistances;
	*output << ',';
	*output << monster->darkvision;
	*output << ',';
	*output << monster->blindsight;
	*output << ',';
	*output << monster->tremorsense;
	*output << ',';
	*output << monster->truesight;
	*output << ',';
	*output << (int)monster->type;
	*output << ',';
	*output << (int)monster->size;
	*output << ',';
	*output << (int)monster->armor;
	*output << ',';
	for (int count = 0; count < monster->langs.size(); count++)
	{
		*output << (int)monster->langs[count];
		*output << ',';
	}
	*output << "done"; //since there may be any number of langs, we need an indication of when the skills stop
	*output << ',';
	for (int count = 0; count < monster->skills.size(); count++)
	{
		*output << monster->skills[count].createCSVEntry();
		*output << ',';
	}
	*output << "done"; //since there may be any number of skills, we need an indication of when the skills stop
	*output << ',';

	for (int count = 0; count < monster->features.size(); count++)
	{
		*output << monster->features[count].createCSVEntry();
		*output << ',';
	}
	*output << "done"; //since there may be any number of features, we need an indication of when the features stop
	*output << ',';

	for (int count = 0; count < monster->attacks.size(); count++)
	{
		*output << monster->attacks[count].createCSVEntry();
		*output << ',';
	}
	*output << "done"; //since there may be any number of attacks, we need an indication of when the attacks stop
	*output << ',';

	for (int count = 0; count < monster->legendaryActions.size(); count++)
	{
		*output << monster->legendaryActions[count].createCSVEntry();
		*output << ',';
	}
	*output << "done";
	*output << ',';

	for (int count = 0; count < monster->resistances.size(); count++)
	{
		*output << (char)monster->resistances[count]; //there are much less than 256 resistance options so we can store them characters that we treat as ints
	}
	*output << ',';

	for (int count = 0; count < monster->immunities.size(); count++)
	{
		*output << (char)monster->immunities[count]; //there are much less than 256 resistance options so we can store them characters that we treat as ints
	}
	*output << ',';
	*output << '\n';
}

Monster importFromCSV(std::fstream* input)
{
	char nextChar = 'Q';
	std::string name = "";

	*input >> nextChar;
	while (nextChar != ',')
	{
		name += nextChar;
		*input >> nextChar;
	}
	Monster output(name);

	for (int count = 0; count < (int)abilityScore::max; count++)
	{
		*input >> output.scores[count];
		*input >> nextChar; //eat comma
	}

	for (int count = 0; count < (int)abilityScore::max; count++)
	{
		std::string saveEntry = "";
		getline(*input, saveEntry, ',');
		output.saves[count] = Skill(saveEntry);
	}

	std::string nextEntry = "";

	getline(*input, nextEntry, ',');
	output.hitdieSize = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.hitdice = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.hitpoints = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.cr = stod(nextEntry);
	getline(*input, nextEntry, ',');
	output.speed = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.ac = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.profBonus = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.climb = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.burrowing = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.swim = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.flying = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.legendaryResistances = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.darkvision = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.blindsight = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.tremorsense = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.truesight = stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.type = (creatureType)stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.size = (creatureSize)stoi(nextEntry);
	getline(*input, nextEntry, ',');
	output.armor = (armorType)stoi(nextEntry);

	for (getline(*input, nextEntry, ','); nextEntry != "done"; getline(*input, nextEntry, ','))
	{
		output.langs.push_back((language)stoi(nextEntry));
	}

	for (getline(*input, nextEntry, ','); nextEntry != "done"; getline(*input, nextEntry, ','))
	{
		output.skills.push_back(Skill(nextEntry));
	}

	for (getline(*input, nextEntry, ','); nextEntry != "done"; getline(*input, nextEntry, ','))
	{
		output.features.push_back(Feature(nextEntry));
	}

	for (getline(*input, nextEntry, ','); nextEntry != "done"; getline(*input, nextEntry, ','))
	{
		output.attacks.push_back(Attack(nextEntry));
	}

	for (getline(*input, nextEntry, ','); nextEntry != "done"; getline(*input, nextEntry, ','))
	{
		if (nextEntry[0] = (char)254) //if legendary action is not an attack
		{
			output.legendaryActions.push_back(LegendaryAction(nextEntry));
		}
		else
		{
			std::string legAtkName = nextEntry.substr(1, (int)nextEntry[0]);
			int count = 0;
			while (output.attacks[count].name != legAtkName)
			{
				if (count + 1 == output.attacks.size())
					break;
			}
			if (count + 1 == output.attacks.size())
				output.legendaryActions.push_back( //new leg action
					LegendaryAction( //constructed from
						nextEntry.substr(legAtkName.size()))); //str that contains name and description
			else
				output.legendaryActions.push_back( //new leg action
					LegendaryAction( //constructed from
						nextEntry.substr(legAtkName.size()), //str that contains name and description
						&(output.attacks[count]))); //and ptr to attack
		}
	}

	getline(*input, nextEntry, ',');
	for (int count = 0; count < nextEntry.size(); count++)
	{
		output.resistances.push_back((damageType)nextEntry[count]);
	}

	getline(*input, nextEntry, ',');
	for (int count = 0; count < nextEntry.size(); count++)
	{
		output.immunities.push_back((damageType)nextEntry[count]);
	}


	return output;
}

