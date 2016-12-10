
# coding: utf-8

# In[ ]:

from bearlibterminal import terminal as blt
import json
from collections import defaultdict
from itertools import product
from functools import reduce


# In[ ]:

def terrain_graph(tileset_data):
    tg = defaultdict(lambda:set())
    for ts in tileset_data.values():
        for t1,t2 in product(ts['terrains'],ts['terrains']):
            tg[t1].add(t1)
            tg[t1].add(t2)
            tg[t2].add(t1)
            tg[t2].add(t2)
    return {k:frozenset(v) for (k,v) in tg.items()}


# In[ ]:

def adjacency_options(adjacency, *terrains):
    return reduce(lambda x,y: x.intersection(y),
                  (adjacency[t] for t in terrains))


# In[ ]:

def generate_line(previous_line):
    new_line = []
    new_line.append()


# In[ ]:

tg = terrain_graph(json.load(open('../Wangscape/example/output/tilesets.json')))


# In[ ]:

adjacency_options(tg,'g')


# In[ ]:

def wangview(fn_tile_groups, fn_tileset_data):
    with open(fn_tileset_data,'r') as f:
        tileset_data = json.load(f)
    with open(fn_tile_groups,'r') as f:
        tile_groups = json.load(f)
    adjacency = terrain_graph(tileset_data)


# In[ ]:




# In[ ]:

if __name__ == '__main__':
    import sys
    try:
        wangview(sys.argv[1], sys.argv[2])
    except (IndexError, FileNotFoundError):
        print('Usage: Wangview.py tile_groups.json tilesets.json')

