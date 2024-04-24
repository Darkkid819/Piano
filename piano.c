#include "raylib.h"
#include <fluidsynth.h>
#include <stdbool.h>

static void DrawPianoKeys(int, int);
static void PlayNote(char, bool, bool);

bool keyPressedState[256] = { false };

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

    fluid_synth_sfload(synth, "resources/piano.sf2", 1);

    InitWindow(screenWidth, screenHeight, "Piano");

    SetTargetFPS(60); 

    while (!WindowShouldClose()) {
        PlayNote('S', IsKeyDown(KEY_S), keyPressedState['S']); // C4
        PlayNote('E', IsKeyDown(KEY_E), keyPressedState['E']); // C#4/Db4
        PlayNote('D', IsKeyDown(KEY_D), keyPressedState['D']); // D4
        PlayNote('R', IsKeyDown(KEY_R), keyPressedState['R']); // D#4/Eb4
        PlayNote('F', IsKeyDown(KEY_F), keyPressedState['F']); // E4
        PlayNote('J', IsKeyDown(KEY_J), keyPressedState['J']); // F4
        PlayNote('I', IsKeyDown(KEY_I), keyPressedState['I']); // F#4/Gb4
        PlayNote('K', IsKeyDown(KEY_K), keyPressedState['K']); // G4
        PlayNote('O', IsKeyDown(KEY_O), keyPressedState['O']); // G#4/Ab4
        PlayNote('L', IsKeyDown(KEY_L), keyPressedState['L']); // A4
        PlayNote('P', IsKeyDown(KEY_P), keyPressedState['P']); // A#4/Bb4
        PlayNote(';', IsKeyDown(KEY_SEMICOLON), keyPressedState[';']); // B4

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

static void PlayNote(char key, bool pressed, bool keyAlreadyPressed) {
    int note = -1;
    switch (key) {
        case 'S': note = 60; break; // C4
        case 'E': note = 61; break; // C#4/Db4
        case 'D': note = 62; break; // D4
        case 'R': note = 63; break; // D#4/Eb4
        case 'F': note = 64; break; // E4
        case 'J': note = 65; break; // F4
        case 'I': note = 66; break; // F#4/Gb4
        case 'K': note = 67; break; // G4
        case 'O': note = 68; break; // G#4/Ab4
        case 'L': note = 69; break; // A4
        case 'P': note = 70; break; // A#4/Bb4
        case ';': note = 71; break; // B4
    }

    if (note != -1) {
        if (pressed && !keyAlreadyPressed) {
            fluid_synth_noteon(synth, 0, note, 127);
            keyPressedState[key] = true;
        } else if (!pressed && keyAlreadyPressed) {
            fluid_synth_noteoff(synth, 0, note);
            keyPressedState[key] = false; 
        }
    }
}