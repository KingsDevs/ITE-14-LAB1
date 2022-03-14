#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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
        
        add_student_end(studs, line);
    }
    

    fclose(student_info_csv);
}

void print_students(students * studs)
{
    for (int i = 0; i < studs->size; i++)
    {
        printf("%s", studs->student_arr[i]);
    }
    
}


int main(int argc, char const *argv[])
{
    students * studs = create_new_studarr();
    add_students_from_csv(studs);

    printf("Array Size: %d\n", studs->size);
    print_students(studs);
    
    return 0;
}
