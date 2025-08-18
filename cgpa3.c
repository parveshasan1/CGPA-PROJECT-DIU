#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    float credit_hours;
    float grade_point;
} Course;


typedef struct {
  
    Course courses[20];
    int num_courses;
    float semester_gpa;
    float semester_points;
    float semester_credits;
} Semester;

float get_grade_point(int code) {
    switch(code) {
        case 1: return 4.00;
        case 2: return 3.75;
        case 3: return 3.50;
        case 4: return 3.25;
        case 5: return 3.00;
        case 6: return 2.75;
        case 7: return 2.50;
        case 8: return 2.25;
        case 9: return 2.00;
        case 10: return 0.00;
        default: return -1.0;
    }
}

void show_grade_menu() {
    printf("\nGrade Codes:\n");
    printf("1. A+ (4.00)\n");
    printf("2. A  (3.75)\n");
    printf("3. A- (3.50)\n");
    printf("4. B+ (3.25)\n");
    printf("5. B  (3.00)\n");
    printf("6. B- (2.75)\n");
    printf("7. C+ (2.50)\n");
    printf("8. C  (2.25)\n");
    printf("9. D  (2.00)\n");
    printf("10. F (0.00)\n");
}

float calculate_gpa(Course courses[], int num_courses) {
    float total_points = 0.0, total_credits = 0.0;
    for (int i = 0; i < num_courses; i++) {
        total_points += courses[i].credit_hours * courses[i].grade_point;
        total_credits += courses[i].credit_hours;
    }

    if (total_credits == 0) return 0.0;
    return total_points / total_credits;
}

void display_waiver(float cgpa) {
    printf("\n Waiver Status:\n");
    if (cgpa >= 3.95)
        printf(" 100%% Tuition Waiver!\n");
    else if (cgpa >= 3.85)
        printf(" 75%% Tuition Waiver!\n");
    else if (cgpa >= 3.75)
        printf(" 50%% Tuition Waiver!\n");
    else if (cgpa >= 3.60)
        printf(" 25%% Tuition Waiver!\n");
    else
        printf(" No Tuition Waiver. Keep up the hard work!\n");
}

int main() {
    int choice;
    int num_semesters = 0;
    
    Semester semesters[10];

    printf(" Welcome to DIU CGPA Calculator\n");

    do {
        printf("\n--- MENU ---\n");
        printf("1. Add Semester GPA\n");
        printf("2. Show CGPA + Waiver\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                if (num_semesters >= 10) {
                    printf(" Maximum number of semesters reached (10).\n");
                    break;
                }

                int num_courses;
                printf("\nEnter number of courses for Semester %d: ", num_semesters + 1);
                scanf("%d", &num_courses);

                if (num_courses <= 0 || num_courses > 20) {
                    printf(" Invalid number of courses. Please enter a number between 1 and 20.\n");
                    break;
                }

                semesters[num_semesters].num_courses = num_courses;
                semesters[num_semesters].semester_points = 0.0;
                semesters[num_semesters].semester_credits = 0.0;

                for (int i = 0; i < num_courses; i++) {
                    printf("\n--- Course %d ---\n", i + 1);
                    printf("Enter course name: ");
                    scanf("%s", semesters[num_semesters].courses[i].name);
                    
                    do {
                        printf("Enter credit hours: ");
                        scanf("%f", &semesters[num_semesters].courses[i].credit_hours);
                        if (semesters[num_semesters].courses[i].credit_hours <= 0) {
                            printf(" Invalid credit hours! Must be greater than 0. Try again.\n");
                        }
                    } while (semesters[num_semesters].courses[i].credit_hours <= 0);

                    int code;
                    float gp;
                    do {
                        show_grade_menu();
                        printf("Enter grade code (1-10): ");
                        scanf("%d", &code);
                        gp = get_grade_point(code);
                        if (gp == -1.0)
                            printf(" Invalid code! Try again.\n");
                    } while (gp == -1.0);
                    
                    semesters[num_semesters].courses[i].grade_point = gp;

                    semesters[num_semesters].semester_points += semesters[num_semesters].courses[i].credit_hours * semesters[num_semesters].courses[i].grade_point;
                    semesters[num_semesters].semester_credits += semesters[num_semesters].courses[i].credit_hours;
                }
                
                semesters[num_semesters].semester_gpa = semesters[num_semesters].semester_points / semesters[num_semesters].semester_credits;
                printf(" Semester %d GPA: %.2f\n", num_semesters + 1, semesters[num_semesters].semester_gpa);
                num_semesters++;
                break;
            }

            case 2: {
                if (num_semesters == 0) {
                    printf(" Please add at least one semester first.\n");
                } else {
                    float total_grade_points = 0.0;
                    float total_credits = 0.0;

                    for (int i = 0; i < num_semesters; i++) {
                        total_grade_points += semesters[i].semester_points;
                        total_credits += semesters[i].semester_credits;
                    }
                    
                    if (total_credits == 0) {
                        printf(" No courses with credits have been added.\n");
                    } else {
                        float cgpa = total_grade_points / total_credits;
                        printf("\n Total Semesters: %d\n", num_semesters);
                        printf(" Overall CGPA: %.2f\n", cgpa);
                        display_waiver(cgpa);
                    }
                }
                break;
            }

            case 3:
                printf(" Thank you! Exiting...\n");
                break;

            default:
                printf(" Invalid choice. Try again.\n");
        }

    } while (choice != 3);

    return 0;
}
