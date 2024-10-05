#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <sqlite3.h>

// Constantes
#define MAX_CARDS 20 
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MIN_CARD_SIZE 50
#define CARD_RATIO 1.4f
#define MAX_SCORES 10

// Structs
typedef struct {
    Rectangle rect;
    char value[3];
    bool revealed;
    bool matched;
    Color color;
    Texture2D texture;
} Card;

typedef struct {
    int score;
    float time;
    char date[20];
} Score;

typedef enum {
    GAME_START,
    GAME_PLAY,
    GAME_OVER,
    GAME_SETTINGS,
    GAME_SCOREBOARD,
    GAME_CONFIRM_EXIT
} GameState;

// Variaveis Globais / Estados
static Card cards[MAX_CARDS];
static int selectedCards[2] = {-1, -1};
static int selectedCount = 0;
static int moves = 0;
static float gameTime = 0;
static GameState currentState = GAME_START;
static Texture2D cardBack;
static Font gameFont;
static int numCards = 16;
static bool musicEnabled = true;
static float musicVolume = 0.1f;
static Music backgroundMusic;
static Sound flipSound;
static sqlite3 *db;
static int gridWidth = 0;
static int gridHeight = 0;
static bool vimMode = false;
static int vimSelectedIndex = 0;

// Declarações de Função
void InitializeCards(void);
void DrawCards(void);
void UpdateGame(void);
void DrawUI(void);
void DrawStartScreen(void);
void DrawGameOverScreen(void);
void DrawSettingsScreen(void);
void UpdateSettings(void);
void DrawScoreboardScreen(void);
void ResetGame(void);
void SaveScore(int score, float gameTime);
int GetTopScores(Score *scores, int limit);
void ResetScoreboard(void);
void DrawConfirmExitScreen(void);

