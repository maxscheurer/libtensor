#ifndef LIBTENSOR_CTF_SYMMETRY_IMPL_H
#define LIBTENSOR_CTF_SYMMETRY_IMPL_H

#include "../ctf.h"
#include "../ctf_symmetry.h"

namespace libtensor {


template<size_t N, typename T>
ctf_symmetry<N, T>::ctf_symmetry() {

    for(size_t i = 0; i < N; i++) {
        m_grp[i] = i;
        m_sym[i] = 0;
    }
}


template<size_t N, typename T>
ctf_symmetry<N, T>::ctf_symmetry(const sequence<N, unsigned> &grp,
    const sequence<N, unsigned> &sym) : m_grp(grp), m_sym(sym) {

}


template<size_t N, typename T>
void ctf_symmetry<N, T>::build(const transf_list<N, T> &trl) {

}


template<size_t N, typename T>
void ctf_symmetry<N, T>::permute(const permutation<N> &perm) {

    perm.apply(m_grp);
}


template<size_t N, typename T>
void ctf_symmetry<N, T>::write(int (&sym)[N]) const {

    sequence<N, unsigned> grp(0);
    for(size_t i = 0; i < N; i++) grp[i] = m_grp[N - 1 - i];
    size_t i = 0;
    size_t symidx = 0;
    while(i < N) {
        unsigned g = grp[i];
        size_t i0 = i;
        while(i < N && grp[i] == g) i++;
        sym[i0] = m_sym[g] == 0 ? SY : AS;
        for(size_t j = i0 + 1; j < i; j++) {
            sym[j] = NS;
            symidx++;
        }
    }
    if(symidx == 0) {
        for(size_t i = 0; i < N; i++) sym[i] = NS;
    }
}


} // namespace libtensor

#endif // LIBTENSOR_CTF_SYMMETRY_IMPL_H
