#include<iostream>
#include<string>
#include<map>

#include "State.h"

/**
 * Inserts all next possible game states in the received map and prints
 * in dot format "currentState.board" -> "nextState.board"; for each
 * @param [currentState]
 * @param [stateM]
 */
void moveToPossibleStates(State &currentState, std::map<std::string, State> &stateM);

int main()
{
  // declaration
  std::map<std::string, State> stateM[SIZE*SIZE];
  std::map<std::string, State>::iterator it;

  int startMoveCount = 2;

  State currentState("...O...X.", startMoveCount, 'X', false);

  // END declaration

  stateM[startMoveCount][currentState.board] = currentState;

  // start dot graph
  std::cout << "digraph TicTacToeMoves {" << std::endl;

	for (int i = startMoveCount; i < SIZE*SIZE; i++) {
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

void moveToPossibleStates(State &currentState, std::map<std::string, State> &stateM){
  State movedS;

	for(int i = 0; i<SIZE; i++){
    for(int j = 0; j<SIZE; j++){
      if(currentState.board.at((i * SIZE) + j) == '.'){
        movedS = currentState.Move(i, j);

        // print in dot format
        std::cout << "\t\"" << currentState.board <<
        "\" -> \"" << movedS.board << "\";" << std::endl;

        // if game didn't end && not in the map already
        if (!(movedS.ended) && (stateM.count(movedS.board) == 0)) {
        	// insert in map
          stateM[movedS.board] = movedS;
        }
      }
    }
  }
}
