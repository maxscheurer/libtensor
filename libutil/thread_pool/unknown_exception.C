#include "unknown_exception.h"

namespace libutil {


const char *unknown_exception::k_what = "libutil::unknown_exception";


unknown_exception::~unknown_exception() {

}


const char *unknown_exception::what() const noexcept {

    return k_what;
}


rethrowable_i *unknown_exception::clone() const {

    try {
        return new unknown_exception;
    } catch(...) {
        return 0;
    }
}


void unknown_exception::rethrow() const {

    throw unknown_exception();
}


} // namespace libutil
