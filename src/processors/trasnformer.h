#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <Arduino.h>

template<class T>
T scaler(T inp, float scale) {
    return T(inp * scale);
}

template<class T>
T truncate(T inp, T min,T max) {
    if (inp <= min) {
        return inp;
    } 
    else if (inp >= max) {
        return max;
    }
    return inp;
}

template<class T>
T analog_map(T inp, T min,T max) {
    return map(inp,0,1023,min,max);
}
#endif