#ifndef KMUCS_GRAPHICS_TRANSFORM_HPP
#define KMUCS_GRAPHICS_TRANSFORM_HPP

#include <cmath>
#include "vec.hpp"
#include "mat.hpp"
#include "operator.hpp"

namespace kmuvcl
{
    namespace math
    {
#ifndef M_PI
        const float M_PI = 3.14159265358979323846;
#endif

        template <typename T>
        mat<4, 4, T> translate(T dx, T dy, T dz)
        {
            mat<4, 4, T> translateMat;

            // TODO: Fill up this function properly 
			for (int i = 0; i < 4; i++)
				translateMat(i, i) = 1.0;

			translateMat(0, 3) = dx;
			translateMat(1, 3) = dy;
			translateMat(2, 3) = dz;

            return translateMat;
        }

        template <typename T>
        mat<4, 4, T> rotate(T angle, T x, T y, T z)
        {
            mat<4, 4, T> rotateMat;

            // TODO: Fill up this function properly 
			T rad = angle * (M_PI / 180.0);
			T r = sqrt(x*x + y*y + z*z);
			
			x = x / r;
			y = y / r;
			z = z / r;

			rotateMat(0, 0) = cos(rad) + (x*x*(1.0 - cos(rad)));
			rotateMat(1, 0) = (y*x*(1.0 - cos(rad))) + (z*sin(rad));
			rotateMat(2, 0) = z*x*(1.0 - cos(rad)) - y*sin(rad);
			rotateMat(0, 1) = x*y*(1.0 - cos(rad)) - z*sin(rad);
			rotateMat(1, 1) = cos(rad) + y*y*(1 - cos(rad));
			rotateMat(2, 1) = z*y*(1.0 - cos(rad)) + x*sin(rad);
			rotateMat(0, 2) = x*z*(1.0 - cos(rad)) + y*sin(rad);
			rotateMat(1, 2) = y*z*(1.0 - cos(rad)) - x*sin(rad);
			rotateMat(2, 2) = cos(rad) + z*z*(1.0 - cos(rad));
			rotateMat(3, 3) = 1.0;

            return rotateMat;
        }

        template<typename T>
        mat<4, 4, T> scale(T sx, T sy, T sz)
        {
            mat<4, 4, T> scaleMat;

            // TODO: Fill up this function properly 
			scaleMat(0, 0) = sx;
			scaleMat(1, 1) = sy;
			scaleMat(2, 2) = sz;
			scaleMat(3, 3) = 1.0;

            return scaleMat;
        }

        template<typename T>
        mat<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
        {
            mat<4, 4, T> viewMat;

            // TODO: Fill up this function properly 
			mat<4, 4, T> posMat;
			for (int i = 0; i < 4; i++)
				posMat(i, i) = 1.0;
			posMat(0, 3) = -1 * eyeX;
			posMat(1, 3) = -1 * eyeY;
			posMat(2, 3) = -1 * eyeZ;

			vec<3,T> vecZ;

			vecZ(0) = eyeX - centerX;
			vecZ(1) = eyeY - centerY;
			vecZ(2) = eyeZ - centerZ;
			T r = sqrt(vecZ(0)*vecZ(0) + vecZ(1)*vecZ(1) + vecZ(2)*vecZ(2));

			vecZ(0) /= r;
			vecZ(1) /= r;
			vecZ(2) /= r;

			vec<3,T> vecUp;
			vecUp(0) = upX;
			vecUp(1) = upY;
			vecUp(2) = upZ;

			
			vec<3,T> vecX = cross(vecUp, vecZ);

			r = sqrt(vecX(0)*vecX(0) + vecX(1)*vecX(1) + vecX(2)*vecX(2));
			vecX(0) /= r;
			vecX(1) /= r;
			vecX(2) /= r;

			vec<3,T> vecY = cross(vecZ, vecX);

			r = sqrt(vecY(0)*vecY(0) + vecY(1)*vecY(1) + vecY(2)*vecY(2));
			vecY(0) /= r;
			vecY(1) /= r;
			vecY(2) /= r;

			mat<4, 4, T> axisMat;

			for (int i = 0; i < 3; i++)
				axisMat(0, i) = vecX(i);
			for (int i = 0; i < 3; i++)
				axisMat(1, i) = vecY(i);
			for (int i = 0; i < 3; i++)
				axisMat(2, i) = vecZ(i);
			axisMat(3, 3) = 1.0;

			viewMat = axisMat * posMat;


            return viewMat;
        }

        template<typename T>
        mat<4, 4, T> ortho(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
            mat<4, 4, T> orthoMat;
            
            // TODO: Fill up this function properly 
			orthoMat(0, 0) = 2.0 / (right - left);
			orthoMat(1, 1) = 2.0 / (top - bottom);
			orthoMat(2, 2) = -2.0 / (farVal - nearVal);
			orthoMat(3, 3) = 1.0;
			orthoMat(0, 3) = -(right + left) / (right - left);
			orthoMat(1, 3) = -(top + bottom) / (top - bottom);
			orthoMat(2, 3) = -(farVal + nearVal) / (farVal - nearVal);

            return orthoMat;
        }

        template<typename T>
        mat<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
           mat<4, 4, T> frustumMat;

           // TODO: Fill up this function properly 
		   frustumMat(0, 0) = (2 * nearVal) / (right - left);
		   frustumMat(1, 1) = (2 * nearVal) / (top - bottom);
		   frustumMat(0, 2) = (right + left) / (right - left);
		   frustumMat(1, 2) = (top + bottom) / (top - bottom);
		   frustumMat(2, 2) = -(farVal + nearVal) / (farVal - nearVal);
		   frustumMat(3, 2) = -1.0;
		   frustumMat(2, 3) = -(2 * farVal*nearVal) / (farVal - nearVal);

           return frustumMat;
        }

        template<typename T>
        mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar)
        {
          T  right, top;

          // TODO: Fill up this function properly 
		  
		  T rad = fovy * (M_PI / 180.0) / 2;

		  top = zNear * tan(rad);
		  right = aspect * top;

          return frustum(-right, right, -top, top, zNear, zFar);
        }
    }
}
#endif
