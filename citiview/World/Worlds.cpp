#include "World/World.h"
#include "World_builder.h"
#include "Materials/Reflective.h"
#include "Materials/Transparent.h"

#include "Cameras/Fisheye.h"
#include "Cameras/Pinhole.h"
#include "Cameras/StereoCamera.h"
#include "Cameras/ThinLens.h"

#include "GeometricObjects/Instance.h"

#include "GeometricObjects/Primitives/Plane.h"

#include "GeometricObjects/BeveledObjects/BeveledBox.h"

#include "GeometricObjects/CompoundObjects/Box.h"
#include "GeometricObjects/CompoundObjects/Grid.h"
#include "GeometricObjects/CompoundObjects/RoundRimmedBowl.h"
#include "GeometricObjects/CompoundObjects/SolidCylinder.h"
#include "GeometricObjects/CompoundObjects/SolidCone.h"
#include "GeometricObjects/CompoundObjects/ThickRing.h"
#include "GeometricObjects/Triangles/Triangle.h"
#include "GeometricObjects/Triangles/SmoothTriangle.h"
#include "GeometricObjects/Instance.h"
#include "GeometricObjects/Primitives/Sphere.h"

#include "Lights/Directional.h"
#include "Lights/PointLight.h"

#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"

#include "Textures/Checker3D.h"
#include "Textures/ImageTexture.h"

#include "Samplers/MultiJittered.h"

#include "Tracers/RayCast.h"

#include "World/Worlds.h"


RGBColor lightRed(1, 0.4, 0.4);
RGBColor darkRed(0.9, 0.1, 0.1);

RGBColor brown(0.71, 0.40, 0.16);
RGBColor redBrown(0.85, 0.6, 0.2);


RGBColor orange(1, 0.6, 0.2);

RGBColor lemon(1, 1, 0.33);
RGBColor yellow(1, 1, 0);
RGBColor darkYellow(0.61, 0.61, 0);

RGBColor lightGreen(0.65, 0.8, 0.30);
RGBColor lightLightGreen(0.85, 1.0, 0.6);
RGBColor green(0, 0.6, 0.3);
RGBColor realGreen(0, 1.0, 0.1);
RGBColor darkGreen(0.0, 0.81, 0.41);

RGBColor  cyan(0, 1, 1);
RGBColor  blue_green(0.1, 1, 0.5);

RGBColor lightLightBlue(0.4, 0.64, 0.82);
RGBColor lightBlue(0.1, 0.4, 0.8);
RGBColor darkBlue(0.0, 0.0, 1.0);

RGBColor lightPurple(0.65, 0.3, 1);
RGBColor darkPurple(0.5, 0, 1);

RGBColor lightLightGrey(0.9);
RGBColor lightGrey(0.7);
RGBColor grey(0.25);
RGBColor darkDarkGrey(0.2, 0.2, 0.2);

RGBColor darkBlack(0, 0, 0);


struct ColorCenterRadius {
    RGBColor color;
    Point3D  center;
    int      radius;
};

void build_spheres_helper(World* w, const std::vector<ColorCenterRadius>& spheres) {
    for (const ColorCenterRadius& s : spheres) {
        add_sphere_helper(w, s.color, s.center, s.radius);
    }
}

