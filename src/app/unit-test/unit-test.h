/******************************************************************************/
/*
  Author  - Ming-Lun "Allen" Chou
  Web     - http://AllenChou.net
  Twitter - @TheAllenChou
 */
/******************************************************************************/

#ifndef UNIT_TEST_H
#define UNIT_TEST_H


class UnitTest : public CppUnit::TestFixture
{
  public:
    CPPUNIT_TEST_SUITE(UnitTest);
    CPPUNIT_TEST(TestBasicUnits);
    CPPUNIT_TEST(TestDerivedUnits);
    CPPUNIT_TEST_SUITE_END();

  public:
    void TestBasicUnits();
    void TestDerivedUnits();
};


#endif
