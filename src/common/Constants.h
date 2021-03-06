
#ifndef MICROMACHINES_CONSTANTS_H
#define MICROMACHINES_CONSTANTS_H

// Client constants
#define GAME_NAME "Micromachines"
#define MtoP 3     // Relación metros a píxeles
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

//Sv constants
#define CONFIG_PATH "../config.cfg"
#define BACKLOG 15
#define MAX_PROJECTILES_NUMBER 3
#define MAX_ENTITIES_NUMBER 10
#define TIME_ELAPSE_PLUGINS 40
#define TIME_ELAPSE_GRANDSTANDS 5

//Serializing sv-client rescailing
#define SERIALIZING_RESCAILING 1000


//Protocol sv-client messages
#define CREATE_MATCH "create"
#define VALID 0
#define MATCH_HAS_STARTED 1
#define MATCH_EQUAL_NAMED 2
#define CLIENT_EQUAL_NAMED 3
#define READY 'R'
#define SET 'S'
#define GO 'G'


//Movement ID's
#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'

//Bodies sizes
#define CAR_H 15.f
#define CAR_W 6.f
#define STONE_RADIUS 5.f
#define OIL_RADIUS 9.f
#define BOOSTERS_RADIUS 8.f
#define EDGE_THICKNESS 0.5f
#define TILE_WIDTH 70
#define TILE_HEIGHT 70
#define GRANDSTAND_WIDTH 100
#define GRANDSTAND_HEIGHT 100
#define MUD_WIDTH 13
#define MUD_HEIGHT 13
#define PROJECTILE_RADIUS 2

//Car constants
#define MAX_DISTANCE_TO_TRACK 100


//Config Keys
#define MAX_FORWARD_SPEED_KEY "maxForwardSpeed"
#define MAX_BACKWARD_SPEED_KEY "maxBackwardSpeed"
#define FRONT_MAX_DRIVE_FORCE_KEY "frontTireMaxDriveForce"
#define BACK_MAX_DRIVE_FORCE_KEY "backTireMaxDriveForce"
#define FRONT_MAX_LAT_IMPULSE_KEY "frontTireMaxLateralImpulse"
#define BACK_MAX_LAT_IMPULSE_KEY "backTireMaxLateralImpulse"
#define FPS_KEY "framesPerSecond"
#define HEALTH_BOOST_KEY "healthBoost"
#define OIL_GRIP_DECREMENT_KEY "oilGripDecrement"
#define TRACK_FRICTION_KEY "trackFriction"
#define GRASS_FRICTION_KEY "grassFriction"
#define CAR_COLLISION_DAMAGE_KEY "carCollisionDamage"
#define SPEED_BOOST_KEY "speedBoost"
#define STONE_DAMAGE_KEY "stoneDamage"
#define STONE_SPEED_DECREMENT_KEY "stoneSpeedDecrement"
#define GRANDSTAND_OBJECTS_THROWN "grandStandObjectsThrown"

#endif //MICROMACHINES_CONSTANTS_H