void build_spheres(World* w) {
    std::vector<ColorCenterRadius> spheres =
        {
           { yellow,       Point3D(   5,  3,    0),   30 },
           { brown,        Point3D(  45, -7,  -60),   20 },
           { darkGreen,    Point3D(  40, 43, -100),   17 },
           { orange,       Point3D( -20, 28,  -15),   20 },
           { green,        Point3D( -25, -7,  -35),   27 },

           { lightGreen,   Point3D(  20, -27,  -35),  25 },
           { green,        Point3D(  35,  18,  -35),  22 },
           { brown,        Point3D( -57, -17,  -50),  15 },
           { lightGreen,   Point3D( -47,  16,  -80),  23 },
           { darkGreen,    Point3D( -15, -32,  -60),  22 },

           { darkYellow,   Point3D( -35, -37,  -80),  22 },
           { darkYellow,   Point3D(  10,  43,  -80),  22 },
           { darkYellow,   Point3D(  30,  -7,  -80),  10 },  // hidden
           { darkGreen,    Point3D( -40,  48, -110),  18 },
           { brown,        Point3D( -10,  53, -120),  18 },

           { lightPurple,  Point3D(-55, -52, -100),  10 },
           { brown,        Point3D(  5, -52, -100),  15 },
           { darkPurple,   Point3D(-20, -57, -120),  15 },
           { darkGreen,    Point3D( 55, -27, -100),  1 },
           { brown,        Point3D( 50, -47, -120),  15 },

           { lightPurple,  Point3D( 70, -42, -150),  10 },
           { lightPurple,  Point3D(  5,  73, -130),  12 },
           { darkPurple,   Point3D( 66,  21, -130),  13 },
           { lightPurple,  Point3D( 72, -12, -140),  12 },
           { green,        Point3D( 64,   5, -160),  11 },

           { lightPurple,  Point3D( 55,  38, -160),  12 },
           { lightPurple,  Point3D(-73,  -2, -160),  12 },
           { darkPurple,   Point3D( 30, -62, -140),  15 },
           { darkPurple,   Point3D( 25,  63, -140),  15 },
           { darkPurple,   Point3D(-60,  46, -140),  15 },

           { lightPurple,  Point3D(-30,  68, -130),  12 },
           { green,        Point3D( 58,  56, -180),  11 },
           { green,        Point3D(-63, -39, -180),  11 },
           { lightPurple,  Point3D( 46,  68, -200),  10 },
           { lightPurple,  Point3D( -3, -72, -130),  12 }
        };

    w->init_cameras_viewplane_lights_plane(SPHERES);

    build_spheres_helper(w, spheres);
}

struct ColorBottomTop {
    RGBColor color;
    Point3D  bottom;
    Point3D  top;
};

void build_city_helper(World* w, const std::vector<ColorBottomTop>& buildings) {
    for (const ColorBottomTop& bldg : buildings) {
        add_bb_helper(w, bldg.color, bldg.bottom, bldg.top);
    }
}
void build_city(World* w) {
    std::vector<ColorBottomTop> buildings =
        { { yellow,      Point3D( 1,  1,  0),   Point3D( 2,  2, 60)  },
          { darkPurple,  Point3D( 0,  0,  0),   Point3D( 1,  1, 60)  },
          { grey,        Point3D(-2,  2,  0),   Point3D(-1,  3,  65) },
          { green,       Point3D(-4,  0,  0),   Point3D(-3,  1,  70) },
          { darkPurple,  Point3D( 3,  0,  0),   Point3D( 4,  1,  65) },

          { darkBlue,    Point3D( 3, -4,  0),   Point3D( 4, -3,  70) },
          { darkPurple,  Point3D(-3, -4,  0),   Point3D(-2, -3,  75) },
          { yellow,      Point3D( 3,  3,  0),   Point3D( 4,  4,  70) },
          { green,       Point3D( 0, -3,  0),   Point3D( 1, -2,  70) },
          { darkBlue,    Point3D( 0,  2,  0),   Point3D( 1,  3,  70) },

          { darkBlue,    Point3D(-2,  0,  0),   Point3D(-1,  1,  70) },
          { darkBlue,    Point3D(-4, -3,  0),   Point3D(-3, -3,  80) },
          { grey,        Point3D( 2, -2,  0),   Point3D( 3, -1,  60) },
          { red,         Point3D(-4,  3,  0),   Point3D(-3,  4,  65) },

          { darkBlue,    Point3D(-6, -5,  0),   Point3D(-5, -5,  80) },
          { green,       Point3D (0,  5,  0),   Point3D( 1,  6,  60) },
          { darkPurple,  Point3D( 3,  5,  0),   Point3D( 4,  6,  65) },
          { darkBlue,    Point3D( 4,  1,  0),   Point3D( 5,  2,  70) },
          { lightRed,    Point3D(-5, -3,  0),   Point3D(-4, -2,  75) },
          { green,       Point3D( 5, -2,  0),   Point3D( 6, -1,  60) },

          { green,       Point3D(-2,  4,  0),   Point3D(-1,  5,  70) },
          { darkBlue,    Point3D(-5,  2,  0),   Point3D(-4,  3,  70) },
          { darkBlue,    Point3D(-5,  5,  0),   Point3D(-4,  6,  60) },
          { darkPurple,  Point3D(-5, -2,  0),   Point3D(-4, -1,  60) },
          { green,       Point3D(-2,  -4,  0),  Point3D(-1, -3, 65) },
          { darkBlue,    Point3D(-2,  -2,  0),  Point3D(-1, -1, 70) },
          { darkBlue,    Point3D(-6,  -1,  0),  Point3D(-5,  0, 70) }
        };

    w->init_cameras_viewplane_lights_plane(CITY);

    build_city_helper(w, buildings);
    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
    Instance* cone = new Instance(new SolidCone(3,2));
    w->add_object(cone);


    w->set_material(cone, darkBlue);
    cone->rotate_x(110);
    build_checkerboard(plane, grey, white, 2);
    w->add_object(plane);
}

