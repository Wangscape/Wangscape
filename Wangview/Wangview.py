
# coding: utf-8

# In[ ]:

from bearlibterminal import terminal as blt
import json
from collections import deque, namedtuple
from itertools import product
import random
from functools import reduce
from os import path


# In[ ]:

class Wangview(object):
    def __init__(self,
                 rel_path='.',
                 fn_tile_groups='tile_groups.json',
                 fn_terrain_hypergraph='terrain_hypergraph.json',
                 fn_tileset_data='tileset_data.json'):
        with open(path.join(rel_path, fn_tileset_data),'r') as f:
            self.init_tilesets(json.load(f))
        with open(path.join(rel_path,fn_tile_groups),'r') as f:
            self.init_tile_groups(json.load(f))
        with open(path.join(rel_path, fn_terrain_hypergraph),'r') as f:
            self.hypergraph = Hypergraph(json.load(f))
        self.width = blt.state(blt.TK_WIDTH)
        self.height = blt.state(blt.TK_HEIGHT)
        self.init_terrain_map()
        self.init_tile_map()
    def simplify_tile(self, tile):
        tileset = self.tilesets[tile['file']]
        return tileset.offset + tileset.width*tile['y'] + tile['x']
    def simplify_tile_group(self, tile_group):
        return [self.simplify_tile(tile) for tile in tile_group]
    def init_tile_groups(self, raw_groups):
        self.tile_groups = {tuple(k.split('.')):self.simplify_tile_group(v)
                            for (k,v) in raw_groups.items()}
        
    def init_tilesets(self, raw_tileset_data):
        self.resolution = raw_tileset_data.pop('resolution')
        blt.open()
        blt.set("window: size=30x20, cellsize:{0}x{0}, title='Wangview'".format(
            self.resolution))
        tileset_offset_counter = 0xE000
        self.tilesets = {}
        for filename, tileset in raw_tileset_data.items():
            rx = tileset['x']//self.resolution
            ry = tileset['y']//self.resolution
            self.tilesets[filename] = Tileset(
                filename, tileset_offset_counter,
                rx,ry, tuple(tileset['terrains']))
            blt.set("0x{0:x}: {1}, size={2}x{2}".format(
                    tileset_offset_counter,
                    filename,
                    self.resolution))
            tileset_offset_counter += rx*ry
    def init_terrain_map(self):
        terrain_iter = self.hypergraph.generate_lines(self.width, self.height)
        terrain_deque_iter = (deque(line, self.width) for line in terrain_iter)
        self.terrain_map = deque(terrain_deque_iter, self.height)
    def init_tile_map(self):
        tile_iter = ((self.select_tile(self.get_tile_corners(x,y))
                      for x in range(self.width-1))
                     for y in range(self.height-1))
        tile_deque_iter = (deque(line, self.width-1) for line in tile_iter)
        self.tile_map = deque(tile_deque_iter, self.height-1)
    def get_tile_corners(self, x, y):
        return (self.terrain_map[y][x]
                for (x,y) in
                product((x,x+1),(y,y+1)))
    def select_tile(self, corners):
        return random.choice(self.tile_groups[tuple(corners)])
    def draw(self):
        for y, line in enumerate(self.tile_map):
            for x, c in enumerate(line):
                blt.put(x,y,c)
    def run(self):
        stop = False
        while not stop:
            self.draw()
            blt.refresh()
            while blt.has_input():
                kp = blt.read()
                if kp == blt.TK_CLOSE:
                    stop = True
        blt.close()


# In[ ]:

Tileset = namedtuple('Tileset',['filename','offset','width','height','clique'])


# In[ ]:

class Hypergraph(object):
    def __init__(self, raw_hypergraph):
        self.data = {k: frozenset(map(frozenset,v))
                     for (k,v) in raw_hypergraph.items()}
    @staticmethod
    def flatten_options(options):
        return reduce(lambda x,y: x.union(y),
                      options,
                      frozenset())
    def terrain_options(self, *terrains):
        if len(terrains) == 0:
            return list(self.data.keys())
        return self.flatten_options(reduce(
                lambda options, terrain: [clique for clique in options if terrain in clique],
                terrains[1:], list(self.data[terrains[0]])))
    def terrain_options_2(self, t_left=[], t_up=[]):
        if len(t_up) == 0:
            return self.terrain_options(*t_left)
        x = self.terrain_options(*(t_left+t_up[:2]))
        if len(t_up) == 3:
            y = self.terrain_options(*t_up[1:])
            return x.intersection(y)
        return x
    def generate_line(self, width, previous_line=None):
        new_line = []
        t_left = []
        t_up = []
        for i in range(width):
            if previous_line is not None:
                t_up = previous_line[max(0,i-1):i+2]
            options = self.terrain_options_2(t_left, t_up)
            new_line.append(random.choice(list(options)))
            t_left = [new_line[-1]]
        return new_line
    def generate_lines(self, width, height):
        line = self.generate_line(width)
        yield line
        for i in range(height):
            line = self.generate_line(width, line)
            yield line


# In[ ]:

# th = Hypergraph({'a':[['a','b'],['c','a']],
#                  'b':[['a','b'],['b','c']],
#                  'c':[['b','c'],['c','a']]})
# for i in map(lambda x: print(''.join(x)), th.generate_lines(10,10)):
#     pass


# In[ ]:

def wangview(*args, **kwargs):
    w = Wangview(*args, **kwargs)
    w.run()


# In[ ]:

wangview('../Wangscape/example/output',
         'tile_groups.json',
         'terrain_hypergraph.json',
         'tilesets.json')


# In[ ]:

# if __name__ == '__main__':
#     import sys
#     try:
#         w = wangview(*sys.argv[1:])
#     except (IndexError, FileNotFoundError):
#         print('Usage: Wangview.py [path [tile_groups.json [terrain_hypergraph.json [tileset_data.json]]]]')

