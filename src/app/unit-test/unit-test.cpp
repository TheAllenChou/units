/******************************************************************************/
/*
  Author  - Ming-Lun "Allen" Chou
  Web     - http://AllenChou.net
  Twitter - @TheAllenChou
 */
/******************************************************************************/

#include "unit-test.h"

#include "units/units.h"


// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest);

MAKE_BASIC_UNIT(Length, float, _m);                         // meter (m)
MAKE_BASIC_UNIT(Time, float, _s);                           // second (s)
MAKE_DERIVED_UNIT_DIV(Velocity, float, _m_s, Length, Time); // meters per second (m/s)

MAKE_BASIC_UNIT(Current, float, _a);                        // ampere (a)
MAKE_BASIC_UNIT(Voltage, float, _v);                        // volt (v)
MAKE_DERIVED_UNIT_MUL(Power, float, _w, Current, Voltage);  // watt (w)


void UnitTest::TestBasicUnits()
{
  const Length kPosInfinity = Length::PosInfinity();
  const Length kNegInfinity = Length::NegInfinity();
  const Length kZero = Length::Zero();

  const Length a = 1_m;
  const Length b = 2.0_m;
  const Length c = a + b;
  const Length d = 2 * b;
  const Length e = 4.0f * b;
  const Length f = b / 2;
  Length g = b; g *= 2;
  Length h = b; h /= 2.0f;

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
  const Length length = 4.0_m;
  const Time time = 2.0_s;
  const Velocity speed = length / time;
  const Length derivedLength = speed * 4.0_s;

  CPPUNIT_ASSERT_EQUAL(2.0f, speed.GetRaw());
  CPPUNIT_ASSERT(Length::From(8.0f) == derivedLength);

  const Current current = 2.0_a;
  const Voltage voltage = 3.0_v;
  const Power power0 = current * voltage;
  const Power power1 = voltage * current;
  const Current derivedCurrent = power0 / voltage;
  const Voltage derivedVoltage = power1 / current;

  CPPUNIT_ASSERT_EQUAL(6.0f, power0.GetRaw());
  CPPUNIT_ASSERT(power0 == power1);
  CPPUNIT_ASSERT(current == derivedCurrent);
  CPPUNIT_ASSERT(voltage == derivedVoltage);
}
