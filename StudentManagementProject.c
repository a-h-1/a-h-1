// Header Files
#include <stdio.h> // For input and output
#include <stdlib.h> // For dynamic memory allocation
#include <string.h> // For strings

// Definitions
#define CHARMAX 50
#define GRADESMAX 5
#define STUDENTSMAX 10
#define HONOUR_ROLL 0x01
#define POOR_PERFORM 0x02
#define ATHLETE 0x04
#define TEACHERS_PET 0x08

// Student Struct
typedef struct {
    char name[CHARMAX];
    int id;
    int grades[GRADESMAX];
    int flags;
    float avg;
} Student;

// Functions
// Reset All Grades for All Students
void setAllGradesToZero(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < GRADESMAX; j++) {
            students[i].grades[j] = 0;
        }
    }
}
// Swap two Students
void swapStudents(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}
// Get Student with Best Average
Student* getTopStudent(Student* students, int count) {
    // Set pointer to first student
    Student* topStudent = &students[0];
    // Iterate through each student comparing averages, highest is top
    for (int i = 1; i < count; i++) {
        if (students[i].avg > topStudent->avg) {
            topStudent = &students[i];
        }
    }
    return topStudent;
}
// Sum Individual Student Grades
int sumGrades (Student* student) {
    int sum = 0;
    for (int i = 0; i < GRADESMAX; i++){
        sum += student->grades[i];
    }
    return sum;
}
// Search Student ID
Student* searchStudentByID(Student* students, int count, int id) {
    for (int i = 0; i < count; i++){
        if (students[i].id == id){
            return &students[i];
        }
    }
    printf("Student Not Found\n");
    return NULL; // terminates search
}
// Display Students
void displayStudent(Student* student){
        printf("Name: %s\n", student->name);
        printf("ID: %d\n", student->id);
        printf("Average Grade: %.1f\n", student->avg);
        for (int j = 0; j < GRADESMAX; j++){
            printf("Grade %d: %d\n", j + 1, student->grades[j]);
        }
        printf("Attributes: ");
        if (student->flags & HONOUR_ROLL)   printf("[Honour Roll] ");
        if (student->flags & POOR_PERFORM)  printf("[Poor Performer] ");
        if (student->flags & TEACHERS_PET)  printf("[Teacher's Pet] ");
        if (student->flags & ATHLETE)       printf("[Athlete] ");
        printf("\n");
}
// Add Student
void addStudent(Student* students, int* count, int max){
    if (*count >= max) {
        printf("Cannot add more students. MAXIMUM limit reached.\n");
        return;
    }

    // Refer to next student slot
    Student* s = &students[*count];

    // Name
    printf("Student name:\n");
    fgets(s->name, sizeof(s->name), stdin); // get name using fgets because it tracks spaces
    s->name[strcspn(s->name, "\n")] = '\0'; // replace newline with null terminator
    // ID
    printf("Student ID:\n");
    scanf("%d", &s->id);
    // Grades
    printf("Enter 5 grades:\n");
    for (int i = 0; i < 5; i++) {
        printf("Grade %d: ", i + 1); // j+1 describes grade number exclusing 0
        scanf("%d", &s->grades[i]);
    }
    while (getchar() != '\n'); // Clearing buffer after scanf
    // Average Grade
    s->avg = (float) sumGrades(s) / GRADESMAX;

    // Add 1 to count and confirm it is successful
    (*count)++;
    printf("Student added successfully.\n");
}
// Edit Student
void editStudent(Student* student) {
    int choice;
    printf("Which would you like to edit?\n");
    printf("1. Name\n");
    printf("2. ID\n");
    printf("3. Grades\n");
    printf("4. Attributes\n");
    printf("Choose a Number: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // clear input

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            fgets(student->name, sizeof(student->name), stdin);
            student->name[strcspn(student->name, "\n")] = '\0';
            break;
        case 2:
            printf("Enter new ID: ");
            scanf("%d", &student->id);
            break;
        case 3:
            printf("Enter 5 new grades:\n");
            int sum = 0;
            for (int i = 0; i < GRADESMAX; i++) {
                printf("Grade %d: ", i + 1);
                scanf("%d", &student->grades[i]);
                sum += student->grades[i];
            }
            student->avg = (float)sum / GRADESMAX;
            break;
        case 4:{
            int fchoice;
            do {
                printf("\n-- Attributes Menu --\n");
                printf("1. Honour Roll\n");
                printf("2. Poor Performer\n");
                printf("3. Teacher's Pet\n");
                printf("4. Athlete\n");
                printf("5. Back\n");
                printf("Select flag (number) to toggle: ");
                scanf("%d", &fchoice);
                while (getchar() != '\n');

                switch (fchoice)
                {
                case 1:
                    toggleFlag(student, HONOUR_ROLL);
                    break;
                case 2:
                    toggleFlag(student, POOR_PERFORM);
                    break;
                case 3:
                    toggleFlag(student, ATHLETE);
                    break;
                case 4:
                    toggleFlag(student, TEACHERS_PET);
                    break;
                case 5:
                    printf("Exiting Attributes Menu.");
                    break;
                default:
                    break;
                }

            } while (fchoice != 5);
        }
            break;
        default:
            printf("Invalid choice.\n");
    }

    printf("Update complete.\n");
}
// Remove Student
void removeStudent(Student* students, int* count, int id){
    for (int i = 0; i < *count; i++){
        if (students[i].id == id){
            for (int j = i; j < *count - 1; j++){
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student removed.\n");
            return;
        }
    }
    printf("Student Not Found.");
}
// Toggle Flag
void toggleFlag(Student* student, int flag){
    student->flags ^= flag;
}

// Main
int main() {
    int i, j, id, count = 0, choice;

    // Allocate dynamic memory for (number of students)
    Student* students = (Student*) malloc(STUDENTSMAX * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Menu Loop
    do
    {
        // Menu Screen
        printf("\n");
        printf("---- Student Management System ----\n");
        printf("\n");
        printf("1. Display All Students\n");
        printf("2. Search by ID\n");
        printf("3. Add a Student\n");
        printf("4. Edit a Student\n");
        printf("5. Remove a Student\n");
        printf("6. Exit\n");
        printf("Choose a Number:");
        scanf("%d", &choice);
        while (getchar() != '\n'); // clear newline from buffer
        printf("\n");

        // Choice Selection
        switch (choice)
        {
        case 1:
            printf("\nDisplaying All Students:\n");
            for (int k = 0; k < count; k++){
            printf("Student %d: ", k);
            displayStudent(&students[k]);
            printf("\n");
            }
            break;
        case 2:{
            printf("\nSearch for Student\n");
            printf("Enter Student ID:");
            scanf("%d", &id);
            Student* found = searchStudentByID(students, count, id);
            if (found != NULL){
                displayStudent(found);
            }
            break;
        }
        case 3:
            printf("\nAdd a New Student\n");
            addStudent(students, &count, STUDENTSMAX);
            printf("Welcome!");
            break;
        case 4:
            printf("Enter Student ID:");
            scanf("%d", &id);
            Student* found = searchStudentByID(students, count, id);
            if (found != NULL){
                editStudent(found);
            }
            break;
        case 5:
            printf("\nRemoving a Student by ID\n");
            printf("Enter Student ID:");
            scanf("%d", &id);
            removeStudent(students, &count, id);
            break; 
        case 6:
            printf("\nGoodbye.\n");
            return 0;
            break;
        default:
            printf("Invalid Choice. Try Again.\n");
            break;
        }
    } while (choice != 6);
    
    // Free memory
    free(students);

    return 0;
}