// Inicializa as cartas
void InitializeCards(void) {
    const char *values[] = {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
    const Color colors[] = {RED, BLUE, GREEN, YELLOW, PURPLE, ORANGE, PINK, SKYBLUE, LIME, GOLD, VIOLET, BEIGE, BROWN};
    const int totalValues = sizeof(values) / sizeof(values[0]);
    int numUniqueCards = numCards / 2;
    if (numUniqueCards > totalValues) numUniqueCards = totalValues;

    // Calcula o tamanho do Grid
    gridWidth = (int)sqrt(numCards);
    while (numCards % gridWidth != 0) gridWidth--;
    gridHeight = numCards / gridWidth;
    
    // Calcula o tamanho das cartas e espaços
    float padding = 10.0f;
    float totalPaddingWidth = padding * (gridWidth + 1);
    float totalPaddingHeight = padding * (gridHeight + 1);
    float availableWidth = SCREEN_WIDTH - totalPaddingWidth;
    float availableHeight = SCREEN_HEIGHT - totalPaddingHeight;
    float cardWidth = availableWidth / gridWidth;
    float cardHeight = availableHeight / gridHeight;

    if (cardHeight / cardWidth > CARD_RATIO) cardHeight = cardWidth * CARD_RATIO;
    else cardWidth = cardHeight / CARD_RATIO;

    float startX = (SCREEN_WIDTH - (cardWidth * gridWidth + padding * (gridWidth - 1))) / 2;
    float startY = (SCREEN_HEIGHT - (cardHeight * gridHeight + padding * (gridHeight - 1))) / 2;

    // Inicializa cada carta com seu tamanho, imagem e posição
    for (int i = 0; i < numCards; i++) {
        int valueIndex = i % numUniqueCards;
        cards[i] = (Card){
            .rect = {0, 0, cardWidth, cardHeight},
            .revealed = false,
            .matched = false,
            .color = colors[valueIndex],
            .texture = LoadTexture(TextFormat("resources/card_spades_%s.png", values[valueIndex]))
        };
        strcpy(cards[i].value, values[valueIndex]);
    }

    // Embaralha as cartas
    for (int i = numCards - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }

    // Coloca a posição de cada carta no Grid
    for (int i = 0; i < numCards; i++) {
        int row = i / gridWidth;
        int col = i % gridWidth;
        cards[i].rect.x = startX + col * (cardWidth + padding);
        cards[i].rect.y = startY + row * (cardHeight + padding);
    }
}


// Mostra as cartas na tela
void DrawCards(void) {
    for (int i = 0; i < numCards; i++) {
        Rectangle destRect = cards[i].rect;
        if (cards[i].matched) {
            DrawRectangleRec(destRect, Fade(cards[i].color, 0.5f));
            DrawTexturePro(cards[i].texture, (Rectangle){0, 0, cards[i].texture.width, cards[i].texture.height},
                           destRect, (Vector2){0, 0}, 0, WHITE);
        } else if (cards[i].revealed) {
            DrawTexturePro(cards[i].texture, (Rectangle){0, 0, cards[i].texture.width, cards[i].texture.height},
                           destRect, (Vector2){0, 0}, 0, WHITE);
        } else {
            DrawTexturePro(cardBack, (Rectangle){0, 0, cardBack.width, cardBack.height},
                           destRect, (Vector2){0, 0}, 0, WHITE);
        }
        if (vimMode && i == vimSelectedIndex) DrawRectangleLinesEx(destRect, 3, RED);
    }
}


// Atualiza o estadado do jogo
void UpdateGame(void) {
    if (currentState != GAME_PLAY) return;

    gameTime += GetFrameTime();

    // Modo VIM :)
    if (vimMode) {
        if (IsKeyPressed(KEY_H) && vimSelectedIndex % gridWidth > 0) vimSelectedIndex--;
        if (IsKeyPressed(KEY_L) && vimSelectedIndex % gridWidth < gridWidth - 1) vimSelectedIndex++;
        if (IsKeyPressed(KEY_K) && vimSelectedIndex >= gridWidth) vimSelectedIndex -= gridWidth;
        if (IsKeyPressed(KEY_J) && vimSelectedIndex + gridWidth < numCards) vimSelectedIndex += gridWidth;
        if (IsKeyPressed(KEY_SPACE)) {
            int i = vimSelectedIndex;
            if (!cards[i].matched && !cards[i].revealed && selectedCount < 2) {
                cards[i].revealed = true;
                selectedCards[selectedCount++] = i;
                moves++;
                PlaySound(flipSound);
            }
        }
        if (IsKeyPressed(KEY_ESCAPE)) vimMode = false;
    } else {
        // Modo Mouse
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();
            for (int i = 0; i < numCards; i++) {
                if (CheckCollisionPointRec(mousePoint, cards[i].rect) &&
                    !cards[i].matched && !cards[i].revealed && selectedCount < 2) {
                    cards[i].revealed = true;
                    selectedCards[selectedCount++] = i;
                    moves++;
                    PlaySound(flipSound);
                    break;
                }
            }
        }
        if (IsKeyPressed(KEY_I)) {
            vimMode = true;
            vimSelectedIndex = 0;
        }
        if (IsKeyPressed(KEY_BACKSPACE)) currentState = GAME_CONFIRM_EXIT;
    }

    // Checa se foram selecionadas 2 cartas
    if (selectedCount == 2) {
        if (strcmp(cards[selectedCards[0]].value, cards[selectedCards[1]].value) == 0) {
            cards[selectedCards[0]].matched = cards[selectedCards[1]].matched = true;
        } else {
            cards[selectedCards[0]].revealed = cards[selectedCards[1]].revealed = false;
        }
        selectedCount = 0;
        selectedCards[0] = selectedCards[1] = -1;
    }

    // Checa fim do jogo
    bool allMatched = true;
    for (int i = 0; i < numCards; i++) {
        if (!cards[i].matched) {
            allMatched = false;
            break;
        }
    }
    if (allMatched) currentState = GAME_OVER;
}


// Coloca o número de movimentos e tempo na tela
void DrawUI(void) {
    DrawTextEx(gameFont, TextFormat("Moves: %d", moves), (Vector2){10, 10}, 30, 2, BLACK);
    DrawTextEx(gameFont, TextFormat("Time: %.1f", gameTime), (Vector2){SCREEN_WIDTH - 150, 10}, 30, 2, BLACK);
}


// Tela Inicial 
void DrawStartScreen(void) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(RAYWHITE, 0.8f));
    const char* title = "Memory Game";
    int textWidth = MeasureText(title, 60);
    DrawText(title, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT / 2 - 150, 60, BLACK);

    const char* instructions[] = {
        "Click to start",
        "Press S for settings",
        "Press B for scoreboard"
    };
    for (int i = 0; i < 3; i++) {
        textWidth = MeasureText(instructions[i], 30);
        DrawText(instructions[i], (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT / 2 + i * 70 - 50, 30, DARKGRAY);
    }
}

// Tela de Fim de Jogo
void DrawGameOverScreen(void) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(RAYWHITE, 0.8f));
    const char* title = "Game Over!";
    int textWidth = MeasureText(title, 60);
    DrawText(title, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT / 2 - 100, 60, BLACK);

    char movesAndTimeText[100];
    snprintf(movesAndTimeText, sizeof(movesAndTimeText), "Moves: %d  Time: %.1f", moves, gameTime);
    textWidth = MeasureText(movesAndTimeText, 30);
    DrawText(movesAndTimeText, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT / 2, 30, DARKGRAY);

    const char* playAgain = "Click to play again";
    textWidth = MeasureText(playAgain, 30);
    DrawText(playAgain, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT / 2 + 50, 30, DARKGRAY);
}



