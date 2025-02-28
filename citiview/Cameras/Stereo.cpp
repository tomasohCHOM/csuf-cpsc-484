//#include "Utilities/Constants.h"
//#include "Utilities/Point3D.h"
//#include "Utilities/Vector3D.h"
//#include "Cameras/Stereo.h"
//#include <math.h>


//Stereo::Stereo()
//: d(100), zoom(1.0) { }

//Stereo::Stereo(const Stereo& other)
//: Stereo() { copy(other); }


//Stereo& Stereo::operator=(const Stereo& other) {
//  if (this != &other) { copy(other); }
//    return *this;
//}

//void Stereo::copy(const Stereo& other) {
//  Camera::operator=(other);

//  d = other.d;		// view plane distance
//  zoom = other.zoom;	// zoom factor
//}

//Stereo* Stereo::clone(void) const { return new Stereo(*this); }


//Stereo::~Stereo() { }


//// ----------------------------------------------------------------------------- render_scene
//void
//Stereo::render_scene(const World& w, float, int) {
//  struct World unused = w;  // silence unused warning
//  qDebug() << "Stereo::render_scene() not yet implemented";
//     RGBColor	L;
//     ViewPlane	vp(w.vp);
//     Ray			ray;
//     int 		depth = 0;
//     Point2D 	pp;		// sample point on a pixel
//     int n = (int)sqrt((float)vp.num_samples);
		
//     vp.s /= zoom;
//     ray.o = eye;
		
//     for (int r = 0; r < vp.vres; r++) {			// up
//        for (int c = 0; c < vp.hres; c++) {		// across
//            L = black;
			
//            for (int p = 0; p < n; p++)			// up pixel
//                for (int q = 0; q < n; q++) {	// across pixel
//                    pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n);
//                    pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);
//                    ray.d = get_direction(pp);
//                    L += w.tracer_ptr->trace_ray(ray, depth);
//                }
											
//            L /= vp.num_samples;
//            L *= exposure_time;
//            w.display_pixel(r, c, L);
//        }
//     }
//}


