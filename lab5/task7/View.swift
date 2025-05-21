import Foundation

class View {
    static func show(message: String) {
        print(message)
    }

    static func showArray(_ array: [Int]?) {
        if let arr = array {
            print("Array: \(arr)")
        } else {
            print("Array is missing.")
        }
    }

    static func prompt(_ message: String) -> String? {
        print(message, terminator: " ")
        return readLine()
    }
}
