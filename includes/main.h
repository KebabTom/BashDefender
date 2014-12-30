typedef enum tutPhase {

	phaseOne = 1,
	phaseTwo = 2,
	phaseThree = 3,
	phaseFour = 4,
	phaseFive =5,
	phaseSix = 6,
	phaseSeven = 7,
	phaseEight = 8,
	phaseNine = 9,
	phaseTen = 10,
	phaseEleven = 11
} tutPhase;


void quitGame();
void startLevel(Display d, int *restart);
void testing();
void tutorialLevel(Display d,int *restart);
/*----------System Test Functions-----------*/

void parseToQueueTesting();
void parseToTowerTesting();
void towerToEnemyTesting();
void enemyToGamePropertiesTesting();

/*----------Testing Suites-----------*/
void testEnemyDeath();
void testParseToTower();
void testValidParses();
void testEnemyInRange();
