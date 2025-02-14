//
// Created by 0srma on 13/02/2025.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include <cstdint>
#include <iostream>

inline uint32_t multiplyShiftHash(uint32_t k, uint32_t l) {
    constexpr uint32_t w = 32; // Tamaño de palabra
    constexpr double A_fraction = 0.6180339887; // Aproximación de (√5 - 1) / 2
    uint64_t A = static_cast<uint64_t>(A_fraction * (1ULL << w)); // Calcula A que es a/2^w

    // Calcula k * A mod 2^w, que es k * A en un tipo de 64 bits
    uint64_t ka = static_cast<uint64_t>(k) * A;

    // Desplaza los bits necesarios: l bits más significativos
    uint32_t hashValue = ka >> (w - l);

    // Aplica una mascara de l bits para extraer los bits mas significativos
    uint32_t mask = (1U << 14) - 1;
    return hashValue & mask;
}

#endif //UTILITIES_H
