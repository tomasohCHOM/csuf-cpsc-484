#include "ViewPlane.h"
#include "Samplers/Sampler.h"
#include "Samplers/MultiJittered.h"
#include "Samplers/Regular.h"

int ViewPlane::max_depth = 10;

	
// ---------------------------------------------------------------- default constructor	
						
ViewPlane::ViewPlane()
    : 	hres(VIEWPLANE_HRES),
        vres(VIEWPLANE_VRES),
		s(1.0),
		num_samples(1),
		gamma(1.0),
		inv_gamma(1.0),
        show_out_of_gamut(false),
        sampler_ptr(nullptr)
{}
// ---------------------------------------------------------------- copy constructor

ViewPlane::ViewPlane(const ViewPlane& vp)   
	:  	hres(vp.hres),  
		vres(vp.vres), 
		s(vp.s),
		num_samples(vp.num_samples),
		gamma(vp.gamma),
		inv_gamma(vp.inv_gamma),
        show_out_of_gamut(vp.show_out_of_gamut),
        sampler_ptr(vp.sampler_ptr)
{}
// ---------------------------------------------------------------- assignment operator
ViewPlane& 
ViewPlane::operator= (const ViewPlane& rhs) {
    if (this == &rhs) { return (*this); }
		
	hres 				= rhs.hres;
	vres 				= rhs.vres;
	s					= rhs.s;
	num_samples			= rhs.num_samples;
	gamma				= rhs.gamma;
	inv_gamma			= rhs.inv_gamma;
	show_out_of_gamut	= rhs.show_out_of_gamut;
    sampler_ptr         = rhs.sampler_ptr;
	
	return (*this);
}


void ViewPlane::set_samples(int n)            {
    num_samples = n;
    if (sampler_ptr != nullptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
    if (num_samples > 1) {
        sampler_ptr = new MultiJittered(num_samples);
    } else { sampler_ptr = new Regular(1); }
}

void ViewPlane::set_sampler(Sampler* sp) {
    if (sampler_ptr) {
        delete sampler_ptr;
        sampler_ptr = nullptr;
    }
    num_samples = sp->get_num_samples();
    sampler_ptr = sp;
}

void ViewPlane::set_max_depth(int max) { max_depth = max; }






	





