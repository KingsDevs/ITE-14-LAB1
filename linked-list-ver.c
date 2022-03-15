#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<math.h>

typedef struct _node
{
    int student_id;
    char * firstname;
    char * lastname;
    char * middlename;
    char course[5];
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

void addnode_start(linlst_studinfo * headptr, node * new_node)
{
    new_node->next = headptr->next;
    headptr->next = new_node;
    headptr->size++;
}

void print_node(node * will_printnode)
{
    printf("Student Id: %d\n", will_printnode->student_id);
    printf("Fullname: %s, %s, %s\n", will_printnode->lastname, will_printnode->firstname, will_printnode->middlename);
    printf("Course and Year: %s - %d\n", will_printnode->course, will_printnode->year);
    printf("Email: %s\n", will_printnode->email_add);
    printf("Mobile Number: %s\n", will_printnode->mobile_num);
}

void print_allnodes(node * head_node)
{
    if(head_node != NULL)
    {
        print_node(head_node);
        print_allnodes(head_node->next);
    }
    else
        printf("\n");
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
                new_student->middlename = (char *)malloc(strlen(extracted_data) + 1);
                strcpy(new_student->middlename, extracted_data);
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

        addnode_start(headptr, new_student);

        // if(row == 4)
        //     break;   
    }
    
    fclose(student_info_csv);
}

void add_node_end(linlst_studinfo * headptr, node * head, node * new_node)
{
    if(head->next == NULL)
    {
        head->next = new_node;
        headptr->size ++;
    }
    else
    {
        add_node_end(headptr, head->next, new_node);
    }
}

void add_node_mid(linlst_studinfo * headptr, node * head, node * new_node)
{
    int mid = (int)ceilf((float)headptr->size / 2);
    node * curr_node = head;

    for(int i = 1; i <= mid; i++)
    {
        if(i == mid)
        {
            new_node->next = curr_node->next;
            curr_node->next = new_node;
            headptr->size++;
        }
        else
            curr_node = curr_node->next;
    }
}

void delete_start_node(linlst_studinfo * headptr)
{
    if(headptr->size > 0)
    {
        node * head = headptr->next;
        node * new_head = head->next;

        headptr->next = new_head;

        free(head);
        head = NULL;

        headptr->size--;
    }
    else
        printf("The linked list is empty\n");
}

void delete_end_node(linlst_studinfo * headptr, node * head)
{
    if(headptr->size > 0)
    {
        node * curr_node = head;
        node * before_node = head;

        while (1)
        {
            if(curr_node-> next->next == NULL)
            {
                free(curr_node->next);
                curr_node->next = NULL;
            
                headptr->size--;
                break;
            }
            
            curr_node = curr_node->next;

        }
        
    }
    else
        printf("The linked list is empty\n");
}

void delete_mid_node(linlst_studinfo * headptr, node * head)
{
    if(headptr->size > 0)
    {
        int mid = (int)ceilf((float)headptr->size / 2);
        node * curr_node = head;

        for(int i = 1; i < mid; i++)
        {
            if(i == mid - 1)
            {
                node * next = curr_node->next->next;
                free(curr_node->next);
                curr_node->next = next;

                headptr->size--;
            }
            else
                curr_node = curr_node->next;
        }
        
    }
    else
        printf("The linked list is empty\n");
}

node * search_node_at_start(linlst_studinfo * headptr)
{
    return headptr->next;
}

node * search_node_at_mid(linlst_studinfo * headptr)
{
    if(headptr->size > 0)
    {
        int mid = (int)ceilf((float)headptr->size / 2);
        node * curr_node = headptr->next;

        for (int i = 1; i <= mid; i++)
        {
            if (i == mid)
            {
                return curr_node;
            }
            else
                curr_node = curr_node->next;
        }
        
    }
    else
        printf("The linked list is empty\n");
}

node * search_node_at_end(node * head)
{
    if(head->next == NULL)
    {
        return head;
    }
    else
        search_node_at_end(head->next);
}

