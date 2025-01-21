#ifndef LINUX
#include <windows.h>
#endif
#include "Game.h"

/* Init */
Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) {
    mScreenHeight = pScreenHeight;
    mBoard = pBoard;
    mIO = pIO;

    InitGame();
}

/* Returns a random integer between the two integers entered*/
int Game::getRand(int pA, int pB) {
    return rand() % (pB - pA + 1) + pA;
}

/* Initialize Parameters of the Game*/
void Game::InitGame() {
    srand((unsigned int) time(NULL));

    // First piece
    mPiece = getRand(0, 6);
    mRotation = getRand(0, 3);
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

    // Next piece
    mNextPiece = getRand(0, 6);
    mNextRotation = getRand(0, 3);
    mNextPosX = BOARD_WIDTH + 5;
    mNextPosY = 5;
}

void Game::CreateNewPiece() {
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition(mPiece, mRotation);
    mPosY = mPieces->GetYInitialPosition(mPiece, mRotation);

    // Random Next Piece
    mNextPiece = getRand(0, 6);
    mNextRotation = getRand(0, 3);
}

/* Draw Piece*/
void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation) {
    color mColor;

    int mPixelsX = mBoard->GetXPosInPixels(pX);
    int mPixelsY = mBoard->GetYPosInPixels(pY);

    for (int i = 0; i < PIECE_BLOCKS; i++) {
        for (int j = 0; j < PIECE_BLOCKS; j++) {
            switch(mPieces->GetBlockType(pPiece, pRotation, j, i)) {
                case 1: mColor = GREEN; break;
                case 2: mColor = BLUE; break;
            }
            if (mPieces->GetBlockType(pPiece, pRotation, j, i) != 0) {
                mIO->DrawRectangle(mPixelsX + i * BLOCK_SIZE, mPixelsY + j * BLOCK_SIZE, (mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
                (mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED);
            }
        }
    }
}

/* Draw Scene*/
void Game::DrawScene() {
    DrawBoard();
    DrawPiece(mPosX, mPosY, mPiece, mRotation);
    DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}