# svglight
SVG light library for C++

## Examples
```cpp
#include <svglight.h>

...

svglight::SVG image;
image.draw_line(0, 0, 10, 0);
image.draw_line(0, 0, 0, 10);
image.draw_line(10, 10, 0, 10);
image.draw_line(10, 10, 0, 10);
image.save("result.svg");
```

## Installation
```
git clone https://github.com/vladislavbelov/svglight
```

or

```
wget https://raw.githubusercontent.com/vladislavbelov/svglight/master/svglight.h
```

## Task list
- [ ] Open image
- [x] Save image
- [x] Add basic drawing functions
- [ ] Add advanced drawing functions

## License
It's available on the MIT license.
