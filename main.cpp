#include <iostream>
#include <raylib.h>
#include <vector>
#include <cmath>

using namespace std;

void brickBuilding(vector<vector<int>> &brick)
{
    // brick building
    int size = brick.size();
    for (int i = 0; i < size; i++)
    {
        DrawCircle(brick[i][0], brick[i][1], 20, RED);
    }
}
void brick_Vector(vector<vector<int>> &bricks)
{
    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 13; col++)
        {
            int x = (col * 60) + 30; // Adjust the spacing
            int y = (row * 60) + 30;
            bricks.push_back({x, y});
        }
    }
}
void collisioncheck(vector<vector<int>> &brick, int ball_x, int ball_y, int ball_radius, int brick_radius, int &ball_x_speed, int &ball_y_speed)
{
    int size = brick.size();
    for (int i = 0; i < size; i++)
    {
        if (sqrt(pow((brick[i][0] - ball_x), 2) + pow((brick[i][1] - ball_y), 2)) <= (float)brick_radius + ball_radius)
        {
            brick.erase(brick.begin() + i);
            ball_x_speed *= -1;
            ball_y_speed *= -1;
            break;
        }
    }
}
static void gamerunning()
{
    int ball_x = 355;
    int ball_y = 565;
    int ball_speed_x = 2;
    int ball_speed_y = 3;
    int ball_radius = 8;
    int brick_radius = 20;
    const int screenWidth = 800;
    const int screenHeight = 600;
    int board_x = 360;
    int board_y = 570;
    int board_width = 80;
    int board_speed = 4;
    bool paused = false;
    bool restart = false;
    vector<vector<int>> brick;
    brick_Vector(brick);
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        if (!paused && !restart)
        {
            ClearBackground(BLACK);
            ball_x += ball_speed_x;
            ball_y -= ball_speed_y;

            if (ball_x + ball_radius >= screenWidth || ball_x - ball_radius <= 0)
            {
                ball_speed_x *= -1;
            }

            if (ball_y + ball_radius >= screenHeight || ball_y - ball_radius <= 0)
            {
                ball_speed_y *= -1;
            }
            if (IsKeyDown(KEY_D) && board_x + board_width <= 800)
            {
                board_x += board_speed;
            }
            if (IsKeyDown(KEY_A) && board_x >= 0)
            {
                board_x -= board_speed;
            }
            if (ball_y + ball_radius >= 570 && ball_x + ball_radius <= board_x + board_width && ball_x - ball_radius >= board_x)
            {
                ball_speed_y *= -1;
            }
            if (ball_y + ball_radius >= 600 && (ball_x + ball_radius < board_x - 1 || ball_x - ball_radius > board_x + board_width + 1))
            {
                restart = true;
            }
            if (IsKeyPressed(KEY_SPACE))
            {
                paused = true;
            }
            collisioncheck(brick, ball_x, ball_y, ball_radius, brick_radius, ball_speed_x, ball_speed_y);
            brickBuilding(brick);
            DrawRectangle(board_x, board_y, 80, 10, YELLOW);
            DrawCircle(ball_x, ball_y, ball_radius, WHITE);
        }
        else if (paused)
        {
            DrawText("PAUSED", 320, 200, 30, YELLOW);
            if (IsKeyPressed(KEY_SPACE))
            {
                paused = false;
            }
        }
        else
        {
            DrawText("OUT", 300, 300, 30, YELLOW);
            DrawText("Press R to Restart", 160, 400, 40, YELLOW);
            DrawText("Press Esc to exit", 160, 430, 40, YELLOW);

            if (IsKeyPressed(KEY_R))
            {
                gamerunning();
            }
            else if (IsKeyPressed(KEY_ESCAPE))
            {
                exit(0);
            }
        }
        EndDrawing();
    }
}
int main()
{
    InitWindow(800, 600, "BRICK GAME");
    gamerunning();
    CloseWindow();
    return 0;
}
