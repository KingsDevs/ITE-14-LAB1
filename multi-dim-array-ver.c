#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

typedef struct _students
{
    int size;
    char ** student_arr;
}students;

students * create_new_studarr()
{
    students * stud = (students *)malloc(sizeof(students));
    stud->student_arr = (char **)malloc(sizeof(char *));
    stud->size = 0;
}

void add_student_end(students * studs, char * new_student)
{
    if(studs->size == 0)
    {
        studs->student_arr[0] = (char *)malloc(strlen(new_student) + 1);
        strcpy(studs->student_arr[0], new_student);

        studs->size++;
    }
    else
    {
        int new_size = studs->size + 1;
        studs->student_arr = (char **)realloc(studs->student_arr, new_size * sizeof(char *));    
        studs->student_arr[studs->size] = (char *)malloc(strlen(new_student) + 1);
        strcpy(studs->student_arr[studs->size], new_student);
        studs->size = new_size;
    }
}

void add_student(students * studs, int pos, char * new_student)
{
    int new_size = studs->size + 1;
    studs->student_arr = (char **)realloc(studs->student_arr, new_size * sizeof(char *));

    for(int i = studs->size - 1; i >= pos; i--)
    {
        studs->student_arr[i + 1] = studs->student_arr[i];
        // studs->student_arr[i+1] = (char *)malloc(strlen(studs->student_arr[i]) + 1);
        // strcpy(studs->student_arr[i+1], studs->student_arr[i]);
        // free(studs->student_arr[i]);
        
    }

    studs->student_arr[pos] = (char *)malloc(strlen(new_student) + 1);
    strcpy(studs->student_arr[pos], new_student);

    studs->size = new_size;
}

void add_student_start(students * studs, char * new_student)
{
    if(studs->size == 0)
        add_student_end(studs, new_student);
    else
    {
        add_student(studs, 0, new_student);
    }
}

void add_student_mid(students * studs, char * new_student)
{
    if(studs->size == 0)
        add_student_end(studs, new_student);
    else
    {
        int mid = (int)ceilf((float)studs->size / 2);
        add_student(studs, mid - 1, new_student);
    }
}

void delete_student(students * studs, int pos)
{
    free(studs->student_arr[pos]);
    for(int i = 0; i < studs->size - 1; i++)
    {
        studs->student_arr[i] = studs->student_arr[i + 1];
    }

    int new_size = studs->size - 1;
    studs->student_arr = (char **)realloc(studs->student_arr, sizeof(char *) * new_size);

    studs->size = new_size;
}

void delete_student_end(students * studs)
{
    if(studs->size > 0)
    {
        free(studs->student_arr[studs->size - 1]);
        int new_size = studs->size - 1;
        studs->student_arr = (char **)realloc(studs->student_arr, sizeof(char *) * new_size);

        studs->size = new_size;
    }
    else
        printf("Empty!\n");
}

void delete_student_start(students * studs)
{
    if(studs->size > 0)
    {
        delete_student(studs, 0);
    }
    else
        printf("Empty!\n");
}


void add_students_from_csv(students * studs)
{
    FILE * student_info_csv = fopen("student-info.csv", "r");

    int row = 0;
    char line[1024];

    while (!feof(student_info_csv))
    {
        row++;
        
        fgets(line, 1024, student_info_csv);

        if(row == 1)
            continue;

        line[strlen(line) - 1] = '\0';
        add_student_end(studs, line);

        if(row == 5)
            break;
    }
    

    fclose(student_info_csv);
}

void print_students(students * studs)
{
    for (int i = 0; i < studs->size; i++)
    {
        printf("%s\n", studs->student_arr[i]);
    }
    
}


int main(int argc, char const *argv[])
{
    students * studs = create_new_studarr();
    add_students_from_csv(studs);

    printf("Array Size: %d\n", studs->size);
    print_students(studs);
    
    printf("-----------------------------\n");

    
    delete_student_start(studs);
    
    printf("Array Size: %d\n", studs->size);
    
    print_students(studs);
    return 0;
}
