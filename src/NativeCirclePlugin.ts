/**
 * JSI 版本 — 同步调用，无 bridge 序列化开销。
 *
 * JSI 绑定的 __drawCircle 在 native 模块加载时注册到全局。
 * 调用方式:
 *   const result = __drawCircle(100, 0xFF0000FF)
 *   const pixels = new Uint8Array(result.buffer)
 */

export interface CircleResult {
  width: number;
  height: number;
  buffer: ArrayBuffer;
}

/**
 * 调用 C++ 绘制圆形（同步，通过 JSI）。
 * 需要 native 模块已初始化。
 */
export function drawCircle(radius: number, color: number): CircleResult {
  if (typeof globalThis.__drawCircle !== 'function') {
    throw new Error(
      'CirclePlugin JSI not initialized. Make sure the native module is linked.'
    );
  }
  return globalThis.__drawCircle(radius, color) as CircleResult;
}

// 类型声明
declare global {
  function __drawCircle(radius: number, color: number): CircleResult;
}
