#pragma once

#include "types.h"

/**
 * @brief Loads game resources.
 */
void load_resources();

/**
 * @brief Retrieves the appropriate bitmap for a power-up kind.
 * @param kind The kind of the power-up.
 * @return The bitmap corresponding to the power-up kind.
 */
bitmap get_power_up_bitmap(PowerUpKind kind);
