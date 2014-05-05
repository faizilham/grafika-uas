#ifndef LIBGRAPH_HPP
#define LIBGRAPH_HPP

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <graphics.h>

/** Graphic Primitive **/

void init_graph();
void paintpix(int x, int y, int color);

/** Graphics Algorithms **/

void draw_line(int x1, int y1, int x2, int y2, int color);

void draw_ellipse(int xc, int yc, int rx,int ry, int color);

void fill (int x, int y, int fill_color, int boundary_color);
bool isExtremePoint(int x, int y); //used for fill_polygon method
void fill_polygon (int xmin, int ymin, int xmax, int ymax, int fill_color, int boundary_color);
#endif