#define SPACING 5
#define SIDE 1

void add_checkerboard(World* w, const RGBColor& c1, const RGBColor& c2, int size) {
    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
    build_checkerboard(plane, c1, c2, size);
    w->add_object(plane);
}


#define SPACING 5

void build_practical(World *w) {
    w->init_cameras_viewplane_lights_plane(PRACTICAL);

    for (int i = 0; i < 60; i += SPACING) {
        add_bb_helper(w, orange, Point3D( i, 0, 0),     1, 1, 4);
        add_bb_helper(w, orange, Point3D( 0, 3 * SPACING + i, 0), 1, 1, 4);

        add_bb_helper(w, cyan, Point3D( i, SPACING, 0), 1, 1, 8);

        add_bb_helper(w, lightGreen, Point3D( i,  2 * SPACING, 0), 1, 1, 16);
    }
    add_checkerboard(w, darkBlue, white, 1);
}

void build_impractical(World *w) {
    w->init_cameras_viewplane_lights_plane(PRACTICAL);
    for (int i = 0; i < 200; i += SPACING) {
        if (i % 2 == 0) {
            add_bb_helper(w, red, Point3D(i, 0, 0), 1, 1, 16);
            add_bb_helper(w, red, Point3D(i, -2, 13), 1, 5, 1);
            add_bb_helper(w, darkBlue, Point3D(i, 4 * SPACING, 0), 1, 1, 16);
            add_bb_helper(w, darkBlue, Point3D(i, 4 * SPACING - 2, 13), 1, 5, 1);
        } else {
            add_bb_helper(w, darkBlue, Point3D(i, 0, 0), 1, 1, 16);
            add_bb_helper(w, darkBlue, Point3D( i, -2, 13), 1, 5, 1);
            add_bb_helper(w, red, Point3D( i, 4 * SPACING, 0), 1, 1, 16);
            add_bb_helper(w, red, Point3D( i, 4 * SPACING - 2, 13), 1, 5, 1);
        }
    }
    add_checkerboard(w, grey, white, 1);
}

void build_imaginary(World *w) {
    w->init_cameras_viewplane_lights_plane(PRACTICAL);

    Instance* cone = new Instance(new SolidCone(3,2));
    w->set_material(cone, lightLightBlue);
    cone->translate(Point3D(-6,0,-7));
    w->add_object(cone);
    cone->rotate_x(110);

    Instance* cylin = new Instance(new SolidCylinder(0,3,1));
    //cylin->hit();
    //cylin->shadow_hit();
     cylin->translate(Point3D(2, 0, -7));
    w->set_material(cylin, lightGreen);
    w->add_object(cylin);
    cylin->rotate_x(110);

    //add_triangle_helper(w, red, Point3D(3, 2, 4) , Point3D(5, 2, 5), Point3D(0, 5, 2));
    Instance* tri = new Instance(new Triangle(Point3D(-1,-1,0),Point3D(5,0,1.5),Point3D(0,5,2)));
    w->set_material(tri, red);
    w->add_object(tri);
    tri->translate(Point3D(-2,3,0));

    Instance* box = new Instance(new Box(Point3D(2,2,2), Point3D(6,3,6)));
    w->set_material(box, redBrown);
    w->add_object(box);
    box->translate(Point3D(-9,-8,-1));

    Instance* ring1 = new Instance(new ThickRing(-1,0,7,8));
    w->set_material(ring1, yellow);
    w->add_object(ring1);
    ring1->translate(Point3D(-3,3,0));
    ring1->rotate_y(180);
    ring1->rotate_z(50);

    Instance* ring2 = new Instance(new ThickRing(-1,0,6,7));
    w->set_material(ring2, white);
    w->add_object(ring2);
    ring2->translate(Point3D(-5,-12,0));
    ring2->rotate_y(180);
    ring2->rotate_z(70);
    Instance* sph = new Instance(new Sphere(Point3D(-10,-1,1),4));
    w->set_material(sph,yellow);
    std::shared_ptr<Reflective> ref = std::make_shared<Reflective>();

    ref->set_ka(0.15);
    ref->set_kd(0.25);
    ref->set_kr(0.7);
    ref->set_ks(0.1);
    ref->set_cd(yellow);
    sph->set_material(ref);

    w->add_object(sph);
    add_checkerboard(w, red, white, 1);
}

