#include "OptionMenuState.h"

// "Privates" Structs/Unions and Enums
typedef struct sprite {
    SDL_Texture *texture;
    SDL_Rect rect;
} sprite;

typedef enum {
    WHITE_TEAM,
    BLACK_TEAM
} chessTeam;

typedef enum {
    WHITE_TURN,
    BLACK_TURN
} chessTurn;

typedef struct chessPiece {
    sprite sprite;
    chessTeam team;
    char pieceType; // 'R', 'K', etc...
} chessPiece;

typedef struct boardSquare {
    chessPiece *piece; // NULL ou une pièce
    int row;
    int col;
} boardSquare;

// "Privates" variables
/* Configuration */
SDL_Color gameBackgroundColor = { 30, 74, 32, 255 };

sprite chessBoardSprite = { NULL, { 0, 0, 0, 0 } };

boardSquare *chessBoard;
const int SQUARES_COUNT = 64;

chessPiece *chessPieces;
const int PIECES_COUNT = 32;

int SQUARE_HEIGHT;
int SQUARE_WIDTH;

/* Move pieces */
SDL_bool isASquareSelected;
boardSquare *squareSelected;

/* Player turn */
chessTurn playerTurn;

// Functions
void initGameState(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;
    (void)renderer;

    chessBoardSprite.texture = LoadTexture(*renderer, "res/Images/chessBoard.png");
    SDL_QueryTexture(chessBoardSprite.texture, NULL, NULL, &chessBoardSprite.rect.w, &chessBoardSprite.rect.h);
    chessBoardSprite.rect.y = (int)((0.5 * SCREEN_HEIGHT) - (chessBoardSprite.rect.h / 2));

    SQUARE_HEIGHT = chessBoardSprite.rect.h / 8;
    SQUARE_WIDTH = chessBoardSprite.rect.w / 8;

    // Initialisation des pieces
    chessPieces = malloc(PIECES_COUNT * sizeof(chessPiece));

    // Les pièces blanches
    chessPieces[0] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'R' }; // A1
    chessPieces[0].sprite.texture = LoadTexture(*renderer, "res/Images/whiteRook.png");
    SDL_QueryTexture(chessPieces[0].sprite.texture, NULL, NULL, &chessPieces[0].sprite.rect.w, &chessPieces[0].sprite.rect.h);
    chessPieces[1] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'K' };
    chessPieces[1].sprite.texture = LoadTexture(*renderer, "res/Images/whiteKnight.png");
    SDL_QueryTexture(chessPieces[1].sprite.texture, NULL, NULL, &chessPieces[1].sprite.rect.w, &chessPieces[1].sprite.rect.h);
    chessPieces[2] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'B' };
    chessPieces[2].sprite.texture = LoadTexture(*renderer, "res/Images/whiteBishop.png");
    SDL_QueryTexture(chessPieces[2].sprite.texture, NULL, NULL, &chessPieces[2].sprite.rect.w, &chessPieces[2].sprite.rect.h);
    chessPieces[3] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'Q' };
    chessPieces[3].sprite.texture = LoadTexture(*renderer, "res/Images/whiteQueen.png");
    SDL_QueryTexture(chessPieces[3].sprite.texture, NULL, NULL, &chessPieces[3].sprite.rect.w, &chessPieces[3].sprite.rect.h);
    chessPieces[4] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'K' };
    chessPieces[4].sprite.texture = LoadTexture(*renderer, "res/Images/whiteKing.png");
    SDL_QueryTexture(chessPieces[4].sprite.texture, NULL, NULL, &chessPieces[4].sprite.rect.w, &chessPieces[4].sprite.rect.h);
    chessPieces[5] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'B' };
    chessPieces[5].sprite.texture = LoadTexture(*renderer, "res/Images/whiteBishop.png");
    SDL_QueryTexture(chessPieces[5].sprite.texture, NULL, NULL, &chessPieces[5].sprite.rect.w, &chessPieces[5].sprite.rect.h);
    chessPieces[6] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'K' };
    chessPieces[6].sprite.texture = LoadTexture(*renderer, "res/Images/whiteKnight.png");
    SDL_QueryTexture(chessPieces[6].sprite.texture, NULL, NULL, &chessPieces[6].sprite.rect.w, &chessPieces[6].sprite.rect.h);
    chessPieces[7] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'R' };
    chessPieces[7].sprite.texture = LoadTexture(*renderer, "res/Images/whiteRook.png");
    SDL_QueryTexture(chessPieces[7].sprite.texture, NULL, NULL, &chessPieces[7].sprite.rect.w, &chessPieces[7].sprite.rect.h);

    chessPieces[8] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'p' }; // A2
    chessPieces[8].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[8].sprite.texture, NULL, NULL, &chessPieces[8].sprite.rect.w, &chessPieces[8].sprite.rect.h);
    chessPieces[9] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'p' };
    chessPieces[9].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[9].sprite.texture, NULL, NULL, &chessPieces[9].sprite.rect.w, &chessPieces[9].sprite.rect.h);
    chessPieces[10] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'p' };
    chessPieces[10].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[10].sprite.texture, NULL, NULL, &chessPieces[10].sprite.rect.w, &chessPieces[10].sprite.rect.h);
    chessPieces[11] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'p' };
    chessPieces[11].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[11].sprite.texture, NULL, NULL, &chessPieces[11].sprite.rect.w, &chessPieces[11].sprite.rect.h);
    chessPieces[12] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'p' };
    chessPieces[12].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[12].sprite.texture, NULL, NULL, &chessPieces[12].sprite.rect.w, &chessPieces[12].sprite.rect.h);
    chessPieces[13] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'p' };
    chessPieces[13].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[13].sprite.texture, NULL, NULL, &chessPieces[13].sprite.rect.w, &chessPieces[13].sprite.rect.h);
    chessPieces[14] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'p' };
    chessPieces[14].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[14].sprite.texture, NULL, NULL, &chessPieces[14].sprite.rect.w, &chessPieces[14].sprite.rect.h);
    chessPieces[15] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, 'p' };
    chessPieces[15].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[15].sprite.texture, NULL, NULL, &chessPieces[15].sprite.rect.w, &chessPieces[15].sprite.rect.h);

    // Les pièces noires
    chessPieces[16] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'p' }; // A7
    chessPieces[16].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[16].sprite.texture, NULL, NULL, &chessPieces[16].sprite.rect.w, &chessPieces[16].sprite.rect.h);
    chessPieces[17] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'p' };
    chessPieces[17].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[17].sprite.texture, NULL, NULL, &chessPieces[17].sprite.rect.w, &chessPieces[17].sprite.rect.h);
    chessPieces[18] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'p' };
    chessPieces[18].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[18].sprite.texture, NULL, NULL, &chessPieces[18].sprite.rect.w, &chessPieces[18].sprite.rect.h);
    chessPieces[19] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'p' };
    chessPieces[19].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[19].sprite.texture, NULL, NULL, &chessPieces[19].sprite.rect.w, &chessPieces[19].sprite.rect.h);
    chessPieces[20] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'p' };
    chessPieces[20].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[20].sprite.texture, NULL, NULL, &chessPieces[20].sprite.rect.w, &chessPieces[20].sprite.rect.h);
    chessPieces[21] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'p' };
    chessPieces[21].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[21].sprite.texture, NULL, NULL, &chessPieces[21].sprite.rect.w, &chessPieces[21].sprite.rect.h);
    chessPieces[22] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'p' };
    chessPieces[22].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[22].sprite.texture, NULL, NULL, &chessPieces[22].sprite.rect.w, &chessPieces[22].sprite.rect.h);
    chessPieces[23] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'p' };
    chessPieces[23].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[23].sprite.texture, NULL, NULL, &chessPieces[23].sprite.rect.w, &chessPieces[23].sprite.rect.h);

    chessPieces[24] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'R' }; // A8
    chessPieces[24].sprite.texture = LoadTexture(*renderer, "res/Images/blackRook.png");
    SDL_QueryTexture(chessPieces[24].sprite.texture, NULL, NULL, &chessPieces[24].sprite.rect.w, &chessPieces[24].sprite.rect.h);
    chessPieces[25] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'K' };
    chessPieces[25].sprite.texture = LoadTexture(*renderer, "res/Images/blackKnight.png");
    SDL_QueryTexture(chessPieces[25].sprite.texture, NULL, NULL, &chessPieces[25].sprite.rect.w, &chessPieces[25].sprite.rect.h);
    chessPieces[26] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'B' };
    chessPieces[26].sprite.texture = LoadTexture(*renderer, "res/Images/blackBishop.png");
    SDL_QueryTexture(chessPieces[26].sprite.texture, NULL, NULL, &chessPieces[26].sprite.rect.w, &chessPieces[26].sprite.rect.h);
    chessPieces[27] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'Q' };
    chessPieces[27].sprite.texture = LoadTexture(*renderer, "res/Images/blackQueen.png");
    SDL_QueryTexture(chessPieces[27].sprite.texture, NULL, NULL, &chessPieces[27].sprite.rect.w, &chessPieces[27].sprite.rect.h);
    chessPieces[28] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'K' };
    chessPieces[28].sprite.texture = LoadTexture(*renderer, "res/Images/blackKing.png");
    SDL_QueryTexture(chessPieces[28].sprite.texture, NULL, NULL, &chessPieces[28].sprite.rect.w, &chessPieces[28].sprite.rect.h);
    chessPieces[29] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'B' };
    chessPieces[29].sprite.texture = LoadTexture(*renderer, "res/Images/blackBishop.png");
    SDL_QueryTexture(chessPieces[29].sprite.texture, NULL, NULL, &chessPieces[29].sprite.rect.w, &chessPieces[29].sprite.rect.h);
    chessPieces[30] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'K' };
    chessPieces[30].sprite.texture = LoadTexture(*renderer, "res/Images/blackKnight.png");
    SDL_QueryTexture(chessPieces[30].sprite.texture, NULL, NULL, &chessPieces[30].sprite.rect.w, &chessPieces[30].sprite.rect.h);
    chessPieces[31] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, 'R' };
    chessPieces[31].sprite.texture = LoadTexture(*renderer, "res/Images/blackRook.png");
    SDL_QueryTexture(chessPieces[31].sprite.texture, NULL, NULL, &chessPieces[31].sprite.rect.w, &chessPieces[31].sprite.rect.h);

    // Initialisation du plateau
    chessBoard = malloc(SQUARES_COUNT * sizeof(boardSquare));
    for(int i = 0; i < SQUARES_COUNT; ++i) {
        chessBoard[i].row = (int) (i / 8);
        chessBoard[i].col = (int) (i % 8);
        chessBoard[i].piece = NULL;
    }

    for(int i = 0; i < SQUARES_COUNT; ++i) {
        if(chessBoard[i].col == 0 && chessBoard[i].row == 7) { chessBoard[i].piece = &chessPieces[0]; }
        if(chessBoard[i].col == 1 && chessBoard[i].row == 7) { chessBoard[i].piece = &chessPieces[1]; }
        if(chessBoard[i].col == 2 && chessBoard[i].row == 7) { chessBoard[i].piece = &chessPieces[2]; }
        if(chessBoard[i].col == 3 && chessBoard[i].row == 7) { chessBoard[i].piece = &chessPieces[3]; }
        if(chessBoard[i].col == 4 && chessBoard[i].row == 7) { chessBoard[i].piece = &chessPieces[4]; }
        if(chessBoard[i].col == 5 && chessBoard[i].row == 7) { chessBoard[i].piece = &chessPieces[5]; }
        if(chessBoard[i].col == 6 && chessBoard[i].row == 7) { chessBoard[i].piece = &chessPieces[6]; }
        if(chessBoard[i].col == 7 && chessBoard[i].row == 7) { chessBoard[i].piece = &chessPieces[7]; }
        
        if(chessBoard[i].col == 0 && chessBoard[i].row == 6) { chessBoard[i].piece = &chessPieces[8]; }
        if(chessBoard[i].col == 1 && chessBoard[i].row == 6) { chessBoard[i].piece = &chessPieces[9]; }
        if(chessBoard[i].col == 2 && chessBoard[i].row == 6) { chessBoard[i].piece = &chessPieces[10]; }
        if(chessBoard[i].col == 3 && chessBoard[i].row == 6) { chessBoard[i].piece = &chessPieces[11]; }
        if(chessBoard[i].col == 4 && chessBoard[i].row == 6) { chessBoard[i].piece = &chessPieces[12]; }
        if(chessBoard[i].col == 5 && chessBoard[i].row == 6) { chessBoard[i].piece = &chessPieces[13]; }
        if(chessBoard[i].col == 6 && chessBoard[i].row == 6) { chessBoard[i].piece = &chessPieces[14]; }
        if(chessBoard[i].col == 7 && chessBoard[i].row == 6) { chessBoard[i].piece = &chessPieces[15]; }

        if(chessBoard[i].col == 0 && chessBoard[i].row == 1) { chessBoard[i].piece = &chessPieces[16]; }
        if(chessBoard[i].col == 1 && chessBoard[i].row == 1) { chessBoard[i].piece = &chessPieces[17]; }
        if(chessBoard[i].col == 2 && chessBoard[i].row == 1) { chessBoard[i].piece = &chessPieces[18]; }
        if(chessBoard[i].col == 3 && chessBoard[i].row == 1) { chessBoard[i].piece = &chessPieces[19]; }
        if(chessBoard[i].col == 4 && chessBoard[i].row == 1) { chessBoard[i].piece = &chessPieces[20]; }
        if(chessBoard[i].col == 5 && chessBoard[i].row == 1) { chessBoard[i].piece = &chessPieces[21]; }
        if(chessBoard[i].col == 6 && chessBoard[i].row == 1) { chessBoard[i].piece = &chessPieces[22]; }
        if(chessBoard[i].col == 7 && chessBoard[i].row == 1) { chessBoard[i].piece = &chessPieces[23]; }
        
        if(chessBoard[i].col == 0 && chessBoard[i].row == 0) { chessBoard[i].piece = &chessPieces[24]; }
        if(chessBoard[i].col == 1 && chessBoard[i].row == 0) { chessBoard[i].piece = &chessPieces[25]; }
        if(chessBoard[i].col == 2 && chessBoard[i].row == 0) { chessBoard[i].piece = &chessPieces[26]; }
        if(chessBoard[i].col == 3 && chessBoard[i].row == 0) { chessBoard[i].piece = &chessPieces[27]; }
        if(chessBoard[i].col == 4 && chessBoard[i].row == 0) { chessBoard[i].piece = &chessPieces[28]; }
        if(chessBoard[i].col == 5 && chessBoard[i].row == 0) { chessBoard[i].piece = &chessPieces[29]; }
        if(chessBoard[i].col == 6 && chessBoard[i].row == 0) { chessBoard[i].piece = &chessPieces[30]; }
        if(chessBoard[i].col == 7 && chessBoard[i].row == 0) { chessBoard[i].piece = &chessPieces[31]; }
    }

    // Initialisation des positions en fonction des cases
    for(int i = 0; i < SQUARES_COUNT; ++i) {
        if(chessBoard[i].piece != NULL) {
            chessBoard[i].piece->sprite.rect.x = chessBoardSprite.rect.x + (chessBoard[i].col * SQUARE_WIDTH);
            chessBoard[i].piece->sprite.rect.y = chessBoardSprite.rect.y + (chessBoard[i].row * SQUARE_HEIGHT);
        }
    }

    isASquareSelected = SDL_FALSE;
    squareSelected = NULL;

    playerTurn = WHITE_TURN;
}

