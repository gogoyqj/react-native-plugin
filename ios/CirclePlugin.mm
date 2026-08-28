#import "CirclePlugin.h"
#import <React/RCTLog.h>

#include "../cpp/CircleDrawer.h"

@implementation CirclePlugin

RCT_EXPORT_MODULE();

+ (BOOL)requiresMainQueueSetup {
  return NO;
}

/**
 * Draw a filled circle.
 * Returns { width, height, data: base64 string }
 */
RCT_EXPORT_METHOD(drawCircle:(double)radius
                  color:(double)color
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
  @try {
    int r = (int)radius;
    uint32_t c = (uint32_t)color;

    if (r <= 0 || r > 2048) {
      reject(@"INVALID_RADIUS", @"radius must be between 1 and 2048", nil);
      return;
    }

    // Call C++ implementation
    auto result = circleplugin::drawCircle(r, c);

    // Convert pixel buffer to NSData
    NSData *data = [NSData dataWithBytes:result.pixels.data()
                                  length:result.pixels.size()];

    // Return base64 encoded RGBA data
    NSString *base64 = [data base64EncodedStringWithOptions:0];

    resolve(@{
      @"width": @(result.width),
      @"height": @(result.height),
      @"data": base64,
    });
  } @catch (NSException *exception) {
    reject(@"CIRCLE_ERROR", exception.reason, nil);
  }
}

@end
