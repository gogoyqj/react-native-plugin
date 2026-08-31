#pragma once

#include <jsi/jsi.h>
#include "CircleDrawer.h"

namespace circleplugin {

/**
 * Register drawCircle as a global JSI function.
 * Call once during module initialization.
 *
 * JS 侧调用:
 *   const { width, height, buffer } = __drawCircle(100, 0xFF0000FF)
 *   const pixels = new Uint8Array(buffer)
 */
void installCircleJSI(facebook::jsi::Runtime &runtime);

} // namespace circleplugin
