#ifndef MATHY_VEC2_H
#define MATHY_VEC2_H

#include "raylib.h"

namespace math {
template<typename T>
struct Vec2{
    T x = 0;
    T y = 0;

    static bool coolinear(
        const Vec2<T>&p1,
        const Vec2<T>&p2,
        const Vec2<T>&p3)
    {
        int cl =
            p1.x * ( p2.y - p3.y) +
            p2.x * ( p3.y - p1.y) +
            p3.x * ( p1.y - p2.y);

        return (cl == 0);
    }

    Vec2() = default;
    // Vec2():x(0),y(0){};
    Vec2(T x, T y):x(x),y(y){};
    Vec2(T v):x(v),y(v){};

    // operator+
    Vec2<T> operator+(const Vec2<T>&v2) const{
        return Vec2<T>(this->x + v2.x,this->y + v2.y);
    }

    // operator-
    Vec2<T> operator-(const Vec2<T>&v2) const{
        return Vec2<T>(this->x - v2.x,this->y - v2.y);
    }

    // operator*
    Vec2<T> operator*(const Vec2<T> v2) const{
        return Vec2<T>(this->x * v2.x,this->y * v2.y);
    }

    // operator*
    Vec2<T> operator*(const T& s) const{
        return Vec2<T>(this->x * s,this->y * s);
    }

    Vec2<T> operator/(T s) const{
        assert(s != 0 && "division by zero not permitted.");
        return Vec2<T>(this->x / s,this->y /s);
    }


    // operator+=
    Vec2<T> &operator+=(const Vec2<T>&v2){
        this->x += v2.x;
        this->y += v2.y;
        return *this;
    }

    // operator-=
    Vec2<T> &operator-=(const Vec2<T>&v2){
        this->x -= v2.x;
        this->y -= v2.y;
        return *this;
    }

    // operator/=
    Vec2<T> &operator/=(T s){
        assert(s != 0 && "division by zero not permitted.");
        this->x /= s;
        this->y /= s;
        return *this;
    }


    // operator+=
    Vec2<T> &operator*=(const Vec2<T>&v2){
        this->x *= v2.x;
        this->y *= v2.y;
        return *this;
    }

    // operator*=
    Vec2<T>& operator*=(T s){
        this->x *= s;
        this->y *= s;
        return *this;
    }

    Vec2<T>& normalize(){
        T length = magnitude();

        // if(length == 0){
        //     return {0,0};
        // }

        if(length != 0.0f){
            this->x = x/length;
            this->y = y/length;
        }

        return *this;
    }

    Vec2<T> unitVector() const{

        Vec2<T> res;
        T length = std::sqrt(x*x + y*y);

        if(length == 0){
            return {0,0};
        }

        res.x = x/length;
        res.y = y/length;

        return res;
    }

    T magnitude() const{
        // T length = std::sqrt(x*x + y*y);
        return std::sqrt(x*x+y*y);
    }

    T magnitudeSquared() const{
        T length = x*x + y*y;
        return length;
    }

    T distance(const Vec2<T>&other) const{
        T dist = std::sqrt(((other.x - x)*(other.x - x))+((other.y - y)*(other.y - y)));
        return dist;
    }

    T squaredDistance(const Vec2<T>&other) const{
        T dist = ((other.x - x)*(other.x - x))+((other.y - y)*(other.y - y));
        return dist;
    }

    Vec2<T> normal() const{
        return Vec2<T>(y,-x).normalize();
    }

    Vec2<T> rotate(float angle) const{
        Vec2<T> result;

        // angle to rad
        // angle = angle * (PI/180.0f);
        result.x = x * cos(angle) - y * sin(angle);
        result.y = x * sin(angle) + y * cos(angle);

        return result;
    }

    float dot(const Vec2<T>& other) const{
        return ((float)this->x * (float)other.x) + ((float)this->y * (float)other.y);
    }

    float cross(const Vec2<T>& other) const{
        return (this->x * other.y) - (this->y * other.x);
    }

    void print(const std::string& tag = "") const{
        if(tag.empty()){
            TraceLog(LOG_INFO,"x:%f, y:%f",x,y);
        }else{
            TraceLog(LOG_INFO,"%s -> x:%f, y:%f",x,y,tag.c_str());
        }

    }
};

using Vec2u     = math::Vec2<uint32_t>;
using Vec2i     = math::Vec2<int>;
using Vec2f     = math::Vec2<float>;

}

#endif // MATH_Vec2_H
