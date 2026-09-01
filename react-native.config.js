module.exports = {
  dependency: {
    platforms: {
      android: {
        sourceDir: './android',
        packageImportPath: 'import com.circleplugin.CirclePluginPackage;',
        packageInstance: 'new CirclePluginPackage()',
      },
      ios: {
        podspecPath: './ios/ReactNativePlugin.podspec',
      },
    },
  },
};
