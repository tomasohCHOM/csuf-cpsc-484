#include "Utilities/Constants.h"
#include "Utilities/Point3D.h"
#include "Utilities/Vector3D.h"
#include "Cameras/Pinhole.h"
#include <math.h>
#include <random>
#include <algorithm>


Pinhole::Pinhole()
: Camera(), d(500), zoom(1.0) { }


Pinhole::Pinhole(const Pinhole& other)
: Pinhole() { copy(other); }


Pinhole& Pinhole::operator= (const Pinhole& other) {
    if (this != &other) { copy(other); }
    return (*this);
}


void Pinhole::copy(const Pinhole& other) {
    Camera::operator= (other);
    d = other.d;
    zoom = other.zoom;
 }


Pinhole::~Pinhole() { }


Camera*	Pinhole::clone() const { return (new Pinhole(*this)); }


void Pinhole::set_view_distance(const float vpd) { d = vpd; }

void Pinhole::set_zoom(const float zoom_factor)  { zoom = zoom_factor; }

Vector3D Pinhole::get_direction(const Point2D& p) const {
    Vector3D dir = p.x * u + p.y * v - d * w;
    dir.normalize();
    return(dir);
}

// ----------------------------------------------------------------------------- render_scene
void 												
Pinhole::render_scene(const World& w, float x /* =0 */, int offset /* =0 */ ) {
    RGBColor    L;
    ViewPlane    vp(w.vp);
    Ray            ray;
    int         depth = 0;
    Point2D     pp;        // sample point on a pixel
    int n = (int)sqrt((float)vp.num_samples);

    vp.s /= zoom;
    ray.o = eye;

    std::vector<RowCol> row_col;

    for (int r = 0; r < vp.vres; r++) {            // up
        for (int c = 0; c < vp.hres; c++) {        // across
            row_col.push_back(RowCol(r, c));
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(row_col.begin(), row_col.end(), g);
    // std::random_shuffle(row_col.begin(), row_col.end());
    int rendered = 0;

    for (const RowCol& rcp: row_col) {
        L = black;
        int r = rcp.r;
        int c = rcp.c;
        for (int p = 0; p < n; p++)            // up pixel
            for (int q = 0; q < n; q++) {    // across pixel
                pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n) + x;
                pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);
                ray.d = get_direction(pp);
                L += w.tracer_ptr->trace_ray(ray, depth);
            }

        L /= vp.num_samples;
        L *= exposure_time;
        w.display_pixel(r, c + offset, L);
    }
}

