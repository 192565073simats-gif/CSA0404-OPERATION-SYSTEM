#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

int main() {
    FILE *fp;
    struct Employee emp;
    int choice, id;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL)
        fp = fopen("employee.dat", "wb+");

    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    do {
        printf("\n1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Update Employee\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter ID, Name and Salary: ");
            scanf("%d %49s %f",
                  &emp.empId, emp.empName, &emp.empSalary);

            fseek(fp, (emp.empId - 1) * sizeof(emp), SEEK_SET);
            fwrite(&emp, sizeof(emp), 1, fp);
            printf("Employee added successfully\n");
            break;

        case 2:
            printf("Enter Employee ID: ");
            scanf("%d", &id);

            fseek(fp, (id - 1) * sizeof(emp), SEEK_SET);
            if (fread(&emp, sizeof(emp), 1, fp) == 1 &&
                emp.empId == id) {
                printf("ID: %d\nName: %s\nSalary: %.2f\n",
                       emp.empId, emp.empName, emp.empSalary);
            } else {
                printf("Employee not found\n");
            }
            break;

        case 3:
            printf("Enter Employee ID to update: ");
            scanf("%d", &id);

            fseek(fp, (id - 1) * sizeof(emp), SEEK_SET);
            if (fread(&emp, sizeof(emp), 1, fp) == 1 &&
                emp.empId == id) {
                printf("Enter new Name and Salary: ");
                scanf("%49s %f", emp.empName, &emp.empSalary);

                fseek(fp, (id - 1) * sizeof(emp), SEEK_SET);
                fwrite(&emp, sizeof(emp), 1, fp);
                printf("Employee updated successfully\n");
            } else {
                printf("Employee not found\n");
            }
            break;

        case 4:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice\n");
        }
    } while (choice != 4);

    fclose(fp);
    return 0;
}