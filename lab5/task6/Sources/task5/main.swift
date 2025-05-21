import Foundation

let patientManager = PatientManager()
let hospitalManager = HospitalManager()

func printMenu() {
    print("""
    
    ========== MENU ==========
    1. Entering patients
    2. Show all patients
    3. Number of patients
    4. Find a patient by name
    5. Add patient
    6. Change diagnosis
    7. Sort by name
    8. Sort by diagnosis
    9. Delete patient
    10. Clear all patients
    11. Show hospitals
    12. Number of hospitals
    0. Exit
    ==========================
    """)
}

while true {
    printMenu()
    print("Select an item:", terminator: " ")
    guard let choice = readLine(), let option = Int(choice) else { continue }

    switch option {
    case 1: patientManager.inputPatients()
    case 2: patientManager.printAll()
    case 3: patientManager.count()
    case 4: patientManager.printByKey()
    case 5: patientManager.addPatient()
    case 6: patientManager.modifyPatient()
    case 7: patientManager.sortByKey()
    case 8: patientManager.sortByValue()
    case 9: patientManager.removeByKey()
    case 10: patientManager.clearAll()
    case 11: hospitalManager.printAll()
    case 12: hospitalManager.count()
    case 0:
        print("Exiting the program.")
        exit(0)
    default:
        print("Wrong choice.")
    }
}
