/******************************************************************************/
/*
  Author  - Ming-Lun "Allen" Chou
  Web     - http://AllenChou.net
  Twitter - @TheAllenChou
*/
/******************************************************************************/

#ifndef UNITS_DEFINES_H
#define UNITS_DEFINES_H


#include <limits>

#define UNITS_MACRO_CONCAT2(x, y) x ## y
#define UNITS_MACRO_CONCAT(x, y) UNITS_MACRO_CONCAT2(x, y)
#define UNITS_MACRO_END_HELPER(UnitName) struct UNITS_MACRO_CONCAT(UnitName, MacroEndHelper) { } // so we can end macro with a semi-colon


// basic units
// ------------------------------------------------------------------------------------------------------------------------------

#define BASIC_UNIT_INTERNAL(UnitName, StorageType)                                                                                     \
    public:                                                                                                                            \
      typedef StorageType Storage;                                                                                                     \
                                                                                                                                       \
      static const UnitName PosInfinity() { return UnitName(std::numeric_limits<Storage>::max()); }                                    \
      static const UnitName NegInfinity() { return UnitName(std::numeric_limits<Storage>::lowest()); }                                 \
      static const UnitName Zero() { return From(0.0); }                                                                               \
                                                                                                                                       \
      template <typename V> static const UnitName From(V value) { return UnitName(static_cast<Storage>(value)); }                      \
      template <typename V> const V To() const { return static_cast<V>(m_data); }                                                      \
                                                                                                                                       \
      const Storage GetRaw() const { return m_data; }                                                                                  \
                                                                                                                                       \
      const UnitName operator+(const UnitName rhs) const { return UnitName(m_data + rhs.m_data); }                                     \
      const UnitName operator-(const UnitName rhs) const { return UnitName(m_data - rhs.m_data); }                                     \
      const UnitName operator+() const { return UnitName(+m_data); }                                                                   \
      const UnitName operator-() const { return UnitName(-m_data); }                                                                   \
      const bool operator>(const UnitName rhs) const { return m_data > rhs.m_data; }                                                   \
      const bool operator>=(const UnitName rhs) const { return m_data >= rhs.m_data; }                                                 \
      const bool operator<(const UnitName rhs) const { return m_data < rhs.m_data; }                                                   \
      const bool operator<=(const UnitName rhs) const { return m_data <= rhs.m_data; }                                                 \
      const bool operator==(const UnitName rhs) const { return m_data == rhs.m_data; }                                                 \
      const bool operator!=(const UnitName rhs) const { return m_data != rhs.m_data; }                                                 \
                                                                                                                                       \
      template <typename V> const UnitName operator*(const V rhs) const { return From(m_data * rhs); }                                 \
      template <typename V> const UnitName operator/(const V rhs) const { return From(m_data / rhs); }                                 \
      template <typename V> UnitName &operator*=(const V rhs) { m_data *= static_cast<Storage>(rhs); return *this; }                   \
      template <typename V> UnitName &operator/=(const V rhs) { m_data /= static_cast<Storage>(rhs); return *this; }                   \
                                                                                                                                       \
    private:                                                                                                                           \
      explicit UnitName(Storage data) : m_data(data) { }                                                                               \
  Storage m_data;                                                                                                                      \

#define BASIC_UNIT_EXTERNAL(UnitName, StorageType, LiteralSuffix)                                                                      \
  template <typename V> const UnitName operator*(V lhs, UnitName rhs) { return UnitName::From(lhs * rhs.GetRaw()); }                   \
  static const UnitName operator"" LiteralSuffix (long double data) { return UnitName::From(static_cast<UnitName::Storage>(data)); }   \
  static const UnitName operator"" LiteralSuffix (std::size_t data) { return UnitName::From(static_cast<UnitName::Storage>(data)); }   \

#define MAKE_BASIC_UNIT(UnitName, StorageType, LiteralSuffix)                                                                          \
  class UnitName                                                                                                                       \
  {                                                                                                                                    \
    BASIC_UNIT_INTERNAL(UnitName, StorageType)                                                                                         \
  };                                                                                                                                   \
  BASIC_UNIT_EXTERNAL(UnitName, StorageType, LiteralSuffix)                                                                            \
  UNITS_MACRO_END_HELPER(UnitName)                                                                                                     \

// ------------------------------------------------------------------------------------------------------------------------------
// end basic units


// derived units (division)
// ------------------------------------------------------------------------------------------------------------------------------

#define DERIVED_UNIT_DIV_INTERNAL(UnitName, LhsType, RhsType)                                                                          \
    public:                                                                                                                            \
      typedef LhsType Lhs;                                                                                                             \
      typedef RhsType Rhs;                                                                                                             \
      const Lhs operator*(Rhs rhs) const { return Lhs::From(m_data * rhs.GetRaw()); }

