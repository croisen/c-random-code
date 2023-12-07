#include <raylib.h>
#include <stdio.h>
#include <string.h>

struct Snake {
    Vector2 snake_head;
    Vector2 snake_body;
    int snake_lenght;
};

int main(void) {
    InitWindow(800, 400, "Croisen's Snake game in C");
    SetTargetFPS(120);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    int  windowX            = GetScreenWidth();
    int  windowY            = GetScreenHeight();
    int  lower_for_box      = (windowX > windowY) ? windowY/3 : windowX/3;
    int  fontSize           = lower_for_box / 10;
    /*int  max_score          = 0;*/
    bool portrait           = false;

    int  game_rec_thickness = lower_for_box / 100;
    Rectangle game_rec      = { 
                                (float)windowX/5 - (float)lower_for_box/5,
                                (float)windowY/5 - (float)lower_for_box/5,
                                (windowX - (((float)windowX/5) + ((float)lower_for_box/5))),
                                (windowY - (((float)windowY/5) + ((float)lower_for_box/5)))
                              };
    struct Snake snake      = {
                                { 3, 5 },
                                { 4, 5 },
                                69
                              };

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            windowX    = GetScreenWidth();
            windowY    = GetScreenHeight();
            lower_for_box   = (windowX > windowY) ? windowY/3 : windowX/3;
            game_rec_thickness  = lower_for_box / 50;
            game_rec.x      =  (float)windowX/5 - (float)lower_for_box/5;
            game_rec.y      =  (float)windowY/5 - (float)lower_for_box/5;
            game_rec.width  =  (windowX - (((float)windowX/5) + ((float)lower_for_box/5)));
            game_rec.height =  (windowY - (((float)windowY/5) + ((float)lower_for_box/5)));
            portrait        = (windowX > windowY) ? false : true;
            fontSize        = lower_for_box / 5;
        }
        
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleLinesEx(game_rec, game_rec_thickness, WHITE);
        (portrait)
            ? DrawText(TextFormat("Score:\n%4d", snake.snake_lenght),
                       (windowX / 2) - fontSize,
                       (windowY / 8) - ((fontSize * strlen(TextFormat("Score:\n%4d", snake.snake_lenght))) / 4),
                        fontSize,
                        RAYWHITE)
            : DrawText(TextFormat("Score:\n%4d", snake.snake_lenght),
                       (windowX / 8) - ((fontSize * strlen(TextFormat("Score:\n%4d", snake.snake_lenght))) / 4),
                       (windowY / 2) - fontSize,
                       fontSize,
                       RAYWHITE);
        DrawFPS(0, 0);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
