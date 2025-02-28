#ifndef WORLDS_H
#define WORLDS_H

#include "World.h"

enum CHOICE { A, B, C, D, E, F };


void build_spheres(World* w);

void build_city(World* w);

void build_practical(World *w);

void build_impractical(World *w);

void build_imaginary(World* w);

void build_sphere_triangle_box(World* w);

void build_sphere_triangle_box_world(World* w, CHOICE choice);

void build_thinlens(World* w, double focal_distance);
void build_figure_10_10(World* w, CHOICE choice);

void build_fisheye(World* w, CHOICE choice);
void build_figure_11_7(World* w, CHOICE choice);

void build_stereographic(World* w, double focal_distance);
void build_figure_12_12(World* w, CHOICE choice);

void build_mcdonalds(World* w);

void build_reflective_and_transparent_sphere(World* w, int fig);

void build_five_reflective_transparent_spheres(World* w);

void build_sundial(World* w, double radius);



#endif // WORLDS_H
