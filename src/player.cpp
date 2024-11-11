#include "player.h"
#include <math.h>
#include <raymath.h>

static inline float CalculateSpeed(float vx, float vy)
{
    return sqrtf(vx * vx + vy * vy);
}

Player::Player(Vector2 initalPosition, float maxSpeed, float accelerationFactor, float deaccelerationMultipler, Color color, float scaleFactor)
{
    this->position = initalPosition;
    this->velocity = {0.0f , 0.0f};
    this->acceleration = {0.0f, 0.0f};

    this->maxSpeed = maxSpeed;
    this->accelerationFactor = accelerationFactor;
    this->deaccelerationMultipler = deaccelerationMultipler;

    this->scaleFactor = scaleFactor;

    this->color = color;
}

Vector2 Player::GetPosition()
{
    return this->position;
}

float Player::GetSpeed()
{
    return CalculateSpeed(this->velocity.x, this->velocity.y);
}

void Player::SetPosition(Vector2 pos)
{
    this->position = pos;
}

void Player::Move(float dx, float dy)
{
    this->position.x += dx;
    this->position.y += dy;
}

void Player::ApplyAccelerationInDirection(float angle)
{
    this->acceleration.x = this->accelerationFactor * cosf(angle);
    this->acceleration.y = this->accelerationFactor * sinf(angle);
}

void Player::SetAcceleration(Vector2 accel)
{
    this->acceleration = accel;
}

void Player::Deaccelerate()
{
    //acclerate opposite of the velocity.
    this->acceleration.x = -this->velocity.x * this->deaccelerationMultipler;
    this->acceleration.y = -this->velocity.y * this->deaccelerationMultipler;
}

void Player::Update()
{
    this->velocity.x += this->acceleration.x;
    this->velocity.y += this->acceleration.y;

    // ratio is what percentage of the max speed player is going.
    float speed = CalculateSpeed(this->velocity.x, this->velocity.y);
    float ratio = speed /= this->maxSpeed;

    //if the player is going higher than the max speed, undo the acceleration add.
    // (maxspeed * ratio) / ratio = maxSpeed
    if (ratio > 1.0f)
    {
        this->velocity.x /= ratio;
        this->velocity.y /= ratio;     
    }

    this->position.x += this->velocity.x;
    this->position.y += this->velocity.y;
}

void Player::Draw()
{
    //triangle in the origin
    Vector2 p1 = {12.0f , 0.0f};
    Vector2 p2 = {-12.0f, -8.0f};
    Vector2 p3 = {-12.0f, 8.0f};

    //angle of velocity
    float angle = atan2f(this->velocity.y, this->velocity.x);
    if (angle < 0.0f) angle += 2.0f * PI;

    //scale original triangle
    //x scale factor is based on current speed.
    float scaleFactorX = this->scaleFactor + CalculateSpeed(this->velocity.x, this->velocity.y) / this->maxSpeed;

    p1 = Vector2Scale(p1, scaleFactorX);
    p2.x = scaleFactorX * p2.x;
    p3.x = scaleFactorX * p3.x;

    //rotate original triangle
    p1 = Vector2Rotate(p1, angle);
    p2 = Vector2Rotate(p2, angle);
    p3 = Vector2Rotate(p3, angle);
    
    //translate original triangle
    p1 = Vector2Add(p1, this->position);
    p2 = Vector2Add(p2, this->position);
    p3 = Vector2Add(p3, this->position);

    DrawTriangle(p1, p2, p3, this->color);
}

void Player::SetColor(Color color)
{
    this->color = color;
}

void Player::SetMaxSpeed(float speed)
{
    this->maxSpeed = speed;
}
