#!/usr/bin/env python3


import pygame
import random
import sys
import time

class snake:    
    head_x_pos = random.randint(10, 60) * 10
    head_y_pos = random.randint(5, 35) * 10
    move_dir = None
    body = []
    texture = pygame.Surface((8, 8))
    texture.fill((255, 255, 255))

def main():
    pygame.init()
    pygame.display.set_caption("Snake Game by Croisen")
    clock = pygame.time.Clock()
    screen_x, screen_y = 800, 400
    screen = pygame.display.set_mode((screen_x, screen_y))
    blak_screen = pygame.Surface((screen_x, screen_y))
    blak_screen.fill((0, 0, 0))
    frames = 0

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_w or event.key == pygame.K_UP:
                        snake.move_dir = "Up"
                elif event.key == pygame.K_a or event.key == pygame.K_LEFT:
                    snake.move_dir = "Left"
                elif event.key == pygame.K_s or event.key == pygame.K_DOWN:
                    snake.move_dir = "Down"
                elif event.key == pygame.K_d or event.key == pygame.K_RIGHT:
                    snake.move_dir = "Right"

        if frames == 6:
            if snake.move_dir == "Up":
                snake.head_y_pos -= 10
            elif snake.move_dir == "Left":
                snake.head_x_pos -= 10
            elif snake.move_dir == "Down":
                snake.head_y_pos += 10
            elif snake.move_dir == "Right":
                snake.head_x_pos += 10

            frames = 0

        screen.blit(blak_screen, (0, 0))
        pygame.draw.rect(screen, (255, 255, 255), pygame.Rect(90, 40, 500, 300), 6, 0)
        screen.blit(snake.texture, (snake.head_x_pos + 1, snake.head_y_pos + 1))
        pygame.display.update()
        frames += 1
        clock.tick(60)

if __name__ == '__main__':
    main()
