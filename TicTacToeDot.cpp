#include<iostream>
#include<string>
#include<map>

#define TRUE  (1==1)
#define FALSE (!TRUE)

#define SIZE 3

typedef std::string string;

class State {
public:
  string board;
  int moveCount;
  char turn;
  int won;
  // size_t hash;

  State() {}

  State(string b, int moveCount, char turn, int won);

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

/**
 * Inserts all next possible game states in the received map and prints
 * in dot format "currentState.board" -> "nextState.board"; for each
 * @param [currentState]
 * @param [stateM]
 */
void moveToPossibleStates(State &currentState, std::map<string, State> &stateM);

int main()
{
  // declaration
  std::map<string, State> stateM[SIZE*SIZE];
  std::map<string, State>::iterator it;

  int startMoveCount = 2;

  State currentState("...O...X.", startMoveCount, 'X', FALSE);

  // END declaration

  stateM[startMoveCount][currentState.board] = currentState;

  // start dot graph
  std::cout << "graph TicTacToeMoves {" << std::endl;

	for (int i = startMoveCount; i < SIZE; i++) {
    for (it = stateM[i].begin(); it != stateM[i].end(); it++) {
      // currentState = it->second;
	    moveToPossibleStates(it->second, stateM[i+1]);
    }

    stateM[i].clear();
	}

  // end dot graph
  std::cout << "}" << std::endl;

  return 0;
}

void moveToPossibleStates(State &currentState, std::map<string, State> &stateM){
  State movedS;

	for(int i = 0; i<SIZE; i++){
    for(int j = 0; j<SIZE; j++){
      std::cout << (i*SIZE) + j << std::endl;
      if(currentState.board.at((i * SIZE) + j) == '.'){
        movedS = currentState.Move(i, j);

        // print in dot format
        std::cout << "\"" << currentState.board <<
        "\" -> \"" << movedS.board << "\";" << std::endl;

        // if game didn't win && not in the map already
        if (!(movedS.won) && (stateM.count(movedS.board) == 0)) {
        // insert in map
          // stateM[movedS.board] = movedS;
        }
      }
    }
  }
}

State::State(string b, int moveCount, char turn, int won) :
  moveCount(moveCount),
  turn(turn),
  won(won),
  board(b)
{}

State State::Move(int x, int y){
  // copy current state to new state (ns)
  State ns(*this);

  // check if game is won with the move
  ns.movedToWinState(x, y);

  // mark move
  ns.board[(x * SIZE) + y] = ns.turn;

  ns.moveCount++;

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
  if(i == SIZE-1){
    won = TRUE;
  }

  // row
  for(i = 0; i < SIZE; i++){
    if(board[(i * SIZE) + y] != turn)
      break;
  }
  if(i == SIZE-1){
    won = TRUE;
  }

  // diag
  if(x == y){
  // move is on diag
    for(i = 0; i < SIZE; i++){
      if(board[(i * SIZE) + i] != turn)
        break;
    }
    if(i == SIZE-1){
      won = TRUE;
    }
  }

  // anti diag
  if(x + y == SIZE - 1){
  // move is on anti diag
    for(i = 0; i < SIZE; i++){
      if(board[(i * SIZE) + (SIZE-1)-i] != turn)
        break;
    }
    if(i == SIZE-1){
      won = TRUE;
    }
  }
}
