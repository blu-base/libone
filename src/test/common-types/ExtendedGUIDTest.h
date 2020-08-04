#ifndef EXTENDEDGUIDTEST_H
#define EXTENDEDGUIDTEST_H

#include <cppunit/TestCase.h>

class ExtendedGUIDTest : public CppUnit::TestCase
{
public:
  static CppUnit::Test *suite();

  void setUp();
  void tearDown();

  void test_constructor();
  void test_to_string();
  void test_from_string();
  void test_is_equal();

};

#endif // EXTENDEDGUIDTEST_H
