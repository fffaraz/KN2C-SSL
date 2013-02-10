#ifndef REFPROTOCOL_H
#define REFPROTOCOL_H

// http://small-size.informatik.uni-bremen.de/referee:protocol
struct GameStatePacket{
  char cmd;                      // current referee command
  unsigned char cmd_counter;     // increments each time new command is set
  unsigned char goals_blue;      // current score for blue team
  unsigned char goals_yellow;    // current score for yellow team
  unsigned short time_remaining; // seconds remaining for current game stage (network byte order)
};

#endif // REFPROTOCOL_H
