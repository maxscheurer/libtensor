#ifndef LIBTENSOR_LABELED_BTENSOR_EXPR_DIAG_CORE_H
#define LIBTENSOR_LABELED_BTENSOR_EXPR_DIAG_CORE_H

#include <libtensor/exception.h>
#include <libtensor/core/sequence.h>
#include "../expr_exception.h"
#include "../letter.h"
#include "../letter_expr.h"
#include "../labeled_btensor_expr.h" // for g_ns

namespace libtensor {
namespace labeled_btensor_expr {


template<size_t N, size_t M, typename T> class diag_eval;


/** \brief Expression core for the extraction of a diagonal
    \tparam N Tensor order.
    \tparam M Diagonal order.

    \ingroup libtensor_btensor_expr
 **/
template<size_t N, size_t M, typename T>
class diag_core {
public:
    static const char k_clazz[]; //!< Class name

public:
    //! Evaluating container type
    typedef diag_eval<N, M, T> eval_container_t;

private:
    const letter &m_diag_let; //!< Diagonal letter
    letter_expr<M> m_diag_lab; //!< Indexes defining a diagonal
    expr<N, T> m_subexpr; //!< Sub-expression
    sequence<N - M + 1, const letter*> m_defout; //!< Default output label

public:
    /** \brief Creates the expression core
        \param diag_letter Letter in the output.
        \param diag_label Expression defining the diagonal.
        \param subexpr Sub-expression.
     **/
    diag_core(const letter &diag_letter, const letter_expr<M> &diag_label,
        const expr<N, T> &subexpr);

    /** \brief Returns the diagonal letter
     **/
    const letter &get_diag_letter() const {
        return m_diag_let;
    }

    /** \brief Returns the diagonal indexes
     **/
    const letter_expr<M> &get_diag_label() const {
        return m_diag_lab;
    }

    /** \brief Returns the sub-expression
     **/
    expr<N, T> &get_sub_expr() {
        return m_subexpr;
    }

    /** \brief Returns the sub-expression, const version
     **/
    const expr<N, T> &get_sub_expr() const {
        return m_subexpr;
    }

    /** \brief Returns whether the result's label contains a %letter
        \param let Letter.
     **/
    bool contains(const letter &let) const;

    /** \brief Returns the index of a letter in the result's label
        \param let Letter.
        \throw expr_exception If the label does not contain the
            requested letter.
     **/
    size_t index_of(const letter &let) const;

    /** \brief Returns the letter at a given position in the result's label
        \param i Letter index.
        \throw out_of_bounds If the index is out of bounds.
     **/
    const letter &letter_at(size_t i) const;

};


template<size_t N, size_t M, typename T>
const char diag_core<N, M, T>::k_clazz[] = "diag_core<N, M, T>";


template<size_t N, size_t M, typename T>
diag_core<N, M, T>::diag_core(const letter &diag_letter,
    const letter_expr<M> &diag_label, const expr<N, T> &subexpr) :

    m_diag_let(diag_letter), m_diag_lab(diag_label), m_subexpr(subexpr),
    m_defout(0) {

    static const char method[] =
        "diag_core(const letter&, const letter_expr<M>&, const expr<N, T>&)";

    for(size_t i = 0; i < M - 1; i++) {
        for(size_t j = i + 1; j < M; j++) {
            if(m_diag_lab.letter_at(i) == m_diag_lab.letter_at(j)) {
                throw expr_exception(g_ns, k_clazz, method, __FILE__, __LINE__,
                    "Repetitive indexes.");
            }
        }
    }
    for(size_t i = 0; i < M; i++) {
        if(!m_expr.contains(m_diag_lab.letter_at(i))) {
            throw expr_exception(g_ns, k_clazz, method, __FILE__, __LINE__,
                "Bad index in diagonal.");
        }
    }

    size_t j = 0;
    bool first = true;
    for(size_t i = 0; i < N; i++) {
        const letter &l = m_expr.letter_at(i);
        bool indiag = m_diag_lab.contains(l);
        if(!indiag) m_defout[j++] = &l;
        else if(first && indiag) {
            m_defout[j++] = &m_diag_let;
            first = false;
        }
    }
}


template<size_t N, size_t M, typename T>
bool diag_core<N, M, T>::contains(const letter &let) const {

    for(register size_t i = 0; i < N - M + 1; i++) {
        if(m_defout[i] == &let) return true;
    }
    return false;
}


template<size_t N, size_t M, typename T>
size_t diag_core<N, M, T>::index_of(const letter &let) const {

    static const char method[] = "index_of(const letter&)";

    for(register size_t i = 0; i < N - M + 1; i++) {
        if(m_defout[i] == &let) return i;
    }

    throw expr_exception(g_ns, k_clazz, method, __FILE__, __LINE__,
        "Bad letter.");
}


template<size_t N, size_t M, typename T>
const letter &diag_core<N, M, T>::letter_at(size_t i) const {

    static const char method[] = "letter_at(size_t)";

    if(i >= N - M + 1) {
        throw out_of_bounds(g_ns, k_clazz, method, __FILE__, __LINE__,
            "Letter index is out of bounds.");
    }
    return *(m_defout[i]);
}


} // namespace labeled_btensor_expr
} // namespace libtensor

#endif // LIBTENSOR_LABELED_BTENSOR_EXPR_DIAG_CORE_H