// void build_sphere_triangle_box(World* w) {
//     w->init_cameras_viewplane_lights_plane(SPHERE_TRIANGLE_BOX);

//     add_bb_helper(w, orange, Point3D(0, 0, 0),  3, 1, 7);
//     add_triangle_helper(w, lightRed, Point3D(-3, -6, 4.2), Point3D(-2, 5, 1.6), Point3D(0, 0, -1));
//     add_sphere_helper(w, lightGreen, Point3D(0.4, 7, 1.5), 0.5);
//     add_checkerboard(w, red, white, 1);
// }


void build_sphere_triangle_box(World* w) {
    // add_sphere_helper(w, lightGreen, Point3D(1.7, -0.2, 1.7), SIDE/2.5);
    // add_bb_helper(w, orange, Point3D( 2, 0, 0), 0.75 * SIDE, SIDE, 2.5);
    // // add_bb_helper(w, orange, Point3D( 2, 0, 0), 0.75 * SIDE, SIDE, 2.5, Vector3D());

    // std::shared_ptr<Phong> phong = std::make_shared<Phong>();
    // phong->set_cd(cyan);
    // phong->set_ka(0.5);
    // phong->set_kd(0.5);
    // phong->set_ks(0.06);
    // phong->set_exp(1);

    // Triangle* triangle = new Triangle(Point3D(0.7, -1, 0.2), Point3D(3, 0, 1.25), Point3D(1.5, 0.5, 1.75));
    // triangle->set_material(phong);
    // w->add_object(triangle);

    add_sphere_helper(w, darkYellow, Point3D(1, -2, 7), 2.5); // TODO FILL IN CORRECT VALUES
    add_bb_helper(w, orange, Point3D(-3, 1, 0), 5, 3, 9); // TODO FILL IN CORRECT VALUES

    std::shared_ptr<Phong> phong = std::make_shared<Phong>();
    phong->set_cd(cyan);
    phong->set_ka(0.5);
    phong->set_kd(0.5);
    phong->set_ks(0.06);
    phong->set_exp(1);

    Triangle* triangle
        = new Triangle(Point3D(2, 5, 4.5), Point3D(-3, -2, 7), Point3D(4, -4, 1));  /* TODO FILL IN CORRECT VALUES */
    triangle->set_material(phong);
    w->add_object(triangle);

    add_checkerboard(w, lightGrey, white, 1);
}

void build_sphere_triangle_box_world(World* w, CHOICE choice) {
    Pinhole* camera = new Pinhole;
    switch(choice) {
    case A:    // front
        camera->set_eye(10, 0, 5);  // NEED DIFFERENT VALUES FOR EACH CASE
        camera->set_lookat(0, 0, 5);
        camera->set_view_distance(150);
        break;
    case B:    // medium
        camera->set_eye(10, 5, 15);
        camera->set_lookat(0, 0, 5);
        camera->set_view_distance(150);
        break;
    case C:    // overhead
        camera->set_eye(-5, -15, 50);
        camera->set_lookat(0, 0, 5);
        camera->set_view_distance(150);
        break;
    default:
        throw new std::invalid_argument("Invalid choice\n");
        break;
    }

    camera->set_up_vector(0, 0, 1);
    camera->compute_uvw();
    w->set_camera(camera);

    w->init_viewplane();

    w->init_ambient_light();
    Directional* lt = new Directional();
    lt->set_shadows(true);
    lt->set_direction(50, -50, 300);
    lt->scale_radiance(5.0);
    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);

    w->init_plane();

    build_sphere_triangle_box(w);
}



