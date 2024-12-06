## Units

Units is an experimental library that provides macros to define custom unit types with custom literals that enforce dimensional correctness. Basic unit types can be further combined to define derived unit types using mathematical relationships, including division and multiplication.

Enforcing dimensional correctness could help catch logical erros, such as assigning a product of acceleration (lengths per time squared) and duration (times) to a variable representing distance (lengths).

```C++
const float acceleration = 1.0f;
const float duration = 2.0f;
const float distance = acceleration * duration;     // [OOPS!] no compiler error

const Acceleration acceleration = 1.0_m_ss;
const Time duration = 2.0_s;
const Length distance = acceleration * duration;    // [ERROR!] units don't match
                                                    // assigning velocity (m/s) to length (m)

const Acceleration acceleration = 1.0_m_ss;
const Time duration = 2.0_s;
const Velocity velocity = acceleration * duration;
const Length distance = velocity * duration;        // [OK!] units match!
```

This repository contains two projects:  
  * units: Core library (single header file).
  * unit-test: Library unit tests.

The core library is platform-agnostic, whereas the unit tests are targeted for Windows.

To build the unit tests on Windows, you need:  
  * Sublime Text 3 (optional): for convenient premake & build command shortcuts without having to open VS2015
  * Premake 5: for building VS2015 solution & projects
  * Visual Studio 2015: for building binaries


## Code Examples
```C++
#include "units/defines.h"

// make units
MAKE_BASIC_UNIT(Length, float, _m);                         // length - meter (m)
MAKE_BASIC_UNIT(Time, float, _s);                           // time - second (s)
MAKE_DERIVED_UNIT_DIV(Velocity, float, _m_s, Length, Time); // velocity - meters per second (m/s)
MAKE_BASIC_UNIT(Current, float, _a);                        // current - Ampere (a)
MAKE_BASIC_UNIT(Voltage, float, _v);                        // voltage - Volt (v)
MAKE_DERIVED_UNIT_MUL(Power, float, _w, Current, Volt);     // power - Watt (w)

// literals
const Length lengthLiteral = 4.0_m;
const Time timeLiteral = 2.0_s;

// conversion to primitive types
const Length safeType = 1.0_m;
const float rawType = safeType.GetRaw();
const int castedType = safeType.To<int>();

// arithmetics
const Length add = 1.0_m + 2.0_m;
const Length sub = 1.0_m - 2.0_m;
const Length neg = -add;

// scalar operations
const Length mul = 2.0f * 1.0_m; // 2.0 meters
const Length div = 6.0_m / 2.0f; // 3.0 meters

// derived units (divisions)
const Length length = 3.0_m;
const Time time = 1.5_s;
const Velocity speed = length / time; // 2.0 meters per second
const Length derivedLength = speed * time;

// derived units (multiplications)
const Current current = 3.0_a;
const Voltage voltage = 2.0_v;
const Power power = current * voltage; // 6.0 watts
const Current derivedCurrent = power / voltage;
const Voltage derivedVoltage = power / current;

// dimensional correctness
auto badStuff = 1.0_m + 2.0_s; // ERROR
auto goodStuff = 1.0_w + 2.0_a * 3.0_v; // OK
```

----
**Ming-Lun "Allen" Chou**  
[AllenChou.net](http://AllenChou.net)  
[@TheAllenChou](http://twitter.com/TheAllenChou)  
