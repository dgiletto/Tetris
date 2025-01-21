#include "Board.h"

/* Init */
Board::Board(Pieces *pPieces, int pScreenHeight) {
    mPieces = pPieces;
    mScreenHeight = pScreenHeight;
    InitBoard();
}

/* Init the board to have all free positions*/
void Board::InitBoard() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            mBoard[i][j] = POS_FREE;
        }
    }
}

/* Store a Piece in the board by filling the positions*/
void Board::StorePiece(int pX, int pY, int pPiece, int pRotation) {
    for (int i1 = pX, i2 = 0; i1 < PIECE_BLOCKS + pX; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j1 < PIECE_BLOCKS + pY; j1++, j2++) {
            if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) {
                mBoard[i1][j1] = POS_FILLED;
            }
        }
    }
}

/*Looks at the top line of the board to see if the game is over*/
bool Board::IsGameOver() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] == POS_FILLED) {
            return true;
        }
    }
    return false;
}

/*Delete a line of blocks by moving the line above it down*/
void Board::DeleteLine(int pY) {
    for (int j = pY; j > 0; j--) {
        for (int i = 0; i < BOARD_WIDTH; i++) {
            mBoard[i][j] = mBoard[i][j-1];
        }
    }
}

/*Delete all of the lines that are filled*/
void Board::DeletePossibleLines() {
    for (int j = 0; j < BOARD_HEIGHT; j++) {
        int i = 0;
        while (i < BOARD_WIDTH) {
            if (mBoard[i][j] != POS_FILLED) {
                break;
            }
            i++;
        }
        if (i == BOARD_WIDTH) {
            DeleteLine(j);
        }
    }
}

/*Returns true if the block of the board is empty, and false if it is filled*/
bool Board::IsFreeBlock(int pX, int pY) {
    return (mBoard[pX][pY] == POS_FREE);
}

/*Returns the horizontal position of the block given in pixels */
int Board::GetXPosInPixels(int pPos) {
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

/*Returns the vertical position of the block given in pixels */
int Board::GetYPosInPixels(int pPos) {
    return ((BOARD_POSITION - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

/*Check if the piece can be stored at this position without any collision*/
bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation) {
    for (int i1 = pX, i2 = 0; i1 < BOARD_WIDTH; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j1 < BOARD_HEIGHT; j1++, j2++) {
            if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1) {
                if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) {
                    return false;
                }
            }
            if (j1 >= 0) {
                if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0 && !IsFreeBlock(i1,j1)) {
                    return false;
                }
            }
        }
    }
    return true;
}