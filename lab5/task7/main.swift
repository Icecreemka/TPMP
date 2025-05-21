import Foundation

var mutableArray = [Int]() // mutable array
let immutableArray: [Int] = [5, 2, 9, 1] // immutable array
let processor = ArrayProcessor(numbers: nil)

func showMenu() {
    View.show(message: """
    
    === MENU ===
    1. Show array
    2. Enter array elements
    3. Number of elements (mutable and immutable array)
    4. Add item
    5. Insert element by index
    6. Delete last item
    7. Delete element by index
    8. Clear array
    9. Find the median
    0. Exit
    """)
}

while true {
    showMenu()
    guard let choice = View.prompt("Your choice:"), let option = Int(choice) else { continue }

    switch option {
    case 1:
        View.showArray(mutableArray)
    case 2:
        if let input = View.prompt("Enter numbers separated by spaces:"), !input.isEmpty {
            let values = input.split(separator: " ").compactMap { Int($0) }
            mutableArray = values
            processor.setArray(values)
        }
    case 3:
        View.show(message: "An immutable array contains \(immutableArray.count) elements.")
        View.show(message: "The mutable array contains \(mutableArray.count) elements.")
    case 4:
        if let valStr = View.prompt("Enter a number to add:"), let val = Int(valStr) {
            mutableArray.append(val)
            processor.setArray(mutableArray)
        }
    case 5:
        if let valStr = View.prompt("Enter the number:"), let val = Int(valStr),
           let idxStr = View.prompt("Enter index:"), let idx = Int(idxStr),
           idx >= 0 && idx <= mutableArray.count {
            mutableArray.insert(val, at: idx)
            processor.setArray(mutableArray)
        } else {
            View.show(message: "Invalid index.")
        }
    case 6:
        if !mutableArray.isEmpty {
            mutableArray.removeLast()
            processor.setArray(mutableArray)
        }
    case 7:
        if let idxStr = View.prompt("Enter index to delete:"), let idx = Int(idxStr),
           idx >= 0 && idx < mutableArray.count {
            mutableArray.remove(at: idx)
            processor.setArray(mutableArray)
        } else {
            View.show(message: "Invalid index.")
        }
    case 8:
        mutableArray.removeAll()
        processor.setArray(mutableArray)
    case 9:
        if let median = processor.findMedian() {
            View.show(message: "Median: \(median)")
        } else {
            View.show(message: "Unable to find median (array is empty).")
        }
    case 0:
        View.show(message: "Exit...")
        exit(0)
    default:
        View.show(message: "Wrong choice.")
    }
}
