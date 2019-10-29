//
// Created by leobellaera on 18/10/19.
//

#include "Tire.h"

#define FORWARD 'F'
#define BACKWARD 'B'

#define FORWARD_SPEED "maxForwardSpeed"
#define BACKWARD_SPEED "maxBackwardSpeed"
#define DRIVE_FORCE "maxDriveForce"
#define LATERAL_IMPULSE "maxLateralImpulse"
#define TIRES_FRICTION "tiresFriction"

Tire::Tire(b2Body* body, std::map<std::string, float>& config) :
    maxForwardSpeed(config.find(FORWARD_SPEED)->second),
    maxBackwardSpeed(config.find(BACKWARD_SPEED)->second),
    maxDriveForce(config.find(DRIVE_FORCE)->second),
    maxLateralImpulse(config.find(LATERAL_IMPULSE)->second),
    frictionFactor(config.find(TIRES_FRICTION)->second),
    body(body) {}

b2Vec2 Tire::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(1,0) );
    return b2Dot(currentRightNormal, body->GetLinearVelocity()) * currentRightNormal;
}

b2Vec2 Tire::getForwardVelocity() {
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot(currentForwardNormal, body->GetLinearVelocity()) * currentForwardNormal;
}

void Tire::updateFriction() {
    //lateral linear velocity
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    if (impulse.Length() > maxLateralImpulse)
        impulse *= maxLateralImpulse / impulse.Length();
    body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

    //angular velocity
    body->ApplyAngularImpulse(0.1f * body->GetInertia() * -body->GetAngularVelocity(), true);

    //forward linear velocity
    b2Vec2 currentForwardNormal = getForwardVelocity();
    float currentForwardSpeed = currentForwardNormal.Normalize();
    float dragForceMagnitude = -frictionFactor * currentForwardSpeed;
    body->ApplyForce(dragForceMagnitude * currentForwardNormal, body->GetWorldCenter(), true);
}

void Tire::setFriction(float newFriction) {
    frictionFactor = newFriction;
}

void Tire::setMaxForwardSpeed(float newForwardSpeed) {
    maxForwardSpeed = newForwardSpeed;
}

void Tire::updateDrive(char controlState) {
    float desiredSpeed = 0;
    switch (controlState) {
        case FORWARD: desiredSpeed = maxForwardSpeed;  break;
        case BACKWARD: desiredSpeed = maxBackwardSpeed; break;
        default: return;
    }

    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot(getForwardVelocity(), currentForwardNormal);

    float force = 0;
    if (desiredSpeed > currentSpeed) {
        force = maxDriveForce;
    } else if (desiredSpeed < currentSpeed) {
        force = -maxDriveForce;
    } else {
        return;
    }
    body->ApplyForce(force * currentForwardNormal, body->GetWorldCenter(), true);
}

Tire::~Tire() {}