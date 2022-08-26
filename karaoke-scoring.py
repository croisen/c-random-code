#!/usr/bin/env python3


import pygame
import random
import sys
import time


pygame.init()

window_x = 800
window_y = 400
window = pygame.display.set_mode((window_x, window_y))
pygame.display.set_caption("Karaoke Scoring")

karaoke_main = pygame.Surface((window_x, window_y))
karaoke_main.fill('White')


score = []

for i in range(54):
    score.append(str(random.randint(0, 99)))

score_font = pygame.font.SysFont('MesloLGS NF Bold', 200)
actual_score = score.append(str(random.randint(85, 99)))

clock = pygame.time.Clock()

def main():
    i = 0

    pygame.mixer.music.load("file-dependency/karaoke-sound.wav")
    pygame.mixer.music.set_volume(0.6)
    pygame.mixer.music.play()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        if  i == len(score):
            time.sleep(6)
            pygame.quit()
            sys.exit()

        score_render = score_font.render(score[i], True, 'Black')
        score_rect = score_render.get_rect()
        score_rect.center = ((window_x / 2), (window_y / 2))

        window.blit(karaoke_main, (0, 0))
        score_anin_num = str(random.randint(0, 100))
        window.blit(score_render, score_rect)
        pygame.display.update()

        i += 1
        clock.tick(10)

if __name__ == '__main__':
    main()