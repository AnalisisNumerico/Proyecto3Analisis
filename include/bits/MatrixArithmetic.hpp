/*
 * Copyright (C) 2017 
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: Pablo Alvarado
 * @Date:   28.12.2017
 */

#ifndef ANPI_MATRIX_ARITHMETIC_HPP
#define ANPI_MATRIX_ARITHMETIC_HPP

#include "Intrinsics.hpp"
#include <type_traits>
#include <iostream>
#include <vector>

namespace anpi
{
  namespace fallback {
    /*
     * Sum
     */

    // Fallback implementation
    
    // In-copy implementation c=a+b
    template<typename T,class Alloc>
    inline void add(const Matrix<T,Alloc>& a,
                    const Matrix<T,Alloc>& b,
                    Matrix<T,Alloc>& c) {

      assert( (a.rows() == b.rows()) &&
              (a.cols() == b.cols()) );

      const size_t tentries = a.rows()*a.dcols();
      c.allocate(a.rows(),a.cols());
      
      T* here        = c.data();
      T *const end   = here + tentries;
      const T* aptr = a.data();
      const T* bptr = b.data();

      for (;here!=end;) {
        *here++ = *aptr++ + *bptr++;
      }
    }

    // In-place implementation a = a+b
    template<typename T,class Alloc>
    inline void add(Matrix<T,Alloc>& a,
                    const Matrix<T,Alloc>& b) {

      assert( (a.rows() == b.rows()) &&
              (a.cols() == b.cols()) );

      const size_t tentries = a.rows()*a.dcols();
      
      T* here        = a.data();
      T *const end   = here + tentries;
      
      const T* bptr = b.data();

      for (;here!=end;) {
        *here++ += *bptr++;
      }
    }


    /*
     * Subtraction
     */

    // Fall back implementations

    // In-copy implementation c=a-b
    template<typename T,class Alloc>
    inline void subtract(const Matrix<T,Alloc>& a,
                         const Matrix<T,Alloc>& b,
                         Matrix<T,Alloc>& c) {

      assert( (a.rows() == b.rows()) &&
              (a.cols() == b.cols()) );

      const size_t tentries = a.rows()*a.dcols();
      c.allocate(a.rows(),a.cols());
      
      T* here        = c.data();
      T *const end   = here + tentries;
      const T* aptr = a.data();
      const T* bptr = b.data();

      for (;here!=end;) {
        *here++ = *aptr++ - *bptr++;

      }
    }

    // In-place implementation a = a-b
    template<typename T,class Alloc>
    inline void subtract(Matrix<T,Alloc>& a,
                         const Matrix<T,Alloc>& b) {

      assert( (a.rows() == b.rows()) &&
              (a.cols() == b.cols()) );
      
      const size_t tentries = a.rows()*a.dcols();
      
      T* here        = a.data();
      T *const end   = here + tentries;
      
      const T* bptr = b.data();

      for (;here!=end;) {
        *here++ -= *bptr++;
      }
    }


      /*
     * Product
     */

      // Fall back implementations

      // In-copy implementation c = a*b
      template<typename T,class Alloc>
      inline void product(const Matrix<T,Alloc>& a,
                           const std::vector<T>& b,
                          std::vector<T>& c) {

          for(size_t i=0;i<a.rows();++i){
              T sum=T();
              for(size_t k=0;k<b.size();++k){
                  sum+=a(i,k)*b[k];
              }
              c[i]=sum;
          }
      }
      // In-place implementation a = a*b
      template<typename T,class Alloc>
      inline void product(Matrix<T,Alloc>& a,
                           const std::vector<T>& b) {

          ::anpi::fallback::product(a,b,b);

      }

      // In-place implementation a = a*b
      template<typename T,class Alloc>
      inline void product(Matrix<T,Alloc>& a,
                          const Matrix<T,Alloc>& b) {

          Matrix<T,Alloc> c(a.rows(),b.cols());
          c.allocate(a.rows(),b.cols());

          int aRows = a.rows();
          int aCols = a.cols();
          int bCols = b.cols();

          for(int row = 0; row < aRows; row++) {
              for(int column = 0; column < bCols; column++) {
                  for(int index = 0; index < aCols; index++) {
                      c[row][column] += a[row][index] * b[index][column];
                  }
              }
          }

          a=std::move(c);

      }


