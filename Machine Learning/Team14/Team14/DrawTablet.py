# -*- coding: utf-8 -*-
import pygame

""" Parameters """
WIDTH = 1280
HEIGHT = 720
SCREEN_SIZE = (WIDTH, HEIGHT)
WINDOW_TITLE = 'Draw Tablet'

""" COLOR """
CLR_WHITE = (255, 255, 255)
CLR_BLACK = (0, 0, 0)


class DrawTablet:

    """ Variables """
    screen = None
    background = None
    event_log = []
    event_log_path = ''

    def __init__(self):
        pass

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

    def log_initialize(self, log_path):
        # Clear Log
        self.event_log = []
        self.event_log_path = log_path
        with open(self.event_log_path, 'w') as file:
            # Just Clear
            pass

    def log_dump(self):
        # Dump Log
        with open(self.event_log_path, 'a') as file:
            for event in self.event_log:
                file.write(event+'\n')

    def log_write(self, msg):
        # Write Log
        self.event_log.append(msg)

    def log_flush(self):
        # Flush Log
        if (len(self.event_log) > 0):
            self.log_dump()
            self.event_log = []

    def run(self, log_path):
        self.game_initialize()
        self.log_initialize(log_path)

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
                    self.log_write('[START]')

                elif event.type == pygame.MOUSEBUTTONUP:
                    pressing = False
                    self.log_write('[END]')

            # After Event Handle
            last_cursor_pos = cur_cursor_pos
            cur_cursor_pos = pygame.mouse.get_pos()

            if (pressing):
                # Write Log
                self.draw_pixel(cur_cursor_pos, CLR_BLACK)
                self.draw_line(last_cursor_pos, cur_cursor_pos, CLR_BLACK)
                if (cur_cursor_pos != last_cursor_pos):
                    self.log_write(cur_cursor_pos.__str__())
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
