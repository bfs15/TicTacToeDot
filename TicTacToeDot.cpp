#define TRUE  (1==1)
#define FALSE (!TRUE)

#define SIZE 3

typedef enum Square{
  O = -1,
  B = 0,
  X = 1
};

class State {
public:
  Square board[SIZE][SIZE];
  int moveCount;
  Square turn;
  int ended;
  size_t hash;

  State(Square b[][], int moveCount, Square turn, int ended) :
    moveCount(moveCount),
    turn(turn),
    ended(ended)
  {
    std::copy(std::begin(b), std::end(b), std::begin(board));
    hash();

    // DEBUG
    for (std::vector<char>::const_iterator i = path.begin();
      i != path.end();
      ++i) {
      std::cout << *i << ' ';
    }
  }

  char* getString() {
    char c[SIZE * SIZE];

    for(int i; i<SIZE-1; i++){
      for(int j; j<SIZE-1; j++){
        c[(i * SIZE) + j] = board[i][j];
      }
    }

    return c;
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
    board[x][y] = ns.turn;
    ns.hash();

  	ns.moveCount++;

    // change player turn
    ns.turn *= -1;

    return ns;
  }


  int movedToWinState(int x, int y) {
    // col
    for(int i = 0; i < SIZE; i++){
      if(board[x][i] != turn)
        break;
    }
    if(i == SIZE-1){
      ended = TRUE;
    }

    // row
    for(int i = 0; i < SIZE; i++){
      if(board[i][y] != turn)
        break;
    }
    if(i == SIZE-1){
      ended = TRUE;
    }

    // diag
    if(x == y){
    // move is on diag
      for(int i = 0; i < SIZE; i++){
        if(board[i][i] != turn)
          break;
      }
      if(i == SIZE-1){
        ended = TRUE;
      }
    }

    // anti diag
    if(x + y = SIZE - 1){
    // move is on anti diag
      for(int i = 0; i < SIZE; i++){
        if(board[i][(SIZE-1)-i] != turn)
          break;
      }
      if(i == SIZE-1){
        ended = TRUE;
      }
    }
  }

  bool operator==(const State &s) const {
    if ((turn != s.turn) ||
      (moveCount != s.moveCount) ||
      (hash != s.hash)) {
      return FALSE;
    }

    for (size_t i = 0; i < SIZE; i++) {
      for (size_t j = 0; j < SIZE; j++) {
        if (board[i][j] != s.board[i][j]) {
          return FALSE;
        }
      }
    }

    return TRUE;
  }
  bool operator<(const State &s) const {
    return hash < s.hash;
  }
  bool operator!=(const Packet& p) const { return !(*this == p); }
  bool operator> (const Packet& p) const { return p < *this; }
  bool operator>=(const Packet& p) const { return !(*this < p); }
  bool operator<=(const Packet& p) const { return !(p < *this); }

  void hash() {
    size_t hash = 0x3a7eb429; // Just some random seed value
    for (int i = 0; i != 8; ++i)
    {
        for (int j = 0; j != 8; ++j)
        {
            hash = (hash >> 1) | (hash << (sizeof(size_t) * 8 - 1));
            hash ^= k.a[i][j] * 0xee6b2807;
        }
    }
    hash *= 0xee6b2807;
    hash ^= hash >> 16;
  }
};

int main()
{
  // declaration

  std::deque<State> stateQ[SIZE];

  State currentState(
    {
      { B, B, B },
      { O, B, B },
      { B, X, B }
    }, moveCount = 2, turn = X, ended = FALSE);

  // END declaration

  stateQ[2].push_back(currentState);

  printf("graph TicTacToeMoves {\n");


	// for (int i = 2; i < SIZE; i++) {
	//   while (!stateQ[i].empty) {
	//     currentState = stateQ.front();
	//     stateQ.pop_front();
  //
	//     moveToPossibleStates(currentState, stateQ[i+1]);
	//   }
  //
	//   // remove repetitions
	//   stateQ[i+1].sort();
	//   // stateQ[i+1].unique();
	// 	std::unique(stateQ[i+1].begin(), stateQ[i+1].end());
	// }
  //
  // printf("}\n");

  return 0;
}

void moveToPossibleStates(State &currentState, std::deque<State> &stateQ){
  State movedS;

	for(int i; i<SIZE-1; i++){
    for(int j; j<SIZE-1; j++){
      if(currentState.board[i][j] == B){
        movedS = currentState.Move(i, j);

        // print in dot format
        printf("\"%s\" -> \"%s\";\n",
          currentState.getString(), movedS.getString());

        if (!(movedS.ended)) {
          stateQ.push_back(movedS);
        }
      }
    }
  }
}
