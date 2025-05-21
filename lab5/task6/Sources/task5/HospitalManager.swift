import Foundation

class HospitalManager {
    private var hospitals: [String: String] = [ // name: city
        "City Hospital": "New York",
        "Green Clinic": "Boston"
    ]

    func printAll() {
        for (name, city) in hospitals {
            print("\(name): \(city)")
        }
    }

    func count() {
        print("Hospitals in the dictionary: \(hospitals.count)")
    }
}
