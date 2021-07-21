#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
///////////////////////////////////////////////////////PART 1///////////////////////////////////////////////////////
bool isStrongPassword(const char * username, const char * password) 
{
    //condition 1: password must be at least 8 characters
    int size_password = strlen(password);

    if(size_password<8)
        return false;

    // condition 2: at least 1 uppercase, 1 lowercase, 1 digits, and no special characters
    int uppercase = 0, lowercase = 0, digit = 0, special_char = 0;
    const char *ptr = password; //pointer ptr to track each char in password

    for(int i = 0; i < size_password; i++)
    {
        if(isupper(*(ptr+i))) // check if it is upper case letter
            uppercase += 1;
        else if(islower(*(ptr+i))) // check if it is lower case letter
            lowercase += 1;
        else if(isdigit(*(ptr+i))) // check if it is a digit
            digit += 1;
        else
            special_char += 1; // check if it is a special character
    }

    //condition 3: the password does not contain the username 
    char s1[size_password]; 
    strcpy(s1,password);
    //instantiate a string and copy the password into it
    for(int i = 0; s1[i]; i++)
    {
        s1[i] = tolower(s1[i]); //convert to lower case
    }
    char *res = strstr(s1,username); // check if there is a substring(username in password)

    //condition 4: password has at least 4 letters either lower or upper case(continuously)
    int count = 0; // counter to track the continuous letters
    for(int i = 0; i < size_password; i++)
    {   
        if(count==4)
            break;
        if(isalpha(*(ptr+i))) // if the char detected is a letter
        {
            count+=1; // increment by 1
            for(int j = 1; j < 4 && *(ptr+i+j)!='\0'; j++)
            {            
                if(isalpha(*(ptr+j+i)))
                {
                    count+=1; //if the next char is a letter, count+1
                }
                else
                {
                    count=0; // reset counter if it is not continuous
                    break;// move the pointer
                }
            }
        }
    }
    if(lowercase==0)
        printf("Need at least one lowercase.\n");
    else if (uppercase==0)
        printf("Need at least one uppercase\n");
    else if (digit==0)
        printf("Need at least one digit.\n");
    else if (special_char!=0)
        printf("It has special char, not allowed\n");
    else if (res!=NULL)
        printf("Contain users name: %s\n",res);
    else if (count!=4)
        printf("Need continues 4 letters.");
    

    if(size_password >= 8 && lowercase != 0 && uppercase != 0 && digit != 0 
        && special_char == 0 && res == NULL && count == 4)
        return true; // combine all the condition to validate whether it is a strong password

	return false;
}

///////////////////////////////////////////////////////PART 2///////////////////////////////////////////////////////
bool isStrongDefaultPassword(const char* username, const char* password) 
{
	//TODO: your code goes here.
    int size_default_password = strlen(password);

    if(size_default_password<8||size_default_password>15)
        return false;// double check size

    // condition 1: at least 1 uppercase, 1 lowercase, 1 digits, and no special characters
    int uppercase = 0, lowercase = 0, digit = 0, special_char = 0;
    const char *ptr = password; //pointer ptr to track each char in password

    for(int i = 0; i < size_default_password; i++)
    {
        if(isupper(*(ptr+i))) // check if it is upper case letter
            uppercase += 1;
        else if(islower(*(ptr+i))) // check if it is lower case letter
            lowercase += 1;
        else if(isdigit(*(ptr+i))) // check if it is a digit
            digit += 1;
        else
        {
            special_char+=1;
        }      
    }

    //condition 2: the password does not contain the username 
    char s1[size_default_password]; 
    strcpy(s1,password);
    //instanciate a string and copy the password into it
    for(int i = 0; s1[i]; i++)
    {
        s1[i] = tolower(s1[i]); //convert to lower case
    }
    char *res = strstr(s1,username); // check if there is a substring(username in password)

    if(lowercase != 0 && uppercase != 0 && digit != 0 && special_char==0 && res == NULL)
        return true; // all default password conditions passed

	return false;
}
void generateDefaultPassword(char * default_password, const char * username) 
{
    printf("Generating a default password...\n");	
    srand(time(0));
    char num[] = "0123456789"; // int array contains 0-9
    char lower[] = "abcdefghijklmnoqprstuvwxyz"; // array contains lowercase letter a-z
    char upper[] = "ABCDEFGHIJKLMNOQPRSTUVWXYZ"; // array contains uppercase letter A-Z
    int ran = rand() % 3; // range 0-2, according to three arrays above

    //condition: default password must be no longer than 15 char and less than 8 char(part 1)
    int upp = 15; // upper bound
    int low = 8; // lower bound
    int size_default = (rand() % (upp - low +1)) + low; //size of the password array generate randomly

    for(int i = 0; i < size_default; i++)
    {
        if(ran==0)
        {   
            default_password[i] = num[rand()%10]; // generate a number randomly
            ran = rand() % 3;//reset the randomizer
        }
        else if(ran==1)
        {
            default_password[i] = lower[rand()%26]; // generate a lowercase letter randomly
            ran = rand() % 3;//reset the randomizer
        }
        else
        {
            default_password[i] = upper[rand()%26]; // generate a uppercase letter randomly
            ran = rand() % 3;//reset the randomizer
        }
    }
    default_password[size_default] = '\0';//set the last char to \0
    while(isStrongDefaultPassword(username,default_password)==false) // if not a strong default password
    {
        generateDefaultPassword(default_password,username); //regenerate until it passes all conditions
    }
}
int main(void)
{

    char username[51]; //50 (+ 1 for null terminator)
    char password[51];

    printf("Enter username: \n"); //ask user for an username
    scanf("%s", username);
    
    char default_password[16]; // array to store default password
    generateDefaultPassword(default_password, username); //generate default password
    printf("Generated default password: %s\n",default_password); // show the password

    char answer[10];// array to store the answer if the user want to input own password
    printf("Would you like to change the default password?\n");
    scanf("%s",answer);

    for(int i = 0; answer[i];i++)
    {
        answer[i] = tolower(answer[i]);
    }

    if(strcmp(answer,"yes")==0) // if the user says "yes"
    {
        printf("Enter your own password: \n");
        scanf("%s",password);
        //check user enter-password validation
        while(isStrongPassword(username,password)==false)
        {
            printf("Your password is weak. Try again!\n");
            printf("Enter your own password: \n");
            scanf("%s",password);
            if(isStrongPassword(username,password)==true)
            {
                printf("Strong password!\n");
                break;
            }
        }
    }
    return 0;
}