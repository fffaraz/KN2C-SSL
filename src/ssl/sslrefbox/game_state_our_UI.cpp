#include "game_state_our_UI.h"

const int GameStateOurUI::GAME_ON =  (1 << 0);
const int GameStateOurUI::GAME_OFF = (1 << 1);
const int GameStateOurUI::HALTED =   (1 << 2);

const int GameStateOurUI::KICKOFF =  (1 << 3);
const int GameStateOurUI::PENALTY =  (1 << 4);
const int GameStateOurUI::DIRECT =   (1 << 5);
const int GameStateOurUI::INDIRECT = (1 << 6);
const int GameStateOurUI::RESTART = (GameStateOurUI::KICKOFF | GameStateOurUI::PENALTY | GameStateOurUI::DIRECT | GameStateOurUI::INDIRECT);

const int GameStateOurUI::BLUE =     (1 << 8);
const int GameStateOurUI::YELLOW =   (1 << 9);

const int GameStateOurUI::READY =    (1 << 10);
const int GameStateOurUI::NOTREADY = (1 << 11);
