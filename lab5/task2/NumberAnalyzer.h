// NumberAnalyzer.h

#import <Foundation/Foundation.h>

@interface NumberAnalyzer : NSObject

- (NSArray<NSNumber *> *)findNumbersWithFiveDivisorsInRangeFrom:(int)start to:(int)end;

@end
