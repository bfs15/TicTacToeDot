#include<iostream>
#include<string>
#include<map>


#define TRUE  (1==1)
#define FALSE (!TRUE)

#define SIZE 3

class State {
public:
  string board;
  int moveCount;
  char turn;
  int won;
  // size_t hash;

  State(string b, int moveCount, Square turn, int won) :
    moveCount(moveCount),
    turn(turn),
    won(won),
    board(b)
  {
    // DEBUG
    for (std::vector<char>::const_iterator i = path.begin();
      i != path.end();
      ++i) {
      std::cout << *i << ' ';
    }
  }

  /**
   * Returns new game state from a move, move has to be valid
   * @param  x [x position of the move]
   * @param  y [y position of the move]
   * @return   [returns new game state]
   */
  State Move(int x, int y){
    // copy current state to new state (ns)
    State ns(*this);

    // check if game is won with the move
    ns.movedToWinState(x, y);

    // mark move
    board[(x * SIZE) + y] = ns.turn;

  	ns.moveCount++;

    // change player turn
    if (ns.turn == 'X') {
      ns.turn = 'O';
    } else {
      ns.turn = 'X';
    }

    return ns;
  }

  int movedToWinState(int x, int y) {
    // col
    for(int i = 0; i < SIZE; i++){
      if(board[(x * SIZE) + i] != turn)
        break;
    }
    if(i == SIZE-1){
      won = TRUE;
    }

    // row
    for(int i = 0; i < SIZE; i++){
      if(board[(i * SIZE) + y] != turn)
        break;
    }
    if(i == SIZE-1){
      won = TRUE;
    }

    // diag
    if(x == y){
    // move is on diag
      for(int i = 0; i < SIZE; i++){
        if(board[(i * SIZE) + i] != turn)
          break;
      }
      if(i == SIZE-1){
        won = TRUE;
      }
    }

    // anti diag
    if(x + y = SIZE - 1){
    // move is on anti diag
      for(int i = 0; i < SIZE; i++){
        if(board[(i * SIZE) + (SIZE-1)-i] != turn)
          break;
      }
      if(i == SIZE-1){
        won = TRUE;
      }
    }
  }
};

int main()
{
  // declaration
  std::map<string, State> stateM[SIZE];
  std::map<string, State>::iterator it;

  int startMoveCount = 2;

  State currentState("...O...X.", moveCount = startMoveCount, turn = 'X', won = FALSE);

  // END declaration

    // DEBUG
    std::cout << stateM[currentState.board] << endl;

  stateM[currentState.board] = currentState;

    // DEBUG
    std::cout << stateM[currentState.board] << endl;
    if (stateM[currentState.board] != null) {
      std::cout << "TRUE" << endl;
    } else {
      std::cout << "FALSE" << endl;
    }

  // start dot graph
  std::cout << "graph TicTacToeMoves {" << endl;

	// for (int i = startMoveCount; i < SIZE; i++) {
  //   for (it = stateM[i].begin(); it != stateM[i].end(); it++) {
  //     // currentState = it->second;
	//     moveToPossibleStates(it->second, stateM[i+1]);
  //   }
  //
  //   stateM[i].clear();
	// }

  // end dot graph
  std::cout << "}" << endl;

  return 0;
}

void moveToPossibleStates(State &currentState, std::map<string, State> &stateM){
  State movedS;

	for(int i; i<SIZE-1; i++){
    for(int j; j<SIZE-1; j++){
      if(currentState.board.at((i * SIZE) + j) == '.'){
        movedS = currentState.Move(i, j);

        // print in dot format
        std::cout << "\"" << currentState.board <<
        "\" -> \"" << movedS.board << "\";" << endl;

        // if game didn't end,
        if (!(movedS.won) && !(stateM.count(movedS.board))) {
          stateM[movedS.board] = movedS;
        }
      }
    }
  }
}
