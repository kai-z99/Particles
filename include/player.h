#include "raylib.h"

class Player
{
public:
    //Create player at position
    Player(Vector2 initialPosition, Color color = RED);

    //Gets current position
    Vector2 GetPosition();

    //Gets current speed
    float GetSpeed();

    //Move by dx dy
    void Move(float dx, float dy);

    //Apply acceleration in a specified direction in radians
    void ApplyAccelerationInDirection(float direction);

    //Set the acceleration of th player
    void SetAcceleration(Vector2 accel);

    //Apply acceleration opposite to velocity to slow down
    void Deaccelerate();

    //Simulate one tick
    void Update();

    //Draws the player as a triangle. Streches based on current velocity
    void Draw();

    //Set the coloe of the player
    void SetColor(Color color);

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    //How fast the player can accelerate
    float accelerationScalar = 4.8f;

    //How fast the player slows down
    const float deaccelerationMultiplier = 0.18f;

    //Max speed player can go
    const float maxSpeed = 10.0f;

    Color color;

};