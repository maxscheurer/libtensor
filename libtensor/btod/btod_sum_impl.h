#ifndef LIBTENSOR_BTOD_SUM_IMPL_H
#define LIBTENSOR_BTOD_SUM_IMPL_H

#include "../core/orbit.h"
#include "../symmetry/so_add.h"
#include "../symmetry/so_copy.h"

namespace libtensor {


template<size_t N>
const char* btod_sum<N>::k_clazz = "btod_sum<N>";


template<size_t N>
inline btod_sum<N>::btod_sum(additive_btod<N> &op, double c) :
	m_bis(op.get_bis()), m_bidims(m_bis.get_block_index_dims()),
	m_sym(m_bis), m_dirty_sch(true), m_sch(0) {

	so_copy<N, double>(op.get_symmetry()).perform(m_sym);
	add_op(op, c);
}


template<size_t N>
btod_sum<N>::~btod_sum() {

	delete m_sch;
}


template<size_t N>
void btod_sum<N>::compute_block(tensor_i<N, double> &blk, const index<N> &i) {

	abs_index<N> ai(i, m_bidims);
	transf<N, double> tr0;

	tod_set<N>().perform(blk);

	for(typename std::list<node_t>::iterator iop = m_ops.begin();
		iop != m_ops.end(); iop++) {

		if(iop->get_op().get_schedule().contains(ai.get_abs_index())) {
			additive_btod<N>::compute_block(iop->get_op(), blk, i,
				tr0, iop->get_coeff());
		}
		else {
			const symmetry<N, double> &sym = iop->get_op().get_symmetry();
			orbit<N, double> orb(sym, i);
			abs_index<N> ci(orb.get_abs_canonical_index(), m_bidims);

			if(iop->get_op().get_schedule().contains(ci.get_abs_index())) {
				const transf<N, double> &tr = orb.get_transf(i);
				additive_btod<N>::compute_block(iop->get_op(), blk, ci.get_index(),
					tr, iop->get_coeff());
			}
		}
	}
}


template<size_t N>
void btod_sum<N>::compute_block(tensor_i<N, double> &blk, const index<N> &i,
	const transf<N, double> &tr, double c) {

	abs_index<N> ai(i, m_bidims);

	for(typename std::list<node_t>::iterator iop = m_ops.begin();
		iop != m_ops.end(); iop++) {

		if(iop->get_op().get_schedule().contains(ai.get_abs_index())) {
			additive_btod<N>::compute_block(iop->get_op(), blk, i,
				tr, c * iop->get_coeff());
		}
		else {
			const symmetry<N, double> &sym = iop->get_op().get_symmetry();
			orbit<N, double> orb(sym, i);
			abs_index<N> ci(orb.get_abs_canonical_index(), m_bidims);

			if(iop->get_op().get_schedule().contains(ci.get_abs_index())) {
				transf<N, double> tra(orb.get_transf(i));
				tra.transform(tr);

				additive_btod<N>::compute_block(iop->get_op(), blk, ci.get_index(),
					tra, c * iop->get_coeff());
			}
		}
	}
}


template<size_t N>
void btod_sum<N>::add_op(additive_btod<N> &op, double c) {

	static const char *method = "add_op(additive_btod<N>&, double)";

	if(!op.get_bis().equals(m_bis)) {
		throw bad_block_index_space(g_ns, k_clazz, method,
			__FILE__, __LINE__, "op");
	}
	if(c == 0.0) return;

	if(m_ops.empty()) {
		so_copy<N, double>(op.get_symmetry()).perform(m_sym);
	} else {
		symmetry<N, double> sym1(m_bis);
		permutation<N> perm0;
		so_add<N, double>(m_sym, perm0, op.get_symmetry(), perm0).
			perform(sym1);
		so_copy<N, double>(sym1).perform(m_sym);
	}
	m_ops.push_back(node_t(op, c));
}


template<size_t N>
void btod_sum<N>::make_schedule() const {

	delete m_sch;
	m_sch = new assignment_schedule<N, double>(m_bidims);

	for(typename std::list<node_t>::iterator iop = m_ops.begin();
		iop != m_ops.end(); iop++) {

		const assignment_schedule<N, double> &sch =
			iop->get_op().get_schedule();
		for(typename assignment_schedule<N, double>::iterator j =
			sch.begin(); j != sch.end(); j++) {

			if(!m_sch->contains(sch.get_abs_index(j))) {
				m_sch->insert(sch.get_abs_index(j));
			}
		}
	}

	m_dirty_sch = false;
}


} // namespace libtensor

#endif // LIBTENSOR_BTOD_SUM_IMPL_H