void thin_lens_helper(World* w, const Point3D& p1, const Point3D& p2,
                      const RGBColor& c1, const RGBColor& c2) {
    Checker3D* check = new Checker3D;
    check->set_size(2.0);
    check->set_color1(c1);
    check->set_color2(c2);

    std::shared_ptr<SV_Matte> matte = std::make_shared<SV_Matte>();
    matte->set_ka(0.5);
    matte->set_kd(0.35);
    matte->set_cd(check);

    Box* b = new Box(p1, p2);
    b->set_material(matte);
    w->add_object(b);
}

void build_thinlens(World* w, double focal_distance) {
    w->init_cameras_viewplane_lights_plane(THIN_LENS);

    int num_samples = 100;

    w->vp.set_hres(400);
    w->vp.set_vres(300);
    w->vp.set_pixel_size(0.05);
    w->vp.set_sampler(new MultiJittered(num_samples));
    w->vp.set_max_depth(0);

    w->tracer_ptr = new RayCast(w);
    w->background_color = white;

    Ambient* ambient_ptr = new Ambient;
    ambient_ptr->scale_radiance(0.5);
    w->set_ambient_light(ambient_ptr);

    ThinLens* tl = new ThinLens;
    tl->set_sampler(new MultiJittered(num_samples));
    tl->set_eye(0, 6, 50);
    tl->set_lookat(0, 6, 0);
    tl->set_view_distance(40.0);

    tl->set_focal_distance(focal_distance);

    tl->set_lens_radius(1.0);
    tl->compute_uvw();
    w->set_camera(tl);


    Directional* lp = new Directional;
    lp->set_direction(1, 1, 1);
    lp->scale_radiance(7.5);
    lp->set_shadows(true);
    w->add_light(lp);

    thin_lens_helper(w, Point3D(-9, 0, -1),     Point3D(-3, 12, 0),     lemon,      black);
    thin_lens_helper(w, Point3D(-3.25, 0, -25), Point3D(4.75, 14, -24), blue_green, black);
    thin_lens_helper(w, Point3D(8, 0, -49),     Point3D(18, 15, -48),   orange,     black);

    Instance* isplane = new Instance(new Plane(Point3D(0, 0, 0), Normal(0, 1, 0)));
    isplane->rotate_y(90);
    build_checkerboard(isplane, lightGrey, black, 8);

    w->add_object(isplane);
}


