/*
Author: Egor Dourasov
Description: CodeQuest - Egor's Version
*/

#define _CRT_SECURE_NO_WARNINGS
#define NL 30   //max string size - don't change
#define SL "30"   //max string size in scanf - don't change

#define INV 10  //Inventory Size - Can be modified

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static double PI = 3.14159265359;

//devours buffer until '\n' - Om-nom-nom
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
//struct for holding monster info
struct Monster{
	int eStr, eDef, eIntl, eHP, eSpd, eLvl;
};

//struct for player info
struct Player{
	int lvl, str, spd, def, intl, lck, mhp, hp, exp, expReq, gold;
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

//inventory sorting script
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


//Places a random item into the inventory if it's not full
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
//type of item determines what the item does
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

//main Inventory selection menu
void inventory(struct Player* p1, struct Item* inv[INV], int* invSize){
	//set random seed, declare variables and initialized the inventory array
	int itemChoice, choice = 0;
	//main menu loop
	while (choice != 3){
		printf("\n1. Show Inventory\n2. Use Item\n3. Quit\n\n");
		printf("Select Option: ");
		scanf("%d", &choice);
		garbage();
		//invokes specific functions based on choices from the menu
		if (choice == 1) {
			sort(inv, *invSize);
			showInventory(inv, *invSize);
		}
		if (choice == 2) {
			sort(inv, *invSize);
			showInventory(inv, *invSize);
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

//prompts for a file name to save the game/char data into
int saveGame(struct Player player, float days, struct Item* inventory, 
			int inventorySize){
	FILE *fp = NULL;
	char fileName[NL] = { NULL };
	printf("Enter filename to write: ");
	scanf(" %"SL"[^\n]", fileName);
	garbage();
	fp = fopen(fileName, "w");
	if (fp != NULL){
		fprintf(fp, "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
					player.name, player.str, player.def, player.spd, player.intl,
					player.lvl, player.mhp, player.hp, player.lck, inventorySize,
					player.exp, player.expReq, player.gold, days);

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

//prompts for file name and loads char/game data from it
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
		fscanf(fp, "%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,",
				   player->name, &player->str, &player->def, &player->spd,
				   &player->intl, &player->lvl, &player->mhp, &player->hp, 
				   &player->lck, &inventorySize, &player->exp, &player->expReq,
				   &player->gold, &days);
				   
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

//new enemy generator - uses player level to get the monster max lvl
void enemyGenerator(struct Monster* monst, const int plvl){
	int level = (int)getRandom(3, (3+plvl));
	monst->eLvl = level;
	monst->eHP = (int)(level * level * getRandom(0.5, 2.0));
	monst->eStr = (int)(level * level * getRandom(0.15, 0.5));
	monst->eSpd = (int)(level * level * getRandom(0.15, 0.5));
	monst->eDef = (int)(level * level * getRandom(0.15, 0.5));
	monst->eIntl = (int)(level * level * getRandom(0.15, 0.5));
}

//lab 1 - Most graphical item in the game :)
void introScreen()
{
	printf("+-----------------------+\n");
	printf("|                       |\n");
	printf("|      CODE QUEST       |\n");
	printf("|                       |\n");
	printf("+-----------------------+\n");
	printf("\n");
}
//Takes player stats and normalizes them to 100. If a stat is 0, make it 1
void getStats(struct Player* player, double* days)
{
	double strength = (*player).str;
	double speed = (*player).spd;
	double defense = (*player).def;
	double intelligence = (*player).intl;
	*days = 30.0;
	(*player).mhp = 100;
	(*player).hp = (*player).mhp;
	(*player).exp = 0;
	(*player).lvl = 1;
	int sumOfAttributes = strength + speed + defense + intelligence;
	(*player).str = strength / sumOfAttributes * 100;
	if ((*player).str == 0) (*player).str++;
	(*player).spd = speed / sumOfAttributes * 100;
	if ((*player).spd == 0) (*player).spd++;
	(*player).def = defense / sumOfAttributes * 100;
	if ((*player).def == 0) (*player).def++;
	(*player).intl = intelligence / sumOfAttributes * 100;
	if ((*player).intl == 0) (*player).intl++;
	(*player).lck = 5 + sumOfAttributes % 25;
	(*player).expReq = 50;
	(*player).gold = 0;
}

//Player Attack - does magic or physical based on the choice made before
void playerAttack(int choice, int* eHP, int* eDef, int* eIntl, double* pStr,
	double* pIntl, int *plck){
	int dmg = 0;
	int crit = 1;
	if (rand() % 100 <= *plck) crit = 2;
	if (choice == 1){
		dmg = *pStr / *eDef * 5;
		*eHP -= dmg * crit;
		if (crit == 2) printf("\nCritical Hit!");
		printf("\nYou attacked the enemy for %d!\n", dmg);
	}
	else if (choice == 2){
		dmg = *pIntl / *eIntl * 5;
		*eHP -= dmg * crit;
		if (crit == 2) printf("\nCritical Hit!");
		printf("\nYou shocked the enemy for %d!\n", dmg);
	}
}

//monstar attack - randomizes the type of an attack that the monster does
//and then performes the attack
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

//The main combat function - gives you choices of types of attack and
//access to the inventory. If hp of player or mosnter drops to 0, the 
//loop ends
void combatSequence(struct Monster* monst, struct Player* p1, 
	struct Item* item, int* listSize){
	double pStr = (*p1).str;
	double pDef = (*p1).def;
	double pInt = (*p1).intl;
	int plck = (*p1).lck;
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
				playerAttack(choice, &eHP, &eDef, &eIntl, &pStr, &pInt, &plck);
				if (eHP > 0){
					(*p1).hp = (*p1).hp - monsterAttack(&eStr, &eIntl, &pDef, &pInt);
				}
			}
			else{
				(*p1).hp = (*p1).hp - monsterAttack(&eStr, &eIntl, &pDef, &pInt);
				if ((*p1).hp > 0){
					playerAttack(choice, &eHP, &eDef, &eIntl, &pStr, &pInt, &plck);
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
		(*p1).exp = (*p1).exp + ((*monst).eLvl - 2 ) * 10 ;
		printf("\nYou Won!");
	}
	getchar();
}

// Character Rests: -1 day, sets HP at to its maximum
void rest(int* hp, const int mhp, double* days){
	*hp = mhp;
	*days = *days - 1.0;
	printf("You rested up at the inn (zzz-ZZZ    zzz-ZZZ)\n\n");
}

//Character Level Up. First it validates if the exp is enough, if it is,
//it removes that much exp, increments the next requirement and presents a
//choice of stat to raise by 5
void levelup(struct Player* p1){
	 
	if ((*p1).exp >= (*p1).expReq){
		(*p1).exp -= (*p1).expReq;
		((*p1).lvl)++;
		(*p1).expReq += ((*p1).lvl) * 10;
		int choice = 0;
		printf("Congratulations, you have Leveled Up!\n");
		printf("Please choose a stat to raise by 5:\n1 - Strength\n2 - Speed\n\
3 - Defence\n4 - Intelligence\nChoice: ");
		while (!(choice == 1 || choice == 2 || choice == 3 || choice == 4)){
			scanf("%d", &choice);
			garbage();
			switch (choice){
			case 1:
				(*p1).str += 5;
				break;
			case 2:
				(*p1).spd += 5;
				break;
			case 3:
				(*p1).def += 5;
				break;
			case 4:
				(*p1).intl += 5;
				break;
			default:
				printf("Try Again: ");
			}
		}
	}

}

//Calculates the price of an item for sale based on its type and power
int price(const struct Item* item, const int id){
	int price = 0;
	if (item[id].power > 0){
		int i = item[id].type;
		if (i == 0) price = item[id].power / 20;
		if (i == 1) price = (item[id].power + 3) / 4;
		if (i == 2) price = item[id].power;
		if (i == 3) price = item[id].power;
		if (i == 4) price = item[id].power;
	}
	return price;
}


//Prints the list of items for sale with their prices
void sellInventory(struct Item* itemList, int* listSize){
	printf("Item Name		ID	Power	Price\n");
	for (int i = 0; i < listSize; i++){
		printf("%-20s	%d	%d	%d\n",  
			itemList[i].name, i, itemList[i].power, price(itemList, i));
	}
	printf("\n");
}

//validates the existence of the item and then "sells" it
int sellItem(struct Item* item, struct Player* p1, const int id){
	//makes sure the item exists
	if (item[id].power > 0){
		int i = item[id].type;
		p1->gold += price(item, id);
		printf("Item Sold for %d!\n\n", price(item, id));
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

//Validates inventory space and then Buys the item
void buyItem(struct Item* item, struct Player* p1, int* invTotal, int id){
	//makes sure inventory doesnt exceed 5 items and randomizes the item
	struct Item c;
	if (*invTotal < INV){
		c.power = 5;
		c.type = id;
		if (id == 0)  {
			strcpy(c.name, "Restoration Potion");
			c.power = 100;
			
		}
		if (id == 1) {
			strcpy(c.name, "HP Booster");
			c.power = 20;
		}
		if (id == 2)  strcpy(c.name, "Strength Booster");
		if (id == 3)  strcpy(c.name, "Defense Booster");
		if (id == 4)  strcpy(c.name, "Intelligence Booster");
		item[*invTotal] = c;
		(*invTotal)++;
		p1->gold -= 10;
	}
	//if inventory is full
	else {
		printf("\nYou can't hold anymore items!\n");
		
	}
}

//Main Shop menu with choices to buy and sell items
void store(struct Player* p1, struct Item* item, int* listsize){
	int buyChoice, itemChoice, choice = 0;
	//main menu loop
	while (choice != 3){
		printf("Current GOLD balance: %d\n\n", p1->gold);
		printf("Please chose your action:\n1 - Sell\n2 - Buy\n3 - Exit\nChoice: ");
		scanf("%d", &choice);
		garbage();
		//invoces specific functions based on choices from the menu
		if (choice == 1) {
			sort(item, *listsize);
			sellInventory(item, *listsize);
			printf("Select item ID to sell (any other key to exit): ");
			scanf("%d", &itemChoice);
			garbage();
			if (sellItem(item, p1, itemChoice)){
				sort(item, *listsize);
				(*listsize)--;
			}
			sellInventory(item, *listsize);
		}
		if (choice == 2) {
				printf("Current GOLD balance: %d\n\n", p1->gold);
				printf("Every item costs 10 Gold\n");
				printf("Choose an item to buy (any other key to exit):\n");
				printf("0 - Restoration Potion + 100 HP\n");
				printf("1 - HP Booster + 20 Max HP\n");
				printf("2 - Strength Booster + 5 Str\n");
				printf("3 - Defense Booster + 5 Def\n");
				printf("4 - Intelligence Booster + 5 Intl\nChoice: ");
				scanf("%d", &buyChoice);
				garbage();
				if (buyChoice == 1 || buyChoice == 2 || buyChoice == 3 ||
					buyChoice == 4 || buyChoice == 0){
					if (p1->gold >= 10)	buyItem(item, p1, listsize, buyChoice);
					else printf("Not Enough Gold!\n\n");
				}
				else printf("No such item\n");
		}
		if (choice != 1 && choice != 2 && choice != 3){
			printf("Invalid Input, Try again\n\n");
		}
	}
}

// The main game "Overworld" module
void game(double* days, struct Item* item, struct Player* p1, int* listSize){
	// Set initial HP, EXP, days and sets the menu choice at 0
	int winCond = 0;
	struct Monster monst;
	int choice = 0;
	//	Main loop, Assumes the input is an int value from 1 to 4
	while (winCond == 0 && (*p1).hp > 0 && *days > 0.0 && 
		!(choice == 6 || choice == 7)){
		// outputs of current stats and prints menu choices
		printData(*p1);
		printf("Days remaining: %.1lf HP: %d EXP: %d/%d GOLD: %d INV %d/10\n\n", 
			*days, (*p1).hp, (*p1).exp, (*p1).expReq, (*p1).gold, *listSize);
		printf("1 - Rest at Inn\n2 - Train\n3 - Inventory\n4 - Store\n\
5 - Fight the Demon Lord\n6 - Save and Exit\n7 - Exit Without Saving\n\nSelect: ");
		// Menu choice input, and function choice based on input
		scanf("%d", &choice);
		garbage();
		if (choice == 1) rest(&p1->hp, (*p1).mhp, days);
		if (choice == 2) {
			enemyGenerator(&monst, (*p1).lvl);
			combatSequence(&monst, p1, item, listSize);
			levelup(p1);
			*days = *days - 0.5;
			getItem(item, listSize);
		}
		if (choice == 3) inventory(p1, item, listSize);
		if (choice == 4) store(p1, item, listSize);
		if (choice == 5) {
			enemyGenerator(&monst, 20);
			combatSequence(&monst, p1, item, listSize);
			if ((*p1).hp > 0) winCond = 1;
		}
		if (choice == 6) saveGame(*p1, *days, item, *listSize);
		if (choice != 1 && choice != 2 && choice != 3 && choice != 4 
			&& choice != 5 && choice != 6 && choice != 7){
			printf("Invalid input, please try again\n\n");
		}
	}
	if (*days < 0.1 && (*p1).hp >0 && winCond == 0) printf("You are still alive,\
but time's up and the Demon Lord killed everyone >B-D\n\n");
	if (winCond == 1) {
		printf("\nYou have defeated the Demon Lord!\nThe people of the land are safe\
 and happy.\nYour name will go down in history.\nThe End.");
	}
	else printf("Game Over!");
	// Final Message when the game is over
	
	// Stops the program. Need any key stroke to finish
	getchar();
}

//main
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