// Tela de Configurações
void DrawSettingsScreen(void) {
    // TODO: Nem tudo aqui funciona
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(RAYWHITE, 0.8f));
    const char* title = "Settings";
    int textWidth = MeasureText(title, 60);
    DrawText(title, (SCREEN_WIDTH - textWidth) / 2, 50, 60, BLACK);

    const int totalOptions = 4;
    static int selectedOption = 0;
    const char *options[] = {
        TextFormat("Number of Cards: %d", numCards),
        TextFormat("Music: %s", musicEnabled ? "ON" : "OFF"),
        TextFormat("Volume: %.1f", musicVolume),
        "Reset Scoreboard"
    };

    for (int i = 0; i < totalOptions; i++) {
        Color color = (i == selectedOption) ? RED : BLACK;
        textWidth = MeasureText(options[i], 30);
        DrawText(options[i], (SCREEN_WIDTH - textWidth) / 2, 150 + i * 80, 30, color);
    }

    const char* instruction = "Use H/L to adjust, J/K to navigate, ESC to return";
    textWidth = MeasureText(instruction, 20);
    DrawText(instruction, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT - 50, 20, DARKGRAY);
}

void UpdateSettings(void) {
    const int totalOptions = 4;
    static int selectedOption = 0;

    if (IsKeyPressed(KEY_J)) selectedOption = (selectedOption + 1) % totalOptions;
    if (IsKeyPressed(KEY_K)) selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;

    if (IsKeyPressed(KEY_H) || IsKeyPressed(KEY_L)) {
        switch (selectedOption) {
            case 0:
                numCards = IsKeyPressed(KEY_H) ? (numCards > 4 ? numCards - 2 : numCards) :
                                                 (numCards < MAX_CARDS ? numCards + 2 : numCards);
                InitializeCards();
                break;
            case 1:
                musicEnabled = !musicEnabled;
                break;
            case 2:
                musicVolume = IsKeyPressed(KEY_H) ? (musicVolume > 0.0f ? musicVolume - 0.1f : musicVolume) :
                                                    (musicVolume < 1.0f ? musicVolume + 0.1f : musicVolume);
                SetMusicVolume(backgroundMusic, musicVolume);
                break;
            case 3:
                ResetScoreboard();
                break;
        }
    }
    if (IsKeyPressed(KEY_ESCAPE)) currentState = GAME_START;
}

void DrawScoreboardScreen(void) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(RAYWHITE, 0.8f));
    const char* title = "Scoreboard";
    int textWidth = MeasureText(title, 60);
    DrawText(title, (SCREEN_WIDTH - textWidth) / 2, 50, 60, BLACK);

    Score scores[MAX_SCORES];
    int count = GetTopScores(scores, MAX_SCORES);
    for (int i = 0; i < count; i++) {
        char scoreText[100];
        snprintf(scoreText, sizeof(scoreText), "%d. Score: %d Time: %.1f - %s", i + 1, scores[i].score, scores[i].time, scores[i].date);
        textWidth = MeasureText(scoreText, 20);
        DrawText(scoreText, (SCREEN_WIDTH - textWidth) / 2, 150 + i * 40, 20, BLACK);
    }

    const char* instruction = "Press ESC to return to menu";
    textWidth = MeasureText(instruction, 30);
    DrawText(instruction, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT - 50, 30, DARKGRAY);
}

void ResetGame(void) {
    for (int i = 0; i < numCards; i++) {
        cards[i].revealed = false;
        cards[i].matched = false;
    }
    selectedCount = 0;
    selectedCards[0] = selectedCards[1] = -1;
    moves = 0;
    gameTime = 0;

    for (int i = numCards - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }

    float padding = 10.0f;
    float cardWidth = cards[0].rect.width;
    float cardHeight = cards[0].rect.height;
    float startX = (SCREEN_WIDTH - (cardWidth * gridWidth + padding * (gridWidth - 1))) / 2;
    float startY = (SCREEN_HEIGHT - (cardHeight * gridHeight + padding * (gridHeight - 1))) / 2;

    for (int i = 0; i < numCards; i++) {
        int row = i / gridWidth;
        int col = i % gridWidth;
        cards[i].rect.x = startX + col * (cardWidth + padding);
        cards[i].rect.y = startY + row * (cardHeight + padding);
    }
}

