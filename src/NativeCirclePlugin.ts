import { TurboModule, TurboModuleRegistry } from 'react-native';

export interface CircleResult {
  width: number;
  height: number;
  data: string; // base64 encoded RGBA pixels
}

export interface Spec extends TurboModule {
  /**
   * Draw a filled circle.
   * @param radius  Circle radius in pixels (1-2048)
   * @param color   Fill color as 0xRRGGBBAA (e.g. 0xFF0000FF for red)
   * @returns       Promise with RGBA pixel data
   */
  drawCircle(radius: number, color: number): Promise<CircleResult>;
}

const CirclePlugin = TurboModuleRegistry.get<Spec>('CirclePlugin');

if (!CirclePlugin) {
  console.warn(
    'CirclePlugin native module not found. Make sure the native module is linked.'
  );
}

export default CirclePlugin as Spec;
