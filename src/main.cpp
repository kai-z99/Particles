#include <cstdio>
#include <math.h>
#include <iostream>
#include "raylib.h"
#include "player.h"


int main(void)
{
    InitWindow(1024, 768, "raylib [core] example - basic window");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };   // Center of the camera
    camera.offset = (Vector2){ 1024/2.0f, 768/2.0f }; // Center of the screen
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60); // Set the desired frame rate

    Player* p = new Player({0,0});

    while (!WindowShouldClose()) {
        // Update

        Vector2 mousePosition = GetMousePosition();
        Vector2 centerOfScreen = {1024.0f/2.0f, 768.0f/2.0f};
        DrawCircleV(centerOfScreen, 2.0f, RED);
        DrawCircleV(mousePosition, 2.0f, GREEN);

        std::cout << mousePosition.x - centerOfScreen.x << " , " << mousePosition.y - centerOfScreen.y << '\n';

        float angle = atan2f(mousePosition.y - centerOfScreen.y, mousePosition.x - centerOfScreen.x);

        if (angle < 0.0f) 
        {
            angle += 2.0f * PI;
        }

        if (IsMouseButtonDown(0))
        {
            p->ApplyAccelerationInDirection(angle);
        }
        else
        {
            p->Deaccelerate();
        }
        
        p->Update();

        // Update camera to follow player
        camera.target = p->GetPosition();

        // Zoom controls
        if (IsKeyDown(KEY_UP)) camera.zoom += 0.01f;  // Zoom in
        if (IsKeyDown(KEY_DOWN)) camera.zoom -= 0.01f;  // Zoom out

        // Begin 2D rendering
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera); // Begin using the camera's viewport and transformations

        // Draw a grid to help visualize movement
        for (int y = -1500; y < 1500; y += 40) {
            for (int x = -1500; x < 1500; x += 40) {
                DrawRectangleLines(x, y, 40, 40, LIGHTGRAY);
            }
        }

        p->Draw();

        float number = angle;
        char buffer[50];

        std::sprintf(buffer, "%f",number );

        const char* result = buffer;
        //DrawText(result, p->GetPosition().x, p->GetPosition().y, 30, BLACK);
        EndMode2D(); // End the camera mode


        DrawText("Move with arrow keys, Zoom with A/S", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}