import React from 'react';
import { SafeAreaView, StyleSheet, Text } from 'react-native';
import { CircleView } from 'react-native-circle-plugin';

export default function App() {
  return (
    <SafeAreaView style={styles.container}>
      <Text style={styles.title}>Circle Plugin Example</Text>
      <CircleView
        radius={100}
        color={0x4a90d9ff}
      />
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5F5F5',
  },
  title: {
    fontSize: 24,
    fontWeight: '600',
    marginBottom: 32,
    color: '#333',
  },

});
