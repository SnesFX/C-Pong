#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define PADDLE_WIDTH 15
#define PADDLE_HEIGHT 60

#define BALL_SIZE 10

#define PADDLE_SPEED 5
#define BALL_SPEED 5

int main(int argc, char* args[]) {

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow(
        "PongClone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    // Create paddles and ball
    SDL_Rect player1 = { 20, SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT };
    SDL_Rect player2 = { SCREEN_WIDTH - 20 - PADDLE_WIDTH, SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2, PADDLE_WIDTH, PADDLE_HEIGHT };
    SDL_Rect ball = { SCREEN_WIDTH/2 - BALL_SIZE/2, SCREEN_HEIGHT/2 - BALL_SIZE/2, BALL_SIZE, BALL_SIZE };

    // Set initial ball direction
    int ball_dx = BALL_SPEED;
    int ball_dy = BALL_SPEED;

    // Game loop
    bool running = true;
    while (running) {

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Move paddles
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_W] && player1.y > 0) {
            player1.y -= PADDLE_SPEED;
        }
        if (keystate[SDL_SCANCODE_S] && player1.y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
            player1.y += PADDLE_SPEED;
        }
        if (keystate[SDL_SCANCODE_UP] && player2.y > 0) {
            player2.y -= PADDLE_SPEED;
        }
        if (keystate[SDL_SCANCODE_DOWN] && player2.y < SCREEN_HEIGHT - PADDLE_HEIGHT) {
            player2.y += PADDLE_SPEED;
        }

        // Move ball
        ball.x += ball_dx;
        ball.y += ball_dy;

        // Bounce ball off walls
        if (ball.y < 0 || ball.y > SCREEN_HEIGHT - BALL_SIZE) {
            ball_dy = -ball_dy;
        }

        // Check for collision with paddles
        if (SDL_HasIntersection(&ball, &player1) || SDL_HasIntersection(&ball, &player2)) {
            ball_dx = -ball_dx;
        }

        // Check for score
        if (ball.x < 0 || ball.x > SCREEN_WIDTH - BALL_SIZE) {
            ball.x = SCREEN_WIDTH/2 - BALL_SIZE/2;
            ball.y = SCREEN_HEIGHT/2 - BALL_SIZE/2;
            ball_dx = BALL_SPEED;
            ball_dy = BALL_SPEED;
        }

        // Clear screen and render paddles and ball
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &player1);
        SDL_RenderFillRect(renderer, &player2);
        SDL_RenderFillRect(renderer, &ball);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay to regulate frame rate
        SDL_Delay(16);
    }

        // Clean up
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;

}        