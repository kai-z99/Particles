#include <cstdio>
#include <math.h>
#include <iostream>
#include <vector>
#include "raylib.h"
#include "raymath.h"
#include "player.h"

//TODO: Collect the birds that are flying around to join you. Wild: grey, yours: red. Or somehtin along those lines?
int main(void)
{
    InitWindow(1024, 768, "raylib [core] example - basic window");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };   // Center of the camera
    camera.offset = (Vector2){ 1024/2.0f, 768/2.0f }; // Center of the screen
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60); // Set the desired frame rate

    std::vector<Player*> players;

    for (int i = 0; i < 80; i++)
    {
        players.push_back(new Player((Vector2){GetRandomValue(-3100, 3100), GetRandomValue(-3100, 3100)}));
        if (i == 0) players[i]->SetColor(GREEN);
    }   

    while (!WindowShouldClose()) {
        // Update

        //Convert mouse position to world coordinates.
        Vector2 mousePosition = GetMousePosition();
        Vector2 mouseWorldPosition = GetScreenToWorld2D(mousePosition, camera);

        for (int i = 0; i < players.size(); i++)
        {
            Vector2 playerPos = players[i]->GetPosition();
            float angle;

            //If its the player is the leader, the angle is to the mouse. If its not, the angle is to the 
            if (i == 0) angle = atan2f(mouseWorldPosition.y - playerPos.y, mouseWorldPosition.x - playerPos.x);
            else angle = atan2f(players[i - 1]->GetPosition().y - playerPos.y, players[i - 1]->GetPosition().x - playerPos.x);

            if (angle < 0.0f) 
            {
                angle += 2.0f * PI;
            }

            if (IsMouseButtonDown(0))
            {
                players[i]->ApplyAccelerationInDirection(angle);
            }
            else
            {
                if (i == 0) players[i]->Deaccelerate();
            }
            
            players[i]->Update();
        }
        

        // Update camera to follow player
        float smoothing = 0.03f;
        camera.target = Vector2Lerp(camera.target, players[0]->GetPosition(), smoothing);

        // Zoom controls
        if (IsKeyDown(KEY_UP)) camera.zoom += 0.01f;  // Zoom in
        if (IsKeyDown(KEY_DOWN)) camera.zoom -= 0.01f;  // Zoom out
        if (IsKeyDown(KEY_SPACE)) camera.target = players[0]->GetPosition();
        
        // Begin 2D rendering
        BeginDrawing();
        

        BeginMode2D(camera); // Begin using the camera's viewport and transformations
        ClearBackground(BLACK);
        // Draw a grid to help visualize movement
        for (int y = -1500; y < 1500; y += 80) {
            for (int x = -1500; x < 1500; x += 80) {
                DrawRectangleLines(x, y, 80, 80, { 200, 200, 200, 105 });
            }
        }

        for (Player* p : players)
        {
            p->Draw();
        }

        EndMode2D(); // End the camera mode

        DrawFPS(10,10);
        DrawText("Snake Game", 10, 30, 30, RED);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}