node * input_node()
{
    node * newnode = create_node();
    char line[100];

    printf("Enter Student Id Number: ");
    scanf(" %d", &newnode->student_id);

    printf("Enter Student Firstname: ");
    scanf(" %[^\n]", line);
    newnode->firstname = (char *)malloc(strlen(line) + 1);
    strcpy(newnode->firstname, line);

    printf("Enter Student Middlename: ");
    scanf(" %[^\n]", line);
    newnode->middlename = (char *)malloc(strlen(line) + 1);
    strcpy(newnode->middlename, line);

    printf("Enter Student Lastname: ");
    scanf(" %[^\n]", line);
    newnode->lastname = (char *)malloc(strlen(line) + 1);
    strcpy(newnode->lastname, line);

    printf("Enter Student Course (4 characters only): ");
    scanf(" %s", newnode->course);

    printf("Enter Student Year: ");
    scanf(" %d", &newnode->year);

    printf("Enter Student Email: ");
    scanf(" %[^\n]", line);
    newnode->email_add = (char *)malloc(strlen(line) + 1);
    strcpy(newnode->email_add, line);

    printf("Enter Mobile Number: ");
    scanf(" %[^\n]", line);
    newnode->mobile_num = (char *)malloc(strlen(line) + 1);
    strcpy(newnode->mobile_num, line);

    return newnode;    
}

int choice_start_mid_end()
{
    int choice;
    printf("1. At Start\n");
    printf("2. At Mid\n");
    printf("3. At End\n");
    printf(">> ");
    scanf(" %d", &choice);

    return choice;
}

void wait()
{
    printf("\nPlease press ENTER to continue");
    fflush(stdin);
    getchar();
}

int main(int argc, char const *argv[])
{

    linlst_studinfo * headptr = create_linkedlist_studinfo();
    for (int i = 0; i < 220; i++)
    {
        addnodes_from_csv(headptr);
    }
    
    struct timeval st, et;    

    while (1)
    {
        printf("size of linked list: %d\n", headptr->size);
        
        int choice;
        printf("1. Insert Student\n");
        printf("2. Search Student\n");
        printf("3. Delete Student\n");
        printf("4. Print All Students\n");
        printf("5. Exit\n");
        printf(">> ");
        scanf(" %d", &choice);

        if(choice == 1)
        {
            node * new_student = input_node();
            choice = choice_start_mid_end();

            switch (choice)
            {
            case 1:
                gettimeofday(&st, NULL);
                addnode_start(headptr, new_student);
                gettimeofday(&et, NULL);
                printf("Node added at the front\n");
                break;
            case 2:
                gettimeofday(&st, NULL);
                add_node_mid(headptr, headptr->next, new_student);
                gettimeofday(&et, NULL);
                printf("Node added at the mid\n");
                break;
            case 3:
                gettimeofday(&st, NULL);
                add_node_end(headptr, headptr->next, new_student);
                gettimeofday(&et, NULL);
                printf("Node added at the end\n");
                break;
            default:
                break;
            }

        }
        else if(choice == 2)
        {
            int choice = choice_start_mid_end();
            node * searched_student;
            switch (choice)
            {
            case 1:
                gettimeofday(&st, NULL);
                searched_student = search_node_at_start(headptr);
                gettimeofday(&et, NULL);
                break;
            case 2:
                gettimeofday(&st, NULL);
                searched_student = search_node_at_mid(headptr);
                gettimeofday(&et, NULL);
                break;
            case 3:
                gettimeofday(&st, NULL);
                searched_student = search_node_at_end(headptr->next);
                gettimeofday(&et, NULL);
                break;
            default:
                break;
            }
            printf("Searched Student:\n");
            print_node(searched_student);
        }
        else if(choice == 3)
        {
            choice = choice_start_mid_end();
            switch (choice)
            {
            case 1:
                gettimeofday(&st, NULL);
                delete_start_node(headptr);
                gettimeofday(&et, NULL);
                break;
            case 2:
                gettimeofday(&st, NULL);
                delete_mid_node(headptr, headptr->next);
                gettimeofday(&et, NULL);
                break;
            case 3:
                gettimeofday(&st, NULL);
                delete_end_node(headptr, headptr->next);
                gettimeofday(&et, NULL);
                break;
            default:
                break;
            }
            printf("Node deleted\n");
        }
        else if(choice == 4)
        {
            gettimeofday(&st, NULL);
            print_allnodes(headptr->next);
            gettimeofday(&et, NULL);
        }
        else
            break;
        
        double elapsed = ((et.tv_sec - st.tv_sec) * 1000000) + ((et.tv_usec - st.tv_usec) * 0.000001);
        printf("Runtime: %lf microseconds\n", elapsed);
        wait();
    }
    
    return 0;
}

