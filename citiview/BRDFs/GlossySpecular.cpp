// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "GlossySpecular.h"
#include "Samplers/MultiJittered.h"


// ---------------------------------------------------------------------- default constructor

GlossySpecular::GlossySpecular(void) 
	: BRDF(),
	  ks(0.0), 
		cs(1.0),
		sampler(NULL)
{ }


// ---------------------------------------------------------------------- destructor
GlossySpecular::GlossySpecular(const GlossySpecular& other)
: GlossySpecular() { copy(other); }


GlossySpecular& GlossySpecular::operator=(const GlossySpecular& other) {
	if (this != &other) { copy(other); }
	return (*this);
}


void GlossySpecular::copy(const GlossySpecular& other) { 
	BRDF::operator=(other);

	ks = other.ks;
	cs = other.cs;
	exp = other.exp;

	Sampler* psamp = other.sampler;
	sampler = psamp ? psamp->clone() : NULL;
}


GlossySpecular::~GlossySpecular(void) {
	if (sampler) { delete sampler; }
}


// ---------------------------------------------------------------------- clone
GlossySpecular* GlossySpecular::clone (void) const {
	return (new GlossySpecular(*this));
}

// ---------------------------------------------------------------------- set_sampler
// this allows any type of sampling to be specified in the build functions

void
GlossySpecular::set_sampler(Sampler* sp, const float exp) {
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_hemisphere(exp);
}
// ---------------------------------------------------------------------- set_samples
// this sets up multi-jittered sampling using the number of samples

void
GlossySpecular::set_samples(const int num_samples, const float exp) {
	sampler_ptr = new MultiJittered(num_samples);
	sampler_ptr->map_samples_to_hemisphere(exp);
}
// ----------------------------------------------------------------------------------- f
// no sampling here: just use the Phong formula
// this is used for direct illumination only

RGBColor
GlossySpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const {
	RGBColor 	L;  				
    float 		ndotwi = sr.normal.dot(wi);
    Vector3D 	r(-wi + 2.0 * sr.normal.dot(ndotwi)); // mirror reflection direction
    float 		rdotwo = r.dot(wo);
		
    if (rdotwo > 0.0) { L = ks * cs * pow(rdotwo, exp); }
	return (L);
}
// ----------------------------------------------------------------------------------- sample_f
// this is used for indirect illumination

RGBColor
GlossySpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const {
	
    float ndotwo = sr.normal.dot(wo);
	Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection
	
	Vector3D w = r;								
    Vector3D u = Vector3D(0.00424, 1, 0.00764).cross(w);
	u.normalize();
    Vector3D v = u.cross(w);
		
	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;			// reflected ray direction
	
    if (sr.normal.dot(wi) < 0.0) 						// reflected ray is below tangent plane
		wi = -sp.x * u - sp.y * v + sp.z * w;

    float phong_lobe = pow(r.dot(wi), exp);
    pdf = phong_lobe * (sr.normal.dot(wi));

	return (ks * cs * phong_lobe);
}
// ----------------------------------------------------------------------------------- rho

RGBColor
GlossySpecular::rho(const ShadeRec&, const Vector3D&) const {
    RGBColor black(0, 0, 0);
	return (black);
}

