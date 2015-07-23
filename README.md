so.datetime
===========

Convert from/to a [W3 profile][w3cdt] described date-time string.

E.g.

```cpp
std::cout << so::to_string(so::datetime::now());
```
> ```
> 2015-07-23T15:15:15.080Z
> ```

```cpp
auto t = (so::time_point) so::datetime{"1970-01-01T00:00:01.666Z"};
t -= std::chrono::milliseconds{3600};
std::cout << so::to_string(t);
```
> ```
> 1969-12-31T23:59:58.066Z
> ```


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

[w3cdt]: http://www.w3.org/TR/NOTE-datetime
"Date and Time Formats"

[LGPLv3]: http://www.gnu.org/graphics/lgplv3-88x31.png
"GNU Lesser General Public License version 3"