void
build_fisheye(World* w, CHOICE choice) {
    int num_samples = 100;

    w->vp.set_hres(400);
    w->vp.set_vres(400);
    w->vp.set_samples(num_samples);

    w->background_color = lightBlue;

    w->tracer_ptr = new RayCast(w);

    // pinhole camera for Figure 11.7(a)

    Pinhole* pinHole_ptr = new Pinhole;
    pinHole_ptr->set_eye(250, 300, 150);
    pinHole_ptr->set_lookat(-20, 300, -110);
    pinHole_ptr->set_view_distance(250);
    pinHole_ptr->compute_uvw();
    w->set_camera(pinHole_ptr);


    Fisheye* fisheye = new Fisheye;    // fisheye camera for the other parts

    // for parts (b), (c), (d)

//    fisheye->set_eye(250, 300, 150);
    fisheye->set_eye(350, 450, 150);
    fisheye->set_lookat(-20, 300, -110);
 //   fisheye->set_fov(120);     // part (a)
    fisheye->set_fov(120);  // part (b)
//	fisheye->set_fov(180);  // part (c)
    fisheye->set_fov(360);  // part (d)


/*	// for part (e)
    fisheye->set_eye(250, 450, 150);
    fisheye->set_lookat(-20, 250, -110);
    fisheye->set_fov(360);
*/

/*	// for part (f)
    // for this image the skydome is the only object in the scene
    // you need to comment out the two statements:
     add_object(grid_ptr);
     add_object(plane_ptr);

    fisheye->set_eye(0, 0, 0);
    fisheye->set_lookat(0, 1, 0);
    fisheye->set_fov(180);
*/

    fisheye->compute_uvw();
    w->set_camera(fisheye);


    PointLight* light_ptr1 = new PointLight;
    light_ptr1->set_location(150, 200, 65);
//    light_ptr1->scale_radiance(5.25);
    light_ptr1->scale_radiance(15.25);
    light_ptr1->set_shadows(true);
    w->add_light(light_ptr1);


    // box materials
    std::shared_ptr<Matte> matte1 = std::make_shared<Matte>();
    matte1->set_cd(0, 0.5, 0.5);     // cyan
    matte1->set_ka(0.4);
    matte1->set_kd(0.5);

    std::shared_ptr<Matte> matte2 = std::make_shared<Matte>();
    matte2->set_cd(1, 0, 0);     	  // red
    matte2->set_ka(0.4);
    matte2->set_kd(0.5);

    std::shared_ptr<Matte> matte3 = std::make_shared<Matte>();
    matte3->set_cd(0.5, 0.6, 0);     // green
    matte3->set_ka(0.4);
    matte3->set_kd(0.5);

    Grid* grid = new Grid;    // Construct rows of boxes stored in a grid

    int num_boxes = 40;    // first row
    float wx = 50;
    float wz = 50;
    float h = 150;
    float s = 100;

    for (int j = 0; j < num_boxes; j++) {
        Box* box = new Box(	Point3D(-wx, 0, -(j + 1) * wz - j * s),
                                Point3D(0, h, - j * wz - j * s));
        box->set_material(matte1);
    //	add_object(box);
        grid->add_object(box);
    }

    h = 300;    // second row
    for (int j = 0; j < num_boxes; j++) {
        Box* box = new Box(	Point3D(-wx -wx - s, 0, -(j + 1) * wz - j * s),
                                Point3D(-wx - s, h, - j * wz - j * s));
        box->set_material(matte2);
//		add_object(box);
        grid->add_object(box);
    }

    h = 850; 	// third row
    for (int j = 0; j < num_boxes; j++) {
        Box* box = new Box(	Point3D(-wx - 2 * wx - 2 * s, 0, -(j + 1) * wz - j * s),
                                Point3D(-2 * wx - 2 * s, h, - j * wz - j * s));
        box->set_material(matte3);
//		add_object(box);
        grid->add_object(box);
    }

    // a column
    h = 150;
    for (int j = 0; j < num_boxes; j++) {
        Box* box = new Box(	Point3D(-3 * (wx + s) - (j + 1) * wz - j * s, 0, -wx),
                                Point3D(-3 * (wx + s) - j * wz - j * s, h, 0));
        box->set_material(matte1);
//		add_object(box);
        grid->add_object(box);
    }

    grid->setup_cells();
    w->add_object(grid);

    Checker3D* check = new Checker3D;
    check->set_size(2 * wx);
    check->set_color1(0.7);
    check->set_color2(white);

//	SV_Matte* sv_matte1 = new SV_Matte;
    std::shared_ptr<SV_Matte> sv_matte1 = std::make_shared<SV_Matte>();
//    sv_matte1->set_ka(0.20);
    sv_matte1->set_ka(1.0);
    sv_matte1->set_kd(0.50);
    sv_matte1->set_cd(check);
    Plane* plane = new Plane(Point3D(0, 1, 0), Normal(0, 1, 0));
    plane->set_material(sv_matte1);
    w->add_object(plane);
}

    // skydome with clouds

//	Image* image = new Image;
//	image->read_ppm_file("CloudsSmall.ppm");

//	SphericalMap* spherical_map = new SphericalMap;

//	ImageTexture* image_texture = new ImageTexture(image);
//	image_texture->set_mapping(spherical_map);

////	SV_Matte* sv_matte2 = new SV_Matte;
//    std::shared_ptr<SV_Matte> sv_matte2 = std::make_shared<SV_Matte>();
//	sv_matte2->set_ka(1);
//	sv_matte2->set_kd(0.85);
//	sv_matte2->set_cd(image_texture);

