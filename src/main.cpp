#include <cstdio>
#include <math.h>
#include <iostream>
#include <string>
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

    SetTargetFPS(60);


    char preset = 'a';

    float maxSpeed;
    float accel;
    float deaccel;
    int spread;
    int amount;

    switch (preset)
    {
    case 'a':
        maxSpeed = 110.0f;
        accel = 500.0f;
        deaccel = 0.1f;
        spread = 31000;
        amount = 80000;
        break;

    case 'b':
        maxSpeed = 8.0f;
        accel = 5.0f;
        deaccel = 0.1f;
        spread = 1000;
        amount = 80;
    }

    std::vector<Player*> players;

    for (int i = 0; i < amount; i++)
    {
        players.push_back(new Player((Vector2){(float)GetRandomValue(-spread, spread), (float)GetRandomValue(-spread, spread)}, maxSpeed, accel, deaccel, {(unsigned char)GetRandomValue(0,255),(unsigned char)GetRandomValue(0,255),(unsigned char)GetRandomValue(0,255),255 }, 40.0f));
        if (i == 0) 
        {
            players[i]->SetColor(GREEN);
            players[i]->SetPosition({0.0f, 0.0f});
        }
            

    }   

    int frame = 0;

    while (!WindowShouldClose()) {
        // Update
        frame++;

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
                
                //original
                // if (Vector2Distance((players[i]->GetPosition()), {0.0f , 0.0f}) > 55000)
                // {
                //     players[i]->SetPosition({0.0f , 0.0f});
                // }
                
                //Butterfly
                // if (fabs(players[i]->GetPosition().x) + fabs(players[i]->GetPosition().y) > 55000)
                // {
                //     players[i]->SetPosition({0.0f , 0.0f});
                // }

                //circular border, one rotating spout
                if (Vector2Distance((players[i]->GetPosition()), {0.0f , 0.0f}) > 55000)
                {
                    players[i]->SetPosition({ 50000.0f * (cosf((float)frame / 100.0f)) , 50000.0f * (sinf((float)frame / 100.0f))});
                }

                //circular border, one occilating spout
                // if (Vector2Distance((players[i]->GetPosition()), {0.0f , 0.0f}) > 55000)
                // {
                //     players[i]->SetPosition({ 0.0f , 50000.0f * (sinf((float)frame / 100.0f))});
                // }

                //2 spout
                // if (Vector2Distance((players[i]->GetPosition()), {0.0f , 0.0f}) > 55000)
                // {
                //     if (frame % 2 == 0) players[i]->SetPosition({ 50000.0f * (cosf((float)frame / 100.0f)) , 50000.0f * (sinf((float)frame / 100.0f))});
                //     else players[i]->SetPosition({ 50000.0f * (cosf((float)frame / 100.0f + PI)) , 50000.0f * (sinf((float)frame / 100.0f + PI))});
                // }

                //2 spout uneven
                // if (Vector2Distance((players[i]->GetPosition()), {0.0f , 0.0f}) > 55000)
                // {
                //     if (frame % 2 == 0) players[i]->SetPosition({ 50000.0f * (cosf((float)frame / 50.0f)) , 50000.0f * (sinf((float)frame / 100.0f))});
                //     else players[i]->SetPosition({ 50000.0f * (cosf((float)frame /50.0f + PI)) , 50000.0f * (sinf((float)frame / 100.0f + PI))});
                // }

                //circular contracting border, one rotating spout
                // if (Vector2Distance((players[i]->GetPosition()), {0.0f , 0.0f}) > (0.2f + fabs(sinf((float)frame / 100.0f))) * 55000)
                // {
                //     players[i]->SetPosition({ 5000.0f * (cosf((float)frame / 100.0f)) , 5000.0f * (sinf((float)frame / 100.0f))});
                // }

                //eye
                // Vector2 p = players[i]->GetPosition();
                // Vector2 s = {p.x * sinf((float)frame / 100.0f) , p.y * sinf((float)frame / 100.0f + (0.3f * PI) )};
                // if (Vector2Distance(s, {0.0f , 0.0f}) > 55000)
                // {
                //     if (frame % 2 == 0) players[i]->SetPosition({ 50000.0f * (cosf((float)frame / 100.0f)) , 50000.0f * (sinf((float)frame / 100.0f))});
                //     else players[i]->SetPosition({ 50000.0f * (cosf((float)frame / 100.0f + PI)) , 50000.0f * (sinf((float)frame / 100.0f + PI))});
                // }
            }
            
            players[i]->Update();
        }
        

        // Update camera to follow player
        float smoothing = 0.03f;
        camera.target = Vector2Lerp(camera.target, players[0]->GetPosition(), smoothing);

        // Zoom controls
        // Zoom controls
        float zoomFactor = 1.05f; // Adjust this factor to control zoom speed
        float wheelMove = GetMouseWheelMove();

        if (wheelMove != 0)
        {
            camera.zoom *= pow(zoomFactor, wheelMove);
        }       

        if (IsKeyDown(KEY_SPACE)) camera.target = players[0]->GetPosition();
        
        // Begin 2D rendering
        BeginDrawing();
        

        BeginMode2D(camera); // Begin using the camera's viewport and transformations
        ClearBackground(BLACK);
        
        // Draw a grid to help visualize movement
        for (int y = -3500; y < 3500; y += 80) {
            for (int x = -3500; x < 3500; x += 80) {
                //DrawRectangleLines(x, y, 80, 80, { 200, 200, 200, 105 });
            }
        }

        for (Player* p : players)
        {
            p->Draw();
        }

        EndMode2D(); // End the camera mode
        std::string numberStr = std::to_string(camera.zoom);
        const char* numberCStr = numberStr.c_str();

        DrawText(numberCStr, 10, 10, 20, RED);
        DrawFPS(10,30);
        

        EndDrawing();
    }
    CloseWindow();

    return 0;
}