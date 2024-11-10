#include "raylib.h"

class Player
{
public:
    //Create player at position
    Player(Vector2 initialPosition);

    //Gets current position
    Vector2 GetPosition();

    //Move by dx dy
    void Move(float dx, float dy);

    //Apply acceleration in a specified direction in radians
    void ApplyAccelerationInDirection(float direction);

    //Apply acceleration opposite to velocity to slow down
    void Deaccelerate();

    //Simulate one tick
    void Update();

    //Draws the player as a triangle. Streches based on current velocity
    void Draw();

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    //How fast the player can accelerate
    float accelerationScalar = 0.8f;

    //How fast the player slows down
    const float deaccelerationMultiplier = 0.08f;

    //Max speed player can go
    const float maxSpeed = 8.0f;
};