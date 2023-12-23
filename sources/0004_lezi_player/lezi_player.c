/*  Tweaked example of the music player in the raylib library  */

#include <raylib.h>
#include <stdio.h>

typedef struct {
    Vector2 position;
    float radius;
    float alpha;
    float speed;
    Color color;
} CircleWave;

int main(int argc, char **argv) {
    InitAudioDevice();
    InitWindow(800, 400, TextFormat("Lezi: %s", argv[1]));
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    if (argc < 2) {
        CloseAudioDevice();
        CloseWindow();
        (void)fprintf(stderr,
                      "Expecting an argument for a music file, found NULL\n");
        return 1;
    }

    Music music = LoadMusicStream(argv[1]);
    PlayMusicStream(music);

    int windowX = GetScreenWidth();
    int windowY = GetScreenHeight();
    bool paused = false;
    double time_played_perc =
        (double)GetMusicTimePlayed(music) / (double)GetMusicTimeLength(music);

    Color colors[13] = {BLUE,    GOLD,   GREEN,  LIGHTGRAY, LIME,
                        MAGENTA, MAROON, ORANGE, PURPLE,    SKYBLUE,
                        VIOLET,  YELLOW, WHITE};

    CircleWave circles[64];

    for (int i = 0; i < 64; i++) {
        circles[i].alpha = 0.0F;
        circles[i].color = colors[GetRandomValue(0, 12)];
        circles[i].radius =
            (windowX > windowY)
                ? GetRandomValue((int)(windowY / 40), (int)(windowY / 10))
                : GetRandomValue((int)(windowX / 40), (int)(windowX / 10));
        circles[i].speed = (float)GetRandomValue(1, 100) / 2000.0F;
        circles[i].position.x = (float)GetRandomValue(
            (int)circles[i].radius, (int)(windowX - circles[i].radius));
        circles[i].position.y = (float)GetRandomValue(
            (int)circles[i].radius, (int)(windowY - circles[i].radius));
    }

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            windowX = GetScreenWidth();
            windowY = GetScreenHeight();
        }

        if (paused == false) {
            for (int i = 0; i < 64; i++) {
                circles[i].alpha += circles[i].speed;
                circles[i].radius += circles[i].speed * 10.0F;
                (circles[i].alpha > 1.0F) ? circles[i].speed *= -1
                                          : circles[i].alpha;
                if (circles[i].alpha <= 0.0F) {
                    circles[i].alpha = 0.0F;
                    circles[i].color = colors[GetRandomValue(0, 12)];
                    circles[i].radius =
                        (windowX > windowY)
                            ? GetRandomValue((int)(windowY / 40),
                                             (int)(windowY / 10))
                            : GetRandomValue((int)(windowX / 40),
                                             (int)(windowX / 10));
                    circles[i].speed = (float)GetRandomValue(1, 100) / 2000.0F;
                    circles[i].position.x = (float)GetRandomValue(
                        (int)circles[i].radius,
                        (int)(windowX - circles[i].radius));
                    circles[i].position.y = (float)GetRandomValue(
                        (int)circles[i].radius,
                        (int)(windowY - circles[i].radius));
                }
            }
        }

        UpdateMusicStream(music);
        time_played_perc = (double)GetMusicTimePlayed(music) /
                           (double)GetMusicTimeLength(music);

        if (IsKeyPressed(KEY_P)) {
            paused = !paused;
            (paused) ? PauseMusicStream(music) : ResumeMusicStream(music);
        }
        if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_SPACE)) {
            StopMusicStream(music);
            PlayMusicStream(music);
        }
        if (IsKeyPressed(KEY_LEFT)) {
            SeekMusicStream(music, GetMusicTimePlayed(music) - 1.0F);
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            SeekMusicStream(music, GetMusicTimePlayed(music) + 1.0F);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(0, 0);
        for (int i = 0; i < 64; i++) {
            DrawCircleV(circles[i].position, circles[i].radius,
                        Fade(circles[i].color, circles[i].alpha));
        }
        DrawRectangle(windowX / 20, windowY - 2 * (windowY / 30),
                      windowX - 2 * (windowX / 20), windowY / 30, RED);
        DrawRectangle(windowX / 20, windowY - 2 * (windowY / 30),
                      (windowX - 2 * ((float)windowX / 20)) * time_played_perc,
                      windowY / 30, BLUE);
        DrawRectangleLines(windowX / 20, windowY - 2 * (windowY / 30),
                           windowX - 2 * (windowX / 20), windowY / 30, WHITE);
        EndDrawing();
    }
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}
