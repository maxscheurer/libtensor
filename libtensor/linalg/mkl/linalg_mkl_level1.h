#ifndef LIBTENSOR_LINALG_MKL_LEVEL1_H
#define LIBTENSOR_LINALG_MKL_LEVEL1_H

#include "../linalg_timings.h"
#include "../generic/linalg_generic_level1.h"

namespace libtensor {


/** \brief Level-1 linear algebra operations (MKL)

    \ingroup libtensor_linalg
 **/
class linalg_mkl_level1 :
    public linalg_generic_level1,
    public linalg_timings<linalg_mkl_level1> {

public:
    static const char *k_clazz; //!< Class name

public:
    static void add_i_i_x_x(
        void*,
        size_t ni,
        const double *a, size_t sia, double ka,
        double b, double kb,
        double *c, size_t sic,
        double d);

    static void copy_i_i(
        void*,
        size_t ni,
        const double *a, size_t sia,
        double *c, size_t sic);

    static void mul1_i_x(
        void*,
        size_t ni,
        double a,
        double *c, size_t sic);

    static double mul2_x_p_p(
        void*,
        size_t np,
        const double *a, size_t spa,
        const double *b, size_t spb);

    static void mul2_i_i_x(
        void*,
        size_t ni,
        const double *a, size_t sia,
        double b,
        double *c, size_t sic);

    static void mul2_i_i_i_x(
        void*,
        size_t ni,
        const double *a, size_t sia,
        const double *b, size_t sib,
        double *c, size_t sic,
        double d);

};


} // namespace libtensor

#endif // LIBTENSOR_LINALG_MKL_LEVEL1_H
