#include <iostream>
#include <raylib.h>

using namespace std;

int cpu_score = 0;
int player_score = 0;

class Ball
{
    public:
    float x, y;
    float radius;
    float x_speed, y_speed;

    void Draw()
    {
        DrawCircle(x,y,radius,WHITE);
    }

    void Update()
    {
        x += x_speed;
        y += y_speed;


        if(x + radius >= GetScreenWidth())
        {
            cpu_score++;
            BallReset();
        }
        if(x - radius <= 0)
        {
            player_score++;
            BallReset();
        }
         if(y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            y_speed *= -1;
        }

    }

    void BallReset()
    {
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_choices[2] = {-1, 1};
        x_speed *= speed_choices[GetRandomValue(0, 1)];
        y_speed *= speed_choices[GetRandomValue(0, 1)];
    }

};

class Paddle
{
    protected:
    void Limits()
    {
        if(y<=0)
        {
             y = 0;
        }
        if(y>=GetScreenHeight()-height)
        {
            y = GetScreenHeight()-height;
        }
    }
    public:
    float x, y;
    float width, height;
    float y_speed;

    void Draw()
    {
        DrawRectangle(x,y,width,height,WHITE);
    }

    void Update()
    {
        if(IsKeyDown(KEY_DOWN))
        {
            y += y_speed;
        }
        else if(IsKeyDown(KEY_UP))
        {
            y -= y_speed;
        }

        Limits();

    }
};

class CpuControll :public Paddle
{
    public:
    void Update(float y_ball)
    {
        if(y >= y_ball)
        {
            y -= y_speed;
        }
        else if(y < y_ball)
        {
            y += y_speed;
        }

        Limits();
    }
};

Ball ball;
Paddle player;
CpuControll cpu;

int main () 
{
    const int screen_width = 1200;
    const int screen_height = 800;

    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.x_speed = 7;
    ball.y_speed = 7;
    ball.radius = 20;

    player.height = 125;
    player.width = 25;
    player.x = screen_width-player.width-10;
    player.y = screen_height/2 - player.height/2;
    player.y_speed = 6;

    cpu.height = 125;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screen_height/2 - cpu.height/2;
    cpu.y_speed = 6;


    InitWindow(screen_width,screen_height,"PONG GAME");
    SetTargetFPS(60);


    while(WindowShouldClose()==false)
    {
        BeginDrawing();


        //Updating 
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // Checking for collisions
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.x_speed *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.x_speed *= -1;
        }
        //Drawing
        ClearBackground(BLACK);
        DrawLine(screen_width/2,0,screen_width/2,screen_height,WHITE);
        ball.Draw();
        player.Draw();
        cpu.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
