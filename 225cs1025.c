#include <stdio.h>
#include <limits.h>
#include <string.h> 

 
#define NUM_PITS 6
#define INITIAL_STONES 4
#define PLAYER_SIDE 0
#define AI_SIDE 1
#define SEARCH_DEPTH 5 

 
typedef int GameBoard[14];

 
enum { FALSE = 0, TRUE = 1 };

 
void setup_game(GameBoard board) {
    int i;
    for (i = 0; i < NUM_PITS; i++) {
        board[i] = INITIAL_STONES;  
        board[NUM_PITS + 1 + i] = INITIAL_STONES;  
    }
    board[NUM_PITS] = 0; 
    board[2 * NUM_PITS + 1] = 0; 
}

 
void render_board(const GameBoard board) {
    int i;
 
    printf(" ");
    for (i = 2 * NUM_PITS; i > NUM_PITS; i--) {
        printf("[%2d] ", board[i]);
    }
    printf("\n");

    
    printf("[%2d]                     [%2d]\n", board[2 * NUM_PITS + 1], board[NUM_PITS]);

    
    printf(" ");
    for (i = 0; i < NUM_PITS; i++) {
        printf("[%2d] ", board[i]);
    }
    printf("\n");
}

 
int is_side_clear(const GameBoard board, int side) {
    int startPit = (side == PLAYER_SIDE) ? 0 : (NUM_PITS + 1);
    int i;
    for (i = 0; i < NUM_PITS; i++) {
        if (board[startPit + i] != 0) return FALSE;
    }
    return TRUE;
}

 
int is_game_concluded(const GameBoard board) {
    return is_side_clear(board, PLAYER_SIDE) || is_side_clear(board, AI_SIDE);
}

 
void gather_leftovers(GameBoard board) {
    if (!is_game_concluded(board)) return;
    int i;
  
    for (i = 0; i < NUM_PITS; i++) {
        board[NUM_PITS] += board[i];
        board[i] = 0;
    }
     
    for (i = 0; i < NUM_PITS; i++) {
        board[2 * NUM_PITS + 1] += board[NUM_PITS + 1 + i];
        board[NUM_PITS + 1 + i] = 0;
    }
}

 
int assess_board(const GameBoard board) {
    return board[2 * NUM_PITS + 1] - board[NUM_PITS];
}


