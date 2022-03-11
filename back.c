#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct list
{
    char task[300];
    int flag;
    struct list *link;
};

typedef struct list *NODE;

//function declarations
int read_file();
void print_file(NODE,int);
int header(NODE,int*);
void check_for_streaks(int*,NODE,int*);
void update_streakfile(int,int);
void interface();
void red();
void yellow();
void reset();
void blue();
void purple();
void green();
void cyan();

NODE getnode(){
    NODE x=(NODE)malloc(sizeof(struct list));
    x->link=NULL;
    return x;
}


void insert_at_end(NODE head,char *task_det,int f){
    NODE temp=getnode();
    strcpy(temp->task,task_det);
    temp->flag=f;
    NODE cur=head->link;
    while (cur->link!=head)
        cur=cur->link;
    cur->link=temp;
    temp->link=head;
}

int no_of_tasks_completed(NODE head){
    int number=0;
    NODE cur=head->link;
    while(cur!=head){
        if(cur->flag==1)
            number++;
        cur=cur->link;
    }
    return number;
}

void display(NODE head){
    system("clear");
    if(head->link==head){
        printf("No tasks added");
        return;
    }
    int index=1;

    printf("Your tasks: \n");
    NODE cur=head->link;
    while(cur!=head){
        printf("%d. %s \t\t %d\n",index,cur->task,cur->flag);
        cur=cur->link;
        index++;
    }
    printf("\n0--->Not completed   1--->Completed");
    printf("\nNumber of tasks completed: %d",no_of_tasks_completed(head));
    
}

void delete_by_pos(NODE head,int input_index){
    if(head->link==head){
        printf("List is empty");
        return;
    }
    int index=1;
    NODE cur=head->link,prev=NULL;
    while(index!=input_index){
        prev=cur;
        cur=cur->link;
        index++;
    }
    if(prev==NULL){
        head->link=cur->link;
        free(cur);
        return;
    }
    prev->link=cur->link;
    free(cur);
    printf("\n\nDeletion completed......\n");
    printf("\n\n\nPress any key to go back......");
    getchar();
    getchar();
   
}

void truncate(NODE head){
    NODE temp=head->link;
    NODE cur=NULL;
    while(temp!=head){
        cur=temp;
        free(cur);
        temp=temp->link;
    }
    head->link=head;
}


void update(NODE head,int input_index,int count){
    if(head->link==head){
        printf("List is empty");
        return;
    }
    int index=1;
    NODE cur=head->link;

    while(index!=input_index){
        cur=cur->link;
        index++;
    }
    char mark;
    getchar();
    printf("mark as completed ? press y/n: ");
    scanf("%c",&mark);
    if(mark=='y')
        cur->flag=1;
    printf("\n\nUpdation completed....\n");
    printf("\n\n\nPress any key to go back......");
    getchar();
    getchar();
}

int main(){
    //system("Color 3F");
    //interface'
    interface();
    NODE ToDo=getnode();
    ToDo->link=ToDo;
    int count=0;
    count=read_file(ToDo);
    int ch;
    int Streak=header(ToDo,&count);
    while(1){
        system("clear");
        printf("Streaks: %d\n",Streak);
        time_t currentTime;
        time(&currentTime);
        printf("%s\n",ctime(&currentTime));
        purple();
        printf("\n1.Create a new list\n2.View List\n3.Update your list\n4.Save and Exit\n");
        reset();
        scanf("%d",&ch);
        if(ch==1){
            truncate(ToDo);
            count=0;
            char task_detail[300];
            char choice;
            do{
                system("clear");
                printf("Enter task: \n");
                getchar();
                gets(task_detail);
                insert_at_end(ToDo,task_detail,0);
                count++;
                printf("Task added\n");
                printf("Want to burn up more calories?\nAdd a new task (Press y for yes and n for No)");
                scanf("%c",&choice);
            }while(choice=='y' || choice=='Y');
        }
        else if(ch==2){
            printf("\n");
            display(ToDo);
            printf("\n\n\nPress any key to go back......");
            getchar();
            getchar();
        }
        else if(ch==3){

            while(1){
                system("clear");
                int choice;
                printf("1.Add a task\n2.Delete a task\n3.Mark as completed\n4.Go back\n");
                scanf("%d",&choice);
                if(choice==1){
                    char task_detail[300];
                    system("clear");
                    printf("\n");
                    display(ToDo);
                    printf("\nEnter task: \n");
                    getchar();
                    gets(task_detail);
                    insert_at_end(ToDo,task_detail,0);
                    count++;
                    printf("Task added\n");
                    printf("\n\n\nPress any key to go back......");
                    getchar();
                }
                else if(choice==2){
                    printf("\n");
                    display(ToDo);
                    printf("\nEnter task number: ");
                    int pos;
                    scanf("%d",&pos);
                    delete_by_pos(ToDo,pos);
                    count--;
                   
                }
                else if(choice==3){
                    printf("\n");
                    display(ToDo);
                    printf("\nEnter task number: ");
                    int pos;
                    scanf("%d",&pos);
                    update(ToDo,pos,count);
                }
                else{
                    break;
                }
            }
           
        }
       
        else{
            print_file(ToDo,count);
            int n=no_of_tasks_completed(ToDo);
            update_streakfile(n,Streak);
            break;
        }
    }
}

