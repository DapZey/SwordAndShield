//
// Created by benra on 7/22/2024.
//

#ifndef CLIENT_MATHUTILS_H
#define CLIENT_MATHUTILS_H

#include "raylib.h"
#include "math.h"
class MathUtils {
public:
    static bool pointWithinBoundsOfSquare(RaylibRectangle rect, Vector2 point) {
        return (point.x >= rect.x &&
                point.x <= (rect.x + rect.width) &&
                point.y >= rect.y &&
                point.y <= (rect.y + rect.height));
    }
    static bool hitboxIntersection(RaylibRectangle rect, RaylibRectangle rect2){
        return CheckCollisionRecs(rect,rect2);
    }
    static float magnitude(const Vector2& vec) {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }
    static Vector2 normalize(const Vector2 &vec) {
        float mag = magnitude(vec);
        // Check if the magnitude is not zero to avoid division by zero
        if (mag != 0.0f) {
            return {vec.x / mag, vec.y / mag};
        } else {
            // If the magnitude is zero, return a zero vector or handle it as appropriate for your use case
            return {0.0f, 0.0f};
        }
    }
};


#endif //CLIENT_MATHUTILS_H
