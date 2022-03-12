#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct _node
{
    int student_id;
    char * firstname;
    char * lastname;
    char middle_init;
    char course[4];
    int year;
    char * email_add;
    char * mobile_num;

    struct _node * next;
}node;

typedef struct _linlst_studinfo
{
    int size;
    node * next;
}linlst_studinfo;

node * create_node()
{
    node * created_node = (node *)malloc(sizeof(node));
    created_node->next = NULL;

    return created_node;
}

linlst_studinfo * create_linkedlist_studinfo()
{
    linlst_studinfo * headptr = (linlst_studinfo *)malloc(sizeof(linlst_studinfo));
    headptr->next = NULL;
    headptr->size = 0;

    return headptr;
}

void addnode_studinfo_start(linlst_studinfo * headptr, node * new_node)
{
    clock_t begin = clock();
    
    new_node->next = headptr->next;
    headptr->next = new_node;
    headptr->size++;

    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    printf("Added node at %lfms\n", time_spent/1000);
}

void print_allnodes(node * head_node)
{
    if(head_node != NULL)
    {
        printf("%d. %s\n", head_node->student_id, head_node->firstname);
        print_allnodes(head_node->next);
    }
}

void addnodes_from_csv(linlst_studinfo * headptr)
{
    FILE * student_info_csv = fopen("student-info.csv", "r");

    char line[1024];
    int row  = 0;
    while (!feof(student_info_csv))
    {
        fgets(line, 1024, student_info_csv);
        int column = 0;
        row++;

        if(row == 1)
            continue;

        

        char * extracted_data = strtok(line, ",");
        node  * new_student = create_node();

        while (extracted_data != NULL)
        {
            //printf("%s\n", extracted_data);
            switch (column)
            {
            case 0:
                new_student->student_id = atoi(extracted_data);
                break;
            case 1:
                new_student->firstname = (char *)malloc(strlen(extracted_data) + 1);
                strcpy(new_student->firstname, extracted_data);
                break;
            case 2:
                new_student->middle_init = extracted_data[0];
                break;
            case 3:
                new_student->lastname = (char *)malloc(strlen(extracted_data) + 1);
                strcpy(new_student->lastname, extracted_data);
                break;
            case 4:
                strcpy(new_student->course, extracted_data);
                break;
            case 5:
                new_student->year = atoi(extracted_data);
                break;
            case 6:
                new_student->email_add = (char *)malloc(strlen(extracted_data) + 1);
                strcpy(new_student->email_add, extracted_data);
                break;
            case 7:
                new_student->mobile_num = (char *)malloc(strlen(extracted_data) + 1);
                strcpy(new_student->mobile_num, extracted_data);
                break;
            default:
                break;
            }

            extracted_data = strtok(NULL, ",");
            column++;
        }

        addnode_studinfo_start(headptr, new_student);   
    }
    
}

int main(int argc, char const *argv[])
{

    linlst_studinfo * headptr = create_linkedlist_studinfo();

    clock_t begin = clock();    

    addnodes_from_csv(headptr);

    clock_t end = clock();

    printf("Time spent adding nodes at linked list: %lf \n", (double)(end - begin) / (CLOCKS_PER_SEC / 1000));    
    print_allnodes(headptr->next);
    printf("size of linked list: %d\n", headptr->size);
    
    return 0;
}

