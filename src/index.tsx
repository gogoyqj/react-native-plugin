import React, { useEffect, useState } from 'react';
import { View, Image, StyleSheet, Text, Platform } from 'react-native';
import CirclePlugin, { type CircleResult } from './NativeCirclePlugin';

interface CircleViewProps {
  radius?: number;
  color?: number;
}

export function CircleView({ radius = 64, color = 0xff0000ff }: CircleViewProps) {
  const [uri, setUri] = useState<string | null>(null);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    CirclePlugin.drawCircle(radius, color)
      .then((result: CircleResult) => {
        // RN Image can render base64 data URIs
        setUri(`data:image/raw,${result.data}`);
      })
      .catch((e: Error) => {
        setError(e.message);
        console.error('CirclePlugin.drawCircle failed:', e);
      });
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

export default CirclePlugin;
