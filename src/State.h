#ifndef STATE_H_
#define STATE_H_

#include<string>

#define SIZE 3

class State {
public:
  std::string board;
  int moveCount;
  char turn;
  int ended;
  // size_t hash;

  State();

  State(std::string b, int moveCount, char turn, int ended);

  /**
   * Returns new game state from a move, move has to be valid
   * @param  x [x position of the move]
   * @param  y [y position of the move]
   * @return   [returns new game state]
   */
  State Move(int, int);

  /**
   * Checks if a move in the coordinate will win the game
   * @param  int x coordinate
   * @param  int y coordinate
   * @return     TRUE or FALSE
   */
  void movedToWinState(int, int);
};

#endif /* STATE_H_ */
