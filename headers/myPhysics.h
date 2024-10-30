
typedef struct Vec2 {
        int x;
        int y;
} Vec2;

typedef struct {
        Vec2 min;
        Vec2 max;
} AABB;

typedef struct Circle {
        float radius;
        Vec2 position;
} Circle;

typedef struct Object {
        Vec2 position;
        Vec2 velocity;
        float restitution;
        float mass;
        float inv_mass;
} Object;

typedef struct {
        float width;
        float height;
        float mass;
        float moment_of_inertia;
} BoxShape;

typedef struct {
        Vec2 position;
        Vec2 linear_velocity;
        float angular_velocity;
        float angle;
        Vec2 force;
        float torque;
        BoxShape *shape;
} RigidBody;

float Distance(Vec2, Vec2);
float DotProduct(Vec2, Vec2);
void CalculateBoxInertia(BoxShape *);

Vec2 ComputeGravityForce(Object, Vec2);
Vec2 ComputeForce(Object, Vec2);
int CirclevsCircleUnoptimized(Circle, Circle);
int CirclevsCircleOptimized(Circle, Circle);
int AABBvsAABB(AABB, AABB);
void ResolveCollision(Object, Object);
