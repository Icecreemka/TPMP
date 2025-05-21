// NumberAnalyzer.m

#import "NumberAnalyzer.h"

@implementation NumberAnalyzer

- (NSArray<NSNumber *> *)findNumbersWithFiveDivisorsInRangeFrom:(int)start to:(int)end {
    NSMutableArray<NSNumber *> *result = [NSMutableArray array];

    for (int number = start; number <= end; number++) {
        int divisorCount = 0;
        
        for (int i = 1; i <= number; i++) {
            if (number % i == 0) {
                divisorCount++;
            }
        }
        
        if (divisorCount == 5) {
            [result addObject:@(number)];
        }
    }

    return result;
}

@end
