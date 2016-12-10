# /usr/bin/python
'''
Based on
Representing a chess set in Python
Part 2
Brendan Scott

'''

import Tkinter as tk
from Tkinter import PhotoImage
import os.path
import os
import random
import time

# column_reference = "1 2 3 4 5 6 7 8".split(" ")
column_reference = "a b c d e f g h".split(" ")
EMPTY_SQUARE = " "

TILE_WIDTH = 60

BOARD_WIDTH = 8 * TILE_WIDTH
BOARD_HEIGHT = BOARD_WIDTH
DATA_DIR = "chess_data"
TILES = {"black_tile": "black_tile.gif",
         "greenish_tile": "greenish_tile.gif",
         "n":"chess_n45.gif",
         "N":"chess_n451.gif",
         "redish_tile": "redish_tile.gif",
         "white_tile": "white_tile.gif"
         }


class Model(object):
    def __init__(self):
        '''create a chess board with pieces positioned for a new game
        row ordering is reversed from normal chess representations
        but corresponds to a top left screen coordinate
        '''

        self.board = []
        knight_base = "N " * 8
        white_knights = knight_base.strip()
        black_knights = white_knights.lower()
        self.board.append([EMPTY_SQUARE] * 8)
        self.board.append(black_knights.split(" "))
        for i in range(4):
            self.board.append([EMPTY_SQUARE] * 8)
        self.board.append(white_knights.split(" "))
        self.board.append([EMPTY_SQUARE] * 8)

    def color(self, i, j):
        ''' checks the color of the piece located at the i, j coordinates
        '''
        color = -1  # 0 - white, 1 - black
        if self.board[i][j] == 'k':
            color = 1
        elif self.board[i][j] == 'K':
            color = 0

        return color

    def move(self, start, destination):
        ''' move a piece located at the start location to destination
        (each an instance of BoardLocation)
        Does not check whether the move is valid for the piece
        '''

        # check piece color
        color = self.color(start.i, start.j)

        print "Piece color: ", 'black' if color == 1 else ('white' if color == 0 else 'position empty')
        print "start.j, %d, destination.j %d" % (start.j, destination.j)
        print "start.i, %d, destination.i %d" % (start.i, destination.i)
        print "---"
        print self.board
        print "---"

        # ### error checking ### #
        # check coordinates are valid
        for c in [start, destination]:
            if c.i > 7 or c.j > 7 or c.i < 0 or c.j < 0:
                print 'err - coordinates are not valid (outside of board size)\n---'
                return 0

        # don't move to same location
        if start.i == destination.i and start.j == destination.j:
            print 'err - move to same location\n---'
            return 0

        # nothing to move
        if self.board[start.i][start.j] == EMPTY_SQUARE:
            print 'err - nothing to move\n---'
            return 0

        # if at initial location
        if color==1 and start.i==1 or color==0 and start.i==6:
            # don't move more than two steps
            if abs(destination.i - start.i) > 2 or abs(destination.j - start.j) > 1:
                print 'err - more than two steps at init location\n---'
                return 0
            # can't jump over NON EMPTY blocks
            if abs(destination.i - start.i) == 2 and\
                (color==0 and self.board[destination.i+1][destination.j] != EMPTY_SQUARE\
                    or color==1 and self.board[destination.i-1][destination.j] != EMPTY_SQUARE):
                print 'err - something in the way!!'
                return 0
        # don't move more than one step
        elif abs(destination.i - start.i) > 1 or abs(destination.j - start.j) > 1:
            print 'err - more than one step\n---'
            return 0


        # capture move
        capture_color = self.color(destination.i, destination.j)
        print 'capture color: ', capture_color
        print '---'

        f = self.board[start.i][start.j]
        self.board[destination.i][destination.j] = f
        self.board[start.i][start.j] = EMPTY_SQUARE

        print '---\n'
        return 1 #we moved a white. got no return 0 so far.. all OK


class BoardLocation(object):
    def __init__(self, i, j):
        self.i = i
        self.j = j


