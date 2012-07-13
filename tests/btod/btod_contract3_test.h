#ifndef LIBTENSOR_BTOD_CONTRACT3_TEST_H
#define LIBTENSOR_BTOD_CONTRACT3_TEST_H

#include <libtest/unit_test.h>

namespace libtensor {


/** \brief Tests the libtensor::btod_contract3 class

    \ingroup libtensor_tests_btod
**/
class btod_contract3_test : public libtest::unit_test {
public:
    virtual void perform() throw(libtest::test_exception);

private:
    void test_contr_1();
    void test_contr_2();

};


} // namespace libtensor

#endif // LIBTENSOR_BTOD_CONTRACT3_TEST_H