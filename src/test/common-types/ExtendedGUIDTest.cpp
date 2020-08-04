
#include <cppunit/extensions/HelperMacros.h>

#include <cppunit/TestAssert.h>

#include <tuple>

#include "ExtendedGUIDTest.h"
#include "../../lib/ExtendedGUID.h"
#include "../../lib/GUID.h"


CppUnit::Test *ExtendedGUIDTest::suite()
{
  CppUnit::TestSuite *testSuite = new CppUnit::TestSuite("ExtendedGUIDTest");

  testSuite->addTest(new CppUnit::TestCaller<ExtendedGUIDTest>("ExtendedGUID constructor", &ExtendedGUIDTest::test_constructor));
  testSuite->addTest(new CppUnit::TestCaller<ExtendedGUIDTest>("ExtendedGUID to_string", &ExtendedGUIDTest::test_to_string));
  testSuite->addTest(new CppUnit::TestCaller<ExtendedGUIDTest>("ExtendedGUID from_string", &ExtendedGUIDTest::test_from_string));
  testSuite->addTest(new CppUnit::TestCaller<ExtendedGUIDTest>("ExtendedGUID is_equal", &ExtendedGUIDTest::test_is_equal));

  return testSuite;
}



void ExtendedGUIDTest::setUp()
{
}

void ExtendedGUIDTest::tearDown()
{}

void ExtendedGUIDTest::test_constructor()
{
  libone::ExtendedGUID eguid {};

  CPPUNIT_NS::assertEquals<uint32_t>(eguid.guid().data1(), 0, CPPUNIT_SOURCELINE(), "constructor 1, 0");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid.guid().data2(), 0, CPPUNIT_SOURCELINE(), "constructor 1, 1");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid.guid().data3(), 0, CPPUNIT_SOURCELINE(), "constructor 1, 2");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid.guid().data4().at(0), 0, CPPUNIT_SOURCELINE(), "constructor 1, 3");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid.guid().data4().at(1), 0, CPPUNIT_SOURCELINE(), "constructor 1, 4");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid.guid().data4().at(2), 0, CPPUNIT_SOURCELINE(), "constructor 1, 5");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid.guid().data4().at(3), 0, CPPUNIT_SOURCELINE(), "constructor 1, 6");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid.n(), 0, CPPUNIT_SOURCELINE(), "constructor 1, 7");


  libone::ExtendedGUID eguid2(libone::GUID(1,2,3,4,5,6,7), 8);

  CPPUNIT_NS::assertEquals<uint32_t>(eguid2.guid().data1(), 1, CPPUNIT_SOURCELINE(), "constructor 2, 0");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid2.guid().data2(), 2, CPPUNIT_SOURCELINE(), "constructor 2, 1");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid2.guid().data3(), 3, CPPUNIT_SOURCELINE(), "constructor 2, 2");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid2.guid().data4().at(0), 4, CPPUNIT_SOURCELINE(), "constructor 2, 3");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid2.guid().data4().at(1), 5, CPPUNIT_SOURCELINE(), "constructor 2, 4");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid2.guid().data4().at(2), 6, CPPUNIT_SOURCELINE(), "constructor 2, 5");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid2.guid().data4().at(3), 7, CPPUNIT_SOURCELINE(), "constructor 2, 6");
  CPPUNIT_NS::assertEquals<uint16_t>(eguid2.n(), 8, CPPUNIT_SOURCELINE(), "constructor 2, 7");


}

void ExtendedGUIDTest::test_to_string()
{
  // string, 7 values for m_guid, 1 value m_n
  std::vector<std::tuple<std::string, uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint32_t> > cases {};

  cases.emplace_back("{{00000000-0000-0000-0000-000000000000},0}", 0, 0, 0, 0, 0, 0, 0,0);
  cases.emplace_back("{{FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF},4294967295}", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFFFFFF);
  cases.emplace_back("{{7B5C52E4-D88C-4DA7-AEB1-5378D02996D3},255}", 0X7b5c52e4, 0Xd88c, 0X4da7, 0Xaeb1, 0X5378, 0Xd029, 0X96d3,0xFF);

  for (size_t i {0}; i < cases.size(); i++)
  {
    auto entry = cases.at(i);
    libone::ExtendedGUID eguid;
    eguid.from_string(std::get<0>(entry));

    CPPUNIT_NS::assertEquals(std::get<1>(entry), eguid.guid().data1(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " guid data1");
    CPPUNIT_NS::assertEquals(std::get<2>(entry), eguid.guid().data2(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " guid data2");
    CPPUNIT_NS::assertEquals(std::get<3>(entry), eguid.guid().data3(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " guid data3");
    CPPUNIT_NS::assertEquals(std::get<4>(entry), eguid.guid().data4().at(0), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " guid data4[0]");
    CPPUNIT_NS::assertEquals(std::get<5>(entry), eguid.guid().data4().at(1), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " guid data4[1]");
    CPPUNIT_NS::assertEquals(std::get<6>(entry), eguid.guid().data4().at(2), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " guid data4[2]");
    CPPUNIT_NS::assertEquals(std::get<7>(entry), eguid.guid().data4().at(3), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " guid data4[3]");
    CPPUNIT_NS::assertEquals(std::get<8>(entry), eguid.n(), CPPUNIT_SOURCELINE(), "test case #" + std::to_string(i) + " n");
  }
}

void ExtendedGUIDTest::test_from_string()
{
  // string, 7 values for m_guid, 1 value m_n
  std::vector<std::tuple<std::string, uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint32_t> > cases {};

  cases.emplace_back("{{00000000-0000-0000-0000-000000000000},0}", 0, 0, 0, 0, 0, 0, 0,0);
  cases.emplace_back("{{FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF},4294967295}", 0xFFFFFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFFFFFF);
  cases.emplace_back("{{7B5C52E4-D88C-4DA7-AEB1-5378D02996D3},255}", 0X7b5c52e4, 0Xd88c, 0X4da7, 0Xaeb1, 0X5378, 0Xd029, 0X96d3,0xFF);


  for (size_t i {0}; i < cases.size(); i++)
  {
    auto entry = cases.at(i);
    libone::ExtendedGUID eguid(
      libone::GUID(
        std::get<1>(entry),
        std::get<2>(entry),
        std::get<3>(entry),
        std::get<4>(entry),
        std::get<5>(entry),
        std::get<6>(entry),
        std::get<7>(entry)),
      std::get<8>(entry));

    CPPUNIT_NS::assertEquals(std::get<0>(entry), eguid.to_string(), CPPUNIT_SOURCELINE(), "test case#" + std::to_string(i));
  }


}

void ExtendedGUIDTest::test_is_equal()
{

  libone::ExtendedGUID eguid1{};

  libone::ExtendedGUID eguid2(libone::GUID(0,0,0,0,0,0,0),0);



  CPPUNIT_NS::Asserter::failIf(eguid1 != eguid2, "compare zerod extendedguids", CPPUNIT_SOURCELINE());


  libone::ExtendedGUID eguid3(libone::GUID(1,2,3,4,5,6,7),8);
  libone::ExtendedGUID eguid4(libone::GUID(1,2,3, {{4,5,6,7}}),8);

  CPPUNIT_NS::Asserter::failIf(eguid1 != eguid2, "compare extendedguids 2", CPPUNIT_SOURCELINE());


}
