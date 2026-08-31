#import "CirclePlugin.h"
#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>

#include "../cpp/CircleJSI.h"

@implementation CirclePlugin

RCT_EXPORT_MODULE();

+ (BOOL)requiresMainQueueSetup {
  return NO;
}

- (void)setBridge:(RCTBridge *)bridge {
  [super setBridge:bridge];

  // 等 bridge 初始化完成后注册 JSI 函数
  dispatch_async(dispatch_get_main_queue(), ^{
    [self installJSI];
  });
}

- (void)installJSI {
  RCTCxxBridge *cxxBridge = (RCTCxxBridge *)self.bridge;
  if (!cxxBridge || !cxxBridge.runtime) {
    RCTLogError(@"CirclePlugin: JSI runtime not available");
    return;
  }

  jsi::Runtime *runtime = (jsi::Runtime *)cxxBridge.runtime;
  circleplugin::installCircleJSI(*runtime);

  RCTLogInfo(@"CirclePlugin: JSI bindings installed");
}

@end
