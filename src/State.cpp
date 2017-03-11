#include "State.h"

State::State() {
}

State::State(std::string b, int moveCount, char turn, int ended) :
  moveCount(moveCount),
  turn(turn),
  ended(ended),
  board(b)
{}

State State::Move(int x, int y){
  // copy current state to new state (ns)
  State ns(*this);

	// mark move
	ns.board[(x * SIZE) + y] = ns.turn;

  ns.moveCount++;

  // check if game is ended with the move
  ns.movedToWinState(x, y);

  // change player turn
  if (ns.turn == 'X') {
    ns.turn = 'O';
  } else {
    ns.turn = 'X';
  }

  return ns;
}

void State::movedToWinState(int x, int y) {
  int i;
  // col
  for(i = 0; i < SIZE; i++){
    if(board[(x * SIZE) + i] != turn)
      break;
  }
  if(i == SIZE){
    ended = true;
    return;
  }

  // row
  for(i = 0; i < SIZE; i++){
    if(board[(i * SIZE) + y] != turn)
      break;
  }
  if(i == SIZE){
    ended = true;
    return;
  }

  // diag
  if(x == y){
  // move is on diag
    for(i = 0; i < SIZE; i++){
      if(board[(i * SIZE) + i] != turn)
        break;
    }
    if(i == SIZE){
      ended = true;
      return;
    }
  }

  // anti diag
  if(x + y == SIZE - 1){
  // move is on anti diag
    for(i = 0; i < SIZE; i++){
      if(board[(i * SIZE) + (SIZE-1)-i] != turn)
        break;
    }
    if(i == SIZE){
      ended = true;
      return;
    }
  }

  if (moveCount >= SIZE*SIZE) {
    ended = true;
    return;
  }
}
