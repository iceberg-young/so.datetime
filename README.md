so.datetime
===========

Convert from/to a [W3 profile][w3dt] described date-time string.

Two system types are borrowed and enhanced by this library.

- `timespec`
  The public base of `so::datetime`.

  Easy to convert from/to various date-time representations.

- `std::chrono::system_clock::time_point`
  Aliased to `so::time_point`.

  Easy to do duration operation.


API
---

See [datetime.hpp](include/datetime.hpp).

- Construct from W3 date-time string. E.g.

  ```cpp
  so::datetime epoch{"1970-01-01T00:00:00.000Z"};
  ```

- Covert to W3 date-time string.

  ```cpp
  so::to_string(timespec)
  so::to_string(so::time_point)
  ```

- Construct from and cast to system types.

  ```cpp
  so::datetime::datetime(timespec)
  so::datetime::datetime(so::time_point)
  ```

  ```cpp
  so::datetime::operator time_point()
  ```

  > **Tip!**
  > Casting `so::datetime` to public base `timespec` is an implicit operation.


License
-------
![LGPLv3]

Copyright (C) 2015  Iceberg YOUNG

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


---

[w3dt]: http://www.w3.org/TR/NOTE-datetime
"Date and Time Formats"

[LGPLv3]: http://www.gnu.org/graphics/lgplv3-88x31.png
"GNU Lesser General Public License version 3"