// Functions
int read_file(NODE head){               //Initialize contents of file before start of main screen
    FILE *fp=fopen("tasks.txt","r");
    rewind(fp);
    int ch = getc(fp);
    int c=0;
    if(ch!=EOF){
        char text[300];
        rewind(fp);
        fscanf(fp,"%d\n",&c);
        NODE temp=getnode();
        char buffer[300];
        int flag;
        int i=c;
        while(i!=0){
            fscanf(fp,"%[^\n]\n",buffer);
            fscanf(fp,"%d\n",&flag);
            insert_at_end(head,buffer,flag);
            i--;
        }
        printf("File read successfully!!\n");
    }
    fclose(fp);
    return c;
}

void print_file(NODE head,int count){           //Save to file after doing modifications
    FILE *fp=fopen("tasks.txt","w");
    rewind(fp);
    fprintf(fp,"%d\n",count);    NODE cur=head->link;
    while (cur!=head)
    {
        fprintf(fp,"%s\n",cur->task);
        fprintf(fp,"%d\n",cur->flag);
        cur=cur->link;
    }
}

void update_streakfile(int completed_tasks,int day_streak){
    time_t currentTime;
    time(&currentTime);
    struct tm *myTime = localtime(&currentTime);
    FILE *s=fopen("streaks.txt","w");
    rewind(s);
    fprintf(s,"%d %d %d %d",myTime->tm_mon,myTime->tm_mday,completed_tasks,day_streak);
}

void check_for_streaks(int *streaks,NODE header,int *count){
    FILE *t=fopen("tasks.txt","r");
    FILE *s=fopen("streaks.txt","r");
    int bh=getc(t);
    int ch=getc(s);
    if(ch==EOF){
        *streaks=0;
        return;
    }
    if(bh==EOF)
        return;
    
    time_t currentTime;
    time(&currentTime);
    struct tm *myTime = localtime(&currentTime);
    rewind(t);  rewind(s);
    int total_count,comp_count;
    int mon,day;
    fscanf(t,"%d\n",&total_count);
    fscanf(s,"%d %d %d %d",&mon,&day,&comp_count,streaks);
    fclose(s);
    fclose(t);
    if(myTime->tm_mon>=mon){
        if((myTime->tm_mday-day)==1){
            if(comp_count==total_count)
                (*streaks)+=1;
            else
                (*streaks)=0;
            truncate(header);
            *count=0;
        }
        else if(myTime->tm_mday==day)   
            return;
        else{
            (*streaks)=0;
            truncate(header);
            *count=0;
        }
    }
    
}

int header(NODE head,int *count){
    int streak;
    check_for_streaks(&streak,head,count);
    return streak;
}

void interface(){
    system("clear");
    cyan();
    printf("\n\n\n\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t-----------------------------------------------------------------------------------------------------\n\n");
    printf("\t> : > : > : > : > : > "
           ": > : > : > :   "
           "WELCOME TO TODO LIST"
           "     : < : < : < : < : < "
           ": < : < : < : <\n\n");
    printf("\t-----------------------------------------------------------------------------------------------------\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\nPress Enter to continue! ");
 
    getchar();
    reset();

}


void red () {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}

void blue(){
    printf("\033[0;34m");
}

void green(){
    printf("\033[0;32m");
}
void purple(){
    printf("\033[0;35m");
}

void cyan(){
    printf("\033[0;36m");
}
