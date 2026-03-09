
#include <cstddef>
constexpr double ball_restitution{0.7};
constexpr int speed{300};
constexpr float bspeed{200.0};
#include <raylib.h>



struct window_data
{

    size_t width{800};
    size_t height{600};

    const char* title{" My window"};

};



struct realphysics
{

    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;

    float mass;
};


struct ball:public realphysics
{
    
    float radius=20.f;
    
    float friction =0.9999;

    Color col=BLACK;

    ball(Vector2 position)
    {
    
        this->position=position;
    
        velocity={0,0};
    
        acceleration={0,0};
    
        mass=1.0;

    }


    void update_ball(float time)
    {

        velocity.y+=acceleration.y*time;
        position.y+=velocity.y*time;
        velocity.y*=friction;
        velocity.x+=acceleration.x*time;
        position.x+=velocity.x*time;
        velocity.x*=friction;

        DrawCircle(position.x,position.y,radius,col);
    }

};


struct player:public realphysics
{

    Vector2 shape{20,100};

    float friction=0.91;

    Color col=BLACK;

    player(Vector2 position)
    {
    
        this->position=position;
    
        velocity={0.0,0.0};
    
        acceleration={0,0};

    }


    void update_player(float time)
    {

        velocity.y+=acceleration.y*time;

        position.y+=velocity.y*time;


        velocity.y*=friction;


        DrawRectangle(position.x,position.y,shape.x,shape.y,col);

    }

};

int main()
{
    window_data window1;

    player p1{{0,window1.height/2.f}},p2{{(window1.width/1.f)-20.f,(window1.height/2.f)}};

    ball b1{{window1.width/2.f,window1.height/2.f}};



    InitWindow(window1.width,window1.height,window1.title);

    SetTargetFPS(60);
    
    int random_chances_of_ball_movement = GetRandomValue(-4,4);
    
switch (random_chances_of_ball_movement) {
    case -4:
    b1.velocity={bspeed,0};
    break;
    case -3:
    b1.velocity={-bspeed,0};
    break;
    case -2:
    b1.velocity={bspeed,bspeed};
    break;
    case -1:
    b1.velocity={bspeed,-bspeed};
    break;
    case 0:
        b1.velocity={0,bspeed};
    break;
    case 1:
        b1.velocity={0,-bspeed};
    break;
    case 2:
    b1.velocity={-bspeed,-bspeed};
    break;
    case 3:
    b1.velocity={-bspeed,-bspeed};
    break;
    case 4:
    b1.velocity={bspeed,bspeed};
    break;
    default:
    break;
    }


    float time{};

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(WHITE);
        
        time = GetFrameTime();
        
        
        p1.acceleration={0,0};
        
        p2.acceleration={0,0};

        
        if (IsKeyDown(KEY_W)) {
            
            p1.acceleration.y=-speed;
            
        }
        
        if (IsKeyDown(KEY_S)) {
            
            p1.acceleration.y=+speed;
            
        }
        
        if (IsKeyDown(KEY_UP)) {
            
            p2.acceleration.y=-speed;
            
        }
        
        if (IsKeyDown(KEY_DOWN)) {
            
            p2.acceleration.y=+speed;
            
        }
        
        p1.update_player(time);p2.update_player(time);
    
    
    if (b1.position.x-b1.radius<0) {
        b1.position.x=0+b1.radius;
        b1.velocity.x*=-ball_restitution;
    } 
    
    if (b1.position.x+b1.radius>window1.width) {
        b1.position.x=window1.width-b1.radius;
        b1.velocity.x*=-ball_restitution;
    } 

    if (b1.position.y-b1.radius<0) {
        b1.position.y=0+b1.radius;
        b1.velocity.y*=-ball_restitution;
    } 

    if (b1.position.y+b1.radius>window1.height) {
        b1.position.y=window1.height-b1.radius;
        b1.velocity.y*=-ball_restitution;
    } 
    b1.update_ball(time);
        
        EndDrawing();

    }
    
    CloseWindow();
    
    
    return 0;
    
}