#include "MyColor.h"
#include <math.h>

MyColor::XYZColor MyColor::LAB2XYZ( LabColor& val )
{
	double  var_Y = ( val.l + 16 ) / 116;
	double 	var_X = val.a / 500 + var_Y;
	double 	var_Z = var_Y - val.b / 200;

	double kappa   = 903.3;		//actual CIE standard

	if ( pow(var_X,3) > 0.008856 )  var_X = pow(var_X,3);
	else							var_X = (( var_X * 116 ) - 16)/kappa;

	if ( pow(var_Y,3) > 0.008856 )	var_Y = pow(var_Y,3);
	else							var_Y = (( var_Y * 116 ) - 16)/kappa;

	if ( pow(var_Z,3) > 0.008856 ) var_Z = pow(var_Z,3);
	else                           var_Z = (( var_Z * 116 ) - 16)/kappa;

	double Xr = 0.950456;	//reference white
	double Yr = 1.0;		//reference white
	double Zr = 1.088754;	//reference white

	XYZColor result;
	result.x = Xr * var_X;   
	result.y = Yr * var_Y;   
	result.z = Zr * var_Z;   
	return result;
}

MyColor::RGBColor MyColor::LAB2RGB( LabColor& val )
{
	XYZColor var = LAB2XYZ(val);

	double	var_B = var.x *  3.2406 + var.y * -1.5372 + var.z * -0.4986;
	double	var_G = var.x * -0.9689 + var.y *  1.8758 + var.z *  0.0415;
	double	var_R = var.x *  0.0557 + var.y * -0.2040 + var.z *  1.0570;

	if ( var_R > 0.0031308 ) var_R = 1.055 * pow(var_R, 1.0 / 2.4) - 0.055;
	else                     var_R = 12.92 * var_R;

	if ( var_G > 0.0031308 ) var_G = 1.055 * pow(var_G, 1.0 / 2.4) - 0.055;
	else                     var_G = 12.92 * var_G;

	if ( var_B > 0.0031308 ) var_B = 1.055 * pow(var_B, 1.0 / 2.4) - 0.055;
	else                     var_B = 12.92 * var_B;

	RGBColor result;
	result.r = (int)(var_R * 255);
	result.g = (int)(var_G * 255);
	result.b = (int)(var_B * 255);
	return result;
}

MyColor::XYZColor MyColor::RGB2XYZ( RGBColor& val )
{
	double R = (double)val.r/255.0;
	double G = (double)val.g/255.0;
	double B = (double)val.b/255.0;

	double r, g, b;

	if(R <= 0.04045)	r = R/12.92;
	else				r = pow((R+0.055)/1.055,2.4);
	if(G <= 0.04045)	g = G/12.92;
	else				g = pow((G+0.055)/1.055,2.4);
	if(B <= 0.04045)	b = B/12.92;
	else				b = pow((B+0.055)/1.055,2.4);

	XYZColor result;
	result.x = r*0.4124564 + g*0.3575761 + b*0.1804375;
	result.y = r*0.2126729 + g*0.7151522 + b*0.0721750;
	result.z = r*0.0193339 + g*0.1191920 + b*0.9503041;
	return result;
}

MyColor::LabColor MyColor::RGB2LAB( RGBColor& val )
{
	//------------------------
	// sRGB to XYZ conversion
	//------------------------
	XYZColor var;
	var = RGB2XYZ(val);

	//------------------------
	// XYZ to LAB conversion
	//------------------------
	double epsilon = 0.008856;	//actual CIE standard
	double kappa   = 903.3;		//actual CIE standard

	double Xr = 0.950456;	//reference white
	double Yr = 1.0;		//reference white
	double Zr = 1.088754;	//reference white

	double xr = var.x/Xr;
	double yr = var.y/Yr;
	double zr = var.z/Zr;

	double fx, fy, fz;
	if(xr > epsilon)	fx = pow(xr, 1.0/3.0);
	else				fx = (kappa*xr + 16.0)/116.0;
	if(yr > epsilon)	fy = pow(yr, 1.0/3.0);
	else				fy = (kappa*yr + 16.0)/116.0;
	if(zr > epsilon)	fz = pow(zr, 1.0/3.0);
	else				fz = (kappa*zr + 16.0)/116.0;

	LabColor result;
	result.l = 116.0*fy-16.0;
	result.a = 500.0*(fx-fy);
	result.b = 200.0*(fy-fz);
	return result;
}