//	Instance* sphere = new Instance(new Sphere);
//	sphere->scale(1000000);
//	sphere->set_material(sv_matte2);
//	w->add_object(sphere);
//}


void build_stereo(World* w, CHOICE choice) {
  int num_samples = 1;

  w->vp.set_hres(200);
  w->vp.set_vres(200);
  w->vp.set_pixel_size(0.05);
  w->vp.set_samples(num_samples);
  
  w->tracer_ptr = new RayCast(w);

  float vpd = 100;  // view plane distance for 200 x 200 pixel images

  Pinhole* left_camera = new Pinhole;
  left_camera->set_view_distance(vpd);
  
  Pinhole* right_camera = new Pinhole;
  right_camera->set_view_distance(vpd);
  
  StereoCamera* stereo = new StereoCamera;
//  Stereo* stereo = new Stereo;
  if (choice == A) {
      stereo->set_left_camera(left_camera);
      stereo->set_right_camera(right_camera);
      stereo->use_parallel_viewing();
  } else if (choice == B) {
      stereo->set_left_camera(right_camera);
      stereo->set_right_camera(left_camera);
      stereo->use_transverse_viewing();
  } else {
      throw new std::invalid_argument("invalid choice\n");
  }
  stereo->set_pixel_gap(5);
  stereo->set_eye(5, 0, 100);
  stereo->set_lookat(0);
  stereo->compute_uvw();
  stereo->set_stereo_angle(0.75);  // deg, not radians
  stereo->setup_cameras();
  w->set_camera(stereo);
  
//  PointLight* lt = new PointLight;
  Directional* lt = new Directional;
  lt->set_direction(100, 100, 100);
  lt->scale_radiance(3);
//  lt->scale_radiance(3);
  lt->set_shadows(true);
  w->add_light(lt);

  double exp_ = 1;
  double ka_ = 0.2;
  double kd_ = 0.2;
  double ks_ = 0.06;
  
  std::shared_ptr<Phong> phong1 = std::make_shared<Phong>();
  phong1->set_cd(cyan);
  phong1->set_ka(ka_);
  phong1->set_kd(kd_);
  phong1->set_ks(ks_);
  phong1->set_exp(exp_);
  
  std::shared_ptr<Phong> phong2 = std::make_shared<Phong>();
  phong2->set_cd(redBrown);
  phong2->set_ka(ka_);
  phong2->set_kd(kd_);
  phong2->set_ks(ks_);
  phong2->set_exp(exp_);
  
  std::shared_ptr<Phong> phong3 = std::make_shared<Phong>();
  phong3->set_cd(yellow);
  phong3->set_ka(ka_);
  phong3->set_kd(kd_);
  phong3->set_ks(ks_);
  phong3->set_exp(exp_);
  
  Sphere* sphere1 = new Sphere(Point3D(0, 0, 35), 0.75);
  sphere1->set_material(phong1);
  w->add_object(sphere1);
  
  Sphere* sphere2 = new Sphere(Point3D(0), 2);
  sphere2->set_material(phong2);
  w->add_object(sphere2);
  
  Sphere* sphere3 = new Sphere(Point3D(1.5, 0, -80), 2);
  sphere3->set_material(phong3);
  w->add_object(sphere3);
}

void build_figure_10_10(World* w, CHOICE choice) {
    switch(choice) {
        case A: build_thinlens(w, 50.0); break;
        case B: build_thinlens(w, 74.0); break;
        case C: build_thinlens(w, 98.0); break;
        default: throw new std::invalid_argument("Invalid choice.\n");
    }
}

void build_figure_11_7(World* w, CHOICE choice) {
    qDebug("this is in 11_7\n");
    switch(choice) {
        case A: case B: case C: case D: case E: build_fisheye(w, choice); break;
        default: throw new std::invalid_argument("Invalid choice.\n");
    }
}

void build_figure_12_12(World* w, CHOICE choice) {
    qDebug("this is in 12_12\n");
    switch(choice) {
        case A: case B: build_stereo(w, choice); break;
        default: throw new std::invalid_argument("Invalid choice.\n");
    }
}



