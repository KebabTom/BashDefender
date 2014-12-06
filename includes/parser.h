//
//  parser.h
//  
//
//  Created by ben on 07/11/2014.
//
//

#ifndef _parser_h
#define _parser_h

#include "../includes/actionQueueDataStructure.h"

#define ENABLE_TESTING 0

int getAction( const char * inputAction );
char * strdup(const char * s);
int parse(char *inputString);
void freeCommandArray(char **commandArray,int numberOfChunks);
char ** breakUpString(const char * inputString, int *numberOfChunksPtr, const char * delimiter);
void testCommandArray(char ** commandArray, int numberOfChunks);
void testGetAction(enum commandType action);
void actionUsageError();
upgradeStat getUpgradeStats(const char * inputStringUpgradeStats);
int parseUpgrade(char ** commandArray, int numberOfChunks);
void testGetUpgradeStat(upgradeStat statToUpgrade);
void upgrageStatUsageError(const char * inputStringUpgradeStats, upgradeStat statToUpgrade, const char ** validUpgradeStats, int numberOfStats);
unsigned int getTargetTower(const char * inputStringTargeting);
int parseCat(char * inputStringTargeting);
int parseMan(char * inputStringCommandMan);
int parseMktwr(char ** commandArray);



#endif