int execute_move(GameBoard board, int selectedPit, int side) {
    int stonesCount = board[selectedPit];
    if (stonesCount <= 0) return FALSE;

    board[selectedPit] = 0;
    int currentPos = selectedPit;
    int myStore = (side == PLAYER_SIDE) ? NUM_PITS : (2 * NUM_PITS + 1);
    int oppStore = (side == PLAYER_SIDE) ? (2 * NUM_PITS + 1) : NUM_PITS;
    int myStart = (side == PLAYER_SIDE) ? 0 : (NUM_PITS + 1);
    int myEnd = (side == PLAYER_SIDE) ? (NUM_PITS - 1) : (2 * NUM_PITS);

    while (stonesCount > 0) {
        currentPos = (currentPos + 1) % 14;
        if (currentPos == oppStore) continue;
        board[currentPos]++;
        stonesCount--;
    }

 
    int bonus = (currentPos == myStore) ? TRUE : FALSE;

 
    if (!bonus && board[currentPos] == 1 && currentPos >= myStart && currentPos <= myEnd) {
        int oppositePit = 12 - currentPos;  
        if (board[oppositePit] > 0) {
            board[myStore] += board[oppositePit] + 1;
            board[currentPos] = 0;
            board[oppositePit] = 0;
        }
    }

    return bonus;
}

 
int minimax_search(GameBoard board, int remainingDepth, int alphaVal, int betaVal, int maximizing) {
    if (remainingDepth == 0 || is_game_concluded(board)) {
        GameBoard tempBoard;
        memcpy(tempBoard, board, sizeof(GameBoard));
        if (is_game_concluded(tempBoard)) gather_leftovers(tempBoard);
        return assess_board(tempBoard);
    }

    if (maximizing) {  
        int bestVal = INT_MIN;
        int i;
        for (i = NUM_PITS + 1; i <= 2 * NUM_PITS; i++) {
            if (board[i] == 0) continue;
            GameBoard tempBoard;
            memcpy(tempBoard, board, sizeof(GameBoard));
            int bonus = execute_move(tempBoard, i, AI_SIDE);
            int val = minimax_search(tempBoard, remainingDepth - 1, alphaVal, betaVal, bonus ? TRUE : FALSE);
            bestVal = (val > bestVal) ? val : bestVal;
            alphaVal = (alphaVal > val) ? alphaVal : val;
            if (betaVal <= alphaVal) break;
        }
        return bestVal;
    } else { 
        int bestVal = INT_MAX;
        int i;
        for (i = 0; i < NUM_PITS; i++) {
            if (board[i] == 0) continue;
            GameBoard tempBoard;
            memcpy(tempBoard, board, sizeof(GameBoard));
            int bonus = execute_move(tempBoard, i, PLAYER_SIDE);
            int val = minimax_search(tempBoard, remainingDepth - 1, alphaVal, betaVal, bonus ? FALSE : TRUE);
            bestVal = (val < bestVal) ? val : bestVal;
            betaVal = (betaVal < val) ? betaVal : val;
            if (betaVal <= alphaVal) break;
        }
        return bestVal;
    }
}

 
int select_ai_move(const GameBoard board) {
    int optimalScore = INT_MIN;
    int optimalPit = -1;
    int i;
    for (i = NUM_PITS + 1; i <= 2 * NUM_PITS; i++) {
        if (board[i] == 0) continue;
        GameBoard tempBoard;
        memcpy(tempBoard, board, sizeof(GameBoard));
        int bonus = execute_move(tempBoard, i, AI_SIDE);
        int currentScore = minimax_search(tempBoard, SEARCH_DEPTH - 1, INT_MIN, INT_MAX, bonus ? TRUE : FALSE);
        if (currentScore > optimalScore) {
            optimalScore = currentScore;
            optimalPit = i;
        }
    }
    return optimalPit;
}

int main() {
    GameBoard gameState;
    setup_game(gameState);
    int activeTurn = PLAYER_SIDE; 

    while (!is_game_concluded(gameState)) {
        render_board(gameState);
        if (activeTurn == PLAYER_SIDE) {
            int userSelection;
            do {
                printf("Player's move. Select pit (1 to %d): ", NUM_PITS);
                scanf("%d", &userSelection);
                userSelection--; 
                if (userSelection < 0 || userSelection >= NUM_PITS || gameState[userSelection] == 0) {
                    printf("Error: Choose a valid non-empty pit.\n");
                }
            } while (userSelection < 0 || userSelection >= NUM_PITS || gameState[userSelection] == 0);

            int bonusTurn = execute_move(gameState, userSelection, PLAYER_SIDE);
            if (!bonusTurn) activeTurn = AI_SIDE;
        } else {
            int aiPit = select_ai_move(gameState);
            printf("AI selects pit C%d\n", (aiPit - NUM_PITS));  
            int bonusTurn = execute_move(gameState, aiPit, AI_SIDE);
            if (!bonusTurn) activeTurn = PLAYER_SIDE;
        }
    }

    gather_leftovers(gameState);
    render_board(gameState);

    int playerPoints = gameState[NUM_PITS];
    int aiPoints = gameState[2 * NUM_PITS + 1];
    printf("Game over - Player: %d, AI: %d\n", playerPoints, aiPoints);
    if (playerPoints > aiPoints) {
        printf("Player is the winner!\n");
    } else if (aiPoints > playerPoints) {
        printf("AI is the winner!\n");
    } else {
        printf("Game ends in a draw!\n");
    }

    return 0;
}