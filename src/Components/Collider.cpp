#include "Collider.h"


Collider::Collider(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Collider::Collider(Point position, Size size)
{
    this->x = position.x;
    this->y = position.y;
    this->w = size.width;
    this->h = size.height;
}

Collider::Collider(Size size)
{
    this->x = 0;
    this->y = 0;
    this->w = size.width;
    this->h = size.height;
}


void Collider::SetPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Collider::SetPosition(const Point& position)
{
    this->x = position.x;
    this->y = position.y;
}


void Collider::SetSize(float width, float height)
{
    this->w = width;
    this->h = height;
}

void Collider::SetSize(const Size& size)
{
    this->w = size.width;
    this->h = size.height;
}


Point Collider::GetPosition() const
{
    return Point(this->x, this->y);
}

Size Collider::GetSize() const
{
    return Size(this->w, this->h);
}

Point Collider::GetCenter() const
{
    return Point(
        this->x + this->w / 2,
        this->y + this->h / 2
    );
}


bool Collider::IsEmpty() const
{
    return this->w == 0 || this->h == 0;
}


bool Collider::CollidesWith(const Collider& other) const
{
    if (this->w == 0 || this->h == 0 || other.w == 0 || other.h == 0)
        return false;

    Point center = this->GetCenter();
    Point otherCenter = other.GetCenter();

    float xDistance = abs(center.x - otherCenter.x);
    float yDistance = abs(center.y - otherCenter.y);

    float xOverlap = this->w / 2 + other.w / 2 - xDistance;
    float yOverlap = this->h / 2 + other.h / 2 - yDistance;

    return xOverlap > 0 && yOverlap > 0;
}

Point Collider::GetCollisionOverlap(const Collider& other) const
{
    Point center = this->GetCenter();
    Point otherCenter = other.GetCenter();

    // TODO: Remove this if code below works as expected
    // float xDistance = abs(position.x - other->position.x);
    // float yDistance = abs(position.y - other->position.y);

    float xDistance = abs(center.x - otherCenter.x);
    float yDistance = abs(center.y - otherCenter.y);

    float xOverlap = (this->w + other.w) / 2 - xDistance;
    float yOverlap = (this->h + other.h) / 2 - yDistance;

    return Point(xOverlap, yOverlap);
}


nlohmann::json Collider::Serialize() const
{
    return {
        { "x", this->x }, 
        { "y", this->y }, 
        { "w", this->w }, 
        { "h", this->h }
    };
}

Collider Collider::FromJson(const nlohmann::json& data)
{
    return Collider(
        data["x"].get<float>(), 
        data["y"].get<float>(), 
        data["w"].get<float>(), 
        data["h"].get<float>()
    );
}
