const path = require('path');
const { getDefaultConfig, mergeConfig } = require('@react-native/metro-config');

/**
 * Metro configuration for running directly from the example directory.
 * If running from project root, use the root metro.config.js instead.
 *
 * @type {import('metro-config').MetroConfig}
 */
const root = path.resolve(__dirname, '..');

const config = {
  watchFolders: [root],
  resolver: {
    // 强制所有模块从 example 的 node_modules 解析，避免多实例
    nodeModulesPaths: [path.join(__dirname, 'node_modules')],
    extraNodeModules: {
      'react-native-circle-plugin': root,
    },
  },
};

module.exports = mergeConfig(getDefaultConfig(__dirname), config);
