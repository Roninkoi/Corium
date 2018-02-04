//
// Created by Roni A. Koitermaa on 19.12.2015.
//

#ifndef CORIUM_AUDIO_H
#define CORIUM_AUDIO_H
/*
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>*/

class Audio {
public:
    /*Mix_Chunk *jump;
    Mix_Chunk *select;
    Mix_Chunk *place;
    Mix_Chunk *pickup;
    Mix_Chunk *win;
    Mix_Chunk *lock;

    Mix_Music *music;*/

    void playAudio(/*int channel, Mix_Chunk *chunk, int loops*/) {
        //Mix_PlayChannel(channel, chunk, loops);
    }

    void playMusic(/*Mix_Music *mus, int loops*/) {
        //Mix_PlayMusic(mus, loops);
    }

    int playingMusic() {
        //return Mix_PlayingMusic();
        return 0;
    }

    void haltMusic() {
        //Mix_HaltMusic();
    }

    void initAudio() {
       /* SDL_Init(SDL_INIT_EVERYTHING);

        Mix_Init(MIX_INIT_MP3);
        Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024); // crashes in debug?
        */
    }

    void loadAudio() {
        /*jump = Mix_LoadWAV("sfx/jump.wav");
        Mix_VolumeChunk(jump, 200);
        select = Mix_LoadWAV("sfx/select.wav");
        Mix_VolumeChunk(select, 200);
        place = Mix_LoadWAV("sfx/place.wav");
        Mix_VolumeChunk(place, 200);
        pickup = Mix_LoadWAV("sfx/pickup.wav");
        Mix_VolumeChunk(pickup, 200);
        win = Mix_LoadWAV("sfx/win.wav");
        Mix_VolumeChunk(win, 200);
        lock = Mix_LoadWAV("sfx/lock.wav");
        Mix_VolumeChunk(lock, 200);
        music = Mix_LoadMUS("sfx/music/zigzag.ogg");*/
    }

    Audio() {
    }
};

#endif //CORIUM_AUDIO_H
