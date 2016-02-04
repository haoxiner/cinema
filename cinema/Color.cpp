#include "Color.h"
const Color Color::BLACK = Color(0.0f, 0.0f, 0.0f);
const Color Color::WHITE = Color(1.0f, 1.0f, 1.0f);

Color::Color()
{
}

Color::Color(float rr, float gg, float bb):r(rr),g(gg),b(bb)
{

}

Color::~Color()
{
}
