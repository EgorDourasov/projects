/*
Author: Egor Dourasov
Description: CodeQuest - Egor's Version
*/

#define _CRT_SECURE_NO_WARNINGS
#define NL 30
#define SL "30"
#define INV 10
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static double PI = 3.14159265359;

//devours buffer until '\n'
void garbage(){
	while (getchar() != '\n');
}

//Create a random seed based on current time
void seedRandom(){
	srand(time(NULL)*PI);
}

//Name validation
int validate(const char a[]){
	int ver = 1;
	int length = strlen(a);
	for (int i = 0; i < length; i++){
		if (!(isalpha(a[i]) || isdigit(a[i]) || isblank(a[i]))) ver = 0;
	}
	return ver;
}
//struct for holding player info
struct Monster{
	int eStr, eDef, eIntl, eHP, eSpd, eLvl;
};

struct Player{
	int lvl, str, spd, def, intl, lck, mhp, hp, exp;
	char name[NL];
};

//struct for holding separate item info
struct Item{
	char name[NL];
	int type, power;
};

//Queries for player stats, stores them in a "Player" struct and returns it
struct Player loadPlayer(){
	struct Player p1;
	printf("Please enter the following player Name and desired stats:\nName: ");
	do {
		scanf(" %"SL"[^\n]", p1.name);
		garbage();
		if (validate(p1.name) != 1)printf("Invalid Input, try again ");
	} while (validate(p1.name) != 1);
	printf("Strength: ");
	scanf("%d", &p1.str);
	printf("Speed: ");
	scanf("%d", &p1.spd);
	printf("Defence: ");
	scanf("%d", &p1.def);
	printf("Intelligence: ");
	scanf("%d", &p1.intl);
	garbage();
	printf("\n");
	return p1;
}


void sort(struct Item* inv, const int listSize){
	//delegates temporary arrays used in sorting
	struct Item temps;
	// sorting loop
	for (int i = listSize - 1; i > 0; i--){
		for (int j = 0; j < i; j++){
			// compares strings, resorts if output is 1
			if (strcmp(inv[j].name, inv[j + 1].name) > 0){
				//resort the IDs
				temps = inv[j];
				inv[j] = inv[j+1];
				inv[j+1] = temps;
			}
		}
	}
}

//Randomly generates and returns an item struct
struct Item randItem(){
	struct Item c;
	int i = rand() % 5;
	c.type = i;
	c.power = 1 + rand() % 5;
	if (i == 0)  {
		strcpy(c.name, "Restoration Potion");
		c.power = 25 + rand() % 76;
	}
	if (i == 1) {
		strcpy(c.name, "HP Booster");
		c.power = 5 + rand() % 16;
	}
	if (i == 2)  strcpy(c.name, "Strength Booster");
	if (i == 3)  strcpy(c.name, "Defense Booster");
	if (i == 4)  strcpy(c.name, "Intelligence Booster");
	return c;
}

void getItem(struct Item* item, int* invTotal){
	//makes sure inventory doesnt exceed 5 items and randomizes the item
	if (*invTotal < INV){
		item[*invTotal] = randItem();
		(*invTotal)++;
	}
	//if inventory is full
	else {
		printf("\nYou can't hold anymore types of items!\n");
	}
}



//Takes the Player and Item structs, # of Items
//Formats and outputs data to screen
void printData(const struct Player p1){
	printf("Collected Input:\n\n");
	//Player info from the "Player" struct
	printf("Name			Lvl	Str	Spd	Def	Int	Lck	MHP\n");
	printf("%-20s	%d	%d	%d	%d	%d	%d	%d\n\n", p1.name, p1.lvl,
		p1.str, p1.spd, p1.def, p1.intl, p1.lck, p1.mhp);
	printf("\n");
}
//Prints the inventory to the screen
void showInventory(struct Item* itemList, int* listSize){
	printf("Item Name		ID	Power\n");
	//sort(itemList, *listSize);
	for (int i = 0; i < listSize; i++){
		printf("%-20s	%d	%d\n", itemList[i].name, i,
			itemList[i].power);
	}
	printf("\n");
}

