#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 300

#include "../includes/tower.h"
#include "../includes/sput.h"
#include "../includes/debug.h"

struct tower {
	int towerID;
    int x, y;
    int damage;
    int range;
	int speed;
    int AOErange; //! not yet implemented
	int AOEpower; //!not yet implemented
	int firing;
    int targetPosition[2];
};

void testingTowerModule()	{
	sput_start_testing();
	sput_set_output_stream(NULL);	

	sput_enter_suite("testGetTower(): Tower creation and being placed in tower array");
	sput_run_test(testGetTower);
	sput_leave_suite();
	
	sput_enter_suite("testUpgradeTowerStat(): Upgrading tower stats");
	sput_run_test(testUpgradeTowerStat);
	sput_leave_suite();

	sput_finish_testing();

}

struct towerGroup	{

	tower *listOfTowers;
	unsigned int numOfTowers;
	
};

void createTowerGroup()	{

	TowerGroup Group = (TowerGroup) malloc(sizeof(*Group));
	getTowerGrp(Group);
	Group->listOfTowers=NULL;
	Group->numOfTowers = 0;
}

/*
 * Must be called and created before towers are created.
 */
TowerGroup getTowerGrp(TowerGroup Group)	{

	static TowerGroup newGroup;

	if(Group != NULL)	{
		newGroup = Group;
	}

	return newGroup;
}

commandType checkActQueue()	{

	commandType cmd;
	upgradeStat stat;
	int target;
	if (popFromQueue(getQueue(NULL),&cmd,&stat,&target,getGame(NULL),10)) {
		switch (cmd)	{
			case upgrade:
					if(upgradeTowerStat(stat,target))	{
						return upgrade;
					} else {
						return 0;
					}
					break;
			case execute:
					return execute;
					break;
			default:	
					fprintf(stderr,"unrecognised command");
					break;
		}
	}
	return 0;
}

int upgradeDmg(int target)	{
	
	tower upgradeT;
	if((upgradeT = getTowerID(target))!= NULL)	{
		return upgradeT->damage++;
	}
	return 0;
}

upgradeStat upgradeTowerStat(upgradeStat stat,int target)	{

	switch(stat)	{
		case power:
			if(upgradeDmg(target))	{
				return power;
			}
			return 0;
			break;
		case range:

			break;
		case speed:

			break;
		case AOErange:

			break;
		case AOEpower:

			break;
		default:
			return 0;
			fprintf(stderr,"unrecognised stat");
			break;
	}

	return 0;
}


void testUpgradeTowerStat()	{

	createPath();
	createTowerGroup();
	tower t1 = createTower();
	tower t2 = createTower();
	sput_fail_unless(upgradeTowerStat(power,1) == power,"Valid Power Upgrade: tower one for upgrade");
	sput_fail_unless(upgradeTowerStat(power,1) == power,"Valid Power Upgrade: Tower two for upgrade");
	sput_fail_unless(upgradeTowerStat(0,1) == 0, " Invalid: Passing invalid upgrade");
	sput_fail_unless(upgradeTowerStat(power,3) == 0, " Invalid: Passing invalid target");
	free(t1);
	free(t2);
}

unsigned int getNumberOfTowers()	{
	return ((getTowerGrp(NULL))->numOfTowers);
}

tower createTower() {
	 	
  		getTowerGrp(NULL)->numOfTowers++; //!increased number of towers when one is created
		getTowerGrp(NULL)->listOfTowers = realloc(getTowerGrp(NULL)->listOfTowers, getTowerGrp(NULL)->numOfTowers*sizeof(tower));
	  	tower t = malloc(sizeof(*t));
   	 	getTowerGrp(NULL)->listOfTowers[getTowerGrp(NULL)->numOfTowers-1] = t;

		getTowerPointer(t);  //! Should no longer be used.  Functions should ID tower that they wish to target.
		
   		populateTower(t,getTowerGrp(NULL)->numOfTowers); //! populating tower stats
	
   		return t;

	return NULL;
  
}

void freeAllTowers()	{

	int i = 0;
	while(i < getTowerGrp(NULL)->numOfTowers)	{
		free(getTowerGrp(NULL)->listOfTowers[i]);
		i++;
	}
}

void testGetTower()	{

	createPath();
	createTowerGroup();
	createTower();
	sput_fail_unless(getNumberOfTowers() == 1, "Valid: Number of towers held in group is one.");
	sput_fail_unless(getTowerID(1) != NULL,"Valid: Tower with ID 1 exists.");
	createTower();
	sput_fail_unless(getNumberOfTowers() == 2, "Valid: Number of towers held in group is two");
	sput_fail_unless(getTowerID(2) != NULL,"Valid: Tower with ID 2 exists.");
	freeAllTowers();
	free(getTowerGrp(NULL));
}

tower getTowerPointer(tower updatedT) {
    
    static tower t;
    
    if(updatedT != NULL) {
        t = updatedT;
    }
    
    return t;
}

/*
 *Returns tower based on ID
 */
tower getTowerID(int target)	{
	int i;
	for( i = 0; i < (getTowerGrp(NULL))->numOfTowers; i++)	{
		if((getTowerGrp(NULL))->listOfTowers[i]->towerID == target)	{
				return getTowerGrp(NULL)->listOfTowers[i];
		}
	}

	return NULL;
}



void populateTower(tower newTow, int id) {
   	
    newTow->towerID = id;
    newTow->x = SCREEN_WIDTH/2;
    newTow->y = (SCREEN_HEIGHT/2)+10;
    newTow->damage = 10;
    newTow->range = 10;
    newTow->firing = 0;
}

int getRange() {
    
    tower t = getTowerPointer(NULL);
    
    return t->range;
}

int getTowerX() {
  
    tower t = getTowerPointer(NULL);
    
    return t->x;
}

int getTowerY() {
  
    tower t = getTowerPointer(NULL);
    
    return t->y;
}

int isFiring() {
    
    tower t = getTowerPointer(NULL);
    
    return t->firing;
}

int firingX() {
    tower t = getTowerPointer(NULL);
    
    return t->targetPosition[0];
}

int firingY() {
    tower t = getTowerPointer(NULL);
    
    return t->targetPosition[1];
}


void freeTower(tower t) {
  free(t);
}

void fire() {
  
	int enemyID, towerID;
	for(towerID = 1; towerID < getNumberOfTowers(); towerID++)	{ 
		for(enemyID = 1; enemyID <= getNumberOfEnemies(); enemyID++)	{
			if(inRange(getTowerID(towerID)->x, getTowerID(towerID)->y, getTowerID(towerID)->range, enemyID) == 1) {
				(getTowerID(towerID))->firing = 1;
				towerGetTargetPos(getTowerID(towerID)->targetPosition,enemyID);	
				damageEnemy (getTowerID(towerID)->damage,enemyID);
			} else {
				(getTowerID(towerID))->firing = 0;
			}
		}
	}
//  if(inRange(t->x, t->y, t->range) == 1) {
//      t->firing = 1;
//      getTarget(&t->target[0]);
//      damageEnemy (t->damage);
//  } else {
//      t->firing = 0;
//  }
}


void printTower(tower t) {

  printf("tower x = %d, tower y = %d, tower firing = %d", t->x, t->y, t->firing);
  if(t->firing) {
    printf(" Tower firing coords x = %d, tower firing coords y = %d ", t->targetPosition[0], t->targetPosition[1]);
  } else {
    printf(" ");
  }
}

void present_tower(Display d)
{
    drawTower(d, 80, 100, 80, 80);
}

