#pragma once
#include "Player.h"
#include "Localplayer.h"

#include "Vector3.h"
#include "Offsets.h"



Player* GetClosestEnemy() //etsii l�himm�n pelaajan
{
	LocalPlayer* localPlayer = LocalPlayer::Get(); //asettaa pelaajan tiedot

	float closestDitance = 1000000;
	int closesDistanceIndex = -1;

	for (int i = 1; i < *Player::GetMaxPlayer(); i++) //looppaa kaikki pelaajat l�pi
	{
		Player* currentPlayer = Player::GetPlayer(i); // ottaa loopissa menev�n indexin arvon ja ottaa sill� arvolla hahmolistalta tiedot ja asettaa sen kohteelle

		if (!currentPlayer || !(*(uint32_t*)currentPlayer) || (uint32_t)currentPlayer == (uint32_t)localPlayer) //jatkaa, kun kohde ei ole itse pelaaja
		{
			continue;
		}

		if (*currentPlayer->GetTeam() == *localPlayer->GetTeam()) //jatkaa, jos kohteella ja pelaajalla sama joukkue
		{
			continue;
		}

		if (*currentPlayer->GetHealth() < 1 || *localPlayer->GetHealth() < 1) //jatkaa, jos kohde tai pelaaja on hengiss�
		{
			continue;
		}

		float currentDistance = localPlayer->GetDistance(currentPlayer->GetOrigin()); //asettaa et�isyyden
		
		if (currentDistance < closestDitance) //jos t�m�nhetkinen et�isyys on pienempi kuin aikaisempi pienin et�isyys
		{
			closestDitance = currentDistance;
			closesDistanceIndex = i;	//antaa loopin i arvon muuttujalle, aikaisemmin oli -1
		}
	}

	if (closesDistanceIndex == -1)
	{
		return NULL;
	}
	return Player::GetPlayer(closesDistanceIndex);
}

void Run()
{
	Player* closestEnemy = GetClosestEnemy();

	if (closestEnemy)
	{
		LocalPlayer::Get()->AimAt(closestEnemy->GetBonePos(8));
	}
}
