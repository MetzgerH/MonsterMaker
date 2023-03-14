
#include "monster.h"

std::pair<double, int> g_CRAttackBonus[34] = { {0,3},{0.125,3},{0.25,3},{0.5,3},{1,3},{2,3},{3,4},{4,5},{5,6}, {6,6},{7,6},{8,7},{9,7},{10,7},{11,8},{12,8},{13,8},{14,8},
	{15,8},{16,9},{17,10},{18,10},{19,10},{20,10},{21,11},{22,11},{23,11},{24,12},{25,12},{26,12},{27,13},{28,13},{29,13},{30,14} };

std::pair<double, int> g_CRProfBonus[34] = { {0,2},{0.125,2},{0.25,2},{0.5,2},{1,2},{2,2},{3,2},{4,2},{5,3}, {6,3},{7,3},{8,3},{9,4},{10,4},{11,4},{12,4},{13,5},{14,5},
	{15,5},{16,5},{17,6},{18,6},{19,6},{20,6},{21,7},{22,7},{23,7},{24,7},{25,8},{26,8},{27,8},{28,8},{29,9},{30,9} };

std::pair<double, int> g_CRAC[34] = { {0,13},{0.125,13},{0.25,13},{0.5,13},{1,13},{2,13},{3,13},{4,14},{5,15}, {6,15},{7,15},{8,16},{9,16},{10,17},{11,17},{12,17},{13,18},
	{14,18},{15,18},{16,18},{17,19},{18,19},{19,19},{20,19},{21,19},{22,19},{23,19},{24,19},{25,19},{26,19},{27,19},{28,19},{29,19},{30,19} };

std::pair<double, int> g_CRDC[34] = { {0,13},{0.125,13},{0.25,13},{0.5,13},{1,13},{2,13},{3,13},{4,14},{5,15}, {6,15},{7,15},{8,16},{9,16},{10,17},{11,17},{12,17},{13,18},
	{14,18},{15,18},{16,18},{17,19},{18,19},{19,19},{20,19},{21,20},{22,20},{23,20},{24,21},{25,21},{26,21},{27,22},{28,22},{29,22},{30,23} };

std::pair<double, int> g_CRDamage[34] = { {0,0},{0.125,2},{0.25,4}, {0.5,6},{1,9},{2,15},{3,21},{4,27},{5,33}, {6,39},{7,45},{8,51},{9,57},{10,63},{11,69},{12,75},{13,81},
	{14,87},{15,93},{16,99},{17,105},{18,111},{19,117},{20,122},{21,141},{22,159},{23,177},{24,195},{25,213},{26,231},{27,249},{28,267},{29,285},{30,303} };

std::pair<double, int> g_CRHP[34] = { {0,1},{0.125,7},{0.25,36}, {0.5,50},{1,71},{2,86},{3,101},{4,116},{5,131}, {6,146},{7,161},{8,176},{9,191},{10,206},{11,221},{12,236},{13,251},
	{14,266},{15,281},{16,296},{17,311},{18,326},{19,341},{20,356},{21,401},{22,446},{23,491},{24,536},{25,581},{26,626},{27,671},{28,716},{29,761},{30,806} };

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

std::istream& operator>> (std::istream& lhs, creatureType &rhs)
{
	std::string input;
	lhs >> input;
	if (input == "aberration")
	{
		rhs = creatureType::aberration;
		return lhs;
	}
	if (input == "beast")
	{
		rhs = creatureType::beast;
		return lhs;
	}
	if (input == "celestial")
	{
		rhs = creatureType::celestial;
		return lhs;
	}
	if (input == "construct")
	{
		rhs = creatureType::construct;
		return lhs;
	}
	if (input == "dragon")
	{
		rhs = creatureType::dragon;
		return lhs;
	}
	if (input == "elemental")
	{
		rhs = creatureType::elemental;
		return lhs;
	}
	if (input == "fey")
	{
		rhs = creatureType::fey;
		return lhs;
	}
	if (input == "fiend")
	{
		rhs = creatureType::fiend;
		return lhs;
	}
	if (input == "giant")
	{
		rhs = creatureType::giant;
		return lhs;
	}
	if (input == "humanoid")
	{
		rhs = creatureType::humanoid;
		return lhs;
	}
	if (input == "monstrosity")
	{
		rhs = creatureType::monstrosity;
		return lhs;
	}
	if (input == "ooze")
	{
		rhs = creatureType::ooze;
		return lhs;
	}
	if (input == "plant")
	{
		rhs = creatureType::plant;
		return lhs;
	}
	if (input == "undead")
	{
		rhs = creatureType::undead;
		return lhs;
	}
	return lhs;
}

