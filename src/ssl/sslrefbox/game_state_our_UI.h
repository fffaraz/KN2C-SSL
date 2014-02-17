#ifndef GAME_STATE_OUR_UI_H
#define GAME_STATE_OUR_UI_H

#if 0
#include <constants.h>
#else
#define TEAM_BLUE 0
#define TEAM_YELLOW 1
#endif

#include "base.h"


class GameStateOurUI {

  static const int GAME_ON;
  static const int GAME_OFF;
  static const int HALTED;

  static const int KICKOFF;
  static const int PENALTY;
  static const int DIRECT;
  static const int INDIRECT;
  static const int RESTART;

  static const int BLUE;
  static const int YELLOW;

  static const int READY;
  static const int NOTREADY;

  int state;

//   The set of possible states are:

//   { GAME_ON, GAME_OFF, HALTED, NEUTRAL,
//     { { KICKOFF, PENALTY, DIRECT, INDIRECT } |
//       { BLUE, YELLOW } | { READY, NOTREADY } } }


  int color;

public:
  GameStateOurUI() { color = BLUE; state = GAME_OFF; }

  void init(int _color) { color = (_color == TEAM_BLUE) ? BLUE : YELLOW; }

  int get() { return state; }
  void set(int _state) { state = _state; }

  // This is the state machine transition function.  It takes the last
  // ref_command as input
  void transition(GameStateType ref_command, bool ball_kicked) {
    if (ref_command == STATE_Halt) {
      state = HALTED; return; }

    if (ref_command == STATE_Stop) {
      state = GAME_OFF; return; }

    if (ref_command == STATE_ForceStart) {
      state = GAME_ON; return; }

    if (ref_command == STATE_Start && state & NOTREADY) {
      state &= ~NOTREADY; state |= READY; return; }

    if (state & READY && ball_kicked) {
      state = GAME_ON; return; }

    if (state == GAME_OFF) {
      switch (ref_command) {
      case STATE_Kick_off_Our:
        state = KICKOFF | BLUE | NOTREADY; return;
      case STATE_Kick_off_Opp:
        state = KICKOFF | YELLOW | NOTREADY; return;

      case STATE_Penalty_Our:
        state = PENALTY | BLUE | NOTREADY; return;
      case STATE_Penalty_Opp:
        state = PENALTY | YELLOW | NOTREADY; return;

      case STATE_Free_kick_Our:
        state = DIRECT | BLUE | READY; return;
      case STATE_Free_kick_Opp:
        state = DIRECT | YELLOW | READY; return;

      case STATE_Indirect_Free_kick_Our:
        state = INDIRECT | BLUE | READY; return;
      case STATE_Indirect_Free_kick_Opp:
        state = INDIRECT | YELLOW | READY; return;

      default: break;
      }
    }
  }

  bool gameOn() { return (state == GAME_ON); }

  bool restart() { return (state & RESTART); }
  bool ourRestart() { return restart() && (state & color); }
  bool theirRestart() { return restart() && ! (state & color); }

  bool kickoff() { return (state & KICKOFF); }
  bool ourKickoff() { return kickoff() && (state & color); }
  bool theirKickoff() { return kickoff() && ! (state & color); }

  bool penaltyKick() { return (state & PENALTY); }
  bool ourPenaltyKick() { return penaltyKick() && (state & color); }
  bool theirPenaltyKick() { return penaltyKick() && ! (state & color); }

  bool directKick() { return (state & DIRECT); }
  bool ourDirectKick() { return directKick() && (state & color); }
  bool theirDirectKick() { return directKick() && ! (state & color); }

  bool indirectKick() { return (state & INDIRECT); }
  bool ourIndirectKick() { return indirectKick() && (state & color); }
  bool theirIndirectKick() { return indirectKick() && ! (state & color); }

  bool freeKick() { return directKick() || indirectKick(); }
  bool ourFreeKick() { return ourDirectKick() || ourIndirectKick(); }
  bool theirFreeKick() { return theirDirectKick() || theirIndirectKick(); }

  bool canMove() { return (state != HALTED); }

  bool allowedNearBall() {
    return gameOn() || (state & color); }

  bool canKickBall() {
    return gameOn() || (ourRestart() && (state & READY)); }

  int getColor()
  {
      // Blue   --> 0
      // Yellow --> 1
      return color;
  }

};

#endif // GAME_STATE_OUR_UI_H
