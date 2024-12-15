#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define the Student structure
struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function prototypes
void addStudent(struct Student students[], int *count);
void displayStudents(struct Student students[], int count);
void saveToFile(struct Student students[], int count);
void loadFromFile(struct Student students[], int *count);
void sortStudents(struct Student students[], int count, int criterion);
void searchStudents(struct Student students[], int count);

int main() {
    struct Student students[100];
    int count = 0, choice;

    // Load records from file on startup
    loadFromFile(students, &count);

    do {
        printf("\n=== Student Record Management ===\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Save Records to File\n");
        printf("4. Load Records from File\n");
        printf("5. Sort Students\n");
        printf("6. Search Students\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayStudents(students, count);
                break;
            case 3:
                saveToFile(students, count);
                break;
            case 4:
                loadFromFile(students, &count);
                break;
            case 5:
                printf("Sort by: 1. Roll Number  2. Marks\n");
                int criterion;
                scanf("%d", &criterion);
                sortStudents(students, count, criterion);
                break;
            case 6:
                searchStudents(students, count);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    return 0;
}

// Add a new student
void addStudent(struct Student students[], int *count) {
    printf("Enter roll number: ");
    scanf("%d", &students[*count].roll);
    printf("Enter name: ");
    scanf(" %[^\n]", students[*count].name);
    printf("Enter marks: ");
    scanf("%f", &students[*count].marks);
    (*count)++;
    printf("Student added successfully!\n");
}

// Display all students
void displayStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }
    printf("\n=== Student Records ===\n");
    for (int i = 0; i < count; i++) {
        printf("Roll: %d, Name: %s, Marks: %.2f\n", students[i].roll, students[i].name, students[i].marks);
    }
}

// Save student records to a file
void saveToFile(struct Student students[], int count) {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }
    fwrite(students, sizeof(struct Student), count, file);
    fclose(file);
    printf("Records saved to file successfully.\n");
}

// Load student records from a file
void loadFromFile(struct Student students[], int *count) {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No existing records found.\n");
        return;
    }
    *count = fread(students, sizeof(struct Student), 100, file);
    fclose(file);
    printf("Records loaded from file successfully.\n");
}

// Sort student records
void sortStudents(struct Student students[], int count, int criterion) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int swap = 0;
            if (criterion == 1 && students[j].roll > students[j + 1].roll) {
                swap = 1;  // Sort by roll number
            } else if (criterion == 2 && students[j].marks < students[j + 1].marks) {
                swap = 1;  // Sort by marks
            }
            if (swap) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("Students sorted successfully.\n");
}

// Search for students
void searchStudents(struct Student students[], int count) {
    printf("Search by: 1. Name  2. Marks Range\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        char name[50];
        printf("Enter name to search: ");
        scanf(" %[^\n]", name);
        printf("\nSearch Results:\n");
        for (int i = 0; i < count; i++) {
            if (strstr(students[i].name, name)) {
                printf("Roll: %d, Name: %s, Marks: %.2f\n", students[i].roll, students[i].name, students[i].marks);
            }
        }
    } else if (choice == 2) {
        float minMarks, maxMarks;
        printf("Enter marks range (min max): ");
        scanf("%f %f", &minMarks, &maxMarks);
        printf("\nSearch Results:\n");
        for (int i = 0; i < count; i++) {
            if (students[i].marks >= minMarks && students[i].marks <= maxMarks) {
                printf("Roll: %d, Name: %s, Marks: %.2f\n", students[i].roll, students[i].name, students[i].marks);
            }
        }
    } else {
        printf("Invalid choice!\n");
    }
}
