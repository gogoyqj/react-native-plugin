#pragma once

#include <jsi/jsi.h>
#include "CircleDrawer.h"

namespace circleplugin {

/**
 * 注册 CirclePlugin TurboModule 到 runtime。
 * 包装已有的 __turboModuleProxy，注入我们的模块。
 * JS 侧通过 TurboModuleRegistry.getEnforcing('CirclePlugin') 访问。
 */
void installCirclePluginTurboModule(facebook::jsi::Runtime &runtime);

} // namespace circleplugin
