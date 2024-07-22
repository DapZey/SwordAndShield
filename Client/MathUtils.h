//
// Created by benra on 7/22/2024.
//

#ifndef CLIENT_MATHUTILS_H
#define CLIENT_MATHUTILS_H

#include "raylib.h"
class MathUtils {
public:
    static bool pointWithinBoundsOfSquare(RaylibRectangle rect, Vector2 point) {
        return (point.x >= rect.x &&
                point.x <= (rect.x + rect.width) &&
                point.y >= rect.y &&
                point.y <= (rect.y + rect.height));
    }
};


#endif //CLIENT_MATHUTILS_H