      // In-copy implementation c = a * b
      template<typename T,class Alloc>
      inline void product(const Matrix<T,Alloc>& a,
                          const Matrix<T,Alloc>& b,
                          Matrix<T,Alloc>& c) {

          c.allocate(a.rows(),b.cols());

          int aRows = a.rows();
          int aCols = a.cols();
          int bCols = b.cols();

          for(int row = 0; row < aRows; row++) {
              for(int column = 0; column < bCols; column++) {
                  for(int index = 0; index < aCols; index++) {
                      c[row][column] += a[row][index] * b[index][column];
                  }
              }
          }

      }


      /*
   * Fill
   */

      // Fall back implementations

      // In-copy implementation fill
      template<typename T,class Alloc>
      inline void fill(const T val, Matrix<T,Alloc>& a) {
          T* end = a.data() + ( a.rows() * a.dcols() );
          for (T* ptr = a.data();ptr!=end;++ptr) {
              *ptr = val;
          }
      }


  } // namespace fallback


  namespace simd
  {



      /*
       * Sum
       */

    /*
     * The following code exemplifies how to manually accelerate code using
     * SIMD instructions.  However, for the simple element-wise algorithms
     * like sum or subtraction, modern compilers can automatically vectorize
     * the code, as the benchmarks show.
     */


    /// We wrap the intrinsics methods to be polymorphic versions
    template<typename T,class regType>
    regType mm_add(regType,regType); // We don't implement this to cause, at
                                     // least, a linker error if this version is
                                     // used.
    //{
    // Generic function should never be called.
    // If it is called, then some SIMD chaos is going on...
    
    // A way to cause a compile time error would be better
    // throw std::bad_function_call();
    // return regType();
    //}
  template<typename T, class regType>
  regType mm_div(regType, regType);
  template<typename T, class regType>
  regType mm_sub(regType, regType);
  template<typename T, class regType>
  regType mm_mul(regType, regType);

