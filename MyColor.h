#pragma once
#include <vector>

namespace MyColor
{
	struct RGBColor{
		int r,g,b;
		RGBColor():r(0),g(0),b(0){}
		RGBColor(int in_r,int in_g,int in_b):r(in_r),g(in_g),b(in_b){}
		void operator=(const RGBColor& in){r=in.r;g=in.g;b=in.b;}
	};

	struct XYZColor{
		double x,y,z;
		XYZColor():x(0.0),y(0.0),z(0.0){}
		XYZColor(double in_x,double in_y,double in_z):x(in_x),y(in_y),z(in_z){}
		void operator=(const XYZColor& in){x=in.x;y=in.y;z=in.z;}
	};

	struct LabColor{
		double l,a,b;
		LabColor():l(0.0),a(0.0),b(0.0){}
		LabColor(double in_l,double in_a,double in_b):l(in_l),a(in_a),b(in_b){}
		void operator=(const LabColor& in){l=in.l;a=in.a;b=in.b;}
	};
	typedef std::vector<LabColor> LabVec;

	//============================================================================
	// XYZ to sRGB conversion; helper for RGB2LAB()
	//============================================================================
	XYZColor LAB2XYZ(LabColor& val);
	//============================================================================
	// sRGB to CIELAB conversion
	//============================================================================
	RGBColor LAB2RGB(LabColor& val);
	//============================================================================
	// sRGB to XYZ conversion; helper for RGB2LAB()
	//============================================================================
	XYZColor RGB2XYZ(RGBColor& val);
	//============================================================================
	// sRGB to CIELAB conversion (uses RGB2XYZ function)
	//============================================================================
	LabColor RGB2LAB(RGBColor& val);
};

