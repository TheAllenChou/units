/******************************************************************************/
/*
  Author  - Ming-Lun "Allen" Chou
  Web     - http://AllenChou.net
  Twitter - @TheAllenChou
 */
/******************************************************************************/

#include "unit-test.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest);


#include "units/defines.h"

MAKE_BASIC_UNIT(Meter, float, _m);
MAKE_BASIC_UNIT(Second, float, _s);
MAKE_DERIVED_UNIT_DIV(MeterPerSecond, float, _m_s, Meter, Second);

MAKE_BASIC_UNIT(Ampere, float, _a);
MAKE_BASIC_UNIT(Volt, float, _v);
MAKE_DERIVED_UNIT_MUL(Watt, float, _w, Ampere, Volt);

#include "units/undefs.h"


void UnitTest::TestBasicUnits()
{
  const Meter kPosInfinity = Meter::PosInfinity();
  const Meter kNegInfinity = Meter::NegInfinity();
  const Meter kZero = Meter::Zero();

  const Meter a = 1_m;
  const Meter b = 2.0_m;
  const Meter c = a + b;
  const Meter d = 2 * b;
  const Meter e = 4.0f * b;
  const Meter f = b / 2;
  Meter g = b; g *= 2;
  Meter h = b; h /= 2.0f;

  CPPUNIT_ASSERT_EQUAL(FLT_MAX, kPosInfinity.To<float>());
  CPPUNIT_ASSERT_EQUAL(-FLT_MAX, kNegInfinity.To<float>());
  CPPUNIT_ASSERT_EQUAL(0.0f, kZero.GetRaw());
  CPPUNIT_ASSERT_EQUAL(1.0f, a.GetRaw());
  CPPUNIT_ASSERT_EQUAL(1.0f, (+a).GetRaw());
  CPPUNIT_ASSERT_EQUAL(-1.0f, (-a).GetRaw());
  CPPUNIT_ASSERT_EQUAL(2.0f, b.GetRaw());
  CPPUNIT_ASSERT_EQUAL(3.0f, c.GetRaw());
  CPPUNIT_ASSERT_EQUAL(4.0f, d.GetRaw());
  CPPUNIT_ASSERT_EQUAL(8.0f, e.GetRaw());
  CPPUNIT_ASSERT_EQUAL(1.0f, f.GetRaw());
  CPPUNIT_ASSERT_EQUAL(4.0f, g.GetRaw());
  CPPUNIT_ASSERT_EQUAL(1.0f, h.GetRaw());
  CPPUNIT_ASSERT(a == a);
  CPPUNIT_ASSERT(a == -(-a));
  CPPUNIT_ASSERT(a != b);
  CPPUNIT_ASSERT(a < b);
  CPPUNIT_ASSERT(a <= b);
  CPPUNIT_ASSERT(b > a);
  CPPUNIT_ASSERT(b >= a);
}

void UnitTest::TestDerivedUnits()
{
  const Meter length = 4.0_m;
  const Second time = 2.0_s;
  const MeterPerSecond speed = length / time;
  const Meter derivedLength = speed * 4.0_s;

  CPPUNIT_ASSERT_EQUAL(2.0f, speed.GetRaw());
  CPPUNIT_ASSERT(Meter::From(8.0f) == derivedLength);

  const Ampere current = 2.0_a;
  const Volt voltage = 3.0_v;
  const Watt power0 = current * voltage;
  const Watt power1 = voltage * current;
  const Ampere derivedCurrent = power0 / voltage;
  const Volt derivedVoltage = power1 / current;

  CPPUNIT_ASSERT_EQUAL(6.0f, power0.GetRaw());
  CPPUNIT_ASSERT(power0 == power1);
  CPPUNIT_ASSERT(current == derivedCurrent);
  CPPUNIT_ASSERT(voltage == derivedVoltage);

  1_a + 3_v;
}