void exitGameState() {
    SDL_DestroyTexture(chessBoardSprite.texture);
    chessBoardSprite.texture = NULL;

    for(int i = 0; i < PIECES_COUNT; ++i) {
        SDL_DestroyTexture(chessPieces[i].sprite.texture);
        chessPieces[i].sprite.texture = NULL;
    }
    free(chessPieces);
    free(chessBoard);
}

// Update & Render
int gameStateUpdate(SDL_Window **window, SDL_Renderer **renderer, deltaTimeClock *dtClock) {
    (void)window;
    (void)renderer;
    (void)dtClock;

    /*
     * Valeurs de retour de la fonction :
     *  - 0 -> Pas de changement d'état
     *  - 1 -> Retour au MainMenuState
     *  - 3 -> Quitter le jeu
     */

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        int mouseClickCol = 0;
        int mouseClickRow = 0;

        int indexRebuilt = 0;

        switch(event.type) {
            case SDL_QUIT:
                return 3;
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) { return 1; }
                break;
            
            case SDL_MOUSEBUTTONDOWN:
                mouseClickCol = (event.button.x / SQUARE_WIDTH) - (chessBoardSprite.rect.x / SQUARE_WIDTH);
                mouseClickRow = (event.button.y / SQUARE_HEIGHT) - (chessBoardSprite.rect.y / SQUARE_HEIGHT);

                indexRebuilt = (mouseClickRow * 8) + mouseClickCol; // Voir l'initialisation du plateau pour comprendre le calcul

                if(indexRebuilt >= 0 && indexRebuilt <= 63) { // Le clic est bien dans la grille

                    if(isASquareSelected == SDL_FALSE) {
                        if(chessBoard[indexRebuilt].piece != NULL) {
                            if((playerTurn == WHITE_TURN && chessBoard[indexRebuilt].piece->team == WHITE_TEAM) || (playerTurn == BLACK_TURN && chessBoard[indexRebuilt].piece->team == BLACK_TEAM)) {
                                squareSelected = &chessBoard[indexRebuilt];
                                isASquareSelected = SDL_TRUE;
                            }
                        }
                        break;
                    }

                    if(isASquareSelected == SDL_TRUE) {
                        if(mouseClickCol == squareSelected->col && mouseClickRow == squareSelected->row) {
                            squareSelected = NULL;
                            isASquareSelected = SDL_FALSE;
                        } else {
                            // Si on clique sur un allié on remplace la sélection
                            if(chessBoard[indexRebuilt].piece != NULL && chessBoard[indexRebuilt].piece->team == squareSelected->piece->team) {
                                squareSelected = &chessBoard[indexRebuilt];
                            } else {
                                // On regarde si le déplacement est valide (a implémenter)
                                chessBoard[indexRebuilt].piece = squareSelected->piece;
                                squareSelected->piece = NULL;
                                squareSelected = NULL;
                                isASquareSelected = SDL_FALSE;

                                if(playerTurn == WHITE_TURN) {
                                    playerTurn = BLACK_TURN; 
                                } else {
                                    playerTurn = WHITE_TURN;
                                }
                            }
                        }
                        break;
                    }
                }
                break;

            default:
                break;
        }

        
        for(int i = 0; i < SQUARES_COUNT; ++i) {
            if(chessBoard[i].piece != NULL) {
                chessBoard[i].piece->sprite.rect.x = chessBoardSprite.rect.x + (chessBoard[i].col * SQUARE_WIDTH);
                chessBoard[i].piece->sprite.rect.y = chessBoardSprite.rect.y + (chessBoard[i].row * SQUARE_HEIGHT);
            }
        }
    }

    return 0;
}

void gameStateRender(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    SDL_SetRenderDrawColor(*renderer, gameBackgroundColor.r, gameBackgroundColor.g, gameBackgroundColor.b, gameBackgroundColor.a);
    SDL_RenderClear(*renderer);

    // Render here
    SDL_Rect chessBoardSpriteDestinationRect = { chessBoardSprite.rect.x, chessBoardSprite.rect.y, chessBoardSprite.rect.w, chessBoardSprite.rect.h };
    SDL_RenderCopy(*renderer, chessBoardSprite.texture, NULL, &chessBoardSpriteDestinationRect);

    for(int i = 0; i < SQUARES_COUNT; ++i) {
        if(chessBoard[i].piece != NULL) {
            SDL_Rect pieceDestinationRect = { chessBoard[i].piece->sprite.rect.x, chessBoard[i].piece->sprite.rect.y, chessBoard[i].piece->sprite.rect.w, chessBoard[i].piece->sprite.rect.h };
            SDL_RenderCopy(*renderer, chessBoard[i].piece->sprite.texture, NULL, &pieceDestinationRect);
        }
    }
    
    SDL_RenderPresent(*renderer);
}