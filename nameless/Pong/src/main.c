#include <raylib.h>

int main() {
    InitWindow(0, 0, "Pong");
    Rectangle screen = {0, 0, (float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2};
    Rectangle border = {12, 12, screen.width - 24, screen.height - 24};
    Rectangle top = {screen.x, screen.y, border.width, border.y};
    Rectangle down = {screen.x, border.height + 12, screen.width, screen.y};

    SetWindowPosition(screen.width / 2, screen.height / 2);
    SetWindowSize(screen.width, screen.height);
    SetTargetFPS(60);

    Rectangle ball = {60, border.height, 12, 12};
    Rectangle player = {border.x + 12, border.height / 2, 12, 60};
    Rectangle cpu = {border.width - 12, border.height / 2, 12, 60};

    int score_width = MeasureText("00", 60);
    int ball_x = 12 / 2;
    int ball_y = 12 / 2;

    int player_point = 0;
    int cpu_point = 0;

    while (!WindowShouldClose()) {
        if ((CheckCollisionRecs(ball, player) && ball.x < player.x + player.width) ||
            (CheckCollisionRecs(ball, cpu) && ball.x > cpu.x - cpu.width))
            ball_x = -ball_x;
        else {
            if (CheckCollisionRecs(ball, top) || CheckCollisionRecs(ball, down))
                ball_y = -ball_y;
            else {
                if (ball.x < screen.x) {
                    ++cpu_point;
                    ball.x = border.width / 2;
                    ball.y = GetRandomValue(border.y + 10, border.height);
                } else if (ball.x > screen.width) {
                    ++player_point;
                    ball.x = border.width / 2;
                    ball.y = GetRandomValue(border.y + 10, border.height);
                }
            }
        }

        ball.x += ball_x;
        ball.y += ball_y;
        int step;

        if (IsKeyDown(KEY_W)) {
            step = -12 / 2; 
            if (!(CheckCollisionRecs(top, player) && step < 0)) {
                player.y += step;
            }
        } else if (IsKeyDown(KEY_S)) {
            step = 12 / 2;  
            if (!(CheckCollisionRecs(down, player) && step > 0)) {
                player.y += step;
            }
        }

        if (IsKeyDown(KEY_UP)) {
            step = -12 / 2; 
            if (!(CheckCollisionRecs(top, cpu) && step < 0)) {
                cpu.y += step;
            }
        } else if (IsKeyDown(KEY_DOWN)) {
            step = 12 / 2;  
            if (!(CheckCollisionRecs(down, cpu) && step > 0)) {
                cpu.y += step;
            }
        }

        if ((player_point >= 11) || (cpu_point >= 11)) {
            if (player_point - cpu_point < 2)
	      break;
	    WindowShouldClose(); 
        }

        BeginDrawing();
        DrawRectangleRec(screen, PURPLE);
        DrawRectangle(screen.x, border.y, screen.width, border.height, BLACK);
        DrawRectangle((screen.width / 2) - 5, border.y, 12, border.height, PURPLE);
        DrawText(TextFormat("%02d", player_point), (screen.width / 2) - 50 - score_width, 50, 60, GRAY);
        DrawText(TextFormat("%02d", cpu_point), (screen.width / 2) + 50, 50, 60, GRAY);
        DrawRectangleRec(ball, WHITE);
        DrawRectangleRec(player, WHITE);
        DrawRectangleRec(cpu, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
