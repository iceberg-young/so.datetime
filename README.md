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


Portability
-----------

This library employs `timegm` instead of `mktime`.

> **STANDARDS**
>
> ... The timegm() function is not specified by any standard;
> its function cannot be completely emulated using the standard functions
> described above.
>
>  -- *[FreeBSD - man page for timegm][timegm]*

At least, it is available on BSD (Free/Net/Open- now; as it was introduced there),
and systems which have [Glibc] available.

> **P.S.**
> On my desktop (openSUSE 13.2), `timegm` is 12x ~ 15x faster than `mktime`.


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

### Bonus

- Convert a duration to [XML Schema Part 2][xmld] described string.

  ```cpp
  template<typename rep_t, typename period_t>
  so::to_string(std::chrono::duration<rep_t, period_t>) -> std::string
  ```

  > **Tip!**
  > Since *year* and *month* cannot be used **without** a date context,
  > this function will use *day* as the largest component.
  > E.g. `P366D` instead of `P1Y1D` or `P1Y`.


Precision
---------

- Datetime and duration strings outputted by `so::to_string`
  will have **millisecond** precision.

- Datetime string accepted by `so::datetime`
  could has **nanosecond** precision.


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

[timegm]: http://www.unix.com/man-page/freebsd/3/timegm/
"FreeBSD - man page for timegm"

[Glibc]: http://www.gnu.org/software/gnulib/manual/html_node/timegm.html
"Portability problems fixed by Gnulib"

[xmld]: http://www.w3.org/TR/xmlschema-2/#duration
"XML Schema Part 2: Datatypes - duration"

[LGPLv3]: http://www.gnu.org/graphics/lgplv3-88x31.png
"GNU Lesser General Public License version 3"
