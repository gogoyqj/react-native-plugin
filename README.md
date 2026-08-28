# react-native-circle-plugin

React Native plugin that draws circles using C++ and returns RGBA pixel data.

## Architecture

```
src/NativeCirclePlugin.ts  ← TurboModule spec
        ↓
ios/CirclePlugin.mm        ← ObjC++ bridge (iOS)
android/.../CirclePluginJNI.cpp  ← JNI bridge (Android)
        ↓
cpp/CircleDrawer.h/cpp     ← Pure C++ circle rasterization
```

## Installation

```bash
# iOS
cd ios && pod install

# Android
# Auto-linked via ReactPackage
```

## Usage

```tsx
import { CircleView } from 'react-native-circle-plugin';

function App() {
  return (
    <CircleView radius={100} color={0xFF0000FF} />  // Red circle
  );
}
```

### Direct API

```tsx
import CirclePlugin from 'react-native-circle-plugin';

const result = await CirclePlugin.drawCircle(64, 0x00FF00FF); // Green circle
// result = { width: 128, height: 128, data: "base64..." }
```

## API

### `CircleView` Component

| Prop | Type | Default | Description |
|------|------|---------|-------------|
| `radius` | `number` | `64` | Circle radius in pixels |
| `color` | `number` | `0xFF0000FF` | Fill color as `0xRRGGBBAA` |

### `drawCircle(radius, color)` Function

Returns `Promise<{ width, height, data }>` where `data` is base64-encoded RGBA pixels.

## C++ Implementation

The core drawing logic is in `cpp/CircleDrawer.cpp` — pure C++, no dependencies:

```cpp
auto result = circleplugin::drawCircle(100, 0xFF0000FF);
// result.pixels — RGBA byte array
// result.width, result.height — dimensions (2*radius)
```

## Color Format

Colors are `0xRRGGBBAA`:
- `0xFF0000FF` — Red
- `0x00FF00FF` — Green
- `0x0000FFFF` — Blue
- `0xFF000080` — Red, 50% transparent