//"uses item" deletes 1 count from the specific slot in the array
int useItem(struct Item* item, struct Player* p1, int* invTotal, const int id){
	//makes sure the item exists
	if (item[id].power > 0){
		int i = item[id].type;
		if (i == 0)  {
			(*p1).hp = (*p1).hp + item[id].power;
			if ((*p1).hp > (*p1).mhp) (*p1).hp = (*p1).mhp;
		}
		if (i == 1) {
			(*p1).mhp = (*p1).mhp + item[id].power;
			(*p1).hp = (*p1).hp + item[id].power;
		}
		if (i == 2)  (*p1).str = (*p1).str + item[id].power;
		if (i == 3)  (*p1).def = (*p1).def + item[id].power;
		if (i == 4)  (*p1).intl = (*p1).intl + item[id].power;
		printf("Item Used!\n\n");
		strcpy(item[id].name, "zzz");
		item[id].type = 9;
		item[id].power = 0;
		return 1;
	}
	//Does nothing if the item doesn't exist
	else {
		printf("You don't have that item!\n\n");
		return 0;
	}
}

//main selection menu
void inventory(struct Player* p1, struct Item* inv[INV], int* invSize){
	//set random seed, declare variables and initialized the inventory array
	int itemChoice, choice = 0;
	//main menu loop
	while (choice != 3){
		printf("\n1. Show Inventory\n2. Use Item\n3. Quit\n\n");
		printf("Select Option: ");
		scanf("%d", &choice);
		garbage();
		//invoces specific functions based on choices from the menu
		if (choice == 1) showInventory(inv, *invSize);
		if (choice == 2) {
			printf("Select item: ");
			scanf("%d", &itemChoice);
			garbage();
			if (useItem(inv, p1, invSize, itemChoice)){
				sort(inv, *invSize);
				(*invSize)--;
			}
			showInventory(inv, *invSize);
		}
		if (choice != 1 && choice != 2 && choice != 3){
			printf("Invalid Input, Try again\n\n");
		}
	}
}

int saveGame(struct Player player, float days, struct Item* inventory, 
			int inventorySize){
	FILE *fp = NULL;
	char fileName[NL] = { NULL };
	printf("Enter filename to write: ");
	scanf(" %"SL"[^\n]", fileName);
	garbage();
	fp = fopen(fileName, "w");
	if (fp != NULL){
		fprintf(fp, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
					player.name, player.str, player.def, player.spd, player.intl,
					player.lvl, player.mhp, player.hp, player.lck, inventorySize,
					player.exp, days);

		for (int i = 0; i < inventorySize; i++){
			fprintf(fp, "%s,%d,%d",inventory[i].name, inventory[i].type, 
				inventory[i].power);
		}
		fclose(fp);
		return 1;
	}
	else {
		printf("Failed to open file\n");
		return 0;
	}
}

int loadSaveGame(struct Player* player, float* days, struct Item* inventory, 
				int* inventorySize){
	int trash = 0;
	FILE *fp = NULL;
	char fileName[NL] = { NULL };
	printf("Enter filename to read: ");
	scanf(" %"SL"[^\n]", fileName);
	garbage();
	fp = fopen(fileName, "r");
	if (fp != NULL){
		fscanf(fp, "%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
				   player->name, &player->str, &player->def, &player->spd,
				   &player->intl, &player->lvl, &player->mhp, &player->hp, 
				   &player->lck, &inventorySize, &player->exp, &days);
				   
		for (int i = 0; i < INV; i++){
			fscanf(fp, "%[^,],%d,%d", inventory[i].name, &inventory[i].type, 
				&inventory[i].power);
		}
		return 1;
}
	else {
		printf("Invalid save file!\n");
		return 0;
	}
}

