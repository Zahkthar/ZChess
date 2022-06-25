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

typedef struct chessPiece {
    sprite sprite;
    chessTeam team;
    SDL_bool isAlive;
    int row;
    int col;
    char pieceType; // 'R', 'K', etc...
} chessPiece;

typedef enum {
    WHITE_TURN,
    BLACK_TURN
} chessTurn;

// "Privates" variables
SDL_Color gameBackgroundColor = { 30, 74, 32, 255 };

sprite chessBoard = { NULL, { 0, 0, 0, 0 } };
chessPiece *chessPieces;
const size_t PIECE_COUNT = 32;

int SQUARE_HEIGHT;
int SQUARE_WIDTH;

chessTurn playerTurn = WHITE_TURN;

// Functions
void initGameState(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;
    (void)renderer;

    chessBoard.texture = LoadTexture(*renderer, "res/Images/chessBoard.png");
    SDL_QueryTexture(chessBoard.texture, NULL, NULL, &chessBoard.rect.w, &chessBoard.rect.h);
    chessBoard.rect.y = (int)((0.5 * SCREEN_HEIGHT) - (chessBoard.rect.h / 2));

    SQUARE_HEIGHT = chessBoard.rect.h / 8;
    SQUARE_WIDTH = chessBoard.rect.w / 8;
    
    // Initialisation des pièces
    chessPieces = malloc(PIECE_COUNT * sizeof(chessPiece));
    // Les pièces blanches
    chessPieces[0] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 7, 0, 'R' };
    chessPieces[0].sprite.texture = LoadTexture(*renderer, "res/Images/whiteRook.png");
    SDL_QueryTexture(chessPieces[0].sprite.texture, NULL, NULL, &chessPieces[0].sprite.rect.w, &chessPieces[0].sprite.rect.h);
    chessPieces[1] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 7, 1, 'K' };
    chessPieces[1].sprite.texture = LoadTexture(*renderer, "res/Images/whiteKnight.png");
    SDL_QueryTexture(chessPieces[1].sprite.texture, NULL, NULL, &chessPieces[1].sprite.rect.w, &chessPieces[1].sprite.rect.h);
    chessPieces[2] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 7, 2, 'B' };
    chessPieces[2].sprite.texture = LoadTexture(*renderer, "res/Images/whiteBishop.png");
    SDL_QueryTexture(chessPieces[2].sprite.texture, NULL, NULL, &chessPieces[2].sprite.rect.w, &chessPieces[2].sprite.rect.h);
    chessPieces[3] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 7, 3, 'Q' };
    chessPieces[3].sprite.texture = LoadTexture(*renderer, "res/Images/whiteQueen.png");
    SDL_QueryTexture(chessPieces[3].sprite.texture, NULL, NULL, &chessPieces[3].sprite.rect.w, &chessPieces[3].sprite.rect.h);
    chessPieces[4] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 7, 4, 'K' };
    chessPieces[4].sprite.texture = LoadTexture(*renderer, "res/Images/whiteKing.png");
    SDL_QueryTexture(chessPieces[4].sprite.texture, NULL, NULL, &chessPieces[4].sprite.rect.w, &chessPieces[4].sprite.rect.h);
    chessPieces[5] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 7, 5, 'B' };
    chessPieces[5].sprite.texture = LoadTexture(*renderer, "res/Images/whiteBishop.png");
    SDL_QueryTexture(chessPieces[5].sprite.texture, NULL, NULL, &chessPieces[5].sprite.rect.w, &chessPieces[5].sprite.rect.h);
    chessPieces[6] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 7, 6, 'K' };
    chessPieces[6].sprite.texture = LoadTexture(*renderer, "res/Images/whiteKnight.png");
    SDL_QueryTexture(chessPieces[6].sprite.texture, NULL, NULL, &chessPieces[6].sprite.rect.w, &chessPieces[6].sprite.rect.h);
    chessPieces[7] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 7, 7, 'R' };
    chessPieces[7].sprite.texture = LoadTexture(*renderer, "res/Images/whiteRook.png");
    SDL_QueryTexture(chessPieces[7].sprite.texture, NULL, NULL, &chessPieces[7].sprite.rect.w, &chessPieces[7].sprite.rect.h);
    
    chessPieces[8] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 6, 0, 'p' };
    chessPieces[8].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[8].sprite.texture, NULL, NULL, &chessPieces[8].sprite.rect.w, &chessPieces[8].sprite.rect.h);
    chessPieces[9] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 6, 1, 'p' };
    chessPieces[9].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[9].sprite.texture, NULL, NULL, &chessPieces[9].sprite.rect.w, &chessPieces[9].sprite.rect.h);
    chessPieces[10] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 6, 2, 'p' };
    chessPieces[10].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[10].sprite.texture, NULL, NULL, &chessPieces[10].sprite.rect.w, &chessPieces[10].sprite.rect.h);
    chessPieces[11] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 6, 3, 'p' };
    chessPieces[11].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[11].sprite.texture, NULL, NULL, &chessPieces[11].sprite.rect.w, &chessPieces[11].sprite.rect.h);
    chessPieces[12] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 6, 4, 'p' };
    chessPieces[12].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[12].sprite.texture, NULL, NULL, &chessPieces[12].sprite.rect.w, &chessPieces[12].sprite.rect.h);
    chessPieces[13] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 6, 5, 'p' };
    chessPieces[13].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[13].sprite.texture, NULL, NULL, &chessPieces[13].sprite.rect.w, &chessPieces[13].sprite.rect.h);
    chessPieces[14] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 6, 6, 'p' };
    chessPieces[14].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[14].sprite.texture, NULL, NULL, &chessPieces[14].sprite.rect.w, &chessPieces[14].sprite.rect.h);
    chessPieces[15] = (chessPiece) (chessPiece) { { NULL, { 0, 0, 0, 0 } }, WHITE_TEAM, SDL_TRUE, 6, 7, 'p' };
    chessPieces[15].sprite.texture = LoadTexture(*renderer, "res/Images/whitePawn.png");
    SDL_QueryTexture(chessPieces[15].sprite.texture, NULL, NULL, &chessPieces[15].sprite.rect.w, &chessPieces[15].sprite.rect.h);

    // Les pièces noires
    chessPieces[16] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 1, 0, 'p' };
    chessPieces[16].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[16].sprite.texture, NULL, NULL, &chessPieces[16].sprite.rect.w, &chessPieces[16].sprite.rect.h);
    chessPieces[17] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 1, 1, 'p' };
    chessPieces[17].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[17].sprite.texture, NULL, NULL, &chessPieces[17].sprite.rect.w, &chessPieces[17].sprite.rect.h);
    chessPieces[18] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 1, 2, 'p' };
    chessPieces[18].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[18].sprite.texture, NULL, NULL, &chessPieces[18].sprite.rect.w, &chessPieces[18].sprite.rect.h);
    chessPieces[19] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 1, 3, 'p' };
    chessPieces[19].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[19].sprite.texture, NULL, NULL, &chessPieces[19].sprite.rect.w, &chessPieces[19].sprite.rect.h);
    chessPieces[20] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 1, 4, 'p' };
    chessPieces[20].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[20].sprite.texture, NULL, NULL, &chessPieces[20].sprite.rect.w, &chessPieces[20].sprite.rect.h);
    chessPieces[21] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 1, 5, 'p' };
    chessPieces[21].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[21].sprite.texture, NULL, NULL, &chessPieces[21].sprite.rect.w, &chessPieces[21].sprite.rect.h);
    chessPieces[22] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 1, 6, 'p' };
    chessPieces[22].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[22].sprite.texture, NULL, NULL, &chessPieces[22].sprite.rect.w, &chessPieces[22].sprite.rect.h);
    chessPieces[23] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 1, 7, 'p' };
    chessPieces[23].sprite.texture = LoadTexture(*renderer, "res/Images/blackPawn.png");
    SDL_QueryTexture(chessPieces[23].sprite.texture, NULL, NULL, &chessPieces[23].sprite.rect.w, &chessPieces[23].sprite.rect.h);
    
    chessPieces[24] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 0, 0, 'R' };
    chessPieces[24].sprite.texture = LoadTexture(*renderer, "res/Images/blackRook.png");
    SDL_QueryTexture(chessPieces[24].sprite.texture, NULL, NULL, &chessPieces[24].sprite.rect.w, &chessPieces[24].sprite.rect.h);
    chessPieces[25] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 0, 1, 'K' };
    chessPieces[25].sprite.texture = LoadTexture(*renderer, "res/Images/blackKnight.png");
    SDL_QueryTexture(chessPieces[25].sprite.texture, NULL, NULL, &chessPieces[25].sprite.rect.w, &chessPieces[25].sprite.rect.h);
    chessPieces[26] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 0, 2, 'B' };
    chessPieces[26].sprite.texture = LoadTexture(*renderer, "res/Images/blackBishop.png");
    SDL_QueryTexture(chessPieces[26].sprite.texture, NULL, NULL, &chessPieces[26].sprite.rect.w, &chessPieces[26].sprite.rect.h);
    chessPieces[27] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 0, 3, 'Q' };
    chessPieces[27].sprite.texture = LoadTexture(*renderer, "res/Images/blackQueen.png");
    SDL_QueryTexture(chessPieces[27].sprite.texture, NULL, NULL, &chessPieces[27].sprite.rect.w, &chessPieces[27].sprite.rect.h);
    chessPieces[28] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 0, 4, 'K' };
    chessPieces[28].sprite.texture = LoadTexture(*renderer, "res/Images/blackKing.png");
    SDL_QueryTexture(chessPieces[28].sprite.texture, NULL, NULL, &chessPieces[28].sprite.rect.w, &chessPieces[28].sprite.rect.h);
    chessPieces[29] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 0, 5, 'B' };
    chessPieces[29].sprite.texture = LoadTexture(*renderer, "res/Images/blackBishop.png");
    SDL_QueryTexture(chessPieces[29].sprite.texture, NULL, NULL, &chessPieces[29].sprite.rect.w, &chessPieces[29].sprite.rect.h);
    chessPieces[30] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 0, 6, 'K' };
    chessPieces[30].sprite.texture = LoadTexture(*renderer, "res/Images/blackKnight.png");
    SDL_QueryTexture(chessPieces[30].sprite.texture, NULL, NULL, &chessPieces[30].sprite.rect.w, &chessPieces[30].sprite.rect.h);
    chessPieces[31] = (chessPiece) { { NULL, { 0, 0, 0, 0 } }, BLACK_TEAM, SDL_TRUE, 0, 7, 'R' };
    chessPieces[31].sprite.texture = LoadTexture(*renderer, "res/Images/blackRook.png");
    SDL_QueryTexture(chessPieces[31].sprite.texture, NULL, NULL, &chessPieces[31].sprite.rect.w, &chessPieces[31].sprite.rect.h);
}