std::ostream& operator<< (std::ostream& lhs, creatureSize rhs)
{
	switch (rhs)
	{
	case creatureSize::tiny:
		return lhs << "Tiny";
	case creatureSize::small:
		return lhs << "Small";
	case creatureSize::medium:
		return lhs << "Medium";
	case creatureSize::large:
		return lhs << "Large";
	case creatureSize::huge:
		return lhs << "Huge";
	case creatureSize::gargantuan:
		return lhs << "Gargantuan";
	default:
		return lhs;
	}
}

std::istream& operator>>(std::istream& lhs, creatureSize& rhs)
{
	std::string rawtext;
	lhs >> rawtext;
	if (rawtext == "Small" ||rawtext == "small")
	{
		rhs = creatureSize::small;
		return lhs;
	}
	if (rawtext == "Tiny" || rawtext == "tiny")
	{
		rhs = creatureSize::tiny;
		return lhs;
	}
	if (rawtext == "Medium" || rawtext == "medium")
	{
		rhs = creatureSize::medium;
		return lhs;
	}
	if (rawtext == "Large" || rawtext == "large")
	{
		rhs = creatureSize::large;
		return lhs;
	}
	if (rawtext == "Huge" || rawtext == "huge")
	{
		rhs = creatureSize::huge;
		return lhs;
	}
	if (rawtext == "Gargantuan" || rawtext == "gargantuan")
	{
		rhs = creatureSize::gargantuan;
		return lhs;
	}
	return lhs;
}

//std::ifstream& operator>>(std::ifstream& lhs, creatureSize& rhs)
//{
//	std::string rawtext;
//	lhs >> rawtext;
//	if (rawtext == "Small" || rawtext == "small")
//	{
//		rhs = creatureSize::small;
//		return lhs;
//	}
//	if (rawtext == "Tiny" || rawtext == "tiny")
//	{
//		rhs = creatureSize::tiny;
//		return lhs;
//	}
//	if (rawtext == "Medium" || rawtext == "medium")
//	{
//		rhs = creatureSize::medium;
//		return lhs;
//	}
//	if (rawtext == "Large" || rawtext == "large")
//	{
//		rhs = creatureSize::large;
//		return lhs;
//	}
//	if (rawtext == "Huge" || rawtext == "huge")
//	{
//		rhs = creatureSize::huge;
//		return lhs;
//	}
//	if (rawtext == "Gargantuan" || rawtext == "gargantuan")
//	{
//		rhs = creatureSize::gargantuan;
//		return lhs;
//	}
//}

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

std::istream& operator>> (std::istream& lhs, armorType& rhs)
{
	std::string input;
	lhs >> input;
	if (input == "padded")
	{
		rhs = armorType::padded;
		lhs >> input; //intake the "leather" that comes after padded
		lhs >> input; //intake the "armor" that comes after leather;
		return lhs;
	}
	if (input == "leather")
	{
		rhs = armorType::leather;
		lhs >> input; //intake the "armor" that comes after leather;
		return lhs;
	}
	if (input == "studded")
	{
		rhs = armorType::studded;
		lhs >> input; //intake the "leather" that comes after padded
		return lhs;
	}
	if (input == "hide")
	{
		rhs = armorType::hide;
		lhs >> input; //intake the "armor" that comes after leather;
		return lhs;
	}
	if (input == "chain")
	{
		lhs >> input;
		if (input == "shirt")
		{
			rhs = armorType::chainShirt;
			return lhs;
		}
		rhs = armorType::chain;
		lhs >> input; //intake the "mail";
		return lhs;
	}
	if (input == "scale")
	{
		lhs >> input; //intake the "mail"
		rhs = armorType::scale;
		return lhs;
	}
	if (input == "breastplate")
	{
		rhs = armorType::breastplate;
		return lhs;
	}
	if (input == "half")
	{
		lhs >> input; //intake the "plate"
		rhs = armorType::halfPlate;
		return lhs;
	}
	if (input == "ring")
	{
		lhs >> input; //intake the "mail"
		rhs = armorType::ring;
		return lhs;
	}
	if (input == "chain")
	{
		lhs >> input; //intake the "mail"
		rhs = armorType::chain;
		return lhs;
	}
	if (input == "splint")
	{
		rhs = armorType::splint;
		return lhs;
	}
	if (input == "plate")
	{
		rhs = armorType::plate;
		return lhs;
	}
	if (input == "natural")
	{
		lhs >> input; //intake the "armor"
		rhs = armorType::natural;
		return lhs;
	}
}

