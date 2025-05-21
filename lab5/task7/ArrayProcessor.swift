import Foundation

class ArrayProcessor {
    private var numbers: [Int]?

    init(numbers: [Int]?) {
        self.numbers = numbers
    }

    func findMedian() -> Double? {
        guard var validNumbers = numbers, !validNumbers.isEmpty else {
            return nil
        }

        validNumbers.sort()
        let count = validNumbers.count

        if count % 2 == 0 {
            return Double(validNumbers[count / 2 - 1] + validNumbers[count / 2]) / 2.0
        } else {
            return Double(validNumbers[count / 2])
        }
    }

    func getArray() -> [Int]? {
        return numbers
    }

    func setArray(_ array: [Int]) {
        self.numbers = array
    }
}