void exitGameState() {
    SDL_DestroyTexture(chessBoard.texture);
    chessBoard.texture = NULL;
    
    for(size_t i = 0; i < 32; ++i) {
        SDL_DestroyTexture(chessPieces->sprite.texture);
    }
    free(chessPieces);
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
        switch(event.type) {
            case SDL_QUIT:
                return 3;
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_ESCAPE) { return 1; }
                break;
            
            default:
                break;
        }
    }

    for(size_t i = 0; i < PIECE_COUNT; ++i) {
        chessPieces[i].sprite.rect.x = chessBoard.rect.x + (chessPieces[i].col * SQUARE_WIDTH);
        chessPieces[i].sprite.rect.y = chessBoard.rect.y + (chessPieces[i].row * SQUARE_WIDTH);
    }

    return 0;
}

void gameStateRender(SDL_Window **window, SDL_Renderer **renderer) {
    (void)window;

    SDL_SetRenderDrawColor(*renderer, gameBackgroundColor.r, gameBackgroundColor.g, gameBackgroundColor.b, gameBackgroundColor.a);
    SDL_RenderClear(*renderer);

    // Render here
    SDL_Rect chessBoardDestinationRect = { chessBoard.rect.x, chessBoard.rect.y, chessBoard.rect.w, chessBoard.rect.h };
    SDL_RenderCopy(*renderer, chessBoard.texture, NULL, &chessBoardDestinationRect);

    for(size_t i = 0; i < PIECE_COUNT; ++i) {
        if(chessPieces[i].isAlive == SDL_TRUE) {
            SDL_Rect pieceDestinationRect = { chessPieces[i].sprite.rect.x, chessPieces[i].sprite.rect.y, chessPieces[i].sprite.rect.w, chessPieces[i].sprite.rect.h };
            SDL_RenderCopy(*renderer, chessPieces[i].sprite.texture, NULL, &pieceDestinationRect);
        }
    }
    
    SDL_RenderPresent(*renderer);
}