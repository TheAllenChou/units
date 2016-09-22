## Units

Units is a library that provides convenient macros to define custom type-safe unit types with custom literals. Basic unit types can further combined to define derived unit types using mathematical relationships, including division and multiplication (more relationships are WIP).

This repository contains two projects:  
  * units: Core library (two header files).
  * unit-test: Library unit tests.

The core library is platform-agnostic, whereas the unit tests are targeted for Windows.

To build the unit tests on Windows, you need:  
  * Sublime Text 3 (optional): for convenient premake & build command shortcuts without having to open VS2015
  * Premake 5: for building VS2015 solution & projects
  * Visual Studio 2015: for building binaries


## Code Examples
```C++

// enable macros
#include "units/defines.h"

MAKE_BASIC_UNIT(Meter, float, _m);
MAKE_BASIC_UNIT(Second, float, _s);
MAKE_DERIVED_UNIT_DIV(MeterPerSecond, float, _m_s, Meter, Second);

MAKE_BASIC_UNIT(Ampere, float, _a);
MAKE_BASIC_UNIT(Volt, float, _v);
MAKE_DERIVED_UNIT_MUL(Watt, float, _w, Ampere, Volt);

// disable macros
#include "units/undefs.h"


// conversion from primitive types
const Meter fromFloat = Meter::From(1.0f);
const Meter fromInt = Meter::From(1);
const float fromMeter = fromFloat.To<float>();

// literals
const Meter meterLiteral = 4.0_m;
const Second secondLiteral = 2.0_s;

// arithmetics
const Meter add = 1.0_m + 2.0_m;
const Meter sub = 1.0_m - 2.0_m;
const Meter neg = -add;

// scalar operations
const Meter mul = 2.0f * 1.0_m; // 2 meters
const Meter div = 1.0_m / 2.0f; // 0.5 meters

// derived units (divisions)
const Meter distance = 3.0_m;
const Second time = 1.5_s;
const MeterPerSecond speed = distance / time; // 2.0 meters per second
const Meter derivedDistance = speed * time;

// derived units (multiplicatoins)
const Ampere current = 3.0_a;
const Volt voltage = 2.0_v;
const Watt power = current * voltage; // 6.0 watts
const Ampere derivedCurrent = power / voltage;
const Volt derivedVoltage = power / current;

// type safety
auto badStuff = 1.0_m + 2.0_s; // ERROR
auto goodStuff = 1.0_w + 2.0_a * 3.0_v; // OK
```

----
**Ming-Lun "Allen" Chou**  
[AllenChou.net](http://AllenChou.net)  
[@TheAllenChou](http://twitter.com/TheAllenChou)  
