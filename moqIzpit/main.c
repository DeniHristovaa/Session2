#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned long id_course;
    char course_name[128];
    char start_date[11];
    float price;
    int num_enrolled;
    char type[15];
} Course;

typedef struct {
    char names[80];
    unsigned long id_student;
    int num_courses;
    int course_id[];
} Student;

//2
Course* remove_course(Course* course, int *n, char type[15], char date[11]);
//
//3

//
//4
Course *get_course(Course* course, int n);
//

void main() {
    FILE *file = fopen("courses.bin", "rb");
    if (file == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }

    FILE *bin = fopen("students.bin", "rb");
    if (bin == NULL) {
        printf("File could not be opened\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file); // текуща позиция
    rewind(file); // позициониране в началото на файл

    size_t numCourse = fileSize / sizeof(Course);

    Course *courses = (Course *) malloc(numCourse);
    if (courses == NULL) {
        printf("Memory could not be allocated\n");
        fclose(file);
        exit(1);
    }

    size_t readCount = fread(courses, sizeof(Course), numCourse, file);
    if (readCount != numCourse) {
        printf("File could not be read\n");
        free(courses);
        fclose(file);
        exit(1);
    }

    fclose(file);

    fseek(bin, 0, SEEK_END);
    long binSize = ftell(bin); // текуща позиция
    rewind(bin); // позициониране в началото на файл

    size_t numStudents = fileSize / sizeof(Student);

    Student *students = (Student *) malloc(numStudents);
    if (students == NULL) {
        printf("Memory could not be allocated\n");
        fclose(bin);
        exit(1);
    }

    size_t readCountt = fread(students, sizeof(Student), numStudents, bin);
    if (readCountt != numStudents) {
        printf("File could not be read\n");
        free(students);
        fclose(bin);
        exit(1);
    }

    fclose(bin);
}

//2
Course* remove_course(Course* course, int *n, char type[15], char date[11]) {
    int found = 0;
    int currentD, currentM, currentY, givenD, givenM, givenY;
    sscanf(date, "%d.%d.%d", &givenD, &givenM, &givenY);
    for (int i = 0; i < *n; i++) {
        sscanf(course[i].start_date, "%d.%d.%d", &currentD, &currentM, &currentY);
        if (strcmp(course[i].type, type) == 0 && course[i].num_enrolled < 8 && (currentY > givenY || (currentY == givenY && currentM > givenM) || (currentY == givenY && currentM == givenM && currentD > givenD))) {
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

//3


//4
Course *get_course(Course* course, int n) {
    Course *separete_courses = (Course *) malloc(sizeof (Course));
    if (separete_courses == NULL) {
        printf("Memory could not be allocated");
        exit(1);
    }

    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += course[i].price;
    }
    float average_price = sum / n;

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (course[i].num_enrolled < 30 && course[i].price < average_price) {
            separete_courses[count] = course[i];
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    separete_courses = realloc(separete_courses, sizeof (Course) * count);
    if (separete_courses == NULL) {
        printf("Memory could not be allocated");
        exit(1);
    }

    return separete_courses;
}