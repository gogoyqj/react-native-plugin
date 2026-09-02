import { TurboModuleRegistry } from 'react-native';

export interface Spec {
  drawCircle(radius: number, color: number): {
    width: number;
    height: number;
    buffer: ArrayBuffer;
  };
}

export default TurboModuleRegistry.getEnforcing<Spec>('CirclePlugin');
