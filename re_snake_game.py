#!/usr/bin/env python3

"""
Re written snake game
"""

import random
import sys
import time
import pygame

class Snake:
    """
    The snake
    """
    head_x_pos = random.randint(10, 59) * 10
    head_y_pos = random.randint(5, 34) * 10
    move_dir = None
    length = 0
    body = []
    texture = pygame.Surface((8, 8))
    texture.fill((255, 255, 255))

class Apple:
    """
    The apple
    """
    x_pos = random.randint(10, 59) * 10
    y_pos = random.randint(5, 34) * 10
    texture = pygame.Surface((8, 8))
    texture.fill((255, 0, 0))

    while (x_pos, y_pos) == (Snake.head_x_pos, Snake.head_y_pos) or (x_pos, y_pos) in Snake.body:
        x_pos = random.randint(10, 59) * 10
        y_pos = random.randint(5, 34) * 10

def game_over(score: int):
    """
    Gonna make it display a gameover screen but it's just gonna write it on stdout for now
    """
    print("Your score is:", score)
    Snake.move_dir = None
    time.sleep(3)
    pygame.quit()
    sys.exit()

def game(screen, blak_screen, go_dir):
    """
    The game itself
    """

    clock = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_w or event.key == pygame.K_UP:
                    go_dir = "Up"
                elif event.key == pygame.K_a or event.key == pygame.K_LEFT:
                    go_dir = "Left"
                elif event.key == pygame.K_s or event.key == pygame.K_DOWN:
                    go_dir = "Down"
                elif event.key == pygame.K_d or event.key == pygame.K_RIGHT:
                    go_dir = "Right"

        if go_dir == "Up" and Snake.move_dir != "Down":
            Snake.move_dir = "Up"
        elif go_dir == "Left" and Snake.move_dir != "Right":
            Snake.move_dir = "Left"
        elif go_dir == "Down" and Snake.move_dir != "Up":
            Snake.move_dir = "Down"
        elif go_dir == "Right" and Snake.move_dir != "Left":
            Snake.move_dir = "Right"

        screen.blit(blak_screen, (0, 0))
        pygame.draw.rect(screen, (255, 255, 255), pygame.Rect(100, 50, 500, 300), 6, 0)

        if (Snake.head_x_pos, Snake.head_y_pos) == (Apple.x_pos, Apple.y_pos):
            Snake.length += 1
            Apple.x_pos = random.randint(10, 57) * 10
            Apple.y_pos = random.randint(5, 32) * 10

            while (Apple.x_pos, Apple.y_pos) in Snake.body:
                Apple.x_pos = random.randint(10, 57) * 10
                Apple.y_pos = random.randint(5, 32) * 10

        Snake.body.insert(0, (Snake.head_x_pos, Snake.head_y_pos))

        if Snake.move_dir == "Up":
            Snake.head_y_pos -= 10
        elif Snake.move_dir == "Left":
            Snake.head_x_pos -= 10
        elif Snake.move_dir == "Down":
            Snake.head_y_pos += 10
        elif Snake.move_dir == "Right":
            Snake.head_x_pos += 10

        print((Snake.head_x_pos, Snake.head_y_pos), Snake.body)
        ## Out of bounds (70, y), (600, y), (x, 40), (x, 350)
        if Snake.head_x_pos <= 90 or Snake.head_x_pos >= 600:
            game_over(Snake.length)
        elif Snake.head_y_pos <= 40 or Snake.head_y_pos >= 350:
            game_over(Snake.length)
        elif len(Snake.body) != len(set(Snake.body)):
            game_over(Snake.length)

        if len(Snake.body) > Snake.length:
            Snake.body.pop(-1)

        for Snake_coords in Snake.body:
            x, y = Snake_coords
            screen.blit(Snake.texture, (x + 1, y + 1))

        screen.blit(Snake.texture, (Snake.head_x_pos + 1, Snake.head_y_pos + 1))
        screen.blit(Apple.texture, (Apple.x_pos + 1, Apple.y_pos + 1))
        pygame.display.update()
        clock.tick(10)

def you_win():
    print("You win!")
    Snake.move_dir = None
    time.sleep(3)
    pygame.quit()
    sys.exit()

def main():
    """
    Initializing pygame and the game
    """
    pygame.init()
    pygame.display.set_caption("Snake Game by Croisen")
    screen_x, screen_y = 800, 400
    screen = pygame.display.set_mode((screen_x, screen_y))
    blak_screen = pygame.Surface((screen_x, screen_y))
    blak_screen.fill((0, 0, 0))
    game(screen = screen, blak_screen = blak_screen, go_dir = Snake.move_dir)

if __name__ == '__main__':
    main()
