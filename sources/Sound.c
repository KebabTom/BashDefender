//
//  Sound.c
//  Bash_Defender_V2
//
//  Created by Vlad Vyshnevskyy on 09/12/2014.
//  Copyright (c) 2014 Michael. All rights reserved.
//


#include "../includes/Display.h"
#include "../includes/parser.h"
#include "../includes/tower.h"
#include <stdbool.h>
#include <time.h>

#include <SDL2_mixer/SDL_mixer.h>


struct sound{
    Mix_Music *background_music;
    Mix_Chunk *tower_sound;
    Mix_Chunk *enemy_sound;

};

typedef struct sound *Sound;

//internal functions
Sound getSoundPointer(Sound s);
void check_load_sound(void *music, char *sound_name);


Sound getSoundPointer(Sound s);

void init_sound(){
    
    Sound s = (Sound)malloc(sizeof(struct sound));

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        printf("Error openning audio mixer");
        SDL_Quit();
    }
    
    s->background_music = Mix_LoadMUS("sound.mp3");
    s->enemy_sound = Mix_LoadWAV("enemy_sound.wav");
    s->tower_sound = Mix_LoadWAV("laser_sound.wav");
    
    check_load_sound((Mix_Music*)s->background_music, "sound.mp3");
    check_load_sound((Mix_Chunk*)s->enemy_sound, "enemy_sound.wav");
    check_load_sound((Mix_Chunk*)s->enemy_sound, "laser_sound.wav");
    
    Mix_VolumeMusic(100);

    getSoundPointer(s);
}

void enemySound(int type){
    SDL_Delay(20);
    static int cnt = 0;
    Sound s = getSoundPointer(NULL);
    switch (type) {
        case 1:
            if (cnt == 0) {
                cnt++;
                Mix_PlayChannel(-1, s->enemy_sound, 0);
                Mix_VolumeChunk(s->enemy_sound, 50);
            }
        break;
    }
}

void playBackgroundSound(){
    SDL_Delay(20);
    Sound s = getSoundPointer(NULL);
    Mix_PlayMusic(s->background_music, -1);
}

void check_load_sound(void *music, char *sound_name){
    if(music == NULL){
        printf("Cannot find %s\n", sound_name);
        SDL_Quit();
        exit(1);
    }
}

Sound getSoundPointer(Sound s){
    static Sound sound;
    if(s != NULL)	{
        sound = s;
    }
    return sound;
}

void shutSound(){
    Sound s = getSoundPointer(NULL);
    Mix_FreeMusic(s->background_music);
    Mix_FreeChunk(s->enemy_sound);
    Mix_FreeChunk(s->tower_sound);
    Mix_CloseAudio();
    Mix_Quit();
}
