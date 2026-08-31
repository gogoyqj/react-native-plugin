import React, { useEffect, useState } from 'react';
import { View, Image, StyleSheet, Text } from 'react-native';
import { drawCircle, type CircleResult } from './NativeCirclePlugin';

interface CircleViewProps {
  radius?: number;
  color?: number;
}

export function CircleView({ radius = 64, color = 0xff0000ff }: CircleViewProps) {
  const [uri, setUri] = useState<string | null>(null);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    try {
      // 同步调用 JSI，无 bridge 开销
      const result: CircleResult = drawCircle(radius, color);
      const pixels = new Uint8Array(result.buffer);

      // 转 base64 给 Image 组件
      let binary = '';
      for (let i = 0; i < pixels.length; i++) {
        binary += String.fromCharCode(pixels[i]);
      }
      const base64 = globalThis.btoa(binary);
      setUri(`data:image/raw,${base64}`);
    } catch (e: any) {
      setError(e.message);
      console.error('CirclePlugin.drawCircle failed:', e);
    }
  }, [radius, color]);

  if (error) {
    return (
      <View style={[styles.container, { width: radius * 2, height: radius * 2 }]}>
        <Text style={styles.error}>{error}</Text>
      </View>
    );
  }

  if (!uri) {
    return (
      <View style={[styles.container, { width: radius * 2, height: radius * 2 }]}>
        <Text>Drawing...</Text>
      </View>
    );
  }

  return (
    <Image
      source={{ uri, width: radius * 2, height: radius * 2 }}
      style={{ width: radius * 2, height: radius * 2 }}
    />
  );
}

const styles = StyleSheet.create({
  container: {
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#f0f0f0',
  },
  error: {
    color: 'red',
    fontSize: 12,
  },
});

export { drawCircle } from './NativeCirclePlugin';
export type { CircleResult } from './NativeCirclePlugin';