void SaveScore(int score, float gameTime) {
    char *err_msg = 0;
    char sql[256];
    time_t now = time(NULL);
    struct tm *timenow = localtime(&now);
    sprintf(sql, "INSERT INTO scores (score, time, date) VALUES (%d, %.1f, '%04d-%02d-%02d')", 
            score, gameTime, timenow->tm_year + 1900, timenow->tm_mon + 1, timenow->tm_mday);
    
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

int GetTopScores(Score *scores, int limit) {
    char sql[100];
    sprintf(sql, "SELECT score, time, date FROM scores ORDER BY score DESC, time ASC LIMIT %d", limit);
    
    sqlite3_stmt *res;
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    int count = 0;
    while (sqlite3_step(res) == SQLITE_ROW && count < limit) {
        scores[count].score = sqlite3_column_int(res, 0);
        scores[count].time = (float)sqlite3_column_double(res, 1);
        strcpy(scores[count].date, (const char*)sqlite3_column_text(res, 2));
        count++;
    }
    
    sqlite3_finalize(res);
    return count;
}

void ResetScoreboard(void) {
    char *err_msg = 0;
    const char *sql = "DELETE FROM scores";
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

void DrawConfirmExitScreen(void) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.5f));
    const char* title = "Return to Main Menu?";
    int textWidth = MeasureText(title, 40);
    DrawText(title, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT / 2 - 50, 40, RAYWHITE);

    const char* options = "Y: Yes    N: No";
    textWidth = MeasureText(options, 30);
    DrawText(options, (SCREEN_WIDTH - textWidth) / 2, SCREEN_HEIGHT / 2 + 10, 30, RAYWHITE);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Memory Game");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    srand((unsigned int)time(NULL));
    InitializeCards();

    cardBack = LoadTexture("resources/card_back.png");
    gameFont = LoadFontEx("resources/font.ttf", 32, 0, 0);

    InitAudioDevice();
    backgroundMusic = LoadMusicStream("resources/background_music.mp3");
    flipSound = LoadSound("resources/flip_sound.wav");
    PlayMusicStream(backgroundMusic);
    SetMusicVolume(backgroundMusic, musicVolume);

    if (sqlite3_open("scores.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS scores (id INTEGER PRIMARY KEY AUTOINCREMENT, score INTEGER, time REAL, date TEXT)";
    char *err_msg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }

    while (!WindowShouldClose()) {
        UpdateMusicStream(backgroundMusic);

        if (musicEnabled) {
            if (!IsMusicStreamPlaying(backgroundMusic)) PlayMusicStream(backgroundMusic);
        } else {
            if (IsMusicStreamPlaying(backgroundMusic)) StopMusicStream(backgroundMusic);
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            if (vimMode) {
                vimMode = false;
            } else if (currentState == GAME_SETTINGS || currentState == GAME_SCOREBOARD) {
                currentState = GAME_START;
            } else if (currentState == GAME_PLAY) {
                currentState = GAME_CONFIRM_EXIT;
            } else {
                break;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState) {
            case GAME_START:
                DrawStartScreen();
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    ResetGame();
                    currentState = GAME_PLAY;
                }
                if (IsKeyPressed(KEY_S)) currentState = GAME_SETTINGS;
                if (IsKeyPressed(KEY_B)) currentState = GAME_SCOREBOARD;
                break;
            case GAME_PLAY:
                UpdateGame();
                DrawCards();
                DrawUI();
                break;
            case GAME_OVER:
                DrawCards();
                DrawGameOverScreen();
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    SaveScore(1000 / moves, gameTime);
                    ResetGame();
                    currentState = GAME_PLAY;
                }
                break;
            case GAME_SETTINGS:
                UpdateSettings();
                DrawSettingsScreen();
                break;
            case GAME_SCOREBOARD:
                DrawScoreboardScreen();
                break;
            case GAME_CONFIRM_EXIT:
                DrawCards();
                DrawUI();
                DrawConfirmExitScreen();
                if (IsKeyPressed(KEY_Y)) currentState = GAME_START;
                if (IsKeyPressed(KEY_N) || IsKeyPressed(KEY_ESCAPE)) currentState = GAME_PLAY;
                break;
        }

        EndDrawing();
    }

    for (int i = 0; i < numCards / 2; i++) {
        UnloadTexture(cards[i].texture);
    }
    UnloadTexture(cardBack);
    UnloadFont(gameFont);
    UnloadMusicStream(backgroundMusic);
    UnloadSound(flipSound);
    CloseAudioDevice();
    sqlite3_close(db);

    CloseWindow();
    return 0;
}
