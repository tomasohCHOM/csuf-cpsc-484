#include "Fisheye.h"

#include "Utilities/RGBColor.h"
#include "World/World.h"
#include <cmath>
#include <random>


Fisheye::Fisheye()
: Camera(),
  psi_max(180),
  rectangular(false) {
}


Fisheye::Fisheye(const Fisheye& other)
: Fisheye() { copy(other); }


Fisheye& Fisheye::operator=(const Fisheye& other) {
  if (this != &other) { copy(other); }
    return *this;
}


void Fisheye::copy(const Fisheye& other) {
  Camera::operator=(other);

  psi_max = other.psi_max;
  rectangular = other.rectangular;
}


Fisheye* Fisheye::clone(void) const { return new Fisheye(*this); }


Fisheye::~Fisheye() { }


Vector3D Fisheye::ray_direction(const Point2D& pp, const int hres, const int vres, const float s, float& r_squared) {
  // compute the normalized device coordinates

  Point2D pn(2.0 / (s * hres) * pp.x, 2.0 / (s * vres) * pp.y);
  r_squared = pn.x * pn.x + pn.y * pn.y;

  if ((r_squared <= 1.0 && !rectangular) || rectangular) {
    float r = std::sqrt(r_squared);
    float psi = r * psi_max * PI_ON_180;
    float sin_psi = std::sin(psi);
    float cos_psi = std::cos(psi);
    float sin_alpha = pn.y / r;
    float cos_alpha = pn.x / r;
    Vector3D dir = sin_psi * cos_alpha * u
                 + sin_psi * sin_alpha * v
                 - cos_psi * w;

    return dir;
  } else
    return Vector3D(0.0);
}

//void Fisheye::render_scene(const World& w) {
void Fisheye::render_scene(const World& w, float, int) {
  RGBColor L;
  ViewPlane vp(w.vp);
  int hres = vp.hres;
  int vres = vp.vres;
  float s = vp.s;
  Ray ray;
  int depth = 0;
  Point2D sp;                 // sample point in [0, 1] x [0, 1]
  Point2D pp;                 // sample point on the pixel
  float r_squared = 1.0;      // sum of squares of normalized device coordinates

  ray.o = eye;

/*  for (int r = 0; r < vres; r++) {    // up
    for (int c = 0; c < hres; c++) {  // accross
      L = black;

      for (int j = 0; j < vp.num_samples; j++) {
        sp = vp.sampler_ptr->sample_unit_square();
        pp.x = s * (c - 0.5 * hres + sp.x);
        pp.y = s * (r - 0.5 * vres + sp.y);
        ray.d = ray_direction(pp, hres, vres, s, r_squared);

        if ((r_squared <= 1.0 && !rectangular) || rectangular)
          L += w.tracer_ptr->trace_ray(ray, depth);
      }

      L /= vp.num_samples;
      L *= exposure_time;
      w.display_pixel(r, c, L);
    }
  }*/
  std::vector<RowCol> row_col;

  for (int r = 0; r < vres; r++) {            // up
      for (int c = 0; c < hres; c++) {        // across
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
      for (int j = 0; j < vp.num_samples; j++) {
        sp = vp.sampler_ptr->sample_unit_square();
        pp.x = s * (c - 0.5 * hres + sp.x);
        pp.y = s * (r - 0.5 * vres + sp.y);
        ray.d = ray_direction(pp, hres, vres, s, r_squared);

        if ((r_squared <= 1.0 && !rectangular) || rectangular)
          L += w.tracer_ptr->trace_ray(ray, depth);
      }

      L /= vp.num_samples;
      L *= exposure_time;
      w.display_pixel(r, c, L);
  }
}
