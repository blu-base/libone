
#include <cppunit/extensions/HelperMacros.h>

#include <cppunit/TestAssert.h>

#include <tuple>

#include "GUIDTest.h"
#include "../../lib/GUID.h"


CppUnit::Test *GUIDTest::suite()
{
  CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("GUIDTest");

  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID constructor", &GUIDTest::test_constructor));
  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID to_string", &GUIDTest::test_to_string));
  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID from_string", &GUIDTest::test_from_string));
  testSuite->addTest(new CppUnit::TestCaller<GUIDTest>("GUID is_equal", &GUIDTest::test_is_equal));

  return testSuite;
}



void GUIDTest::setUp()
{
}

void GUIDTest::tearDown()
{}

void GUIDTest::test_constructor()
{
  libone::GUID guid {};

  CppUnit::Asserter::failIf(guid.data1() !=0u, "", CPPUNIT_SOURCELINE());
  CppUnit::Asserter::failIf(guid.data2() !=0u, "", CPPUNIT_SOURCELINE());
  CppUnit::Asserter::failIf(guid.data3() !=0u, "", CPPUNIT_SOURCELINE());
  CppUnit::Asserter::failIf(guid.data4().at(0) !=0u, "", CPPUNIT_SOURCELINE());
  CppUnit::Asserter::failIf(guid.data4().at(1) !=0u, "", CPPUNIT_SOURCELINE());
  CppUnit::Asserter::failIf(guid.data4().at(2) !=0u, "", CPPUNIT_SOURCELINE());
  CppUnit::Asserter::failIf(guid.data4().at(3) !=0u, "", CPPUNIT_SOURCELINE());

}

void GUIDTest::test_to_string()
{
  std::vector<std::tuple<std::string, uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t> > cases {};

  cases.emplace_back("{00000000-0000-0000-0000-000000000000}", 0, 0, 0, 0, 0, 0, 0);
  cases.emplace_back("00000000-0000-0000-0000-000000000000", 0, 0, 0, 0, 0, 0,0);
  cases.emplace_back("00000000000000000000000000000000", 0, 0, 0, 0, 0, 0, 0);
  cases.emplace_back("{FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF}", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  cases.emplace_back("{7B5C52E4-D88C-4DA7-AEB1-5378D02996D3}", 0X7b5c52e4, 0Xd88c, 0X4da7, 0Xaeb1, 0X5378, 0Xd029, 0X96d3);
  cases.emplace_back("FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  cases.emplace_back("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  // failing parsing
  cases.emplace_back("FF", 0, 0, 0, 0, 0, 0, 0);




  for (size_t i {0}; i < cases.size(); i++)
  {
    auto entry = cases.at(i);
    libone::GUID guid;
    guid.from_string(std::get<0>(entry));

    CPPUNIT_NS::assertEquals(std::get<1>(entry), guid.data1(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data1");
    CPPUNIT_NS::assertEquals(std::get<2>(entry), guid.data2(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data2");
    CPPUNIT_NS::assertEquals(std::get<3>(entry), guid.data3(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data3");
    CPPUNIT_NS::assertEquals(std::get<4>(entry), guid.data4().at(0), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data4[0]");
    CPPUNIT_NS::assertEquals(std::get<5>(entry), guid.data4().at(1), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data4[1]");
    CPPUNIT_NS::assertEquals(std::get<6>(entry), guid.data4().at(2), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data4[2]");
    CPPUNIT_NS::assertEquals(std::get<7>(entry), guid.data4().at(3), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " data4[3]");
  }
}

void GUIDTest::test_from_string()
{
  std::vector<std::tuple<std::string, uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t> > cases {};

  cases.emplace_back("{00000000-0000-0000-0000-000000000000}", 0, 0, 0, 0, 0, 0, 0);
  cases.emplace_back("{ffffffff-ffff-ffff-ffff-ffffffffffff}", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
  cases.emplace_back("{7b5c52e4-d88c-4da7-aeb1-5378d02996d3}", 0X7b5c52e4, 0Xd88c, 0X4da7, 0Xaeb1, 0X5378, 0Xd029, 0X96d3);


  for (size_t i {0}; i < cases.size(); i++)
  {
    auto entry = cases.at(i);
    libone::GUID guid(
      std::get<1>(entry),
      std::get<2>(entry),
      std::get<3>(entry),
      std::get<4>(entry),
      std::get<5>(entry),
      std::get<6>(entry),
      std::get<7>(entry));

    CPPUNIT_NS::assertEquals(std::get<0>(entry), guid.to_string(), CPPUNIT_SOURCELINE(), "test case#" + std::to_string(i));
  }


}

void GUIDTest::test_is_equal()
{

  libone::GUID guid1{};

  libone::GUID guid2(0,0,0,0,0,0,0);



  CPPUNIT_NS::Asserter::failIf(guid1 != guid2, "compare zerod guids", CPPUNIT_SOURCELINE());


}
