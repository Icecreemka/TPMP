// main.m

#import <Foundation/Foundation.h>
#import "ArrayProcessor.h"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        ArrayProcessor *processor = [[ArrayProcessor alloc] init];
        [processor processArrays];
    }
    return 0;
}
