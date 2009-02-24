#ifndef __LIBTENSOR_TENSOR_OPERATION_HANDLER_H
#define __LIBTENSOR_TENSOR_OPERATION_HANDLER_H

#include "defs.h"
#include "exception.h"

namespace libtensor {

/**	\brief Base class for tensor operation handlers

	\ingroup libtensor
**/
template<typename _T>
class tensor_operation_handler {
public:
	typedef _T element_t; //!< Tensor element type

public:
	virtual element_t *req_dataptr(const permutation &p) throw(exception);

	virtual const element_t *req_const_dataptr(const permutation &p)
		throw(exception);

	virtual void ret_dataptr(const element_t *p) throw(exception);

	virtual const permutation &req_simplest_permutation() throw(exception);

	virtual size_t req_permutation_cost(const permutation &p)
		throw(exception);

private:
	/**	\brief Throws an exception
	**/
	void throw_exc(const char *method, const char *msg) const
		throw(exception);
};

#ifdef __INTEL_COMPILER
#pragma warning(disable:1011)
#endif

template<typename T>
T *tensor_operation_handler<T>::req_dataptr(const permutation &p)
	throw(exception) {
	throw_exc("tensor_operation_handler<T>::"
		"req_dataptr(const permutation&)", "Unhandled event");
}

template<typename T>
const T *tensor_operation_handler<T>::req_const_dataptr(const permutation &p)
	throw(exception) {
	throw_exc("tensor_operation_handler<T>::"
		"req_const_dataptr(const permutation&)", "Unhandled event");
}

template<typename T>
void tensor_operation_handler<T>::ret_dataptr(const T *p) throw(exception) {
	throw_exc("tensor_operation_handler<T>::"
		"ret_dataptr(const T*)", "Unhandled event");
}

template<typename T>
const permutation &tensor_operation_handler<T>::req_simplest_permutation()
	throw(exception) {
	throw_exc("tensor_operation_handler<T>::"
		"req_simplest_permutation()", "Unhandled event");
}

template<typename T>
size_t tensor_operation_handler<T>::req_permutation_cost(const permutation &p)
	throw(exception) {
	throw_exc("tensor_operation_handler<T>::"
		"req_permutation_cost(const permutation&)", "Unhandled event");
}

template<typename T>
void tensor_operation_handler<T>::throw_exc(const char *method,
	const char *msg) const throw(exception) {
	char s[1024];
	snprintf(s, 1024, "[libtensor::tensor_operation_handler<T>::%s] %s.",
		method, msg);
	throw exception(s);
}

} // namespace libtensor

#endif // __LIBTENSOR_TENSOR_OPERATION_HANDLER_H
