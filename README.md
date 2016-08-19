# svglight
SVG light library for C++. It provides functions of drawing and saving SVG files.

## Examples
```cpp
#include <svglight.h>

int main(int argc, char* argv[])
{
    svglight::SVG image;
    image.draw_line(0, 0, 10, 0);
    image.draw_line(0, 0, 0, 10);
    image.draw_line(10, 10, 0, 10);
    image.draw_line(10, 10, 0, 10);
    image.save("result.svg");
    return 0;
}
```

or

```cpp
#include <svglight.h>

int main(int argc, char* argv[])
{
    svglight::SVG image(512, 512);
    image.draw_ellipse(256, 256, 128, 64);
    image.draw_text(200, 200, "This is ellipse!");
    image.save("result.svg");
    return 0;
}
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