//creates a random stat value based on Min and Max inputs
double getRandom(double a, double b){
	double ranVar = b + 1;
	while (ranVar > b){
		double medium = rand() % 100;
		ranVar = a + (medium) / 100.0 * b;
	}
	return ranVar;
}

//new enemy generator
void enemyGenerator(struct Monster* monst, const int plvl){
	int level = (int)getRandom(3, (3+plvl));
	monst->eLvl = level;
	monst->eHP = (int)(level * level * getRandom(0.5, 2.0));
	monst->eStr = (int)(level * level * getRandom(0.15, 0.5));
	monst->eSpd = (int)(level * level * getRandom(0.15, 0.5));
	monst->eDef = (int)(level * level * getRandom(0.15, 0.5));
	monst->eIntl = (int)(level * level * getRandom(0.15, 0.5));
}

//lab 1
void introScreen()
{
	printf("+-----------------------+\n");
	printf("|                       |\n");
	printf("|      CODE QUEST       |\n");
	printf("|                       |\n");
	printf("+-----------------------+\n");
	printf("\n");
}
//lab 2
void getStats(struct Player* player, double* days)
{
	double strength = (*player).str;
	double speed = (*player).spd;
	double defense = (*player).def;
	double intelligence = (*player).intl;
	*days = 8.0;
	(*player).mhp = 100;
	(*player).hp = (*player).mhp;
	(*player).exp = 0;
	(*player).lvl = 1;
	int sumOfAttributes = strength + speed + defense + intelligence;
	(*player).str = strength / sumOfAttributes * 100;
	(*player).spd = speed / sumOfAttributes * 100;
	(*player).def = defense / sumOfAttributes * 100;
	(*player).intl = intelligence / sumOfAttributes * 100;
	(*player).lck = sumOfAttributes % 30;
}
void playerAttack(int choice, int* eHP, int* eDef, int* eIntl, double* pStr,
	double* pIntl){
	int dmg = 0;
	if (choice == 1){
		dmg = *pStr / *eDef * 5;
		*eHP -= dmg;
		printf("\nYou attacked the enemy for %d!\n", dmg);
	}
	else if (choice == 2){
		dmg = *pIntl / *eIntl * 5;
		*eHP -= dmg;
		printf("\nYou shocked the enemy for %d!\n", dmg);
	}
}

int monsterAttack(int* eStr, int* eIntl, double* pDef, double* pIntl){
	int atp = rand() % 2;
	int dmg = 0;
	if (atp == 1){
		dmg = *eStr / *pDef * 5;
		printf("The enemy attacked you for %d!\n\n", dmg);
	}
	else{
		dmg = *eIntl / *pIntl * 5;
		printf("The enemy shocked you for %d!\n\n", dmg);
	}
	return dmg;
}
//lab 3

void combatSequence(struct Monster* monst, struct Player* p1, 
	struct Item* item, int* listSize){
	double pStr = (*p1).str;
	double pDef = (*p1).def;
	double pInt = (*p1).intl;
	int eStr = monst->eStr, eDef = monst->eDef, eIntl = monst->eIntl,
		eHP = monst->eHP, eSpd = monst->eSpd, eLvl = monst->eLvl;
	int choice = 0;
	printf("Battle Start!\n\n");
	while ((*p1).hp > 0 && eHP > 0)	{
		printf("Your HP: %d Enemy HP: %d", (*p1).hp, eHP);
		printf("\n\n1 - Attack\n2 - Magic\n3 - Inventory\n\nSelect your move: ");
		scanf("%d", &choice);
		garbage();
		if (choice == 1 || choice == 2)	{
			if ((*p1).spd >= eSpd){
				playerAttack(choice, &eHP, &eDef, &eIntl, &pStr, &pInt);
				if (eHP > 0){
					(*p1).hp = (*p1).hp - monsterAttack(&eStr, &eIntl, &pDef, &pInt);
				}
			}
			else{
				(*p1).hp = (*p1).hp - monsterAttack(&eStr, &eIntl, &pDef, &pInt);
				if ((*p1).hp > 0){
					playerAttack(choice, &eHP, &eDef, &eIntl, &pStr, &pInt);
				}
			}
		}
		else if (choice == 3){
			inventory(p1, item, listSize);
		}
		else {
			printf("\nYou entered an invalid choice. Please input 1 or 2\n\n");
		}

	}
	if ((*p1).hp <= 0){
		printf("\nYou died!");
	}
	else if (eHP <= 0 && (*p1).hp > 0){
		printf("\nYou Won!");
	}
	getchar();
}

