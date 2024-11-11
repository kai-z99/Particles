#include "raylib.h"

class Player
{
public:
    //Create player at position
    Player(Vector2 initialPosition, float maxSpeed, float accelerationFactor, float deaccelerationMultipler, Color color = RED, float scaleFactor = 1.0f);

    //Gets current position
    Vector2 GetPosition();

    //Gets current speed
    float GetSpeed();

    //Sets sposition
    void SetPosition(Vector2 pos);

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

    void SetMaxSpeed(float speed);

private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    //How fast the player can accelerate 500
    float accelerationFactor;

    //How fast the player slows down 0.18
    float deaccelerationMultipler;

    //Max speed player can go 110
    float maxSpeed;

    
    float scaleFactor;

    Color color;

};