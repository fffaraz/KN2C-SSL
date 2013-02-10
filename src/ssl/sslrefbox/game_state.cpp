#include "game_state.h"

// !?!

const int GameState::GAME_ON =  (1 << 0);
const int GameState::GAME_OFF = (1 << 1);
const int GameState::HALTED =   (1 << 2);

const int GameState::KICKOFF =  (1 << 3);
const int GameState::PENALTY =  (1 << 4);
const int GameState::DIRECT =   (1 << 5);
const int GameState::INDIRECT = (1 << 6);
const int GameState::RESTART = (GameState::KICKOFF | GameState::PENALTY | GameState::DIRECT | GameState::INDIRECT);

const int GameState::BLUE =     (1 << 8);
const int GameState::YELLOW =   (1 << 9);

const int GameState::READY =    (1 << 10);
const int GameState::NOTREADY = (1 << 11);

