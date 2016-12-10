
# coding: utf-8

# In[ ]:

from bearlibterminal import terminal as blt
import json
from collections import defaultdict
from itertools import product
from functools import reduce


# In[ ]:

def terrain_graph(raw_graph):
    return {k:frozenset(v) for (k,v) in raw_graph.items()}


# In[ ]:

def adjacency_options(adjacency, *terrains):
    return reduce(lambda x,y: x.intersection(y),
                  (adjacency[t] for t in terrains))


# In[ ]:

def generate_line(previous_line=None):
    new_line = []
    new_line.append()


# In[ ]:

def wangview(fn_tile_groups, fn_terrain_adjacency):
    with open(fn_tile_groups,'r') as f:
        tile_groups = json.load(f)
    with open(fn_terrain_adjacency,'r') as f:
        terrain_adjacency = terrain_graph(json.load(f))


# In[ ]:

wangview('../Wangscape/example/output/tile_groups.json',
         '../Wangscape/example/output/terrain_adjacency.json')


# In[ ]:

if __name__ == '__main__':
    import sys
    try:
        wangview(sys.argv[1], sys.argv[2])
    except (IndexError, FileNotFoundError):
        print('Usage: Wangview.py tile_groups.json terrain_adjacency.json')

