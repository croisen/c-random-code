#!/usr/bin/env python3


import pygame
import random
import sys
import time

def main():
    pygame.init()

    window_x = 800
    window_y = 400
    window = pygame.display.set_mode((window_x, window_y))
    pygame.display.set_caption("Snake - Croisen")
    clock = pygame.time.Clock()

    game_window = pygame.Surface((window_x, window_y))
    game_boarder = pygame.Surface((506, 306))
    game_boarder.fill('White')
    game_screen = pygame.Surface((500, 300))

    snake_image = pygame.Surface((8, 8))
    snake_image.fill('White')
    apple_image = pygame.Surface((8, 8))
    apple_image.fill('Red')
    snake_lenght = 1
    snake_head_log = []

    current_direction = 0
    score = str(snake_lenght - 1).rjust(4, '0')
    score_font = pygame.font.SysFont('MesloLGS NF Bold', 80)
    final_score_font = pygame.font.SysFont('MesloLGS NF Bold', 55)
    score_display = score_font.render(score, False, 'White')

    snake_head_x_pos = 190
    snake_head_y_pos = 200
    frame = 0
    snake_speed = 15
    apple_x_pos = round(random.randint(110, 490), -1)
    apple_y_pos = round(random.randint(60, 290), -1)


    def game_over_screen():
        current_direction = 0
        final_score = str(snake_lenght - 1)
        game_over_sad = score_font.render("Game Over!", True, 'Red')
        final_score_display = final_score_font.render("Your final score is: " + final_score, True, 'White')
        width = game_over_sad.get_width()
        height = game_over_sad.get_height()
        window.blit(game_over_sad, ((window_x - width) // 2, ((window_y - height) // 2) - 10))
        window.blit(final_score_display, ((window_x - final_score_display.get_width()) // 2, ((window_y - height) // 2) + 30))
        pygame.display.update()
        time.sleep(2)
        pygame.quit()
        sys.exit()

    def you_win_screen():
        current_direction = 0
        you_win = score_font.render("Game Over!", True, 'Green')
        width = you_win.get_width()
        height = you_win.get_height()
        window.blit(game_over_sad, ((window_x - width) // 2, (window_y - height) // 2))
        pygame.display.update()
        time.sleep(10)
        pygame.quit()
        sys.exit()

    while True:
        for event in pygame.event.get():
            ## I wanna QUIT ##
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            ## Movement Keys ##
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_w or event.key == pygame.K_UP:
                    if current_direction == 3 and snake_lenght != 1:
                        continue
                    current_direction = 1

                if event.key == pygame.K_a or event.key == pygame.K_LEFT:
                    if current_direction == 4 and snake_lenght != 1:
                        continue
                    current_direction = 2

                if event.key == pygame.K_s or event.key == pygame.K_DOWN:
                    if current_direction == 1 and snake_lenght != 1:
                        continue
                    current_direction = 3

                if event.key == pygame.K_d or event.key == pygame.K_RIGHT:
                    if current_direction == 2 and snake_lenght != 1:
                        continue
                    current_direction = 4

        window.blit(game_window, (0, 0))
        window.blit(game_boarder,(97, 47))
        window.blit(game_screen,(100, 50))
        window.blit(score_display, (640, 150))

        if frame == snake_speed:
            ## Head movement logging ##
            snake_head_log.insert(0, (snake_head_x_pos + 1, snake_head_y_pos + 1))
            if len(snake_head_log) == snake_lenght + 1:
                snake_head_log.pop()

            ## Snake Movement ##
            if current_direction == 1:
                snake_head_y_pos -= 10

            if current_direction == 2:
                snake_head_x_pos -= 10

            if current_direction == 3:
                snake_head_y_pos += 10

            if current_direction == 4:
                snake_head_x_pos += 10

            frame = 0

        ## Scoring system && Apple respawning##
        if snake_head_x_pos == apple_x_pos and snake_head_y_pos == apple_y_pos:
            snake_lenght += 1
            score = str(snake_lenght - 1).rjust(4, '0')
            score_display = score_font.render(score, True, 'White')
            apple_x_pos = round(random.randint(110, 490), -1)
            apple_y_pos = round(random.randint(60, 290), -1)

            while (apple_x_pos, apple_y_pos) in snake_head_log:
                apple_x_pos = round(random.randint(110, 490), -1)
                apple_y_pos = round(random.randint(60, 290), -1)

        ## Placing the new pos of the snake n apple ##
        window.blit(snake_image, (snake_head_x_pos + 1, snake_head_y_pos + 1))
        window.blit(apple_image, (apple_x_pos + 1, apple_y_pos + 1))

        ## Tail Generation and a way to follow it's head ##
        for i in range(snake_lenght - 1):
            window.blit(snake_image, snake_head_log[i])

        ## Display the win screen when you achieve the max score ##
        if score == 1449:
            you_win_screen()

        ## Out of Bounds and collision to tail detection ##
        if snake_head_x_pos < 100 or snake_head_x_pos > 600 or snake_head_y_pos < 50 or snake_head_y_pos > 340:
            game_over_screen()

        if len(set(snake_head_log)) < len(snake_head_log):
            game_over_screen()

        ## Display Update ##
        pygame.display.update()
        frame += 1
        clock.tick(120)


if __name__ == '__main__':
    main()