std::ostream& operator<< (std::ostream& lhs, language rhs)
{
	switch (rhs)
	{
	case language::abyssal:
		return lhs << "Abyssal";
	case language::aquan:
		return lhs << "Aquan";
	case language::auran:
		return lhs << "Auran";
	case language::celestial:
		return lhs << "Celestial";
	case language::common:
		return lhs << "Common";
	case language::deepSpeech:
		return lhs << "Deep Speech";
	case language::draconic:
		return lhs << "Draconic";
	case language::druidic:
		return lhs << "druidic";
	case language::dwarvish:
		return lhs << "Dwarvish";
	case language::elvish:
		return lhs << "Elvish";
	case language::giant:
		return lhs << "Giant";
	case language::gnomish:
		return lhs << "Gnomish";
	case language::goblin:
		return lhs << "Goblin";
	case language::gnoll:
		return lhs << "Gnoll";
	case language::halfling:
		return lhs << "Halfling";
	case language::ignan:
		return lhs << "Ignan";
	case language::infernal:
		return lhs << "Infernal";
	case language::orc:
		return lhs << "Orc";
	case language::primordial:
		return lhs << "Primordial";
	case language::sylvan:
		return lhs << "Sylvan";
	case language::terran:
		return lhs << "Terran";
	case language::undercommon:
		return lhs << "Undercommon";
	case language::thievesCant:
		return lhs << "Thieves' Cant";

	default:
		return lhs;
	}
}

