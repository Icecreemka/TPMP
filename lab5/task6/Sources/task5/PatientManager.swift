import Foundation

class PatientManager {
    private var patients: [String: String] = [:] // name: diagnosis

    func inputPatients() {
        print("Enter a list of patients (name:diagnosis), separated by spaces:")
        if let input = readLine() {
            let entries = input.split(separator: " ")
            for entry in entries {
                let parts = entry.split(separator: ":")
                if parts.count == 2 {
                    let name = String(parts[0])
                    let diagnosis = String(parts[1])
                    patients[name] = diagnosis
                }
            }
        }
    }

    func printAll() {
        for (name, diagnosis) in patients {
            print("\(name): \(diagnosis)")
        }
    }

    func count() {
        print("Patients in the dictionary: \(patients.count)")
    }

    func printByKey() {
        print("Enter patient name:")
        if let key = readLine(), let diagnosis = patients[key] {
            print("\(key): \(diagnosis)")
        } else {
            print("Patient not found.")
        }
    }

    func addPatient() {
        print("Enter patient name:")
        guard let name = readLine() else { return }
        print("Enter diagnosis:")
        guard let diagnosis = readLine() else { return }
        patients[name] = diagnosis
        print("Patient added \(name)")
    }

    func modifyPatient() {
        print("Enter the patient name to change:")
        guard let name = readLine(), patients[name] != nil else {
            print("Patient not found.")
            return
        }
        print("Enter a new diagnosis:")
        guard let diagnosis = readLine() else { return }
        patients[name] = diagnosis
        print("Data updated.")
    }

    func sortByKey() {
        let sorted = patients.sorted { $0.key < $1.key }
        for (name, diagnosis) in sorted {
            print("\(name): \(diagnosis)")
        }
    }

    func sortByValue() {
        let sorted = patients.sorted { $0.value < $1.value }
        for (name, diagnosis) in sorted {
            print("\(name): \(diagnosis)")
        }
    }

    func removeByKey() {
        print("Enter the patient name to delete:")
        guard let name = readLine(), patients.removeValue(forKey: name) != nil else {
            print("Patient not found.")
            return
        }
        print("The patient has been removed.")
    }

    func clearAll() {
        patients.removeAll()
        print("All patients have been removed.")
    }
}
