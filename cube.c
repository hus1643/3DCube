#include <raylib.h>
#include <math.h>

#define width 1600
#define height 1400
const float cube_size = 3.0f;
const float centre_cube = cube_size / 2.0f;

Vector3 add2Vec3s(Vector3 p, Vector3 q)
{
    return (Vector3){
        p.x + q.x, p.y + q.y, p.z + q.z};
}

// centre the cube
Vector3 centre(Vector3 p)
{
    return (Vector3){
        p.x - centre_cube, p.y - centre_cube, p.z - centre_cube};
}

// rotate around the y axis
Vector3 rotate(Vector3 p, float angle)
{
    return (Vector3){
        p.x * cosf(angle) + p.z * sinf(angle),
        p.y,
        -p.x * sinf(angle) + p.z * cosf(angle)
    };
}

int main()
{
    InitWindow(width, height, "3d-Cube");
    SetTargetFPS(60);

    Camera camera = {0};
    camera.position = (Vector3){0.0f, 7.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f}; // centre of the scrreen
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};     // y axis as up
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // basic unit points
    Vector3 E1 = {cube_size * 1.0f, 0.0f, 0.0f};
    Vector3 E2 = {0.0f, cube_size * 1.0f, 0.0f};
    Vector3 E3 = {0.0f, 0.0f, cube_size * 1.0f};

    // cube points
    Vector3 A = {0.0f, 0.0f, 0.0f};
    Vector3 c0 = add2Vec3s(A, E1);
    Vector3 c1 = add2Vec3s(A, E2);
    Vector3 c2 = add2Vec3s(A, E3);
    Vector3 c3 = add2Vec3s(A, add2Vec3s(E1, E2));
    Vector3 c4 = add2Vec3s(A, add2Vec3s(E1, E3));
    Vector3 c5 = add2Vec3s(A, add2Vec3s(E2, E3));
    Vector3 c6 = add2Vec3s(A, add2Vec3s(E1, add2Vec3s(E2, E3)));
    // sphere radius
    float r = 0.1f;
    float angle = 0.0f;
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        DrawGrid(10.0f, 1.0f);

        // cube points as small spheres.
        DrawSphere(rotate(centre(A), angle), r, ORANGE);
        DrawSphere(rotate(centre(c0), angle), r, RED);
        DrawSphere(rotate(centre(c1), angle), r, GREEN);
        DrawSphere(rotate(centre(c2), angle), r, BLUE);
        DrawSphere(rotate(centre(c3), angle), r, BLACK);
        DrawSphere(rotate(centre(c4), angle), r, PINK);
        DrawSphere(rotate(centre(c5), angle), r, BROWN);
        DrawSphere(rotate(centre(c6), angle), r, PURPLE);
        angle += 0.01;
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}