std::istream& operator>> (std::istream& lhs, language& rhs)
{
	std::string input;
	lhs >> input;

	if (input[0] == ' ')
		input = input.substr(1);
	if (input[input.size() - 1] == '\n' || input [input.size()-1] == ',')
		input = input.substr(0, input.size() - 1);

	if (input == "abyssal" || input == "Abyssal")
	{
		rhs = language::abyssal;
		return lhs;
	}
	if (input == "aquan" || input == "Aquan")
	{
		rhs = language::aquan;
		return lhs;
	}
	if (input == "auran" || input == "Auran")
	{
		rhs = language::auran;
		return lhs;
	}
	if (input == "celestial" || input == "Celestial")
	{
		rhs = language::celestial;
		return lhs;
	}
	if (input == "common" || input == "Common")
	{
		rhs = language::common;
		return lhs;
	}
	if (input == "deep speech" || input == "Deep Speech")
	{
		rhs = language::deepSpeech;
		return lhs;
	}
	if (input == "draconic" || input == "Draconic")
	{
		rhs = language::draconic;
		return lhs;
	}
	if (input == "druidic" || input == "Druidic")
	{
		rhs = language::druidic;
		return lhs;
	}
	if (input == "dwarvish" || input == "Dwarvish")
	{
		rhs = language::dwarvish;
		return lhs;
	}
	if (input == "elvish" || input == "Elvish")
	{
		rhs = language::elvish;
		return lhs;
	}
	if (input == "giant" || input == "Giant")
	{
		rhs = language::giant;
		return lhs;
	}
	if (input == "giant" || input == "Giant")
	{
		rhs = language::giant;
		return lhs;
	}
	if (input == "gnomish" || input == "Gnomish")
	{
		rhs = language::gnomish;
		return lhs;
	}
	if (input == "goblin" || input == "Goblin")
	{
		rhs = language::goblin;
		return lhs;
	}
	if (input == "gnoll" || input == "Gnoll")
	{
		rhs = language::gnoll;
		return lhs;
	}
	if (input == "halfling" || input == "Halfling")
	{
		rhs = language::halfling;
		return lhs;
	}
	if (input == "ignan" || input == "Ignan")
	{
		rhs = language::ignan;
		return lhs;
	}
	if (input == "infernal" || input == "Infernal")
	{
		rhs = language::infernal;
		return lhs;
	}
	if (input == "orc" || input == "Orc")
	{
		rhs = language::orc;
		return lhs;
	}
	if (input == "primordial" || input == "Primordial")
	{
		rhs = language::primordial;
		return lhs;
	}
	if (input == "sylvan" || input == "Sylvan")
	{
		rhs = language::sylvan;
		return lhs;
	}
	if (input == "terran" || input == "Terran")
	{
		rhs = language::terran;
		return lhs;
	}
	if (input == "undercommon" || input == "Undercommon")
	{
		rhs = language::undercommon;
		return lhs;
	}
	if (input == "theives cant" || input == "thieves' cant" || input == "Thieves Cant" || input == "Thieves' Cant")
	{
		rhs = language::thievesCant;
		return lhs;
	}
	rhs = language::min;
	return lhs;
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



void Monster::addSave(abilityScore saveToAdd)
{
	saves[(int)saveToAdd].setProficiency(true);
}

int Monster::pickBestAttack()
{
	int output = 1;
	for (int count = 0; count < attacks.size(); count++)
		if (attacks[count].averageDamage(scores) > attacks[output].averageDamage(scores))
			output = count;
	return output;
}

int Monster::getBestAttackBonus()
{
	return attacks[pickBestAttack()].attackBonus(scores);
}

int Monster::getBestDamage()
{
	return attacks[pickBestAttack()].averageDamage(scores);
}

bool Monster::usesSave()
{
	return attacks[pickBestAttack()].useSave;
}

int Monster::getBestSaveDC()
{
	return attacks[pickBestAttack()].saveDC(scores,profBonus);
}

int Monster::effectiveAC()
{
	int saveCount = 0;
	for (int count = 0; count < (int)abilityScore::max; count++)
		if (saves[count].isProficient() || saves[count].isExpert())
			saveCount++;
	if (saveCount > 4)
		return ac + 4;
	if (saveCount > 2)
		return ac + 2;
	return ac;
}

double calculateCR(Monster* monster)
{
	int count;
	std::pair<double, double> toHitCRRange = { 30,0 }; //the range of CR's this monster could have based purely on attack bonus or save DC,
	//where first is the lowest and second is the highest
	if (monster->usesSave())
	{
		int saveDC = monster->getBestSaveDC();
		if (saveDC < g_CRDC[0].second)
		{
			toHitCRRange.first = 0;
			toHitCRRange.second = 0;
		}
		else
		{
			for (count = 0; count != 34 && saveDC != g_CRDC[count].second; count++);
			if (count == 34)
				toHitCRRange.first = 30;
			else
				toHitCRRange.first = g_CRAttackBonus[count].first;
			for (count == 33; count != -1 && saveDC != g_CRDC[count].second; count--);
			if (count == -1)
				toHitCRRange.second = 0;
			else
				toHitCRRange.second = g_CRDC[count].first;
		}
	}
	else
	{
		
		int atkBonus = monster->getBestAttackBonus();
		if (atkBonus < g_CRAttackBonus[0].second)
		{
			toHitCRRange.first = 0;
			toHitCRRange.second = 0;
		}
		else
		{
			for (count = 0; count != 34 && atkBonus != g_CRAttackBonus[count].second; count++);
			if (count == 34)
				toHitCRRange.first = 30;
			else
				toHitCRRange.first = g_CRAttackBonus[count].first;
			for (count == 33; count != -1 && atkBonus != g_CRAttackBonus[count].second; count--);
			if (count == -1)
				toHitCRRange.second = 0;
			else
				toHitCRRange.second = g_CRAttackBonus[count].first;
		}
	}

	//std::pair<double, double> profBonusCRRange = { 30,0 }; //the range of CR's this monster could have based purely on proficiency bonus,
	////where first is the lowest and second is the highest
	//int profBonus = monster->profBonus;
	//if (profBonus < g_CRProfBonus[0].second)
	//{
	//	profBonusCRRange.first = 0;
	//	profBonusCRRange.second = 0;
	//}
	//else
	//{
	//	for (count = 0; count != 34 && profBonus != g_CRProfBonus[count].second; count++);
	//	if (count == 34)
	//		profBonusCRRange.first = 30;
	//	else
	//		profBonusCRRange.first = g_CRProfBonus[count].first;
	//	for (count == 33; count != -1 && profBonus != g_CRProfBonus[count].second; count--);
	//	if (count == -1)
	//		profBonusCRRange.second = 0;
	//	else
	//		profBonusCRRange.second = g_CRProfBonus[count].first;
	//} 

	//realized that prof bonus doesn't matter

	std::pair<double, double> acCRRange = { 30,0 }; //the range of CR's this monster could have based purely on proficiency bonus,
	//where first is the lowest and second is the highest
	int ac = monster->effectiveAC();
	if (ac < g_CRAC[0].second)
	{
		acCRRange.first = 0;
		acCRRange.second = 0;
	}
	else
	{
		for (count = 0; count != 34 && ac != g_CRAC[count].second; count++);
		if (count == 34)
			acCRRange.first = 30;
		else
			acCRRange.first = g_CRAC[count].first;
		for (count == 33; count != -1 && ac != g_CRAC[count].second; count--);
		if (count == -1)
			acCRRange.second = 0;
		else
			acCRRange.second = g_CRAC[count].first;
	}

	int damageCR = 0;
	int damage = monster->getBestDamage();
	for (count = 0; count<34 && g_CRDamage[count].second>damage; count++);
	damageCR = g_CRDamage[count].first;

	int hpCR = 0;
	int hitpoints = monster->hitpoints;
	for (count = 0; count<34 && g_CRHP[count].second>hitpoints; count++);
	hpCR = g_CRHP[count].first;

	double offensiveCR;
	if (damageCR > toHitCRRange.first && damageCR < toHitCRRange.second) //if the damage cr fits in the tohit range
	{
		offensiveCR = damageCR; //damage cr must be a good estimate
	}
	else if(damageCR<toHitCRRange.first) //if the problem is that damage is too low compared to tohit range
	{
		offensiveCR = (damageCR + toHitCRRange.first) / 2; //just take the average of lowest in tohit range and damage cr
	}
	else // otherwise damage must be too high
	{
		offensiveCR = (damageCR + toHitCRRange.second) / 2; //again take the average, this time highest instead of lowest
	}

	//same process for defensive
	double defensiveCR;
	if (hpCR > acCRRange.first && hpCR < acCRRange.second) 
	{
		defensiveCR = hpCR;
	}
	else if (hpCR < acCRRange.first)
	{
		defensiveCR = (hpCR + acCRRange.first) / 2;
	} 
	else
	{
		defensiveCR = (hpCR + acCRRange.second) / 2;
	}
	
	int cr = (offensiveCR + defensiveCR) / 2; //average offense and defense
	if (cr >= 1)
		return std::round(cr);//cr goes by integers at 1 and above
	if (cr > 0.5)
		return std::round(cr * 2)/2; //double it, round it, then halve it in order to round to 0.5 or 1
	if (cr > 0.25)
		return std::round(cr * 4) / 4; //same as last except quadrupling and quartering for rounding to 0.25 or 0.5
	if (cr > 0.125)
		return std::round(cr * 8) / 8; //same as before, for 0.125 or 0.25
	if (cr > 0.0625)
		return 0.125;
	return 0; 
}

double Monster::estimatePB()
{
	int count;
	for ( count = 0; g_CRProfBonus[count].first != cr && count < 50; count++);
	if (count == 50)
		return 2;
	
	return g_CRProfBonus[count].second;
}