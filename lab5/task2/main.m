// main.m

#import <Foundation/Foundation.h>
#import "NumberAnalyzer.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NumberAnalyzer *analyzer = [[NumberAnalyzer alloc] init];
        NSArray<NSNumber *> *numbers = [analyzer findNumbersWithFiveDivisorsInRangeFrom:1 to:1000];

        NSLog(@"Numbers with exactly 5 divisors in the range from 1 to 1000:");
        for (NSNumber *num in numbers) {
            NSLog(@"%@", num);
        }
    }
    return 0;
}
