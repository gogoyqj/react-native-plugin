import React, { useEffect, useState } from 'react';
import { View, Image, StyleSheet, Text } from 'react-native';
import NativeCirclePlugin from './NativeCirclePlugin';

export type CircleResult = {
  width: number;
  height: number;
  buffer: ArrayBuffer;
};

interface CircleViewProps {
  radius?: number;
  color?: number;
}

export function CircleView({ radius = 64, color = 0xff0000ff }: CircleViewProps) {
  const [uri, setUri] = useState<string | null>(null);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    try {
      // 同步调用 TurboModule (底层 JSI)，无 bridge 序列化开销
      const result: CircleResult = NativeCirclePlugin.drawCircle(radius, color);
      const rgba = new Uint8Array(result.buffer);
      const w = result.width;
      const h = result.height;

      // RGBA → BMP (32-bit BGRA, bottom-to-top)
      const rowBytes = w * 4;
      const rowPad = (4 - (rowBytes % 4)) % 4;
      const pixelSize = (rowBytes + rowPad) * h;
      const fileSize = 54 + pixelSize;
      const bmp = new Uint8Array(fileSize);
      const dv = new DataView(bmp.buffer);

      // BITMAPFILEHEADER (14 bytes)
      bmp[0] = 0x42; bmp[1] = 0x4D; // 'BM'
      dv.setUint32(2, fileSize, true);
      dv.setUint32(10, 54, true); // pixel data offset

      // BITMAPINFOHEADER (40 bytes)
      dv.setUint32(14, 40, true); // header size
      dv.setInt32(18, w, true);
      dv.setInt32(22, h, true);
      dv.setUint16(26, 1, true); // planes
      dv.setUint16(28, 32, true); // bits per pixel
      dv.setUint32(34, pixelSize, true);

      // 像素数据 (BMP 从底向上，BGRA 顺序)
      let offset = 54;
      for (let y = h - 1; y >= 0; y--) {
        for (let x = 0; x < w; x++) {
          const src = (y * w + x) * 4;
          bmp[offset++] = rgba[src + 2]; // B
          bmp[offset++] = rgba[src + 1]; // G
          bmp[offset++] = rgba[src];     // R
          bmp[offset++] = rgba[src + 3]; // A
        }
        offset += rowPad;
      }

      // base64 编码
      const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/';
      let base64 = '';
      for (let i = 0; i < bmp.length; i += 3) {
        const a = bmp[i];
        const b = i + 1 < bmp.length ? bmp[i + 1] : 0;
        const c = i + 2 < bmp.length ? bmp[i + 2] : 0;
        base64 += chars[a >> 2];
        base64 += chars[((a & 3) << 4) | (b >> 4)];
        base64 += i + 1 < bmp.length ? chars[((b & 15) << 2) | (c >> 6)] : '=';
        base64 += i + 2 < bmp.length ? chars[c & 63] : '=';
      }
      setUri(`data:image/bmp;base64,${base64}`);
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

export function drawCircle(radius: number, color: number): CircleResult {
  return NativeCirclePlugin.drawCircle(radius, color);
}
