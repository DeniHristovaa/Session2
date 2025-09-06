#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned long id_course;
    char name_course[128];
    char name_teacher[64];
    char start_data[11];
    int num_students;
} Course;

typedef struct {
    char names[64];
    unsigned long id_student;
    int num_courses;
    int* course_id;
} Student;

//2
int save_in_file(Course* course, int n, char teacher[64], char start[11], char finish[11]);
//
//3
int enrolling_a_student(Course* course, Student* student, int nc, int ns, int id_student, int* course_id);
//
//4
Course* remove_course(Course* course, int n, char date[11]);
//

int main(void) {
    int n;
    printf("Enter number of course: ");
    scanf("%d", &n);

    Course *courses = (Course *) calloc(n, sizeof(Course));
    if (courses == NULL) {
        printf("Memory could not be allocated");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        Course course;
        printf("Course ID: ");
        scanf("%lu", &course.id_course);
        printf("Course Name: ");
        scanf("%s", course.name_course);
        printf("Course Name Teacher: ");
        scanf("%s", course.name_teacher);
        printf("Course Start Data: ");
        scanf("%s", course.start_data);
        course.num_students = 0;

        courses[i] = course;
    }

    Student *students = (Student *) calloc(n, sizeof(Student));
    if (students == NULL) {
        printf("Memory could not be allocated");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        Student student;

        printf("Student names: ");
        getchar();
        fgets(student.names, sizeof(student.names), stdin);
        // Махаме новия ред от fgets
        // student.names[strcspn(student.names, "\n")] = 0;

        printf("Student ID: ");
        scanf("%lu", &student.id_student);

        student.num_courses = 0;

        student.course_id = calloc(student.num_courses, sizeof(int));
        // for (int j = 0; j < n; j++) {
        //     student.course_id[j] = 0;
        // }
        // // memset(student.course_id, 0, sizeof(int) * n);

        students[i] = student;
    }

    free(courses);
    free(students);

    return 0;
}

//2
int save_in_file(Course* course, int n, char teacher[64], char start[11], char finish[11]) {
    FILE *file = fopen("course_info.txt", "w");
    if (file == NULL) {
        printf("File could not be opened");
        exit(1);
    }

    int count = 0;
    int currentD, currentM, currentY, startD, startM, startY, finishD, finishM, finishY;
    sscanf(start, "%d.%d.%d", &startD, &startM, &startY);
    sscanf(finish, "%d.%d.%d", &finishD, &finishM, &finishY);

    for (int i = 0; i < n; i++) {
        sscanf(course[i].start_data, "%d.%d.%d", &currentD, &currentM, &currentY);
        if (startY < currentY < finishY && startM < currentM < finishM, startD < currentD < finishD) {
            fprintf(file, "%lu:%s:%s:&d", course[i].id_course, course[i].name_course, course[i].start_data, course[i].num_students);
            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        printf("-%d", count);
    }
    else {
        printf("%d", count);
    }
}

//3
int enrolling_a_student(Course* courses, Student* students, int numCourses, int numStudents, int id_student, int* course_id) {
    FILE* bin = fopen("course_student.bin", "wb");
    if (bin == NULL) {
        printf("File could not be opened");
        exit(1);
    }

    for (int i = 0; i < numCourses; i++) {
        if (courses[i].num_students < 30) {

        }
    }
    // // Намери курсa
    // Course *course = NULL;
    // for (int i = 0; i < numCourses; i++) {
    //     if (courses[i].id_course == course_id) {
    //         course = &courses[i];
    //         break;
    //     }
    // }
    // if (course == NULL) return 0; // курсът не съществува
    //
    // // Намери студента
    // Student *student = NULL;
    // for (int i = 0; i < numStudents; i++) {
    //     if (students[i].id_student == id_student) {
    //         student = &students[i];
    //         break;
    //     }
    // }
    // if (student == NULL) return 0; // студентът не съществува
    //
    // // Проверка: студентът вече записан ли е за този курс?
    // FILE *file = fopen("course_student.bin", "rb+");
    // if (!file) {
    //     // Ако файлът не съществува, създаваме го
    //     file = fopen("course_student.bin", "wb+");
    //     if (!file) return -1; // системна грешка
    // }
    //
    // int storedCourseNumber, storedFacultyNumber;
    // while (fread(&storedCourseNumber, sizeof(int), 1, file) == 1 &&
    //        fread(&storedFacultyNumber, sizeof(int), 1, file) == 1) {
    //     if (storedCourseNumber == course_id && storedFacultyNumber == id_student) {
    //         fclose(file);
    //         return 0; // вече записан
    //     }
    //        }
    //
    // // Проверка за капацитети
    // if (course->enrolledCount >= MAX_STUDENTS_PER_COURSE) {
    //     fclose(file);
    //     return 0; // няма свободно място в курса
    // }
    // if (student->coursesCount >= MAX_COURSES_PER_STUDENT) {
    //     fclose(file);
    //     return 0; // студентът вече посещава максимален брой курсове
    // }
    //
    // // Записваме новия запис в края на файла
    // fseek(file, 0, SEEK_END);
    //
    // if (fwrite(&courseNumber, sizeof(int), 1, file) != 1 ||
    //     fwrite(&facultyNumber, sizeof(int), 1, file) != 1) {
    //     fclose(file);
    //     return -1; // системна грешка при запис
    //     }
    //
    // fclose(file);
    //
    // // Актуализирай броя на записаните студенти и броя курсове на студента
    // course->enrolledCount++;
    // student->coursesCount++;
    //
    // return 1; // успешно записване
}

//4
Course* remove_course(Course* course, int *n, char date[11]) {
    int found = 0;
    int currentD, currentM, currentY, givenD, givenM, givenY;
    sscanf(date, "%d.%d.%d", &givenD, &givenM, &givenY);
    for (int i = 0; i < *n; i++) {
        sscanf(course[i].start_data, "%d.%d.%d", &currentD, &currentM, &currentY);
        if (currentY < givenY || (currentY == givenY && currentM < givenM) || (currentY == givenY && currentM == givenM && currentD < givenD)) {
            found++;
            (*n)--;
            for (int j = i; j < (*n-1); j++) {
                course[j] = course[j+1];
            }
            course = realloc(course, (*n)*sizeof(Course));
            if (course == NULL) {
                printf("Memory could not be allocated");
                exit(1);
            }
            return course;
        }
    }
    if (found == 0) {
        printf("There is no course with this ID");
        exit(1);
    }
}