#define DERIVED_UNIT_DIV_EXTERNAL(UnitName, LhsType, RhsType)                                                                          \
  static const UnitName operator/(LhsType lhs, RhsType rhs) { return UnitName::From(lhs.GetRaw() / rhs.GetRaw()); }                    \

#define MAKE_DERIVED_UNIT_DIV(UnitName, StorageType, LiteralSuffix, LhsType, RhsType)                                                  \
  class UnitName                                                                                                                       \
  {                                                                                                                                    \
    BASIC_UNIT_INTERNAL(UnitName, StorageType)                                                                                         \
    DERIVED_UNIT_DIV_INTERNAL(UnitName, LhsType, RhsType)                                                                              \
  };                                                                                                                                   \
  BASIC_UNIT_EXTERNAL(UnitName, StorageType, LiteralSuffix)                                                                            \
  DERIVED_UNIT_DIV_EXTERNAL(UnitName, LhsType, RhsType)                                                                                \
  UNITS_MACRO_END_HELPER(UnitName)                                                                                                     \

// ------------------------------------------------------------------------------------------------------------------------------
// end: derived units (division)


// derived units (multiplication)
// ------------------------------------------------------------------------------------------------------------------------------

#define DERIVED_UNIT_MUL_INTERNAL(UnitName, LhsType, RhsType)                                                                          \
    public:                                                                                                                            \
      typedef LhsType Lhs;                                                                                                             \
      typedef RhsType Rhs;                                                                                                             \
      const Lhs operator/(Rhs rhs) const { return Lhs::From(m_data / rhs.GetRaw()); }                                                  \
      const Rhs operator/(Lhs lhs) const { return Rhs::From(m_data / lhs.GetRaw()); }                                                  \

#define DERIVED_UNIT_MUL_EXTERNAL(UnitName, LhsType, RhsType)                                                                          \
  static const UnitName operator*(LhsType lhs, RhsType rhs) { return UnitName::From(lhs.GetRaw() * rhs.GetRaw()); }                    \
  static const UnitName operator*(RhsType rhs, LhsType lhs) { return UnitName::From(rhs.GetRaw() * lhs.GetRaw()); }                    \

#define MAKE_DERIVED_UNIT_MUL(UnitName, StorageType, LiteralSuffix, LhsType, RhsType)                                                  \
  class UnitName                                                                                                                       \
  {                                                                                                                                    \
    BASIC_UNIT_INTERNAL(UnitName, StorageType)                                                                                         \
    DERIVED_UNIT_MUL_INTERNAL(UnitName, LhsType, RhsType)                                                                              \
  };                                                                                                                                   \
  BASIC_UNIT_EXTERNAL(UnitName, StorageType, LiteralSuffix)                                                                            \
  DERIVED_UNIT_MUL_EXTERNAL(UnitName, LhsType, RhsType)                                                                                \
  UNITS_MACRO_END_HELPER(UnitName)                                                                                                     \

// ------------------------------------------------------------------------------------------------------------------------------
// end: derived units (multiplication)


// reference class
/*
class Meter
{
  public:
    typedef float Storage;

    static const Meter PosInfinity() { return Meter(std::numeric_limits<Storage>::max()); }
    static const Meter NegInfinity() { return Meter(std::numeric_limits<Storage>::lowest()); }
    static const Meter Zero() { return From(0.0); }

    template <typename V> static const Meter From(V value) { return Meter(static_cast<Storage>(value)); }
    template <typename V> const V To() const { return static_cast<V>(m_data); }

    const Storage GetRaw() const { return m_data; }

    const Meter operator+(const Meter rhs) const { return Meter(m_data + rhs.m_data); }
    const Meter operator-(const Meter rhs) const { return Meter(m_data - rhs.m_data); }
    const Meter operator>(const Meter rhs) const { return m_data > rhs.m_data; }
    const Meter operator>=(const Meter rhs) const { return m_data >= rhs.m_data; }
    const Meter operator<(const Meter rhs) const { return m_data < rhs.m_data; }
    const Meter operator<=(const Meter rhs) const { return m_data <= rhs.m_data; }
    const Meter operator==(const Meter rhs) const { return m_data == rhs.m_data; }
    
    template <typename V> const Meter operator*(const V rhs) const { return From(m_data * rhs); }
    template <typename V> const Meter operator/(const V rhs) const { return From(m_data / rhs); }
    template <typename V> Meter &operator*=(const V rhs) { m_data *= static_cast<Storage>(rhs); return *this; }
    template <typename V> Meter &operator/=(const V rhs) { m_data /= static_cast<Storage>(rhs); return *this; }

  protected:
    Meter(Storage data) : m_data(data) { }
    Storage m_data;
};

template <typename V> const Meter operator*(V lhs, Meter rhs) { return Meter::From(lhs * rhs.GetRaw()); }
const Meter operator""_m(long double data) { return Meter::From(static_cast<Meter::Storage>(data)); }
const Meter operator""_m(std::size_t data) { return Meter::From(static_cast<Meter::Storage>(data)); }
*/


#endif
