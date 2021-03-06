/**
 *
 *    MIT License
 *
 *    Copyright (c) 2016 Vladislav Belov
 *
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 *
 */

#ifndef SVGLIGHT_INCLUDED
#define SVGLIGHT_INCLUDED

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace svglight
{

/**
 * Basic color class
 */

class Color
{
public:
    int r, g, b;
    Color(int r = 0, int g = 0, int b = 0) : r(r), g(g), b(b) {}
    std::string to_string() const;
};

/**
 * Describes property of a tag
 */

class Property
{
public:
    Property(const std::string& name, const std::string& str_value) : name(name), value(str_value) {}
    Property(const std::string& name, const int& int_value) : name(name), value(std::to_string(int_value)) {}
    Property(const std::string& name, const float& float_value) : name(name), value(std::to_string(float_value)) {}
    Property(const std::string& name, const Color& color_value) : name(name), value(color_value.to_string()) {}

    std::string name, value;
};

/**
 * Describes basic svg element
 */

class Tag
{
public:
    Tag(const std::string& name) : name(name) {}

    void add(const Property& property);
    void add(const Tag& tag);

    // TODO: implement tag reading
    friend std::istream& operator>>(std::istream& in, Tag& tag);
    friend std::ostream& operator<<(std::ostream& out, const Tag& tag);

    std::string name;
    std::string inner_text;
    std::vector<Property> properties;
    std::vector<Tag> children;
};

/**
 * SVG image class
 */

class SVG
{
public:

    /**
     * A constructor.
     * Fills header and svg tags.
     */
    SVG(int image_width = 640, int image_height = 480);

    // TODO: implement svg loading
    void open(const std::string& path);

    /**
     * save the image to the file
     * @param path a filename of the image
     * @return true if image has saved
     */
    bool save(const std::string& path);

    void draw_line(float x1, float y1, float x2, float y2, const Color& color = Color());
    void draw_rect(float x, float y, float width, float height, const Color& color = Color());
    void draw_circle(float x, float y, float radius, const Color& color = Color());
    void draw_ellipse(float x, float y, float radius_x, float radius_y, const Color& color = Color());
    void draw_text(float x, float y, const std::string& text, const Color& color = Color());

private:
    Tag xml, doctype, svg;

    int image_width, image_height;

    inline std::string property(const std::string& name, const std::string& value);
};

SVG::SVG(int image_width, int image_height)
    : xml("?xml"),
    doctype("!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\""),
    svg("svg"), image_width(image_width), image_height(image_height)
{
    xml.add(Property("version", "1.0"));
    xml.add(Property("encoding", "UTF-8"));
    xml.add(Property("standalone", "no"));

    svg.add(Property("version", "1.0"));
    svg.add(Property("baseProfile", "full"));
    svg.add(Property("xmlns", "http://www.w3.org/2000/svg"));
    svg.add(Property("xmlns:xlink", "http://www.w3.org/1999/xlink"));
    svg.add(Property("xmlns:ev", "http://www.w3.org/2001/xml-events"));
    svg.add(Property("width", image_width));
    svg.add(Property("height", image_height));
}

bool SVG::save(const std::string& path)
{
    std::ofstream out(path);
    if (!out.is_open())
        return false;

    out << xml << doctype << svg;

    out.close();
    return true;
}

void SVG::draw_line(float x1, float y1, float x2, float y2, const Color& color)
{
    Tag line("line");
    line.add(Property("x1", x1));
    line.add(Property("y1", y1));
    line.add(Property("x2", x2));
    line.add(Property("y2", y2));
    line.add(Property("stroke", color));

    svg.add(line);
}

void SVG::draw_rect(float x, float y, float width, float height, const Color& color)
{
    Tag rect("rect");
    rect.add(Property("x", x));
    rect.add(Property("y", y));
    rect.add(Property("width", width));
    rect.add(Property("height", height));
    rect.add(Property("fill", "none"));
    rect.add(Property("stroke", color));

    svg.add(rect);
}

void SVG::draw_circle(float x, float y, float radius, const Color& color)
{
    Tag circle("circle");
    circle.add(Property("cx", x));
    circle.add(Property("cy", y));
    circle.add(Property("r", radius));
    circle.add(Property("fill", "none"));
    circle.add(Property("stroke", color));

    svg.add(circle);
}

void SVG::draw_ellipse(float x, float y, float radius_x, float radius_y, const Color& color)
{
    Tag ellipse("ellipse");
    ellipse.add(Property("cx", x));
    ellipse.add(Property("cy", y));
    ellipse.add(Property("rx", radius_x));
    ellipse.add(Property("ry", radius_y));
    ellipse.add(Property("fill", "none"));
    ellipse.add(Property("stroke", color));

    svg.add(ellipse);
}

void SVG::draw_text(float x, float y, const std::string& text, const Color& color)
{
    Tag txt("text");
    txt.add(Property("x", x));
    txt.add(Property("y", y));
    txt.add(Property("fill", color));

    txt.inner_text = text;

    svg.add(txt);
}

void Tag::add(const Property& property)
{
    properties.push_back(property);
}

void Tag::add(const Tag& tag)
{
    children.push_back(tag);
}

std::ostream& operator<<(std::ostream& out, const Tag& tag)
{
    out << "<" << tag.name;
    for (Property property: tag.properties)
        out << " " << property.name << "=\"" << property.value << "\"";
    if (tag.name[0] == '?')
        out << '?';
    else if (std::isalpha(tag.name[0]) && tag.children.empty() && tag.inner_text.empty())
        out << "/";
    out << ">";

    if (!tag.inner_text.empty())
        out << tag.inner_text;
    for (Tag child: tag.children)
        out << child;
    if (!tag.children.empty() || !tag.inner_text.empty())
        out << "</" << tag.name << ">";

    return out;
}

std::string Color::to_string() const
{
    std::stringstream ss;
    ss << "rgb(" << r << "," << g << "," << b << ")";
    return ss.str();
}

}

#endif // SVGLIGHT_INCLUDED
