/*
<--------------------------------------------------------------------------->
 - Developer: Kolin 'Valtorei'
 - Complete: 100%
 - ScriptName: 'Beastmaster_Trainer'
 - Developed: 07/15/2014
 - Update: 09/22/2014
 <--------------------------------------------------------------------------->
 */

#include "Pet.h"

class Beastmaster_Trainer : public CreatureScript
{
public:
    Beastmaster_Trainer() : CreatureScript("Beastmaster_Trainer") {}

    void CreatePet(Player* player, Creature* creature, uint32 entry)
    {
        Creature* creatureTarget = creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() +2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);
        if(!creatureTarget)
            return;

        Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);
        if(!pet)
            return;

        creatureTarget->setDeathState(JUST_DIED);
        creatureTarget->RemoveCorpse();
        creatureTarget->SetHealth(0);

        pet->SetPower(POWER_HAPPINESS, 10480000);

        pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
        pet->SetUInt64Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());
        pet->SetUInt64Value(UNIT_FIELD_LEVEL, player->getLevel());

        pet->GetMap()->AddToMap(pet->ToCreature());

        pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);
        if(!pet->InitStatsForLevel(player->getLevel()))
            TC_LOG_INFO("misc", "Falha %u", entry);

        pet->UpdateAllStats();
        player->SetMinion(pet, true);

        pet->SavePetToDB(PET_SAVE_AS_CURRENT);
		pet->InitTalentForLevel();
		player->PetSpellInitialize();
				
		player->CLOSE_GOSSIP_MENU();
		creature->Whisper("Você adquiriu um novo pet, parabéns",  LANG_UNIVERSAL, player);
	}
			
	bool OnGossipHello(Player* player, Creature* creature)
	{
		if(player->getClass() != CLASS_HUNTER)
		{
			creature->Whisper("Apenas posso treinar hunters.",  LANG_UNIVERSAL, player);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		
		if(player->GetPet())
		{
			creature->Whisper("Você tem que remover seu pet atual para receber um novo.", LANG_UNIVERSAL, player);
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
				
		player->ADD_GOSSIP_ITEM(1, "Obter novo pet", GOSSIP_SENDER_MAIN, 30);
		if (player->CanTameExoticPets())
			player->ADD_GOSSIP_ITEM(2, "Obter um pet exotico", GOSSIP_SENDER_MAIN, 50);
		player->ADD_GOSSIP_ITEM(5, "Sair!", GOSSIP_SENDER_MAIN, 150);
				
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			return true;
	}
			
	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
					
		switch(action)
		{
					
			case 100:
				OnGossipHello(player, creature);
				break;
						
			case 150:
				player->CLOSE_GOSSIP_MENU();
				break;
								
			case 30:
				player->ADD_GOSSIP_ITEM(6, "Bat", GOSSIP_SENDER_MAIN, 18);
				player->ADD_GOSSIP_ITEM(6, "Bear", GOSSIP_SENDER_MAIN, 1);
				player->ADD_GOSSIP_ITEM(6, "Boar", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(6, "Cat", GOSSIP_SENDER_MAIN, 4);
				player->ADD_GOSSIP_ITEM(6, "Carrion Bird", GOSSIP_SENDER_MAIN, 5);
				player->ADD_GOSSIP_ITEM(6, "Crab", GOSSIP_SENDER_MAIN, 6);
				player->ADD_GOSSIP_ITEM(6, "Crocolisk", GOSSIP_SENDER_MAIN, 7);
				player->ADD_GOSSIP_ITEM(6, "Dragonhawk", GOSSIP_SENDER_MAIN, 17);
				player->ADD_GOSSIP_ITEM(6, "Gorilla", GOSSIP_SENDER_MAIN, 8);
				player->ADD_GOSSIP_ITEM(6, "Hound", GOSSIP_SENDER_MAIN, 9);
				player->ADD_GOSSIP_ITEM(6, "Hyena", GOSSIP_SENDER_MAIN, 10);
				player->ADD_GOSSIP_ITEM(6, "Moth", GOSSIP_SENDER_MAIN, 11);
				player->ADD_GOSSIP_ITEM(6, "Owl", GOSSIP_SENDER_MAIN, 12);
				player->ADD_GOSSIP_ITEM(4, "Next Page ->", GOSSIP_SENDER_MAIN, 31);
				player->ADD_GOSSIP_ITEM(4, "<- Main Menu", GOSSIP_SENDER_MAIN, 100);
				player->ADD_GOSSIP_ITEM(5, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;
								
			case 31:
				player->ADD_GOSSIP_ITEM(6, "Raptor", GOSSIP_SENDER_MAIN, 20);
				player->ADD_GOSSIP_ITEM(6, "Ravager", GOSSIP_SENDER_MAIN, 19);
				player->ADD_GOSSIP_ITEM(6, "Strider", GOSSIP_SENDER_MAIN, 13);
				player->ADD_GOSSIP_ITEM(6, "Scorpid", GOSSIP_SENDER_MAIN, 414);
				player->ADD_GOSSIP_ITEM(6, "Spider", GOSSIP_SENDER_MAIN, 16);
				player->ADD_GOSSIP_ITEM(6, "Serpent", GOSSIP_SENDER_MAIN, 21);  
				player->ADD_GOSSIP_ITEM(6, "Turtle", GOSSIP_SENDER_MAIN, 15);
				player->ADD_GOSSIP_ITEM(6, "Wasp", GOSSIP_SENDER_MAIN, 93);
				player->ADD_GOSSIP_ITEM(4, "<- Previous Page", GOSSIP_SENDER_MAIN, 30);
				player->ADD_GOSSIP_ITEM(4, "<- Main Menu", GOSSIP_SENDER_MAIN, 100);
				player->ADD_GOSSIP_ITEM(5, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;
								
			case 50:
				player->ADD_GOSSIP_ITEM(6, "Chimaera", GOSSIP_SENDER_MAIN, 51);
				player->ADD_GOSSIP_ITEM(6, "Core Hound", GOSSIP_SENDER_MAIN, 52);
				player->ADD_GOSSIP_ITEM(6, "Devilsaur", GOSSIP_SENDER_MAIN, 53);
				player->ADD_GOSSIP_ITEM(6, "Rhino", GOSSIP_SENDER_MAIN, 54);
				player->ADD_GOSSIP_ITEM(6, "Silithid", GOSSIP_SENDER_MAIN, 55);
				player->ADD_GOSSIP_ITEM(6, "Worm", GOSSIP_SENDER_MAIN, 56);  
				player->ADD_GOSSIP_ITEM(6, "Loque'nahak", GOSSIP_SENDER_MAIN, 57);
				player->ADD_GOSSIP_ITEM(6, "Skoll", GOSSIP_SENDER_MAIN, 58);
				player->ADD_GOSSIP_ITEM(6, "Gondri.", GOSSIP_SENDER_MAIN, 59);
				player->ADD_GOSSIP_ITEM(4, "<- Main Menu", GOSSIP_SENDER_MAIN, 100);
				player->ADD_GOSSIP_ITEM(5, "Nevermind!", GOSSIP_SENDER_MAIN, 150);
				player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;
							
			// Credits to Serifaz who helped me with these ID's.
			case 51: // Chimera
				CreatePet(player, creature, 21879);
				break;
									
			case 52: // Core hound
				CreatePet(player, creature, 21108);
				break;
									
			case 53: // Devilsaur
				CreatePet(player, creature, 20931);
				break;
								
			case 54: // Rhino
				CreatePet(player, creature, 30445);
				break;
								
			case 55: // Silithid
				CreatePet(player, creature, 5460);
				break;
								
			case 56: // Worm
				CreatePet(player, creature, 30148);
				break;
								
			case 57: // Loque'nahak
				CreatePet(player, creature, 32517);
				break;
								
			case 58: // Skoll
				CreatePet(player, creature, 35189);
				break;
								
			case 59: // Gondria
				CreatePet(player, creature, 33776);
				break;
								
			case 16: // Spider
				CreatePet(player, creature, 2349);
				break;
								
			case 17: // Dragonhawk
				CreatePet(player, creature, 27946);
				break;
								
			case 18: // Bat
				CreatePet(player, creature, 28233);
				break;
									
			case 19: // Ravager
				CreatePet(player, creature, 17199);
				break;
									
			case 20: // Raptor
				CreatePet(player, creature, 14821);
				break;
									
			case 21: // Serpent
				CreatePet(player, creature, 28358);
				break;
									
			case 1: // Bear
				CreatePet(player, creature, 29319);
				break;
									
			case 2: // Boar
				CreatePet(player, creature, 29996);
				break;
									
			case 93: // Bug
				CreatePet(player, creature, 28085);
				break;
									
			case 4: // Cat
				CreatePet(player, creature, 28097);
				break;
									
			case 5: // Carrion
				CreatePet(player, creature, 26838);
				break;
									
			case 6: // Crab
				CreatePet(player, creature, 24478);
				break;  
									
			case 7: // Crocolisk
				CreatePet(player, creature, 1417);
				break;  
									
			case 8: // Gorila
				CreatePet(player, creature, 28213);
				break;
									
			case 9: // Hound
				CreatePet(player, creature, 29452);
				break;
									
			case 10: // Hyena
				CreatePet(player, creature, 13036);
				break;
									
			case 11: // Moth
				CreatePet(player, creature, 27421);
				break;
									
			case 12: // Owl
				CreatePet(player, creature, 23136);
				break;
									
			case 13: // Strider
				CreatePet(player, creature, 22807);
				break;
									
			case 414: // Scorpid
				CreatePet(player, creature, 9698);
				break;
									
			case 15: // Turtle
				CreatePet(player, creature, 25482);
				break;
		}
					
	return true;
	}
};

void AddSC_Beastmaster_Trainer()
{
	new Beastmaster_Trainer;
}