class View(tk.Frame):
    def __init__(self, parent=None):
        tk.Frame.__init__(self, parent)

        self.var = tk.StringVar()
        win_label = tk.Label(self, textvariable = self.var)
        win_label.pack(pady=5, padx=5, side = tk.BOTTOM)

        self.var.set("Game in progress")

        self.canvas = tk.Canvas(self, width=BOARD_WIDTH, height=BOARD_HEIGHT)
        self.canvas.pack()
        self.images = {}
        for image_file_name in TILES:
            f = os.path.join(DATA_DIR, TILES[image_file_name])
            if not os.path.exists(f):
                print("Error: Cannot find image file: %s at %s - aborting" % (TILES[image_file_name], f))
                exit(-1)
            self.images[image_file_name] = PhotoImage(file=f)
            '''This opens each of the image files, converts the data into a form that Tkinter
            can use, then stores that converted form in the attribute self.images
            self.images is a dictionary, keyed by the letters we used in our model to
            represent the pieces - ie PRNBKQ for white and prnbkq for black
            eg self.images['N'] is a PhotoImage of a white knight
            this means we can directly translate a board entry from the model into a picture
            '''
        self.pack()

    def clear_canvas(self):
        ''' delete everything from the canvas'''
        items = self.canvas.find_all()
        for i in items:
            self.canvas.delete(i)

    def draw_row(self, y, first_tile_white=True, debug_board=False):
        ''' draw a single row of alternating black and white tiles,
        the colour of the first tile is determined by first_tile_white
        if debug_board is set  show the coordinates of each of the tile corners
        '''

        if first_tile_white:
            remainder = 1
        else:
            remainder = 0
        for i in range(8):
            x = i * TILE_WIDTH
            if i % 2 == remainder:
                # i %2 is the remainder after dividing i by 2
                # so i%2 will always be either 0 (no remainder- even numbers) or
                # 1 (remainder 1 - odd numbers)
                # this tests whether the number i is even or odd
                tile = self.images['black_tile']
            else:
                tile = self.images['white_tile']
            self.canvas.create_image(x, y, anchor=tk.NW, image=tile)
            # NW is a constant in the Tkinter module.  It stands for "north west"
            # that is, the top left corner of the picture is to be located at x,y
            # if we used another anchor, the grid would not line up properly with
            # the canvas size
            if debug_board:  # implicitly this means if debug_board == True.
                ''' If we are drawing a debug board, draw an arrow showing top left
                and its coordinates. '''
                text_pos = (x + TILE_WIDTH / 2, y + TILE_WIDTH / 2)
                line_end = (x + TILE_WIDTH / 4, y + TILE_WIDTH / 4)
                self.canvas.create_line((x, y), line_end, arrow=tk.FIRST)
                text_content = "(%s,%s)" % (x, y)
                self.canvas.create_text(text_pos, text=text_content)

    def draw_empty_board(self, debug_board=False):
        ''' draw an empty board on the canvas
        if debug_board is set  show the coordinates of each of the tile corners'''
        y = 0
        for i in range(8):  # draw 8 rows
            y = i * TILE_WIDTH
            # each time, advance the y value at which the row is drawn
            # by the length of the tile
            first_tile_white = not (i % 2)
            self.draw_row(y, first_tile_white, debug_board)

    def draw_pieces(self, board):
        for i, row in enumerate(board):
            # using enumerate we get an integer index
            # for each row which we can use to calculate y
            # because rows run down the screen, they correspond to the y axis
            # and the columns correspond to the x axis
            for j, piece in enumerate(row):
                if piece == EMPTY_SQUARE:
                    continue  # skip empty tiles
                tile = self.images[piece]
                x = j * TILE_WIDTH
                y = i * TILE_WIDTH
                self.canvas.create_image(x, y, anchor=tk.NW, image=tile)

    def display(self, board, debug_board=False):
        ''' draw an empty board then draw each of the
        pieces in the board over the top'''

        self.clear_canvas()
        self.draw_empty_board(debug_board=debug_board)
        if not debug_board:
            self.draw_pieces(board)

            # first draw the empty board
            # then draw the pieces
            # if the order was reversed, the board would be drawn over the pieces
            # so we couldn't see them

    def display_debug_board(self):
        self.clear_canvas()
        self.draw_empty_board()


class Controller(object):
    win = -1

    def __init__(self, parent=None, model=None):
        if model is None:
            self.m = Model()
        else:
            self.m = model
        self.v = View(parent)
        ''' we have created both a model and a view within the controller
        the controller doesn't inherit from either model or view
        '''
        self.v.canvas.bind("<Button-1>", self.handle_click)
        # this binds the handle_click method to the view's canvas for left button down

        self.clickList = []
        # I have kept clickList here, and not in the model, because it is a record of what is happening
        # in the view (ie click events) rather than something that the model deals with (eg moves).

    def run(self, debug_mode=False):
        self.update_display(debug_board=debug_mode)
        tk.mainloop()

    def handle_click(self, event):
        ''' Handle a click received.  The x,y location of the click on the canvas is at
        (event.x, event.y)
        First, we need to translate the event coordinates (ie the x,y of where the click occurred)
        into a position on the chess board
        add this to a list of clicked positions
        every first click is treated as a "from" and every second click as a"to"
        so, whenever there are an even number of clicks, use the most recent to two to perform a move
        then update the display
        '''
        if self.win!=-1:
            return
        j = event.x / TILE_WIDTH
        #  the / operator is called integer division
        # it returns the number of times TILE_WIDTH goes into event.x ignoring any remainder
        # eg: 2/2 = 1, 3/2 = 1, 11/5 = 2 and so on
        # so, it should return a number between 0 (if x < TILE_WIDTH) though to 7
        i = event.y / TILE_WIDTH

        self.clickList.append(BoardLocation(i, j))
        # just maintain a list of all of the moves
        # this list shouldn't be used to replay a series of moves because that is something
        # which should be stored in the model - but it wouldn't be much trouble to
        # keep a record of moves in the model.
        if len(self.clickList) % 2 == 0:
            # move complete, execute the move
            if self.m.move(self.clickList[-2], self.clickList[-1]) == 1: 
                print 'move OK'
                #time.sleep(1)
                #print BoardLocation(Xs,Ys).i, BoardLocation(Xd,Yd).i
            self.update_display()

    def update_display(self, debug_board=False):
        self.v.display(self.m.board, debug_board=debug_board)

    def parse_move(self, move):
        ''' Very basic move parsing
        given a move in the form ab-cd where a and c are in [a,b,c,d,e,f,g,h]
        and b and d are numbers from 1 to 8 convert into BoardLocation instances
        for start (ab) and destination (cd)
        Does not deal with castling (ie 0-0 or 0-0-0) or bare pawn moves (e4)
        or capture d4xe5 etc
        No error checking! very fragile
        '''

        s, d = move.split("-")

        i = 8 - int(s[-1])  # board is "upside down" with reference to the representation
        j = column_reference.index(s[0])
        start = BoardLocation(i, j)

        i = 8 - int(d[-1])
        j = column_reference.index(d[0])
        destination = BoardLocation(i, j)

        return start, destination


if __name__ == "__main__":

    parent = tk.Tk()
    parent.wm_title("Knight's tour - recursive example")
    c = Controller(parent)
    c.run(debug_mode=False)