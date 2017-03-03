# Wangscape algorithms

This file contains detailed information about the algorithms and dataflow used in Wangscape.
Understanding them may help you to configure Wangscape to make the tilesets you want.

## Table of contents

0. [Tiles and tilesets](#tiles-and-tilesets)
0. [Rearranging source tiles](#rearranging-source-tiles)
0. [Terrain hyperraph](#terrain-hypergraph)
0. [Combining terrains](#combining-terrains)
0. [Generating corner masks](#generating-corner-masks)

## Tiles and tilesets

Wangscape's input is:
* A set of image files containing your source terrain tiles.
* A set of configuration files describing the locations of the source terrain tiles and how to combine them into tilesets. The exact format is specified in the [options schema](./schemas/options_schema.json), and includes:
  * The resolution (in pixels) of tiles used.
  * The image file and offset within the image of each terrain.
  * A set of terrain cliques (see [Terrain hypergraph](#terrain-hypergraph)).
  * Filenames of noise module groups used for [generating corner masks](#generating-corner-masks).
  * Which method is used to convert noise values into corner masks ([generating corner masks](#generating-corner-masks)).
* A set of JSON files describing module groups used to [generate noise values](#generating-noise-values).

Wangscape's output is:
* A set of image files, each one containing a full corner Wang tileset for a subset of the input terrain types,
all of them with compatible borders (if configured correctly).
* A set of JSON files describing the tilesets generated, and where to find a specific tile within them.

## Rearranging source tiles

Wangscape's output tiles are designed to be displayed offset by a quarter tile.
In order for the display tiles to match the source tiles,
the source images must be chopped into quarters and reassembled in this arrangement:
```
12 -> 43
34    21
```
When the resolution is an odd number in the x or y dimension,
the pixel at `(0,0)` is translated right and down by `(floor(rx/2), floor(ry/2))`.
So, to correctly display output tiles, they should be translated left and up by the same amount.

## Terrain hypergraph

###Adjacency restrictions

In a display map built strictly from square tiles, there are no restrictions on which terrain types can border each other.
In a display map built from corner Wang tiles, there are restrictions on which terrain types can meet at a single corner.
For instance, you could generate tilesets where desert and tundra can never be adjacent.
However, some restrictions can be more subtle than that.
For instance, you could generate tilesets with this situation :
```
G: grass
C: sea
P: plains
D: desert

GC    GC    GP    CP    GC
PP    DD    DD    DD    PD
Legal Legal Legal Legal Illegal
```
In theory, the algorithms described below allow you to generate any individual corner Wang tile you want,
with as many different versions as you want.
However, manually listing each individual tile and the number of spares would be impractical
when configuring Wangscape to generate a set of tiles usable for map displays.

It is also possible to simply generate one tile for every combination of terrain types in the game.
If you have a lot of terrain types, this will produce a large number of tiles (`N^4`), which has many disadvantages:
* In a single tileset, the size of the tileset may exceed the maximum texture size of low-end or legacy graphics cards.
* In individual files, the number of tiles may affect performance when browsing the output files.
* The large number of tiles will take a long time to generate, slowing down the configuration process.
* A large number of generated tiles may never be used, for instance all tiles containing deep water and land.

A sensible compromise between texture size and folder size,
and between simple and complex configuration,
is to define a [hypergraph](https://en.wikipedia.org/wiki/Hypergraph) on the set of terrains.

### Hypergraph

The terrain hypergraph, for the purposes of Wangscape, is a list of lists of terrains.
For each list of terrains (which we call cliques), one tileset is generated,
with a single tile for each combination of four terrains in the clique.

Subject to the restriction that each clique must be unique (ignoring order of terrains),
the terrain hypergraph can configure the legal terrain combinations as follows:
* If a set of 2, 3 or 4 terrains is not found in any of the cliques,
those terrains cannot appear around a common corner.
In the case of two terrains, this means they cannot be adjacent (even diagonally).
* If a set of terrains appears in more than one (different) clique,
extra tiles will be generated for each combination of those tiles.
The extra tiles will have different borders (except for the single-terrain tiles),
and can be used to add variety to output displays.

Make sure your hypergraph, where appropriate.
If your hypergraph is (for instance) `[["a","b"],["c","d"]]`,
then it will be impossible for terrains `a` and `b` to be on the same map as terrains `c` and `d`.

If you have a set of `N` terrains in which all combinations must be allowed,
you have a few different options:
* Put them all in one clique. This will generate the smallest number of tiles,
but the largest texture size.
* Choose a clique size `4 <= C < N`, and make one clique for each combination of `C` terrains.
That's `N!/(C!(N-C)!)` cliques, each with texture size `(rx*C^2, ry*C^2)`.
Your choice of `C` will depend on your requirements for texture size, folder size, and computation time.
If `N` is so large that no `C` satisfies your requirements,
you will need to introduce more adjacency constraints.

## Combining terrains

Each tile has corner terrains `t1, ..., t4`, and is generated as follows:

0. Generate a [corner mask](#generating-corner-masks) for each corner.
They are essentially 8-bit greyscale images with the same resolution as a tile,
and should satisfy these constraints:
    0. The total of the corner masks in each pixel is 255.
    0. Each one has value 255 at the corresponding corner (hence each one has value 0 at all other corners).
    0. Along the horizontal border (transitioning from `t1` to `t2` or from `t3` to `t4`) incident on the corresponding corner,
    each one has values similar to those generated for all other corner masks with a similar horizontal border.
    0. Equivalent constraints for vertical borders.
0. Initialise the output tile to opaque black `(0,0,0,255)`.
0. For each corner mask and corresponding ([rearranged](#rearranging-source-tiles)) terrain texture:
    0. Add the terrain texture, multiplied by the corner mask and scaled, to the output tile.

Note that this is not the standard alpha blending algorithm.
However, it is easy to configure OpenGL's blending equation and parameters to perform this operation.

## Generating corner masks

Corner masks (effectively 8-bit greyscale images) are generated in two stages:

0. A raster of floating-point noise values is calculated for each corner. They should satisfy these constraints:
    0. Each one has value 1 or greater at the corresponding corner.
    0. Each one has value 0 at all other corners.
    0. Along the horizontal border (transitioning from `t1` to `t2` or from `t3` to `t4`) incident on the corresponding corner,
each one has values similar to those generated for all other corner masks with a similar horizontal border.
    0. Equivalent constraints for vertical borders.
0. For each pixel, an alpha calculator converts the four floating-point values at that pixel into four 8-bit unsigned integer values,
such that the above constraints on corner mask values are satisfied.

### Generating noise values

Noise values are generated using libnoise modules, and a few libnoise-compatible modules defined by Wangscape.
All modules, and their connections to source modules, are fully customisable by the user.
This is done using a module group format similar to that specified by [RESTnoise](restnoise.readme.io/).
The exact format of Wangscape module groups is specified in the [module group schema](./schemas/module_group_schema.json).
The output noise module is evaluated at regularly spaced points in the square `[0,1]x[0,1]`.

The generation of noise values is quite delicate, mostly because of the border constraints.
In order to satisfy them while maintaining fully customisability,
four module groups are combined in order to generate noise values for a corner mask:
0. A horizontal border module group.
0. A vertical border module group.
0. A central module group.
0. A combiner module group.

The central and border module groups take no input, and should output values between -1 and 1.

The combiner module group uses weighting functions to construct a module with values derived from the other three. It should satisfy the following constraints:
* Along the horizontal border incident on the associated corner, it fades from 1 to -1, with exact values modulated by the horizontal border module.
* Along the vertical border incident on the associated corner, it fades from 1 to -1, with exact values modulated by the vertical border module.
* Along the other two borders, it has value 0.
* In the centre, it has values primarily influenced by the central module group.

To ensure variety in output tiles, all seedable modules in the central module group are reseeded before each use.

To ensure border compatibility, all seedable modules in the border module groups are reseeded only once, at the start of execution.
Also, when the corner is at the top of the tile, the horizontal border module group is translated upwards by 1. A similar conditional translation is applied to the vertical border module group.

To ensure that border module group output values are used meaningfully,
user-specified horizontal module groups are replaced with a constant value of 0 when the corner is on the right.
User-specified vertical module groups are similarly replaced when the corner is on the bottom.

The corner combiner group uses 3 major components to combine the central and border module groups:

1. A `CornerCombiner` module, which has value 1 along one of the axes, value -1 along the other axis, and value 0 along diagonals.
This is used as the control module to blend the horizontal and vertical border module groups into one texture with border compatibility.
2. A `NormLPQ` module, which has value 0 at the associated corner and value at least 1 at the other three corners.
This is used as input to two `Curve` modules,
which together form an envelope with range [1,1] at the associated corner and [-1,-1] at the other corners.
Near the associated corner the range of the envelope is a subrange of [-1,1].
This envelope is used to transform the combined border modules into a texture
which will reliably produce correct alpha values at the corners,
and fade noisily along the two incident borders.
3. Another `NormLPQ` module, which is scaled and clamped to have value -1 at the centre of the tile and value 1 near to all the borders.
This is used as the control module to blend the central module group with the combined and faded border modules, without allowing reseeded central module groups to affect border compatibility.

### Alpha calculation

TODO: Description of existing alpha calculators.
