# -*- coding: utf-8 -*-
import pygame
import joblib
import math
import pandas as pd
from sklearn import ensemble

""" Parameters """
WIDTH = 1280
HEIGHT = 720
SCREEN_SIZE = (WIDTH, HEIGHT)
WINDOW_TITLE = 'Draw Tablet'

""" COLOR """
CLR_WHITE = (255, 255, 255)
CLR_BLACK = (0, 0, 0)

alphabet = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
            'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']


class DrawTablet_WithDetection:

    """ Variables """
    screen = None
    background = None
    event_log = []
    event_log_path = ''
    strobe_log = []
    classifier = None

    def __init__(self, model_path):
        self.classifier = joblib.load(model_path)

    def game_initialize(self):
        # Create Screen
        pygame.init()
        self.screen = pygame.display.set_mode(SCREEN_SIZE)
        pygame.display.set_caption(WINDOW_TITLE)

        # Create Background
        self.background = pygame.Surface(self.screen.get_size())
        self.background = self.background.convert()
        self.background.fill(CLR_WHITE)

        # Display Background on Screen
        self.screen.blit(self.background, (0, 0))

        # Display Update
        pygame.display.update()

    def log_initialize(self):
        # Clear Log
        self.event_log = []

    def log_write(self, msg):
        # Write Log
        self.event_log.append(msg)

    def log_flush(self):
        # Flush Log
        if (len(self.event_log) > 0):
            self.strobe_log.append(self.event_log)
            self.event_log = []

    def detection(self):
        if (len(self.strobe_log) == 0):
            return -1

        big_pack = []
        for strobe in self.strobe_log:
            # Clear Pack
            pack = []

            # 0
            # Add slope (Radius)
            dx = strobe[-1][0] - strobe[0][0]
            dy = strobe[-1][1] - strobe[0][1]
            # Get Radius # Don't use dy/dx, the accuracy will be very bad
            pack.append(math.atan2(dy, dx))

            # 1
            # Add vector's length (shift length)
            pack.append(math.sqrt(dx**2+dy**2))

            # 2
            # Add strobe's length (path length)
            length = 0
            last_point = -1
            for point in strobe:
                if (last_point == -1):
                    last_point = point
                else:
                    length += math.sqrt((point[0] - last_point[0])
                                        ** 2 + (point[1] - last_point[1])**2)
                    last_point = point
            pack.append(length)

            # 3
            # Add ratio between these two length
            pack.append(length/math.sqrt(dx**2+dy**2))

            # 4
            # Add offset from first strobe's start
            f_s_start = self.strobe_log[0][0]
            c_s_start = strobe[0]
            offset = math.sqrt(
                (f_s_start[0] - c_s_start[0])**2 + (f_s_start[1] - c_s_start[1])**2)
            pack.append(offset)

            # Add Total dy and dx compare to start of this strobe (for C, S, U ...)
            # c_s_start = strobe[0]
            # total_dy = 0
            # total_dx = 0
            # for point in strobe:
            #     total_dx += abs(point[0] - c_s_start[0])
            #     total_dy += abs(point[1] - c_s_start[1])
            # pack.append(total_dx)
            # pack.append(total_dy)

            # Add number of sign change of x and y
            c_sign_x = False  # Init is negative
            c_sign_y = False  # Init is negative
            nx = 0
            ny = 0
            last_point = -1
            for point in strobe:
                if last_point == -1:
                    last_point = point
                else:
                    sign_x = (point[0] - last_point[0] > 0)
                    sign_y = (point[1] - last_point[1] > 0)
                    if (c_sign_x != sign_x):
                        c_sign_x = sign_x
                        nx += 1
                    if (c_sign_y != sign_y):
                        c_sign_y = sign_y
                        ny += 1
                    last_point = point
            pack.append(nx)
            pack.append(ny)

            # Append big_pack
            big_pack.append(pack)

        # Normalizatoin
        # offset = big_pack[0][0]
        length_adj = 1/big_pack[0][1]
        for pack in big_pack:
            # pack[0] -= offset
            pack[0] *= abs(pack[0])  # radius
            pack[1] *= length_adj   # shift length
            pack[2] *= length_adj   # path length
            # pack[3] *= length_adj # ratio
            pack[4] *= length_adj   # offset from strobe's length

        data = []
        for pack in big_pack:
            data.extend(pack)

        if (len(big_pack) < 4):
            for _ in range(4-len(big_pack)):
                data.extend([0, 0, 0, 0, 0,0,0])

        data = pd.DataFrame([data])

        self.strobe_log = []
        self.event_log = []

        return self.classifier.predict(data)

    def run(self):
        self.game_initialize()
        self.log_initialize()

        running = True
        pressing = False
        last_cursor_pos = (0, 0)
        cur_cursor_pos = (0, 0)
        while running:
            # Input Event
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                elif event.type == pygame.MOUSEBUTTONDOWN:
                    pressing = True

                elif event.type == pygame.MOUSEBUTTONUP:
                    pressing = False

            keys = pygame.key.get_pressed()
            if keys[pygame.K_d]:
                if (pressing == False):
                    ret = self.detection()
                    if (ret != -1):
                        print('Predict: '+alphabet[ret[0]])

            elif keys[pygame.K_c]:
                self.background.fill(CLR_WHITE)
                self.strobe_log = []
                self.event_log = []

            # After Event Handle
            last_cursor_pos = cur_cursor_pos
            cur_cursor_pos = pygame.mouse.get_pos()

            if (pressing):
                # Write Log
                self.draw_pixel(cur_cursor_pos, CLR_BLACK)
                self.draw_line(last_cursor_pos, cur_cursor_pos, CLR_BLACK)
                if (cur_cursor_pos != last_cursor_pos):
                    self.log_write(cur_cursor_pos)
            else:
                # Flush Log
                self.log_flush()

                # Display Update
            self.screen.blit(self.background, (0, 0))
            pygame.display.update()

        # Quit
        pygame.quit()

    def draw_pixel(self, pos, color) -> None:
        # Draw Pixel
        rect_attr = [pos[0], pos[1], 1, 1]
        pygame.draw.rect(self.background, color, rect_attr, 0)

    def draw_line(self, start, end, color) -> None:
        # Draw Line
        pygame.draw.line(self.background, color, start, end, 1)


if __name__ == "__main__":
    dt = DrawTablet_WithDetection('strobe_classification.model')
    dt.run()
