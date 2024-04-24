#include "raylib.h"
#include <fluidsynth.h>
#include <stdbool.h>

static void DrawPianoKeys(int, int);
static void PlayNote(char, bool);

fluid_settings_t* settings = NULL;
fluid_synth_t* synth = NULL;
fluid_audio_driver_t* adriver = NULL;

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    settings = new_fluid_settings();
    fluid_settings_setstr(settings, "audio.driver", "alsa");
    synth = new_fluid_synth(settings);
    adriver = new_fluid_audio_driver(settings, synth);

    InitWindow(screenWidth, screenHeight, "Piano");

    SetTargetFPS(60); 

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawPianoKeys(screenWidth, screenHeight);

        EndDrawing();
    }

    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);

    CloseWindow(); 

    return 0;
}

static void DrawPianoKeys(int screenWidth, int screenHeight) {
    int whiteKeyWidth = screenWidth / 7;
    int whiteKeyHeight = screenHeight - 50;
    char whiteKeys[] = {'S', 'D', 'F', 'J', 'K', 'L', ';'};
    Color keyColor = WHITE;

    for (int i = 0; i < 7; i++) {
        if (IsKeyDown(whiteKeys[i])) {
            keyColor = LIGHTGRAY; 
        } else {
            keyColor = WHITE;
        }

        DrawRectangle(whiteKeyWidth * i, 50, whiteKeyWidth - 2, whiteKeyHeight, keyColor);
        DrawRectangleLines(whiteKeyWidth * i, 50, whiteKeyWidth - 2, whiteKeyHeight, BLACK);
        DrawText(TextFormat("%c", whiteKeys[i]), whiteKeyWidth * i + (whiteKeyWidth / 2) - 10, whiteKeyHeight, 20, BLACK);
    }

    int blackKeyWidth = whiteKeyWidth / 2;
    int blackKeyHeight = whiteKeyHeight * 0.6; 
    char blackKeys[] = {'E', 'R', 'I', 'O', 'P'};
    int blackOffsets[] = {0, 1, 3, 4, 5}; 
    Color blackKeyColor = BLACK; 

    for (int i = 0; i < 5; i++) {
        if (IsKeyDown(blackKeys[i])) {
            blackKeyColor = GRAY;
        } else {
            blackKeyColor = BLACK;
        }

        int blackKeyX = whiteKeyWidth * (blackOffsets[i] + 1) - blackKeyWidth / 2;
        DrawRectangle(blackKeyX, 50, blackKeyWidth - 2, blackKeyHeight, blackKeyColor);
        int textWidth = MeasureText(TextFormat("%c", blackKeys[i]), 20);
        DrawText(TextFormat("%c", blackKeys[i]), blackKeyX + (blackKeyWidth / 2) - (textWidth / 2), 80 + blackKeyHeight / 2, 20, WHITE);
    }
}

static void PlayNote(char, bool) {
    
}