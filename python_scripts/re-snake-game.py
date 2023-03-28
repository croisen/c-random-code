#!/usr/bin/env python3


import pygame, random, sys, time

screen_range: tuple = (800, 400)
game_screen: tuple = ((screen_range[0] * 6) // 8, (screen_range[1] * 7) // 8)
distance_from_border: tuple = ((screen_range[0] * 2) // 36, screen_range[1] // 16)

class Snake:
    def __init__(self):
        self.lim_x, self.lim_y = game_screen
        self.current_dir: str = "NONE"
        self.head_x_pos: int = random.randint(0, self.lim_x + distance_from_border[0]) // 10
        self.head_y_pos: int = random.randint(0, self.lim_y + distance_from_border[1]) // 10
        self.image = pygame.Surface((8, 8))
        self.image.fill('White')
        self.length: int = 0
        self.speed: int = 10
        self.tail: list(tuple, ...) = []

    def check_and_set_dir(self, new_dir: str):
        if self.current_dir == "UP" and new_dir == "DOWN":
            pass
        elif self.current_dir == "LEFT" and new_dir == "RIGHT":
            pass
        elif self.current_dir == "DOWN" and new_dir == "UP":
            pass
        elif self.current_dir == "RIGHT" and new_dir == "LEFT":
            pass
        else:
            self.current_dir = new_dir

    def grow_tail(self):
        self.tail.append((self.head_x_pos, self.head_y_pos))

    def cut_tail(self):
        if len(self.tail) > self.length:
            self.tail.pop()

class Apple:
    def __init__(self):
        self.x_pos: int = random.randint(distance_from_border[0],
                                         game_screen[0] + distance_from_border[0]) // 10
        self.y_pos: int = random.randint(distance_from_border[1],
                                         game_screen[1] + distance_from_border[1]) // 10
        self.image = pygame.Surface((8, 8))
        self.image.fill('Red')

def game():
    snake = Snake()
    apple = Apple()

    pygame.init()
    window = pygame.display.set_mode(screen_range)
    window.fill('Black')
    pygame.display.set_caption("Snake - Croisen", "Snek")
    black_screen = pygame.Surface(screen_range)
    game_rect = pygame.Rect(distance_from_border[0] - 4, distance_from_border[1] - 4, game_screen[0] + 8, game_screen[1] + 8)
    pygame.draw.rect(black_screen, "White", game_rect, 4)

    clock = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_w or event.key == pygame.K_UP:
                    snake.check_and_set_dir("UP")
                if event.key == pygame.K_a or event.key == pygame.K_LEFT:
                    snake.check_and_set_dir("LEFT")
                if event.key == pygame.K_s or event.key == pygame.K_DOWN:
                    snake.check_and_set_dir("DOWN")
                if event.key == pygame.K_d or event.key == pygame.K_RIGHT:
                    snake.check_and_set_dir("RIGHT")
        if snake.current_dir == "UP":
            snake.head_y_pos -= 10
        elif snake.current_dir == "LEFT":
            snake.head_x_pos -= 10
        elif snake.current_dir == "DOWN":
            snake.head_y_pos += 10
        elif snake.current_dir == "RIGHT":
            snake.head_x_pos += 10

        window.blit(black_screen, (0, 0))
        window.blit(snake.image, (snake.head_x_pos, snake.head_y_pos))
        pygame.display.update()
        clock.tick(snake.speed)

if __name__ == '__main__':
    game()
