
#include <stdio.h>

int main() {
    int t = 1;
    while (t == 1) {
        int semesters, sem, subjects, i;
        float marks, credit, grade_point;
        float semester_sum_gp = 0, semester_sum_cr = 0;
        float total_gp = 0, total_cr = 0, cgpa;

        printf("\n--- DIU CGPA Calculator (Marks-Based, Official Scale) ---\n");
        printf("Enter number of semesters: ");
        scanf("%d", &semesters);

        for (sem = 1; sem <= semesters; sem++) {
            semester_sum_gp = 0;
            semester_sum_cr = 0;
            printf("\nSemester %d:\n", sem);
            printf("Enter number of subjects: ");
            scanf("%d", &subjects);

            for (i = 1; i <= subjects; i++) {
                printf("\nSubject %d marks (0-100): ", i);
                scanf("%f", &marks);
                if (marks < 0 || marks > 100) {
                    printf("Invalid marks! Please enter between 0 and 100.\n");
                    i--;
                    continue;
                }
                printf("Enter credit hours: ");
                scanf("%f", &credit);

                // DIU grade system
                if (marks >= 80) grade_point = 4.00;
                else if (marks >= 75) grade_point = 3.75;
                else if (marks >= 70) grade_point = 3.50;
                else if (marks >= 65) grade_point = 3.25;
                else if (marks >= 60) grade_point = 3.00;
                else if (marks >= 55) grade_point = 2.75;
                else if (marks >= 50) grade_point = 2.50;
                else if (marks >= 45) grade_point = 2.25;
                else if (marks >= 40) grade_point = 2.00;
                else grade_point = 0.00;

                semester_sum_gp += grade_point * credit;
                semester_sum_cr += credit;
            }

            float semester_gpa = semester_sum_gp / semester_sum_cr;
            printf("GPA for Semester %d: %.2f\n", sem, semester_gpa);

            total_gp += semester_sum_gp;
            total_cr += semester_sum_cr;
        }

        cgpa = total_gp / total_cr;
        printf("\nYour Final CGPA: %.2f\n", cgpa);

        if (cgpa >= 3.90)
            printf("🏅 Award : Best student \n");
        else if (cgpa >= 3.75)
            printf("🏅 Award: Good Student \n");

        printf("\nCalculate again? 1 = Yes, 0 = No : ");
        scanf("%d", &t);
    }
    return 0;
}