  template<typename T, class regType>
  regType mm_set1(const T);



#ifdef __SSE2__
    template<>
    inline __m128d __attribute__((__always_inline__))
    mm_add<double>(__m128d a,__m128d b) {
      return _mm_add_pd(a,b);
    }
    template<>
    inline __m128 __attribute__((__always_inline__))
    mm_add<float>(__m128 a,__m128 b) {
      return _mm_add_ps(a,b);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_add<std::uint64_t>(__m128i a,__m128i b) {
      return _mm_add_epi64(a,b);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_add<std::int64_t>(__m128i a,__m128i b) {
      return _mm_add_epi64(a,b);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_add<std::uint32_t>(__m128i a,__m128i b) {
      return _mm_add_epi32(a,b);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_add<std::int32_t>(__m128i a,__m128i b) {
      return _mm_add_epi16(a,b);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_add<std::uint16_t>(__m128i a,__m128i b) {
      return _mm_add_epi16(a,b);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_add<std::int16_t>(__m128i a,__m128i b) {
      return _mm_add_epi32(a,b);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_add<std::uint8_t>(__m128i a,__m128i b) {
      return _mm_add_epi16(a,b);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_add<std::int8_t>(__m128i a,__m128i b) {
      return _mm_add_epi32(a,b);
    }


    ///SET
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_set1<short>(short a) {
        return _mm_set1_epi16(a);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_set1<int>(int a) {
        return _mm_set1_epi32(a);
    }
    template<>
    inline __m128i __attribute__((__always_inline__))
    mm_set1<char>(char a) {
        return _mm_set1_epi8(a);
    }
    template<>
    inline __m128d __attribute__((__always_inline__))
    mm_set1<double>(double a) {
        return _mm_set1_pd(a);
    }
    template<>
    inline __m128 __attribute__((__always_inline__))
    mm_set1<float>(float a) {
        return _mm_set1_ps(a);
    }

    ///SUB
    template<>
    inline __m128d __attribute__((__always_inline__))
    mm_sub<double>(__m128d a,__m128d b) {
        return _mm_sub_pd(a,b);
    }
        template<>
        inline __m128 __attribute__((__always_inline__))
        mm_sub<float>(__m128 a,__m128 b) {
            return _mm_sub_ps(a,b);
        }
        template<>
        inline __m128i __attribute__((__always_inline__))
        mm_sub<std::uint64_t>(__m128i a,__m128i b) {
            return _mm_sub_epi64(a,b);
        }
        template<>
        inline __m128i __attribute__((__always_inline__))
        mm_sub<std::int64_t>(__m128i a,__m128i b) {
            return _mm_sub_epi64(a,b);
        }
        template<>
        inline __m128i __attribute__((__always_inline__))
        mm_sub<std::uint32_t>(__m128i a,__m128i b) {
            return _mm_sub_epi32(a,b);
        }
        template<>
        inline __m128i __attribute__((__always_inline__))
        mm_sub<std::int32_t>(__m128i a,__m128i b) {
            return _mm_sub_epi16(a,b);
        }
        template<>
        inline __m128i __attribute__((__always_inline__))
        mm_sub<std::uint16_t>(__m128i a,__m128i b) {
            return _mm_sub_epi16(a,b);
        }
        template<>
        inline __m128i __attribute__((__always_inline__))
        mm_sub<std::int16_t>(__m128i a,__m128i b) {
            return _mm_sub_epi32(a,b);
        }
        template<>
        inline __m128i __attribute__((__always_inline__))
        mm_sub<std::uint8_t>(__m128i a,__m128i b) {
            return _mm_sub_epi16(a,b);
        }
        template<>
        inline __m128i __attribute__((__always_inline__))
        mm_sub<std::int8_t>(__m128i a,__m128i b) {
            return _mm_sub_epi32(a,b);
        }

    ///Div
    template<>
    inline __m128d __attribute__((__always_inline__))
    mm_div<double>(__m128d a,__m128d b) {
        return _mm_div_pd(a,b);
    }
    template<>
    inline __m128 __attribute__((__always_inline__))
    mm_div<float>(__m128 a,__m128 b) {
        return _mm_div_ss(a,b);
    }

    ///Mul
    template<>
    inline __m128d __attribute__((__always_inline__))
    mm_mul<double>(__m128d a,__m128d b) {
        return _mm_mul_pd(a,b);
    }
    template<>
    inline __m128 __attribute__((__always_inline__))
    mm_mul<float>(__m128 a,__m128 b) {
        return _mm_mul_ps(a,b);
    }


#endif


    // On-copy implementation c=a+b
    template<typename T,class Alloc,typename regType>
    inline void addSIMD(const Matrix<T,Alloc>& a,
                        const Matrix<T,Alloc>& b,
                        Matrix<T,Alloc>& c) {

      // This method is instantiated with unaligned allocators.  We
      // allow the instantiation although externally this is never
      // called unaligned
      static_assert(!extract_alignment<Alloc>::aligned ||
		    (extract_alignment<Alloc>::value >= sizeof(regType)),
		    "Insufficient alignment for the registers used");

      const size_t tentries = a.rows()*a.dcols();
      c.allocate(a.rows(),a.cols());

      regType* here        = reinterpret_cast<regType*>(c.data());
      const size_t  blocks = ( tentries*sizeof(T) + (sizeof(regType)-1) )/
        sizeof(regType);
      regType *const end   = here + blocks;

      const regType* aptr  = reinterpret_cast<const regType*>(a.data());
      const regType* bptr  = reinterpret_cast<const regType*>(b.data());

      for (;here!=end;) {
        *here++ = mm_add<T>(*aptr++,*bptr++);
      }

    }

    // On-copy implementation c=a+b for SIMD-capable types
    template<typename T,
	     class Alloc,
	     typename std::enable_if<is_simd_type<T>::value,int>::type=0>
    inline void add(const Matrix<T,Alloc>& a,
                    const Matrix<T,Alloc>& b,
                    Matrix<T,Alloc>& c) {

      assert( (a.rows() == b.rows()) &&
              (a.cols() == b.cols()) );


      if (is_aligned_alloc<Alloc>::value) {
#ifdef __SSE2__
        addSIMD<T,Alloc,typename sse2_traits<T>::reg_type>(a,b,c);
#else
        ::anpi::fallback::add(a,b,c);
#endif
      } else { // allocator seems to be unaligned
        ::anpi::fallback::add(a,b,c);
      }
    }

    // Non-SIMD types such as complex
    template<typename T,
             class Alloc,
             typename std::enable_if<!is_simd_type<T>::value,int>::type = 0>
    inline void add(const Matrix<T,Alloc>& a,
                    const Matrix<T,Alloc>& b,
                    Matrix<T,Alloc>& c) {

      ::anpi::fallback::add(a,b,c);
    }

    // In-place implementation a = a+b
    template<typename T,class Alloc>
    inline void add(Matrix<T,Alloc>& a, const Matrix<T,Alloc>& b) {

      add(a,b,a);
    }


        ///the following code is ger534 trying to understand SIMD instructions
        ///necesito agregar al set de instrucciones las de multiplicacion???

        // On-copy implementation fill
        template<typename T,class Alloc,typename regType>
        inline void fillSIMD(T val, Matrix<T,Alloc>& a) {

            // This method is instantiated with unaligned allocators.  We
            // allow the instantiation although externally this is never
            // called unaligned
            static_assert(!extract_alignment<Alloc>::aligned ||
                          (extract_alignment<Alloc>::value >= sizeof(regType)),
                          "Insufficient alignment for the registers used");

            const size_t tentries = a.rows()*a.dcols();

            regType* here        = reinterpret_cast<regType*>(a.data());

            const size_t  blocks = ( tentries*sizeof(T) + (sizeof(regType)-1) )/
                                   sizeof(regType);
            regType *const end   = here + blocks;

            for (;here!=end;) {

                *here++ = mm_set1<T,regType>(val);
            }

        }


        // On-copy implementation fill for SIMD-capable types
        template<typename T,
                class Alloc,
                typename std::enable_if<is_simd_type<T>::value,int>::type=0>
        inline void fill(const T val, Matrix<T,Alloc>& a) {


            if (is_aligned_alloc<Alloc>::value) {
#ifdef __SSE2__
                fillSIMD<T,Alloc,typename sse2_traits<T>::reg_type>(val, a);
#else
                ::anpi::fallback::fill(val, a);
#endif
            } else { // allocator seems to be unaligned
                ::anpi::fallback::fill(val, a);  ///ERROR
            }
        }

        // Non-SIMD types such as complex
        template<typename T,
                class Alloc,
                typename std::enable_if<!is_simd_type<T>::value,int>::type = 0>
        inline void fill(const T val, Matrix<T,Alloc>& a) {
            ::anpi::fallback::fill(val, a);
        }

        /*
         * Subtraction
         */

    // Fall back implementations

    // In-copy implementation c=a-b
    template<typename T,class Alloc>
    inline void subtract(const Matrix<T,Alloc>& a,
                         const Matrix<T,Alloc>& b,
                         Matrix<T,Alloc>& c) {
      ::anpi::fallback::subtract(a,b,c);
    }

    // In-place implementation a = a-b
    template<typename T,class Alloc>
    inline void subtract(Matrix<T,Alloc>& a,
                         const Matrix<T,Alloc>& b) {

      ::anpi::fallback::subtract(a,b);
    }

        ///para el vector

        // In-copy implementation c=a*b
        template<typename T,class Alloc>
        inline void product(const Matrix<T,Alloc>& a,
                            const std::vector<T>& b,
                            std::vector<T>& c) {
            ::anpi::fallback::product(a,b,c);
        }

        // In-place implementation a = a*b
        template<typename T,class Alloc>
        inline void product(Matrix<T,Alloc>& a,
                            const std::vector<T>& b) {
            //::anpi::fallback::product(a,b,b);
            //::anpi::fallback::product(a,b,a);
        }

        template<typename T,class Alloc>
        // In-place implementation c = a*b
        inline void product(const Matrix<T,Alloc>& a,
                            const Matrix<T,Alloc>& b,
                            Matrix<T,Alloc>& c) {
            ::anpi::fallback::product(a,b,c);
        }

        template<typename T,class Alloc>
        // In-copy implementation a = a*b
        inline void product(Matrix<T,Alloc>& a,
                            const Matrix<T,Alloc>& b) {
            ::anpi::fallback::product(a,b);
        }

    } // namespace simd


  // The arithmetic implementation (aimpl) namespace
  // dispatches to the corresponding methods
#ifdef ANPI_ENABLE_SIMD
  namespace aimpl=simd;
#else
  namespace aimpl=fallback;
#endif
  
} // namespace anpi

#endif
