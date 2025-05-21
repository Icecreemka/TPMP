import Foundation

func analyzeNumber(_ number: Int, compareWith b: Int) {
    guard number >= 100 && number <= 999 else {
        print("The number must be three digits.")
        return
    }

    let hundreds = number / 100
    let tens = (number / 10) % 10
    let ones = number % 10

    let product = hundreds * tens * ones
    let sum = hundreds + tens + ones

    print("Number analysis: \(number)")
    print("Numbers: \(hundreds), \(tens), \(ones)")
    print("Product of numbers: \(product)")
    print("Sum of digits: \(sum)")

    if product > b {
        print("The product of the digits is greater than \(b)")
    } else {
        print("The product of digits is not greater than \(b)")
    }

    if sum % 3 == 0 {
        print("The sum of the digits is a multiple of 3")
    } else {
        print("The sum of the digits isn't' a multiple of 3")
    }
}

analyzeNumber(254, compareWith: 20)
