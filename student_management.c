#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int id;
    char name[100];
    float marks;
};

void addStudent()
{
    FILE *fp = fopen("students.txt", "ab");
    struct Student s;

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    getchar();

    printf("Enter Student Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents()
{
    FILE *fp = fopen("students.txt", "rb");
    struct Student s;

    if (fp == NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("\nID\tName\t\tMarks\n");

    while (fread(&s, sizeof(struct Student), 1, fp) == 1)
    {
        printf("%d\t%s\t%.2f\n", s.id, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp=fopen("students.txt","rb");
    struct Student s;
    int id,found=0;

    if(fp==NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d",&id);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.id==id)
        {
            printf("\nStudent Found\n");
            printf("ID : %d\n",s.id);
            printf("Name : %s\n",s.name);
            printf("Marks : %.2f\n",s.marks);
            found=1;
            break;
        }
    }

    if(!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void updateStudent()
{
    FILE *fp=fopen("students.txt","rb+");
    struct Student s;
    int id,found=0;

    if(fp==NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Student ID to Update: ");
    scanf("%d",&id);

    getchar();

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.id==id)
        {
            printf("Enter New Name: ");
            fgets(s.name,sizeof(s.name),stdin);
            s.name[strcspn(s.name,"\n")]='\0';

            printf("Enter New Marks: ");
            scanf("%f",&s.marks);

            fseek(fp,-sizeof(s),SEEK_CUR);
            fwrite(&s,sizeof(s),1,fp);

            found=1;
            break;
        }
    }

    fclose(fp);

    if(found)
        printf("Student Updated Successfully!\n");
    else
        printf("Student Not Found!\n");
}

void deleteStudent()
{
    FILE *fp=fopen("students.txt","rb");
    FILE *temp=fopen("temp.txt","wb");

    struct Student s;
    int id,found=0;

    if(fp==NULL)
    {
        printf("No Records Found!\n");
        return;
    }

    printf("Enter Student ID to Delete: ");
    scanf("%d",&id);

    while(fread(&s,sizeof(s),1,fp))
    {
        if(s.id!=id)
            fwrite(&s,sizeof(s),1,temp);
        else
            found=1;
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt","students.txt");

    if(found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Student Not Found!\n");
}

int main()
{
    int choice;

    do
    {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("Thank You!\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    }while(choice!=6);

    return 0;
}