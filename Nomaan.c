#include <stdio.h>
#include <stdlib.h>
// Main Function
int main(){
    printf("_________________________________\n");
    printf("            Bookers              \n");
    printf("_________________________________\n");
    int choice=0;
    // Menu Options
    printf("Your Choice:\n");
    printf("1. Sign Up\n");
    printf("2. User Login\n");
    printf("3. Admin Login\n");
    scanf("%d",&choice);
// Handling User Choice
   if(choice==1){
       printf("1. As User\n");
       printf("2. As Admin\n");
       int signup_choice=0;
       scanf("%d",&signup_choice);
       if(signup_choice==1){
           printf("User Sign Up Selected\n");
           // Call User Sign Up Function Here
       }
       else if(signup_choice==2){
           printf("Admin Sign Up Selected\n");
           // Call Admin Sign Up Function Here
       }
       else{
           printf("Invalid Sign Up Choice\n");
       }
    }
    if (choice == 1) {
    char username[10000];
    char password[100];

    printf("Choose Username: ");
    scanf("%s", username);
    printf("Choose Password: ");
    scanf("%s", password);

    FILE *f = fopen("users.txt", "a");
    if (f == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(f, "%s %s\n", username, password);
    fclose(f);

    printf("User registered successfully!\n");
}
    else if(choice==2){
        printf("User Login Selected\n");
        // Call User Login Function Here
    }
    else if(choice==3){
        printf("Admin Login Selected\n");
        // Call Admin Login Function Here
    }
    else{
        printf("Invalid Choice\n");
    }   

    
    
    return 0;
}