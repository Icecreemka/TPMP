// ArrayProcessor.m

#import "ArrayProcessor.h"

@interface ArrayProcessor ()

- (void)reverseArray:(NSMutableArray *)array; // private method

@end

@implementation ArrayProcessor

- (void)processArrays {
    // Immutable array
    NSArray *immutableArray = @[@"Apple", @"Banana", @"Cherry"];
    NSLog(@"Immutable array: %@", immutableArray);

    // Mutable array (empty)
    NSMutableArray *mutableArray = [NSMutableArray array];
    NSLog(@"An empty mutable array was created");

    // Console Input
    char input[100];
    NSLog(@"Enter 3 array elements:");
    for (int i = 0; i < 3; i++) {
        scanf("%s", input);
        NSString *element = [NSString stringWithUTF8String:input];
        [mutableArray addObject:element];
    }

    // Counting the number of elements
    NSLog(@"Elements in immutableArray: %lu", (unsigned long)[immutableArray count]);
    NSLog(@"Elements in mutableArray: %lu", (unsigned long)[mutableArray count]);

    // Adding an element
    [mutableArray addObject:@"NewElement"];
    NSLog(@"After adding: %@", mutableArray);

    // Insert by index
    if ([mutableArray count] >= 2) {
        [mutableArray insertObject:@"InsertedElement" atIndex:1];
        NSLog(@"After inserting: %@", mutableArray);
    }

    // Delete last element
    if ([mutableArray count] > 0) {
        [mutableArray removeLastObject];
        NSLog(@"After deleting the last one: %@", mutableArray);
    }

    // Delete by index
    if ([mutableArray count] > 1) {
        [mutableArray removeObjectAtIndex:1];
        NSLog(@"After deleting by index: %@", mutableArray);
    }

    // Flipping an array
    NSMutableArray *numbers = [NSMutableArray arrayWithObjects:@1, @2, @3, @4, @5, nil];
    NSLog(@"Original: %@", numbers);
    [self reverseArray:numbers];
    NSLog(@"Flipped: %@", numbers);

    // Clearing an array
    [mutableArray removeAllObjects];
    NSLog(@"After clearing: %@", mutableArray);
}

// Private method
- (void)reverseArray:(NSMutableArray *)array {
    NSUInteger count = [array count];
    for (NSUInteger i = 0; i < count / 2; i++) {
        [array exchangeObjectAtIndex:i withObjectAtIndex:(count - i - 1)];
    }
}

@end