// Character Rests: -1 day, sets HP at 10
void rest(int* hp, const int mhp, double* days){
	*hp = mhp;
	*days = *days - 1.0;
	printf("You rested up at the inn (zzz-ZZZ    zzz-ZZZ)\n\n");
}

// Main :)
void game(double* days, struct Item* item, struct Player* p1, int* listSize){
	// Set initial HP, EXP, days and sets the menu choice at 0
	struct Monster monst;
	int choice = 0;
	//	Main loop, Assumes the input is an int value from 1 to 4
	while ((*p1).hp > 0 && *days > 0.0 && !(choice == 5 || choice == 6)){
		// outputs of current stats and prints menu choices
		printData(*p1);
		printf("Days remaining: %.1lf HP: %d EXP: %d\n\n", 
			*days, (*p1).hp, (*p1).exp);
		printf("1 - Rest at Inn\n2 - Train\n3 - Inventory\n\
4 - Fight the Demon Lord\n5 - Save and Exit\n6 - Exit Without Saving\n\nSelect: ");
		// Menu choice input, and function choice based on input
		scanf("%d", &choice);
		garbage();
		if (choice == 1) rest(&p1->hp, (*p1).mhp, days);
		if (choice == 2) {
			enemyGenerator(&monst, (*p1).lvl);
			combatSequence(&monst, p1, item, listSize);
			(*p1).exp = (*p1).exp + 10;
			*days = *days - 0.5;
			((*p1).lvl)++;
			getItem(item, listSize);
			printf("You did some training, and recieved some bruises!\n\n");
		}
		if (choice == 3) inventory(p1, item, listSize);
		if (choice == 4) {
			enemyGenerator(&monst, 20);
			combatSequence(&monst, p1, item, listSize);
		}
		if (choice == 5) saveGame(*p1, *days, item, *listSize);
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 
			&& choice !=5 && choice != 6){
			printf("Invalid input, please try again\n\n");
		}
	}
	if (*days < 0.1 && (*p1).hp >0) printf("You are still alive, but\
time's up and the Demon Lord killed everyone >B-D\n\n");
	// Final Message when the game is over
	printf("Game Over!");
	// Stops the program. Need any key stroke to finish
	getchar();
}

void main(){
	seedRandom();
	struct Player player1;
	struct Item inv[INV];
	int invSize = 5;
	double days = 8.0;
	int menuChoice = 0;
	//Main loop, Quits the program when input is 3
	while (menuChoice != 3){
		//clears the screen
		for (int i = 0; i < 40; i++){
			printf("\n");
		}
	//Main Menu visual + input
		introScreen();
		printf("\n--Main Menu--\n\n1 - New Game\n2 - Load Game\n3 - Exit\n\n\
Select: ");
		scanf("%d", &menuChoice);
		//makes sure that input is 1,2 or 3
		while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3){
			printf("Invalid input, try again: ");
			scanf("%d", &menuChoice);
			garbage();
		}
		switch (menuChoice){
		case 3 :
			printf("Good Bye!");
			getchar(); getchar();
			break;
		case 1 :
			player1 = loadPlayer();
			getStats(&player1, &days);
			for (int i = 0; i < invSize; i++){
				inv[i] = randItem();
			}
		case 2 :
			if (menuChoice == 2) {
				loadSaveGame(&player1, &days, inv, &invSize);
			}
		default:
			//Call combat and such
			game(&days, inv, &player1, &invSize);
		}
	}
}






