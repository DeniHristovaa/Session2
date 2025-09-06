#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[51];
    char start_date[11];
    int lecture;
    float price;
} Course;

//2
void discountCourse(Course *course, int n, int index);
//
//3
int write_in_file(Course *course, int n, float min_price, float max_price);
//
//4
Course* delete_course(Course *courses, int* n, char name[51], char start_date[11]);
//

int main(void) {
    FILE *bin = fopen("courses.bin", "rb");
    if (bin == NULL) {
        printf("Couldn't open courses.bin\n");
        exit(1);
    }

    int n = fread(&n, sizeof(int), 1, bin);
    Course* courses = (Course*) malloc(n * sizeof(Course));

    Course course;
    for (int i = 0; i < n; i++) {
        fread(&course, sizeof(Course), 1, bin);
        courses[i] = course;
    }

    free(courses);
    fclose(bin);
    return 0;
}

//2
void discountCourse(Course* courses, int n, int index) {
    if (index < 0 || index >= n - 1) {
        printf("Invalid index\n");
        exit(1);
    }

    Course course = courses[index];
    course.lecture -= 0.1 * course.price;
    printf("%.2f - %s - %s", course.price, course.name, course.start_date);
}

//3
int write_in_file(Course* courses, int n, float min_price, float max_price) {
    FILE *file = fopen("offer.txt", "w");
    if (file == NULL) {
        printf("Couldn't open offer.txt\n");
        exit(1);
    }

    int count = 0;

    for (int i = 0; i < n; i++) {
        if (courses[i].price >= min_price && courses[i].price <= max_price) {
            fprintf(file, "Course: %s, Price: %.2f\n", courses[i].name, courses[i].price);
            count++;
        }
    }

    fclose(file);

    if (count == 0) {
        return 0;
    }
    else {
        return count;
    }
}

//4
Course* delete_course(Course* courses, int* n, char name[51], char start_date[11]) {
    for (int i = 0; i < *n; i++) {
        if (strcmp(courses[i].name, name) == 0 && strcmp(courses[i].start_date, start_date) == 0) {
            (*n)--;
            for (int j = i; j < (*n - 1); j++) {
                courses[j] = courses[j + 1];
            }
            courses = realloc(courses, (*n) * sizeof(Course));
            if (courses == NULL) {
                printf("Error allocating memory.");
                return NULL;
            }
            return courses;
        }
    }
}