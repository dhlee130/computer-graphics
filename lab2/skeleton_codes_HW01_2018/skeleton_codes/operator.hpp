#ifndef KMUVCL_GRAPHICS_OPERATOR_HPP
#define KMUVCL_GRAPHICS_OPERATOR_HPP

#include "vec.hpp"
#include "mat.hpp"

namespace kmuvcl {
  namespace math {

    /// y_n = s * x_n
    template <unsigned int N, typename T>
    vec<N, T> operator* (const T s, const vec<N, T>& x)
    {
      // TODO: Fill up this function properly 
      vec<N, T>  y;
      
      return  y;
    }

    /// s = u_n * v_n (dot product)
    template <unsigned int N, typename T>
    T dot(const vec<N, T>& u, const vec<N, T>& v)
    {
      // TODO: Fill up this function properly
      T val = 0;
      
      return  val;
    }

    /// w_3 = u_3 x v_3 (cross product, only for vec3)
    template <typename T>
    vec<3,T> cross(const vec<3, T>& u, const vec<3, T>& v)
    {
      // TODO: Fill up this function properly 
      vec<3, T>  w;

      return  w;
    }

    /// y_m = A_{mxn} * x_n
    template <unsigned int M, unsigned int N, typename T>
    vec<M, T> operator* (const mat<M, N, T>& A, const vec<N, T>& x)
    {
      // TODO: Fill up this function properly 
      vec<M, T>   y, col;

      return  y;
    }

    /// y_n = x_m * A_{mxn}
    template <unsigned int M, unsigned int N, typename T>
    vec<N, T> operator* (const vec<M, T>& x, const mat<M, N, T>& A)
    {
      // TODO: Fill up this function properly 
      vec<N, T>   y;
      
      return  y;
    }

    /// C_{mxl} = A_{mxn} * B_{nxl}
    template <unsigned int M, unsigned int N, unsigned int L, typename T>
    mat<M, L, T> operator* (const mat<M, N, T>& A, const mat<N, L, T>& B)
    {
      // TODO: Fill up this function properly 
      mat<M, L, T>   C;
      
      return  C;
    }

    /// ostream for vec class
    template <unsigned int N, typename T>
    std::ostream& operator << (std::ostream& os, const vec<N, T>& v)
    {
      // TODO: Fill up this function properly 

      return  os;
    }

    /// ostream for mat class
    template <unsigned int M, unsigned int N, typename T>
    std::ostream& operator << (std::ostream& os, const mat<M, N, T>& A)
    {
      // TODO: Fill up this function properly 

      return  os;
    }

  } // math
} // kmuvcl

#endif // KMUVCL_GRAPHICS_OPERATOR_HPP
