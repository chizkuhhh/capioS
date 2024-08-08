#include <stdio.h>
#include <stdlib.h> // where the rand() function is stored
#include <time.h> // makes the srand(time(NULL)) line usable, since the numbers aren't actually randomized without this
#include <string.h>
#include <conio.h> // for the getch() function
#include <unistd.h> // sleep function

#define MAX_USERS 30
#define MAX_MSGS 1000
#define MAX_SIZE 101

typedef char string[MAX_SIZE];

struct userTag
{
    string fullName;
    string userName;
    int userID;
    string passWord; // change into string
    string rePass; // change into string
    int secuQuesNo;
    string secuQuestion;
    string userDescription;
    int isLocked;
};

struct loginInfo
{
    string userName;
    string passWord; // change into string
};

typedef struct messageInfo
{
    string strSubject;
    string strMessage;
} messageInfo;

typedef struct messageDisplay
{
    string timestamp;
    string sender;
    string receiver;
    string strSubject;
    string strMessage;
} messageDisplay;

typedef struct userTag userTag; // so you don't have to type "struct userTag", "userTag" na lang
typedef struct loginInfo loginInfo;
typedef userTag userList[MAX_USERS];
typedef messageDisplay msgArray[MAX_MSGS];
typedef string Questions[100]; // for array of questions

// function prototypes
void displayMenu(int);
void displayUserModule();
void displayAdminModule();
void displayAdminUsersModule();
void displayComposeMessage();
int loadSecuQues(Questions);
int randomizeQuestion(Questions, int);
int checkFileExists(string);
void addUser(userList, int*, int);
void viewUsers(userList, int, int, string, messageInfo);
void saveInfotoFile(userList, int);
void loadUserList(userList, int*);
void displayModifyPC();
int loginPage(userList, int*, loginInfo, int);
void changeAdminPass(string);
void loadAdminPass(string);
void personalMessage(string, messageInfo);
void groupMessage(string, messageInfo);
void sendAnnouncement(userList, int, messageInfo, string);
int loadAnnouncements(msgArray);
void viewAnnouncements(msgArray, int);
int loadSent(string, msgArray);
void displaySent(msgArray, int);
int loadInbox(string, msgArray);
void displayInbox(msgArray, int, string, messageInfo);
void replyToPM(string, string, string, string, messageInfo);
void replyToGM(string, string, string, string, string, messageInfo);
void composeMessage(userList, int, messageInfo, string);
void userModule(userList, int, messageInfo, string, msgArray);
void adminModule(userList, int, string);
void displayModifyPC();
void modifyPersonalContents(string, userList, int);
void displayModifyAS();
void modifyAccountSecurity(string, userList, int);
void displayModifyPCon();
void modifyPersonalConnections(string, userList, int);
int checkPersonalConnections(string, string);
void viewUsersAdmin(userList, int);
void adminUsers(userList, int);
void displayListofUsers(userList, int);
void displaySelectedUser(userList, int, int);
void modifyUser(userList, int, int);
void replaceWordinFile(string, string, string);
void forgotPassword(userList, int, string);
void deleteUserNamefromFile(string, string);
void replaceSenderLine(string, string, string);
void displayAdminMessages();
int checkContent(string);
int loadMessages(msgArray);
void viewMessages(msgArray, int);
void adminMessages(userList, int);
void filterBySender(userList, int, msgArray, int, int);
void filterByRecipient(userList, int, msgArray, int, int);
int isUserNameinLine(string, int, string);
void deleteMessageLine(string, int);
int findTimestamp(string, string);
int selectMessagetoDelete(msgArray, int);
void displayUserList(userList, int, string);
void encryptPass(string);
void loadSecurityQuestions();

/*
displayMenu displays the homescreen or the main page of the program
*/
void displayMenu(int numUsers)// done
{
    system("cls");
    printf("------------------------------ Homescreen ------------------------------\n");
    printf("Total number of users: %d\n\n", numUsers);
    printf("\t[1] Log in to Existing Account\n");
    printf("\t[2] Sign Up for a New Account\n");
    printf("\t[3] Access ADMIN MODULE\n");
    printf("\t[4] Exit\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/*
displayUserModule displays the menu for the user module, to be shown when a user 
successfully logs into the system
*/
void displayUserModule()
{
    system("cls");
    printf("------------------------------ User Module -----------------------------\n");
    printf("\t[1] Compose Message\n");
    printf("\t[2] Inbox\n");
    printf("\t[3] Sent\n");
    printf("\t[4] View Announcements\n");
    printf("\t[5] Modify Personal Contents\n");
    printf("\t[6] Modify Account Security\n");
    printf("\t[7] Modify Personal Connections\n");
    printf("\t[8] Browse Users\n");
    printf("\t[9] Log Out\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/*
displayAdminModule displays the menu for the admin module, to be shown when
an administrator successfully logs into the admin account
*/
void displayAdminModule()
{
    system("cls");
    printf("----------------------------- Admin Module -----------------------------\n");
    printf("\t[1] Users\n");
    printf("\t[2] Messages\n");
    printf("\t[3] Change ADMIN Password\n");
    printf("\t[4] Return to Homescreen\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/*
displayAdminUsersModule displays the menu for the user module of the administrator, in which they can
execute actions that have to do with the program's registered users
*/
void displayAdminUsersModule()
{
    system("cls");
    printf("-------------------------------- Users ---------------------------------\n");
    printf("\t[1] View Users\n"); // done
    printf("\t[2] Modify Users\n");
    printf("\t[3] Refresh User Account Password\n");
    printf("\t[4] Delete Users\n");
    printf("\t[5] Security Questions\n");
    printf("\t[6] Return to ADMIN Module\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/*
displayComposeMessage displays the menu for when a user selects the compose message
option in the user module; in this menu they can select from composing a personal message,
a group message, or an announcement for all the users
*/
void displayComposeMessage()
{
    system("cls");
    printf("--------------------------- Compose Message ----------------------------\n");
    printf("\t[1] Personal Message\n");
    printf("\t[2] Group Message\n"); 
    printf("\t[3] Make an Announcement\n");
    printf("\t[4] Return to User Module\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/*
displayAdminMessages displays the menu for the messages module of the administrator;
in this menu, they can view all the messages, view them either by sender or by recipient,
and they can also delete a message
*/
void displayAdminMessages()
{
    system("cls");
    printf("------------------------------- Messages -------------------------------\n");
    printf("\t[1] View Messages\n"); 
    printf("\t[2] View by Filter\n");
    printf("\t[3] Delete Message\n");
    printf("\t[4] Return to ADMIN Module\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/* loadSecuQues reads the contents of a file named "SECUQUES.txt" and loads 
the questions into an array of strings. It then returns the total number of questions read from the file.
@param ques - an array of strings where the questions will be stored
@return lineCount (an integer value indicating the total number of questions read from the file)
Pre-condition: "SECUQUES.txt" file should contain one question per line
*/
int loadSecuQues(Questions ques)
{
    int lineCount = 0, i;
    FILE *quesFile;
    string strLine;
    char ch;

    quesFile = fopen("SECUQUES.txt", "rt");

    if(quesFile != NULL)
    {
        // reads lines until EOF is encountered
        while ((ch = fgetc(quesFile)) != EOF)
        {
            if (ch == '\n')
                lineCount++;
        }

        fclose(quesFile);
    }

    quesFile = fopen("SECUQUES.txt", "rt");

    for (i = 0; i<lineCount; i++)
    {
        fgets(strLine, sizeof(strLine), quesFile);;
        strcpy(ques[i], strLine);
    }

    fclose(quesFile);

    return lineCount;
}

/*
randomizeQuestion randomly selects a question from an array of questions and prints it on the console. 
It then returns the index of the selected question in the array.
@param ques - a pointer to an array of strings containing the questions
@param totalQuestions - an integer value indicating the total number of questions in the array
@return nQues (an integer value indicating the index of the selected question in the array)
Pre-condition: ques must have at least one question stored in it
*/
int randomizeQuestion(Questions ques, int totalQuestions)
{
    int nQues;
    srand(time(NULL));
	nQues = rand() % totalQuestions; // generates a number depending on how many questions there are

    printf("%s", ques[nQues]);

    return nQues;
}

/*
checkFileExists checks if a file with the given filename exists in the current directory. 
It returns 1 if the file exists and 0 if it does not
@param fileName - a string containing the name of the file to be checked for existence
@return 1 if the file exists and 0 if it does not
Pre-condition: None
*/
int checkFileExists(string fileName)
{
    FILE *fptr;
    if ((fptr = fopen(fileName, "r"))!= NULL)
    {
        fclose(fptr);
        return 1;
    }
    return 0;
}

/*
addUser creates a new user account and saves it to the userList.
It asks for the user's full name, username, password, and a security question.
It also checks if the username already exists in the database.
If the username is unique and the password is valid, it creates a file for the user's inbox, sent messages, and personal connections.
@param users - the array of user accounts where the new user will be stored
@param numUsers - a pointer to the integer variable indicating the current number of users in the array
@param choice - an integer value representing the user's choice in the menu
Pre-condition: users should be an initialized array of user accounts with size greater than or equal to *numUsers + 1
*/
void addUser(userList users, int *numUsers, int choice)
{
    string userInbox, userSent, userPC;
    FILE *userInboxFile, *userSentFile, *userPersonalConnections;
    Questions ques;
    int totalQuestions = loadSecuQues(ques);
    
    fflush(stdin); // flushes newline character from previous input
    printf("----------------------------- Add New User -----------------------------\n");
    printf("Name: ");
    fgets(users[*numUsers].fullName, sizeof(users[*numUsers].fullName), stdin);
    users[*numUsers].fullName[strlen(users[*numUsers].fullName) - 1] = '\0';

    fflush(stdin);
    printf("Username: ");
    fgets(users[*numUsers].userName,sizeof(users[*numUsers].userName),stdin);
	users[*numUsers].userName[strlen(users[*numUsers].userName) - 1] = '\0';	
	users[*numUsers].userID = *numUsers;

    fflush(stdin);
    printf("Password: ");
    fgets(users[*numUsers].passWord, sizeof(users[*numUsers].passWord), stdin); // gagawing fgets din
    users[*numUsers].passWord[strlen(users[*numUsers].passWord) - 1] = '\0';

    fflush(stdin);
    printf("Re-enter password: ");
    fgets(users[*numUsers].rePass, sizeof(users[*numUsers].rePass), stdin); //fgets din
    users[*numUsers].rePass[strlen(users[*numUsers].rePass) - 1] = '\0';

    fflush(stdin);

    users[*numUsers].secuQuesNo = randomizeQuestion(ques, totalQuestions);
    fgets(users[*numUsers].secuQuestion,sizeof(users[*numUsers].secuQuestion),stdin);
	users[*numUsers].secuQuestion[strlen(users[*numUsers].secuQuestion) - 1] = '\0';

    // make "DEFAULT USER" the default description
    strcpy(users[*numUsers].userDescription, "DEFAULT USER");
    users[*numUsers].isLocked = 0; // account is unlocked by default
    printf("------------------------------------------------------------------------\n");
	
    // check if the username already exists
    // if not, then check if the password and the re-entered password match each other
    // if they match, then create a file for the user's inbox, sent messages, and announcements

    strcpy(userInbox, users[*numUsers].userName); // assign the username to inbox
    strcat(userInbox, "Inbox.txt");

    strcpy(userSent, users[*numUsers].userName);
    strcat(userSent, "Sent.txt");

    strcpy(userPC, users[*numUsers].userName);
    strcat(userPC, "PC.txt");
    
    if (checkFileExists(userInbox) || checkFileExists(userSent) || checkFileExists(userPC))
    {
        printf("Error! Username already exists in database. Enter '5' to go back to homescreen.");
    }
    else
    {
        if (strcmp(users[*numUsers].passWord, users[*numUsers].rePass) == 0) // gawing strcmp
        {
            userInboxFile = fopen(userInbox, "wt"); // creates the inbox file for each user
            userSentFile = fopen(userSent, "wt"); // creates the sent file for each user
            userPersonalConnections = fopen(userPC, "wt"); // creates the personal connections file for each user

            fclose(userInboxFile);
            fclose(userSentFile);
            fclose(userPersonalConnections);

            (*numUsers)++;

            printf("Account successfully created!");
            sleep(1);
            displayMenu(*numUsers);
        }
        else
        {
            printf("Error! Passwords entered do not match. Enter '5' to go back to homescreen.");
        }
    }
}

/*
displayUserList displaya the list of users stored in the system. If there are no users, it displays 
a message stating that there are no users in the database. If there are users, it displays the total number 
of users and a list of all the users with their corresponding user ID and username. 
At the end, it prompts the user to enter a user ID to select a user
@param users - the array of user accounts where the new user will be stored
@param numUsers - a pointer to the integer variable indicating the current number of users in the array
Pre-condition: users should be an initialized array of user accounts with size greater than or equal to *numUsers + 1
*/
void displayUserList(userList users, int numUsers, string sender)
{
    // view list of users first
    int i;

    if (numUsers == 0)
    {
        system("cls");
        printf("----------------------------- Browse Users -----------------------------\n");
        printf("%55s", "There are currently no users in the database.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to User Module. ");

        getch();
    }
    else
    {
        system("cls");
        printf("----------------------------- Browse Users -----------------------------\n");
        printf("Total number of users: %d\n\n", numUsers);
        for (i = 0; i<numUsers; i++)
        {
            if (strcmp(sender, users[i].userName) != 0)
                printf("\t[%d] %s\n", users[i].userID, users[i].userName);
        }
        printf("------------------------------------------------------------------------\n");
        printf("Enter UserID to select a user: ");
    }
}

/*
viewUsers is used to view the details of a selected user, as well as send them a personal 
message or add them to the current user's personal connections list.
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param selectedUser - the index of the user that the current user has selected to view
@param sender - the username of the current user who is viewing the selected user's information
@param msg - a struct that contains the message subject and message body that the current user wants to send to the selected user
Pre-condition: valid content is stored in users, sender, and msg; 
the necessary input and output files exist and are accessible for reading and writing
*/
void viewUsers(userList users, int numUsers, int selectedUser, string sender, messageInfo msg)
{
    int bStop = 0;
    char cChoice;

    time_t curTime;
    string timestamp;

    string fileName;
    FILE *inbox, *sent, *allMsgs, *userPC;

    // display the details of the selected user
    do
    {
        system("cls");
        printf("----------------------------- Browse Users -----------------------------\n");
        printf("Name: %s\n", users[selectedUser].fullName);
        printf("Username: %s\n", users[selectedUser].userName);
        printf("Description: %s\n", users[selectedUser].userDescription);
        printf("------------------------------------------------------------------------\n");
        printf("[S]end Message  [A]dd to Personal Connections   [R]eturn");
        cChoice = getch();
        
        if (cChoice == 's' || cChoice == 'S')
        {
            // send the user a personal message
            printf("\n\nSending %s a Personal Message\n", users[selectedUser].userName);
            fflush(stdin);
            printf("Subject: ");
            fgets(msg.strSubject, sizeof(msg.strSubject), stdin);
            msg.strSubject[strlen(msg.strSubject) - 1] = '\0';

            fflush(stdin);
            printf("Message: ");
            fgets(msg.strMessage, sizeof(msg.strMessage), stdin);
            msg.strMessage[strlen(msg.strMessage) - 1] = '\0';

            // set timestamp for all versions of the msg
            curTime = time(NULL);
            strcpy(timestamp, ctime(&curTime));

            // open the reciever inbox file and store the sender, subject, and message
            strcpy(fileName, users[selectedUser].userName);
            strcat(fileName, "Inbox.txt");

            if (checkFileExists(fileName))
            {   
                inbox = fopen(fileName,"a+");
                fprintf(inbox, "%s", timestamp);
                fprintf(inbox, "%s\n", sender);
                fprintf(inbox, "Personal Message\n");
                fprintf(inbox, "%s\n", msg.strSubject);
                fprintf(inbox, "%s\n", msg.strMessage);

                fclose(inbox);
                printf("\nMessage successfully sent!");

                // store the same info in the universal messages file
                allMsgs = fopen("ALLMSGS.txt", "a+");
                fprintf(allMsgs, "%s", timestamp);
                fprintf(allMsgs, "Sent by: %s\n", sender);
                fprintf(allMsgs, "Sent to: %s\n", users[selectedUser].userName);
                fprintf(allMsgs, "Subject: %s\n", msg.strSubject);
                fprintf(allMsgs, "Message: %s\n", msg.strMessage);
                fclose(allMsgs);
            }

            // open the sender sent file and store the reciever, subject, and message
            strcpy(fileName, sender);
            strcat(fileName, "Sent.txt");

            if (checkFileExists(fileName))
            {
                sent = fopen(fileName, "a+");
                fprintf(sent, "%s", timestamp);
                fprintf(sent, "Sent to: %s\n", users[selectedUser].userName);
                fprintf(sent, "Subject: %s\n", msg.strSubject);
                fprintf(sent, "Message: %s\n", msg.strMessage);

                fclose(sent);
            }

            sleep(1);
            bStop = 1;
        }
        else if (cChoice == 'a' || cChoice == 'A')
        {
            // open current user's pc file
            strcpy(fileName, sender);
            strcat(fileName, "PC.txt");

            // if the selected user isn't in the current user's personal connections yet
            if (checkPersonalConnections(users[selectedUser].userName, fileName) != 1)
            {
                userPC = fopen(fileName, "a+");
                fprintf(userPC, "%s\n", users[selectedUser].userName);
                printf("\n\nUser successfully added to personal connections!");
                fclose(userPC);
                sleep(1);
            }
            else if (checkPersonalConnections(users[selectedUser].userName, fileName))
            {
                printf("\n\nUser is already in your personal connections...");
                sleep(1);
            }

            bStop = 1;
        }
        else if (cChoice == 'r' || cChoice == 'R')
        {
            bStop = 1;
        }
    } while (!bStop);
}

/*
saveInfotoFile saves the information of all users in the system to a text file named "users.txt". 
It takes as input the user list and the number of users in the list. The function opens the file 
in write text mode and writes the number of users to the file followed by the information of each user, including 
their ID, full name, username, password, security question number, security question, user description, and lock status.
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
Pre-condition: "users.txt" file should exist and be writable by the program, 
or it should be possible for the program to create the file if it does not exist
*/
void saveInfotoFile(userList users, int numUsers)
{
    int i;
    FILE *fptr;

    fptr = fopen("users.txt", "wt"); // creates the file users.txt if it doesn't exist

    if (fptr != NULL) // file exists
    {
        fprintf(fptr, "%d\n", numUsers);
        for (i = 0; i < numUsers; i++)
        {
            fprintf(fptr, "%d\n", users[i].userID);
            fprintf(fptr, "%s\n", users[i].fullName);
            fprintf(fptr, "%s\n", users[i].userName);
            fprintf(fptr, "%s\n", users[i].passWord);
            fprintf(fptr, "%d\n", users[i].secuQuesNo);
            fprintf(fptr, "%s\n", users[i].secuQuestion);
            fprintf(fptr, "%s\n", users[i].userDescription);
            fprintf(fptr, "%d\n", users[i].isLocked);
        }

        fclose(fptr); // close the file
    }
    else
        printf("Error! Unable to save user database...\n");
}

// load users from users.txt in to the program
void loadUserList(userList users, int *numUsers)
{
    int i;
    
    FILE *fptr;
    string strLine;

    fptr = fopen("users.txt", "rt"); // read text from file
    if (fptr != NULL)
    {
        // read no. of users
        fgets(strLine, sizeof(strLine), fptr);
        *numUsers = atoi(strLine);

        // loop through text file, read each user's info
        for (i = 0; i < *numUsers; i++)
        {
            // user ID
            fgets(strLine, sizeof(strLine), fptr);
            users[i].userID = atoi(strLine);

            // name
            fgets(strLine, sizeof(strLine), fptr);
            strLine[strlen(strLine) - 1] = '\0'; // remove newline character
            strcpy(users[i].fullName, strLine);

            // username
            fgets(strLine, sizeof(strLine), fptr);
            strLine[strlen(strLine) - 1] = '\0'; // remove newline character
            strcpy(users[i].userName, strLine);

            // password
            fgets(strLine, sizeof(strLine), fptr);
            strLine[strlen(strLine) - 1] = '\0';
            strcpy(users[i].passWord, strLine); // magiging strcpy na rin

            // security question number
            fgets(strLine, sizeof(strLine), fptr);
            users[i].secuQuesNo = atoi(strLine);

            // security question answer
            fgets(strLine, sizeof(strLine), fptr);
            strLine[strlen(strLine) - 1] = '\0'; // remove newline character
            strcpy(users[i].secuQuestion, strLine);

            // user description
            fgets(strLine, sizeof(strLine), fptr);
            strLine[strlen(strLine) - 1] = '\0'; // remove newline character
            strcpy(users[i].userDescription, strLine);

            // isLocked
            fgets(strLine, sizeof(strLine), fptr);
            users[i].isLocked = atoi(strLine);
        }

        fclose(fptr);
    }
    else // no users.txt file yet
        *numUsers = 0;
}

/*
displayModifyPC displays the menu for modifying personal contents, which can be accessed from the user module
*/
void displayModifyPC()
{
    system("cls");
    printf("----------------------- Modify Personal Contents ------------------------\n");
    printf("\t[1] Change Your Name\n");
    printf("\t[2] Edit User Description\n"); 
    printf("\t[3] Return to User Module\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/*
modifyPersonalContents allows the current user to modify their personal information, such as their name and user description
@param currentUser - username of the current user
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
Pre-condition: users array must have at least one element, numUsers must be greater than 0, and currentUser must be a registered user
*/
void modifyPersonalContents(string currentUser, userList users, int numUsers)
{
    int nChoice, i, userIndex;
    string nameTemp, descTemp, passTemp;

    // get the current user's userID or index
    for (i = 0; i<numUsers; i++) 
    {
        if (strcmp(currentUser, users[i].userName) == 0)
        {
            userIndex = i;
            i = numUsers-1;
        }
    }

    do
    {
        displayModifyPC();
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                // change name
                system("cls");
                printf("--------------------------- Change Your Name ---------------------------\n");
                fflush(stdin);
                printf("Current Name: %s\n", users[userIndex].fullName);
                printf("Enter New Name: ");
                fgets(nameTemp, sizeof(nameTemp), stdin);
                nameTemp[strlen(nameTemp) - 1] = '\0';

                fflush(stdin);
                printf("Enter password to confirm: ");
                fgets(passTemp, sizeof(passTemp), stdin);
                passTemp[strlen(passTemp) - 1] = '\0';
                printf("------------------------------------------------------------------------\n");

                if (strcmp(passTemp, users[userIndex].passWord) == 0)
                {
                    strcpy(users[userIndex].fullName, nameTemp);
                    printf("Name changed successfully!");
                    sleep(1);
                }
                else
                {
                    printf("Incorrect pasword! Could not change your name...");
                    sleep(1);
                }
                break;
            case 2:
                system("cls");
                printf("------------------------- Edit User Description ------------------------\n");
                fflush(stdin);
                printf("Current Description: %s\n", users[userIndex].userDescription);
                printf("Enter New Description: ");
                fgets(descTemp, sizeof(descTemp), stdin);
                descTemp[strlen(descTemp) - 1] = '\0';

                fflush(stdin);
                printf("Enter password to confirm: ");
                fgets(passTemp, sizeof(passTemp), stdin);
                passTemp[strlen(passTemp) - 1] = '\0';
                printf("------------------------------------------------------------------------\n");

                if (strcmp(passTemp, users[userIndex].passWord) == 0)
                {
                    strcpy(users[userIndex].userDescription, descTemp);
                    printf("User description changed successfully!");
                    sleep(1);
                }
                else
                {
                    printf("Incorrect pasword! Could not change your description...");
                    sleep(1);
                }
                break;
            case 3:
                displayUserModule();
                break;
            default:
                printf("\nInvalid input, please try again.\n");
                break;
        }
    } while (nChoice != 3);
    
}

/*
displayModifyAS displays the modify account security menu in which a user can change their
password or security question answer; this is accessible through the user module
*/
void displayModifyAS()
{
    system("cls");
    printf("----------------------- Modify Account Security ------------------------\n");
    printf("\t[1] Change Password\n");
    printf("\t[2] Change Security Question Answer\n"); 
    printf("\t[3] Return to User Module\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/*
modifyAccountSecurity allows the current user to modify their security information, such as their password and
security question answer
@param currentUser - username of the current user
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
Pre-condition: users array must have at least one element, numUsers must be greater than 0, and currentUser must be a registered user
*/
void modifyAccountSecurity(string currentUser, userList users, int numUsers)
{
    int nChoice, i, userIndex;
    string secuQuesTemp, secuQuesTempRedo, passTemp, newPass, newPassRedo;
    Questions ques;
    int totalQuestions = loadSecuQues(ques);

    // get the current user's userID or index
    for (i = 0; i<numUsers; i++) 
    {
        if (strcmp(currentUser, users[i].userName) == 0)
        {
            userIndex = i;
            i = numUsers-1;
        }
    }

    do
    {
        displayModifyAS();
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                system("cls");
                printf("---------------------------- Change Password ---------------------------\n");
                fflush(stdin);
                printf("Enter OLD Password: ");
                fgets(passTemp, sizeof(passTemp), stdin);
                passTemp[strlen(passTemp) - 1] = '\0';

                fflush(stdin);
                printf("Enter New Password: ");
                fgets(newPass, sizeof(newPass), stdin);
                newPass[strlen(newPass) - 1] = '\0';

                fflush(stdin);
                printf("Re-enter New Password: ");
                fgets(newPassRedo, sizeof(newPassRedo), stdin);
                newPassRedo[strlen(newPassRedo) - 1] = '\0';
                printf("------------------------------------------------------------------------\n");

                if (strcmp(newPass, newPassRedo) == 0 && strcmp(passTemp, users[userIndex].passWord) == 0)
                {
                    strcpy(users[userIndex].passWord, newPass);
                    printf("Password changed successfully!");
                    sleep(1);
                }
                else
                    printf("Error! Could not change password, please check for any corrections...");
                    sleep(1);
                break;
            case 2:
                system("cls");
                printf("-------------------- Change Security Question Answer -------------------\n");
                fflush(stdin);
                printf("%s\n", ques[users[userIndex].secuQuesNo]);

                printf("Current Answer: %s\n", users[userIndex].secuQuestion);
                
                fflush(stdin);
                printf("NEW Answer: ");
                fgets(secuQuesTemp, sizeof(secuQuesTemp), stdin);
                secuQuesTemp[strlen(secuQuesTemp) -1 ] = '\0';

                fflush(stdin);
                printf("Re-enter NEW Answer: ");
                fgets(secuQuesTempRedo, sizeof(secuQuesTempRedo), stdin);
                secuQuesTempRedo[strlen(secuQuesTempRedo) -1 ] = '\0';

                fflush(stdin);
                printf("Enter password to confirm: ");
                fgets(passTemp, sizeof(passTemp), stdin);
                passTemp[strlen(passTemp) - 1] = '\0';
                printf("------------------------------------------------------------------------\n");

                if (strcmp(passTemp, users[userIndex].passWord) == 0 && strcmp(secuQuesTemp, secuQuesTempRedo) == 0)
                {
                    strcpy(users[userIndex].secuQuestion, secuQuesTemp);
                    printf("Security Question answer changed successfully!");
                    sleep(1);
                }
                else
                    printf("Failed to change security question answer...");
                    sleep(1);
        }
    } while (nChoice != 3);
    
}

/*
displayModifyPCon displays the menu for the modify personal connections module, in which users
are able to add or remove personal connections, view personal connections, and view user connections;
this is accessible through the user module
*/
void displayModifyPCon()
{
    system("cls");
    printf("---------------------- Modify Personal Connections ---------------------\n");
    printf("\t[1] Add Personal Connection MANUALLY\n");
    printf("\t[2] Add Personal Connection from List\n");
    printf("\t[3] View Personal Connections\n");
    printf("\t[4] Remove a Personal Connection\n");
    printf("\t[5] View User Connections\n"); // list of users that have current user in their personal connections
    printf("\t[6] Exit\n");
    printf("------------------------------------------------------------------------\n");
    printf("\nPlease select an option: ");
}

/*
modifyPersonalConnections allows the current user to add or remove personal connections, 
view personal connections, and view user connections
@param currentUser - username of the current user
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
Pre-condition: users array must have at least one element, numUsers must be greater than 0, and currentUser must be a registered user
*/
void modifyPersonalConnections(string currentUser, userList users, int numUsers)
{
    int nChoice, i, userIndex;

    // for adding to personal connections
    int tempUserID, nExists = 0, nPresent;
    string userFile, tempUserName, strLine;
    FILE *userPC;

    // for removing personal connections
    string toDelete;
    FILE *tempFile;

    // for viewing user connections
    string fileName;
    FILE *pcFile;
    
    // get the current user's userID or index
    for (i = 0; i<numUsers; i++) 
    {
        if (strcmp(currentUser, users[i].userName) == 0)
        {
            userIndex = i;
            i = numUsers-1;
        }
    }

    do
    {
        displayModifyPCon();
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                // add personal connection manually
                system("cls");
                printf("------------------- Add Personal Connection Manually -------------------\n");
                printf("Total number of users: %d\n\n", numUsers);

                for (i = 0; i<numUsers; i++)
                {
                    if(strcmp(currentUser, users[i].userName) != 0)
                        printf("\t[%d] %s\n", users[i].userID, users[i].userName);
                }

                printf("------------------------------------------------------------------------\n");
                printf("Enter username to add to your personal connections: ");
                fflush(stdin);
                fgets(tempUserName, sizeof(tempUserName), stdin);
                tempUserName[strlen(tempUserName) - 1] = '\0';

                strcpy(userFile, users[userIndex].userName);
                strcat(userFile, "PC.txt");

                // check if the username is in the users
                for (i = 0; i<numUsers; i++)
                {
                    if (strcmp(tempUserName, users[i].userName) == 0)
                    {
                        nExists = 1;
                        i = numUsers-1;
                    }
                }

                nPresent = checkPersonalConnections(tempUserName, userFile);

                if (nExists && !nPresent)
                {
                    userPC = fopen(userFile, "a+");
                    fprintf(userPC, "%s\n", tempUserName);
                    printf("User successfully added to personal connections!");
                    fclose(userPC);
                    sleep(1);
                }
                else if (nPresent)
                {
                    printf("User is already in your personal connections...");
                    sleep(1);
                }
                else
                {
                    printf("Error! User does not exist in database...");
                    sleep(1);
                }
                break;
            case 2:
                // add personal connection from list
                system("cls");
                printf("------------------- Add Personal Connection from List ------------------\n");
                printf("Total number of users: %d\n\n", numUsers);

                for (i = 0; i<numUsers; i++)
                {
                    if(strcmp(currentUser, users[i].userName) != 0)
                        printf("\t[%d] %s\n", users[i].userID, users[i].userName);
                }

                printf("------------------------------------------------------------------------\n");
                printf("Enter UserID to add to personal connections: ");
                scanf("%d", &tempUserID);

                strcpy(userFile, users[userIndex].userName);
                strcat(userFile, "PC.txt");

                nPresent = checkPersonalConnections(users[tempUserID].userName, userFile);


                if (tempUserID<numUsers && !nPresent)
                {
                    userPC = fopen(userFile, "a+");
                    fprintf(userPC, "%s\n", users[tempUserID].userName);
                    printf("User successfully added to personal connections!");
                    fclose(userPC);
                    sleep(1);
                }
                else if (nPresent)
                {
                    printf("User is already in your personal connections...");
                    sleep(1);
                }
                else
                {
                    printf("Error! User does not exist in database...");
                    sleep(1);
                }

                break;
            case 3:
                // view personal connections
                strcpy(userFile, users[userIndex].userName);
                strcat(userFile, "PC.txt");

                userPC = fopen(userFile, "rt");
                system("cls");
                printf("----------------------- Your Personal Connections ----------------------\n");
                while(fgets(strLine, sizeof(strLine), userPC) != NULL)
                {
                    strLine[strlen(strLine) - 1] = '\0';
                    printf("\t%s\n", strLine);
                }
                fclose(userPC);
                printf("------------------------------------------------------------------------\n");
                printf("Press any key to return. ");
                getch();
                break;
            case 4:
                // remove a personal connection
                // display the personal connections and ask for the username to be delete
                strcpy(userFile, users[userIndex].userName);
                strcat(userFile, "PC.txt");

                userPC = fopen(userFile, "rt");
                system("cls");
                printf("----------------------- Your Personal Connections ----------------------\n");
                while(fgets(strLine, sizeof(strLine), userPC) != NULL)
                {
                    strLine[strlen(strLine) - 1] = '\0';
                    printf("\t%s\n", strLine);
                }
                fclose(userPC);
                printf("------------------------------------------------------------------------\n");
                printf("Enter username to be deleted: ");
                fflush(stdin);
                fgets(toDelete, sizeof(toDelete), stdin);
                toDelete[strlen(toDelete) - 1] = '\0';
                // open the personal connections file
                // loop to check if the username to be deleted is present                
                
                if (checkPersonalConnections(toDelete, userFile)) // it exists or user exists ganern
                {
                    userPC = fopen(userFile, "rt");
                    tempFile = fopen("tempPC.txt", "wt");
                    while(fgets(strLine, sizeof(strLine), userPC) != NULL)
                    {
                        strLine[strlen(strLine) - 1] = '\0';
                        if (strcmp(strLine, toDelete) != 0) // if nde same, write it to the temp file
                            fprintf(tempFile, "%s\n", strLine);
                    }
                    fclose(userPC);
                    fclose(tempFile);
                    remove(userFile);
                    rename("tempPC.txt", userFile);

                    printf("User successfully deleted from your personal connections!");
                    sleep(1);
                }
                else
                {
                    printf("Error! The user you want to delete does not exist in your personal connections...");
                    sleep(1);
                }
                // write all the usernames na nde idedelete to a temp file
                // rename temp file to <username>PC.txt
                // delete the original file
                break;
            case 5:
                // view user connections
                // i-for loop yung PC.txt files ng kada user
                system("cls");
                printf("------------------------- Your User Connections ------------------------\n");
                for (i = 0; i<numUsers; i++)
                {
                    if (strcmp(users[i].userName, currentUser) != 0)
                    {
                        strcpy(fileName, users[i].userName);
                        strcat(fileName, "PC.txt");

                        // open pc files of all users other than the current user
                        pcFile = fopen(fileName, "rt"); 
                        while (fgets(strLine, sizeof(strLine), pcFile) != NULL)
                        {
                            strLine[strlen(strLine) - 1] = '\0';
                            if (strcmp(strLine, currentUser) == 0)
                            {
                                printf("\t%s\n", users[i].userName);
                            }
                        }
                        fclose(pcFile);
                    }
                    
                }
                printf("------------------------------------------------------------------------\n");
                printf("Press any key to return. ");
                getch();
                // inside the for loop, dun i-read yung files
                // pag currentUser is in the file, kunin username of the PC file
                break;
            case 6:
                displayUserModule();
                break;
            default:
                printf("\nInvalid input, please try again.\n");
                break;
        }
    } while (nChoice != 6);
    
}

/*
checkPersonalConnections checks is a given key or username is present in a file
@param key - the string or username to search for
@param fileName - the name of the file to search in
Pre-condition: file must be formatted such that each line contains only one string or username
*/
int checkPersonalConnections(string key, string fileName)
{
    FILE *pcFile;
    string strLine;

    pcFile = fopen(fileName, "rt");

    while(fgets(strLine, sizeof(strLine), pcFile) != NULL)
    {
        strLine[strlen(strLine) - 1] = '\0';
        if(strcmp(strLine, key) == 0)
        {
            fclose(pcFile);
            return 1;
        }
    }

    fclose(pcFile);
    return 0;
}

/*
loginPage displays a login page and prompts the user to enter their username and password.
It checks if the user exists, their account is not locked, and is not deleted
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param login - a loginInfo structure representing the user's login information
@param choice - an integer representing the user's choice
@return the index of the user in the users array if the login is successful, or -1 if there is an error
Pre-condition: users array must have valid data, and *numUsers points to a valid integer
*/
int loginPage(userList users, int *numUsers, loginInfo login, int choice)
{
    string tempPass, tempRePass;

    if (*numUsers <= 0) // if there are no users yet
    {
        system("cls");
        printf("----------------------- Login to Existing Account ----------------------\n");
        printf("%55s", "There are currently no users in the database.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to Homescreen. ");

        getch();
        return -1;

    }
    else
    {
        system("cls");
        char opt;
        fflush(stdin); // flushes newline character from previous input
        printf("----------------------- Login to Existing Account ----------------------\n");
        printf("Username: ");
        fgets(login.userName,sizeof(login.userName),stdin);
        login.userName[strlen(login.userName) - 1] = '\0';	
        
        printf("Password: ");
        fgets(login.passWord,sizeof(login.passWord),stdin);
        login.passWord[strlen(login.passWord) - 1] = '\0';
        printf("------------------------------------------------------------------------\n");

        int i, nIndex = -1;

        // find the user index of the user that wants to login
        for (i = 0; i <= *numUsers; i++)
        {
            if (strcmp(login.userName, users[i].userName) == 0)
            {
                nIndex = i;
                i = (*numUsers) - 1; // alternative to break;
            }
        }

        // if user exists, account is unlocked, isn't deleted, and password isn't default
        if (nIndex != -1 && users[nIndex].isLocked == 0 && 
        strcmp(users[nIndex].fullName, "DELETED USER") != 0 && strcmp(users[nIndex].passWord, "default") != 0)
        {
            if (strcmp(login.passWord, users[nIndex].passWord) == 0)
            {
                printf("Login succesful!\n");
                sleep(1);
                return nIndex;
            }
            else
            {
                printf("Error! Incorrect password...\n");
                printf("[F]orgot Password or [T]ry Again?\n");
                fflush(stdin);
                opt = getch();
                if (opt == 'f' || opt == 'F')
                {
                    forgotPassword(users, nIndex, users[nIndex].userName);
                    return -1;
                }
                else if (opt == 't' || opt == 'T')
                {
                    return -1;
                }
            }
        }
        else if (users[nIndex].isLocked)
        {
            printf("%50s", "- USER ACCOUNT LOCKED BY ADMIN -");
            sleep(1);
            return -1;
        }
        else if (strcmp(users[nIndex].fullName, "DELETED USER") == 0)
        {
            printf("%47s", "- USER HAS BEEN DELETED FROM DATABASE -");
            sleep(1);
        }
        else if (strcmp(users[nIndex].passWord, "default") == 0)
        {
            // change password
            printf("To continue, please change your password.\n\n");
            printf("NEW Password: ");
            fgets(tempPass, sizeof(tempPass), stdin);
            tempPass[strlen(tempPass) - 1] = '\0';

            printf("Re-enter NEW Password: ");
            fgets(tempRePass, sizeof(tempRePass), stdin);
            tempRePass[strlen(tempRePass) - 1] = '\0';

            if (strcmp(tempPass, tempRePass) == 0)
            {
                strcpy(users[nIndex].passWord, tempPass);
                printf("Password changed successfully!");
            }
            else
            {
                printf("Passwords do not match! Please try again...");
            }
            sleep(1);
            return -1;
        }
        else
        {
            printf("Error! User does not exist...");
            sleep(1);
            return -1;
        }
    }
    
}

/*
changeAdminPass allows administrators to change their password.
It asks for the old password, and asks for the new password to be inputted twice.
If all inputs are valid, the adminPass file is then rewritten with the new password in it
@param adminPass - a string containing the current password for the administrator account
Pre-condition: "adminPass.txt" file exists and contains the current password for the administrator account
*/
void changeAdminPass(string adminPass)
{
    string oldPass, newPass, reNewPass;
    system("cls");
    printf("--------------------- Change Administrator Password --------------------\n");
    fflush(stdin);
    printf("Enter current password: ");
    fgets(oldPass, sizeof(oldPass), stdin);
    oldPass[strlen(oldPass) - 1] = '\0';

    fflush(stdin);
    printf("Enter new password: ");
    fgets(newPass, sizeof(newPass), stdin);
    newPass[strlen(newPass) - 1] = '\0';

    fflush(stdin);
    printf("Re-enter new password: ");
    fgets(reNewPass, sizeof(reNewPass), stdin);
    reNewPass[strlen(reNewPass) - 1] = '\0';
    printf("------------------------------------------------------------------------\n");
    
    if (strcmp(oldPass, adminPass) == 0 && strcmp(newPass, reNewPass) == 0)
    {
        FILE *fptr;
    
        fptr = fopen("adminPass.txt", "wt");

        if (fptr != NULL)
        {
            fprintf(fptr, "%s", newPass);
            fclose(fptr);
            printf("Admin password changed successfully!\n");
            sleep(1);
        }
        else
        {
            printf("Error! Unable to store new password...\n");
            sleep(1);
        }
            
    }
    else
    {
        printf("Incorrect Old/New Password Input...");
        sleep(1);
    }     
}

/*
loadAdminPass loads the administrator password from a text file named "adminPass.txt" 
and stores it in a string variable named "adminPass"
@param adminPass - a string variable to store the administrator password
Pre-condition: "adminPass.txt" file must exist in the directory
*/
void loadAdminPass(string adminPass)
{
    FILE *fptr;
    string temp;

    fptr = fopen("adminPass.txt", "rt");

    if (fptr != NULL)
    {
        fgets(temp, sizeof(temp), fptr);
        strcpy(adminPass, temp);

        fclose(fptr);
    }
    else
    {
        printf("Database error! Admin Password File does not exist...");
        sleep(1);
    }
}

/*
personalMessage  function allows a user to send a personal message to another user by prompting for the 
recipient, subject, and message content. It then stores the message in the recipient's inbox file and 
the sender's sent file, and also in a universal messages file
@param sender - a string containing the username of the sender
@param msg - a messageInfo struct containing the message subject and the message itself
Pre-condition: the sender is logged in
*/
void personalMessage(string sender, messageInfo msg)
{
    string reciever;
    time_t curTime;
    string timestamp;

    system("cls");
    printf("------------------------ Send a Personal Message -----------------------\n");
    fflush(stdin);
    FILE *recieverFile, *senderFile, *allMsgs;
    string fileName;

    // type in the target reciever
    printf("To: ");
    fgets(reciever, sizeof(reciever), stdin);
    reciever[strlen(reciever) - 1] = '\0';

    // type in the subject
    fflush(stdin);
    printf("Subject: ");
    fgets(msg.strSubject, sizeof(msg.strSubject), stdin);
    msg.strSubject[strlen(msg.strSubject) - 1] = '\0';

    // type in the message
    fflush(stdin);
    printf("Message: ");
    fgets(msg.strMessage, sizeof(msg.strMessage), stdin);
    msg.strMessage[strlen(msg.strMessage) - 1] = '\0';

    printf("------------------------------------------------------------------------\n");

    // set timestamp for all versions of the msg
    curTime = time(NULL);
    strcpy(timestamp, ctime(&curTime));

    // open the reciever inbox file and store the sender, subject, and message
    strcpy(fileName, reciever);
    strcat(fileName, "Inbox.txt");

    if (checkFileExists(fileName))
    {   
        recieverFile = fopen(fileName,"a+");
        fprintf(recieverFile, "%s", timestamp);
        fprintf(recieverFile, "%s\n", sender);
        fprintf(recieverFile, "Personal Message\n");
        fprintf(recieverFile, "%s\n", msg.strSubject);
        fprintf(recieverFile, "%s\n", msg.strMessage);

        fclose(recieverFile);
        printf("Message successfully sent!");

        // store the same info in the universal messages file
        allMsgs = fopen("ALLMSGS.txt", "a+");
        fprintf(allMsgs, "%s", timestamp);
        fprintf(allMsgs, "Sent by: %s\n", sender);
        fprintf(allMsgs, "Sent to: %s\n", reciever);
        fprintf(allMsgs, "Subject: %s\n", msg.strSubject);
        fprintf(allMsgs, "Message: %s\n", msg.strMessage);
        fclose(allMsgs);
    }
    else 
        printf("Target receiver does not exist!");        


    // open the sender sent file and store the reciever, subject, and message
    strcpy(fileName, sender);
    strcat(fileName, "Sent.txt");

    if (checkFileExists(fileName))
    {
        senderFile = fopen(fileName, "a+");
        fprintf(senderFile, "%s", timestamp);
        fprintf(senderFile, "Sent to: %s\n", reciever);
        fprintf(senderFile, "Subject: %s\n", msg.strSubject);
        fprintf(senderFile, "Message: %s\n", msg.strMessage);

        fclose(senderFile);
    }
    else
        printf(" Could not send message.");
    
    sleep(1);
}

/*
groupMessage sends a group message to multiple receivers, which are entered manually by the user
@param sender - a string containing the username of the sender
@param msg - a messageInfo struct containing the message subject and the message itself
Pre-condition: the sender is logged in
*/
void groupMessage(string sender, messageInfo msg)
{
    int i, j, nReceivers = 0;
    string receivers[MAX_USERS], fileName;
    FILE *recFiles[MAX_USERS], *senderFile, *allMsgs;

    time_t curTime;
    string timestamp;

    system("cls");
    printf("------------------------- Send a Group Message -------------------------\n");
    
    printf("To (type '-' once all desired receivers have been inputted): \n");
    do // while dash is not inputted, keep asking for receivers
    {
        fflush(stdin);
        fgets(receivers[nReceivers], sizeof(receivers[nReceivers]), stdin);
        receivers[nReceivers][strlen(receivers[nReceivers]) - 1] = '\0';
        nReceivers++;
    } while (strcmp(receivers[nReceivers-1], "-") != 0);

    // type in the subject
    fflush(stdin);
    printf("Subject: ");
    fgets(msg.strSubject, sizeof(msg.strSubject), stdin);
    msg.strSubject[strlen(msg.strSubject) - 1] = '\0';

    // type in the message
    fflush(stdin);
    printf("Message: ");
    fgets(msg.strMessage, sizeof(msg.strMessage), stdin);
    msg.strMessage[strlen(msg.strMessage) - 1] = '\0';

    printf("------------------------------------------------------------------------\n");

    // set timestamp for all versions of the msg
    curTime = time(NULL);
    strcpy(timestamp, ctime(&curTime));

    // open receiver inbox files and store message + message info
    for (i = 0; i<nReceivers-1; i++) // nReceivers - 1 since the last item in the array is the "-"
    {
        strcpy(fileName, receivers[i]);
        strcat(fileName, "Inbox.txt");

        if (checkFileExists(fileName))
        {
            recFiles[i] = fopen(fileName,"a+");
            fprintf(recFiles[i], "%s", timestamp);
            fprintf(recFiles[i], "%s\n", sender);
            for (j = 0; j<nReceivers-1; j++)
            {
                if (strcmp(receivers[j], receivers[i]) != 0)
                    fprintf(recFiles[i], "%s ", receivers[j]);
            }
            fprintf(recFiles[i], "\n");
            fprintf(recFiles[i], "%s\n", msg.strSubject);
            fprintf(recFiles[i], "%s\n", msg.strMessage);

            fclose(recFiles[i]);
        }
        else 
            printf("Target receiver %s does not exist!\n", receivers[i]);
    }

    if (checkFileExists("ALLMSGS.txt"))
    {
        // store in universal messages file
        allMsgs = fopen("ALLMSGS.txt", "a+");
        fprintf(allMsgs, "%s", timestamp);
        fprintf(allMsgs, "Sent by: %s\n", sender);
        fprintf(allMsgs, "Sent to: ");
        for (j = 0; j<nReceivers-1; j++)
        {
            if (strcmp(receivers[j], receivers[i]) != 0)
                fprintf(allMsgs, "%s ", receivers[j]);
        }
        fprintf(allMsgs, "\n");
        fprintf(allMsgs, "Subject: %s\n", msg.strSubject);
        fprintf(allMsgs, "Message: %s\n", msg.strMessage);
        fclose(allMsgs);
    }
    else
        printf("Universal Messages Database does not exist!");

    // open sender sent file
    strcpy(fileName, sender);
    strcat(fileName, "Sent.txt");

    if (checkFileExists(fileName))
    {
        senderFile = fopen(fileName, "a+");
        fprintf(senderFile, "%s", timestamp);
        fprintf(senderFile, "Sent to: ");
        for (i = 0; i<nReceivers-1; i++)
        {
            fprintf(senderFile, "%s ", receivers[i]);
        }
        fprintf(senderFile, "\nSubject: %s\n", msg.strSubject);
        fprintf(senderFile, "Message: %s\n", msg.strMessage);

        fclose(senderFile);

        printf("Message successfully sent!");
    }
    else
        printf(" Could not send message.");

    sleep(1);
}

/*
sendAnnouncement allows a user to send an announcement to all users in the system. 
The function prompts the user to enter a subject and message for the announcement. 
The announcement is stored in a file named "ANNOUNCEMENTS.txt" along with the sender's name, subject, and message. 
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param sender - a string containing the username of the sender
@param msg - a messageInfo struct containing the message subject and the message itself
Pre-condition: users and numUsers have been properly initialized, sender is a registered user
*/
void sendAnnouncement(userList users, int numUsers, messageInfo msg, string sender)
{
    int i;
    FILE *announcementsFile, *senderFile;
    string fileName;

    time_t curTime;
    string timestamp;

    system("cls");
    printf("------------------------- Send an Announcement -------------------------\n");

    // type in the subject
    fflush(stdin);
    printf("Subject: ");
    fgets(msg.strSubject, sizeof(msg.strSubject), stdin);
    msg.strSubject[strlen(msg.strSubject) - 1] = '\0';

    // type in the message
    fflush(stdin);
    printf("Message: ");
    fgets(msg.strMessage, sizeof(msg.strMessage), stdin);
    msg.strMessage[strlen(msg.strMessage) - 1] = '\0';

    printf("------------------------------------------------------------------------\n");

    // set timestamp for all versions of the msg
    curTime = time(NULL);
    strcpy(timestamp, ctime(&curTime));

    // store announcement in ONE FILE
    announcementsFile = fopen("ANNOUNCEMENTS.txt","a+");
    fprintf(announcementsFile, "%s", timestamp);
    fprintf(announcementsFile, "[ANNOUNCEMENT]\n");
    fprintf(announcementsFile, "%s\n", sender);
    fprintf(announcementsFile, "%s\n", msg.strSubject);
    fprintf(announcementsFile, "%s\n", msg.strMessage);

    fclose(announcementsFile);

    // store the announcement in sender's sent file
    strcpy(fileName, sender);
    strcat(fileName, "Sent.txt");

    if (checkFileExists(fileName))
    {
        senderFile = fopen(fileName, "a+");
        fprintf(senderFile, "%s", timestamp);
        fprintf(senderFile, "-- ANNOUNCEMENT FOR ALL --\n");
        fprintf(senderFile, "%s\n", msg.strSubject);
        fprintf(senderFile, "%s\n", msg.strMessage);

        fclose(senderFile);

        printf("Announcement successfully sent!");
    }
    else
        printf("Could not send announcement.");

    sleep(1);
}

/*
loadAnnouncements reads announcements from a text file "ANNOUNCEMENTS.txt" 
and stores them in an array of msgArray structures named "announcements"
@param announcements - an array of msgDisplay structs
Pre-condition: "ANNOUNCEMENTS.txt" file exists and contains valid data in the expected format
*/
int loadAnnouncements(msgArray announcements)
{
    int nAnnouncements, lineCount = 0, i;
    FILE *announcementsFile;
    string strLine;
    char ch;

    announcementsFile = fopen("ANNOUNCEMENTS.txt", "rt");
    
    if (announcementsFile != NULL)
    {
        // reads lines until EOF is encountered
        while ((ch = fgetc(announcementsFile)) != EOF)
        {
            if (ch == '\n')
                lineCount++;
        }

        fclose(announcementsFile);
    }

    announcementsFile = fopen("ANNOUNCEMENTS.txt", "rt");

    nAnnouncements = lineCount / 5; // total number of announcements

    // loop through the text file to read each announcement
    for (i = 0; i<nAnnouncements; i++)
    {
        // timestamp
        fgets(strLine, sizeof(strLine), announcementsFile);
        strcpy(announcements[i].timestamp, strLine);

        // announcement header
        fgets(strLine, sizeof(strLine), announcementsFile);
        // no need to store since this is just a header

        // sender
        fgets(strLine, sizeof(strLine), announcementsFile);
        strcpy(announcements[i].sender, strLine);

        // subject
        fgets(strLine, sizeof(strLine), announcementsFile);
        strcpy(announcements[i].strSubject, strLine);

        // message
        fgets(strLine, sizeof(strLine), announcementsFile);
        strcpy(announcements[i].strMessage, strLine);
    }

    fclose(announcementsFile);

    return nAnnouncements;
}

/*
viewAnnouncements displays the announcements stored in the "announcements" array
@param announcements - an array of msgDisplay structs that holds the announcements to be displayed
@param nAnnouncements - the number of announcements in the array
Pre-condition: announcements array should be initialized with valid data
*/
void viewAnnouncements(msgArray announcements, int nAnnouncements)
{
    int i = 0, bStop = 0;
    char cChoice;

    if (nAnnouncements == 0)
    {
        system("cls");
        printf("----------------------------- Announcements ----------------------------\n");
        printf("%53s", "There are currently no official announcements yet.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to user module. ");

        getch();
    }
    else
    {
        do
        {
            system("cls");
            printf("----------------------------- Announcements ----------------------------\n");
            printf("[ANNOUNCEMENT]\n\n");
            printf("%s\n", announcements[i].timestamp);
            printf("Sent by: %s\n", announcements[i].sender);
            printf("Subject: %s\n", announcements[i].strSubject);
            printf("Message: %s\n", announcements[i].strMessage);
            printf("------------------------------------------------------------------------\n");
            printf("\n[N]ext  [P]rev  [R]eturn");
            cChoice = getch();

            if (cChoice == 'n' || cChoice == 'N')
			{
				if (i < nAnnouncements-1)
					i++;
			}
			else if (cChoice == 'p' || cChoice == 'P')
			{
				if (i > 0)
					i--;
			}
			else if (cChoice == 'r' || cChoice == 'R')
				bStop = 1;
        } while (!bStop);
        
    }
}

/*
loadSent stores the contents of the current user's sent file in an array.
It then returns the total number of sent messages loaded
@param currentUser - the username of the logged in user
@param sent - an array of msgDisplay in which the sent messages will be stored
@return nSent (an integer representing the total messages loaded)
Pre-condition: the user must have a sent file
*/
int loadSent(string currentUser, msgArray sent)
{
    int nSent, lineCount = 0, i;
    FILE *sentFile;
    string strLine, userFile;
    char ch;

    strcpy(userFile, currentUser);
    strcat(userFile, "Sent.txt");
    sentFile = fopen(userFile, "rt");

    if(sentFile != NULL)
    {
        // reads lines until EOF is encountered
        while ((ch = fgetc(sentFile)) != EOF)
        {
            if (ch == '\n')
                lineCount++;
        }

        fclose(sentFile);
    }

    sentFile = fopen(userFile, "rt");

    nSent = lineCount / 4;

    // loop through the text file to read each sent message
    for (i = 0; i<nSent; i++)
    {
        // timestamp
        fgets(strLine, sizeof(strLine), sentFile);
        strcpy(sent[i].timestamp, strLine);

        // receiver/s
        fgets(strLine, sizeof(strLine), sentFile);
        strcpy(sent[i].receiver, strLine);

        // subject
        fgets(strLine, sizeof(strLine), sentFile);
        strcpy(sent[i].strSubject, strLine);

        // message
        fgets(strLine, sizeof(strLine), sentFile);
        strcpy(sent[i].strMessage, strLine);
    }

    fclose(sentFile);

    return nSent;
}

/*
displaySent displays the sent messages of a user that was loaded with the loadSent function
@param sent - an array of msgDisplay structs in which the sent messages will be stored
@param nSent - an integer value indicating the number of sent messages in the sent array
Pre-condition: sent and nSent are initialized with valid data
*/
void displaySent(msgArray sent, int nSent)
{
    int i = 0, bStop = 0;
    char cChoice;

    if (nSent == 0)
    {
        system("cls");
        printf("----------------------------- Sent Messages ----------------------------\n");
        printf("%56s", "You have currently not sent any messages.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to user module. ");

        getch();
    }
    else
    {
        do
        {
            system("cls");
            printf("----------------------------- Sent Messages ----------------------------\n");
            printf("%s\n", sent[i].timestamp);
            printf("%s\n", sent[i].receiver);
            printf("%s\n", sent[i].strSubject);
            printf("%s\n", sent[i].strMessage);
            printf("------------------------------------------------------------------------\n");
            printf("\n[N]ext  [P]rev  [R]eturn");
            cChoice = getch();

            if (cChoice == 'n' || cChoice == 'N')
			{
				if (i < nSent-1)
					i++;
			}
			else if (cChoice == 'p' || cChoice == 'P')
			{
				if (i > 0)
					i--;
			}
			else if (cChoice == 'r' || cChoice == 'R')
				bStop = 1;
        } while (!bStop);
        
    }
}

/*
loadInbox stores the contents of the current user's inbox file in an array.
It then returns the total number of messages loaded
@param currentUser - the username of the logged in user
@param inbox - an array of msgDisplay in which the messages will be stored
@return ninbox (an integer representing the total messages loaded)
Pre-condition: the user must have an inbox file
*/
int loadInbox(string currentUser, msgArray inbox)
{
    int nInbox, lineCount = 0, i;
    FILE *inboxFile;
    string strLine, userFile;
    char ch;

    strcpy(userFile, currentUser);
    strcat(userFile, "Inbox.txt");
    inboxFile = fopen(userFile, "rt");

    if(inboxFile != NULL)
    {
        // reads lines until EOF is encountered
        while ((ch = fgetc(inboxFile)) != EOF)
        {
            if (ch == '\n')
                lineCount++;
        }

        fclose(inboxFile); 
    }

    inboxFile = fopen(userFile, "rt");

    nInbox = lineCount / 5;

    // loop through the text file to read each received message
    for (i = 0; i<nInbox; i++)
    {
        // timestamp
        fgets(strLine, sizeof(strLine), inboxFile);
        strcpy(inbox[i].timestamp, strLine);

        // sender
        fgets(strLine, sizeof(strLine), inboxFile);
        strcpy(inbox[i].sender, strLine);

        // "personal message" or group message receivers
        fgets(strLine, sizeof(strLine), inboxFile);
        strcpy(inbox[i].receiver, strLine);

        // subject
        fgets(strLine, sizeof(strLine), inboxFile);
        strcpy(inbox[i].strSubject, strLine);

        // message
        fgets(strLine, sizeof(strLine), inboxFile);
        strcpy(inbox[i].strMessage, strLine);
    }

    fclose(inboxFile);

    return nInbox;
}

/*
displayInbox displays the messages of a user that was loaded with the loadInbox function
@param inbox - an array of msgDisplay structs in which the messages will be obtained from
@param nInbox - an integer value indicating the number of messages in the inbox array
@param currentUser - string containing the username of the logged in user
@param msg - messageInfo struct containing message details
Pre-condition: inbox and nInbox are initialized with valid data
*/
void displayInbox(msgArray inbox, int nInbox, string currentUser, messageInfo msg)
{
    int i = 0, bStop = 0;
    char cChoice;

    if (nInbox == 0)
    {
        system("cls");
        printf("------------------------------- User Inbox -----------------------------\n");
        printf("%56s", "You currently have no messages in your inbox.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to user module. ");

        getch();
    }
    else
    {
        do
        {
            system("cls");
            printf("------------------------------- User Inbox -----------------------------\n");
            printf("%s\n", inbox[i].timestamp);
            printf("Sent by: %s\n", inbox[i].sender);

            if (strcmp(inbox[i].receiver, "Personal Message\n") == 0)
                printf("%s\n", inbox[i].receiver);
            else if (strncmp(inbox[i].receiver, "Replying to:", 12) == 0)
                printf("%s\n", inbox[i].receiver);
            else 
                printf("CC: %s\n", inbox[i].receiver);

            printf("Subject: %s\n", inbox[i].strSubject);
            printf("Message: %s\n", inbox[i].strMessage);
            printf("------------------------------------------------------------------------\n");
            printf("\n[N]ext  [P]rev  [R]eturn\n");
            printf("Enter 'A' to reply to displayed message.");
            cChoice = getch();

            if (cChoice == 'a' || cChoice == 'A')
            {
                system("cls");
                printf("----------------------------- Send a Reply -----------------------------\n");
                printf("Replying to: %s\n", inbox[i].sender);
                if (strcmp(inbox[i].receiver, "Personal Message\n") == 0)
                    printf("%s\n", inbox[i].receiver);
                else 
                    printf("CC: %s\n", inbox[i].receiver);

                printf("Subject: %s\n", inbox[i].strSubject);
                printf("Message: %s\n", inbox[i].strMessage);
                printf("------------------------------------------------------------------------\n");
                // reply to the message
                if (strcmp(inbox[i].receiver, "Personal Message\n") == 0 || strncmp(inbox[i].receiver, "Replying to:", 8) == 0) // if it's a personal message
                {
                    inbox[i].sender[strlen(inbox[i].sender) - 1] = '\0';
                    replyToPM(inbox[i].sender, currentUser, inbox[i].strSubject, 
                    inbox[i].strMessage, msg);
                }
                else // if it's a group message
                {
                    replyToGM(inbox[i].sender, currentUser, inbox[i].receiver, 
                    inbox[i].strSubject, inbox[i].strMessage, msg);
                }

                printf("Reply successfully sent!");
                sleep(1);
            }
            else if (cChoice == 'n' || cChoice == 'N')
			{
				if (i < nInbox-1)
					i++;
			}
			else if (cChoice == 'p' || cChoice == 'P')
			{
				if (i > 0)
					i--;
			}
			else if (cChoice == 'r' || cChoice == 'R')
				bStop = 1;
        } while (!bStop);
        
    }
}

/*
replyToPM allows a user to reply to a private message (PM) and saves the message in the recipient's
inbox and the sender's sent file, as well as the universal message file
@param receiver - string that represents the username of the message recipient
@param sender - string that represents the username of the sender of the message
@param subject - string containing the subject of the message being replied to
@param message - string containing the initial message being replied to
@param msg - struct containing message details
Pre-condition: files to be opened must exist and the string parameters must not be empty
*/
void replyToPM(string receiver, string sender, string subject, string message, messageInfo msg)
{
    fflush(stdin);
    FILE *receiverFile, *senderFile, *allMsgs;
    string fileName;

    time_t curTime;
    string timestamp;

    // take in the reply
    printf("Reply: ");
    fgets(msg.strMessage, sizeof(msg.strMessage), stdin);
    msg.strMessage[strlen(msg.strMessage) - 1] = '\0';

    // set timestamp for all versions of the msg
    curTime = time(NULL);
    strcpy(timestamp, ctime(&curTime));

    strcpy(fileName, receiver); // the original sender, the one current user is replying to
    strcat(fileName, "Inbox.txt");

    if (checkFileExists(fileName))
    {
        receiverFile = fopen(fileName,"a+");
        fprintf(receiverFile, "%s", timestamp);
        fprintf(receiverFile, "%s\n", sender);
        fprintf(receiverFile, "Replying to: %s", message);
        fprintf(receiverFile, "%s", subject);
        fprintf(receiverFile, "%s\n", msg.strMessage);

        fclose(receiverFile);

        // store info in universal messages file
        allMsgs = fopen("ALLMSGS.txt", "a+");
        fprintf(allMsgs, "%s", timestamp);
        fprintf(allMsgs, "Sent by: %s\n", sender);
        fprintf(allMsgs, "Replying to: %s\n", receiver);
        fprintf(allMsgs, "Subject: %s", subject);
        fprintf(allMsgs, "Message: %s\n", msg.strMessage);
        fclose(allMsgs);
    }

    strcpy(fileName, sender);
    strcat(fileName, "Sent.txt");

    if (checkFileExists(fileName))
    {
        senderFile = fopen(fileName, "a+");
        fprintf(senderFile, "%s", timestamp);
        fprintf(senderFile, "Reply to: %s\n", receiver);
        fprintf(senderFile, "Subject: %s", subject);
        fprintf(senderFile, "Message: %s\n", msg.strMessage);

        fclose(senderFile);
    }
}

/*
replyToGM allows a user to reply to a group message (GM) and saves the message in the recipients'
inbox and the sender's sent file, as well as the universal message file
@param receiver - string that represents the username of the message recipient
@param sender - string that represents the username of the sender of the message
@param CCLine - contains the other recipients of the message
@param subject - string containing the subject of the message being replied to
@param message - string containing the initial message being replied to
@param msg - struct containing message details
Pre-condition: files to be opened must exist and the string parameters must not be empty
*/
void replyToGM(string receiver, string sender, string CCLine, string subject, string message, messageInfo msg)
{
    fflush(stdin);
    FILE *receiverFile, *senderFile, *CCFiles[MAX_USERS], *allMsgs;
    string fileName;
    string CC[MAX_USERS];

    time_t curTime;
    string timestamp;

    // take in the reply
    printf("Reply: ");
    fgets(msg.strMessage, sizeof(msg.strMessage), stdin);
    msg.strMessage[strlen(msg.strMessage) - 1] = '\0';

    // set timestamp for all versions of the msg
    curTime = time(NULL);
    strcpy(timestamp, ctime(&curTime));

    // send reply to the original sender first
    receiver[strlen(receiver)-1] = '\0';
    subject[strlen(subject)-1] = '\0';
    CCLine[strlen(CCLine) - 1] = '\0';

    // step 1: separate each username in CCLine and store in a local array
    
    int i, j = 0, ctr = 0;
    for (i = 0; i<(strlen(CCLine)); i++)
    {
        // if space or NULL found, assign into new string
        if (CCLine[i] == ' ' || CCLine[i] == '\0')
        {
            CC[ctr][j] = '\0';
            ctr++;
            j = 0;
        }
        else
        {
            CC[ctr][j] = CCLine[i];
            j++;
        }
    }

    strcpy(fileName, receiver);
    strcat(fileName, "Inbox.txt");

    if (checkFileExists(fileName))
    {
        receiverFile = fopen(fileName,"a+");
        fprintf(receiverFile, "%s", timestamp);
        fprintf(receiverFile, "%s\n", sender);
        for (i = 0; i<ctr; i++)
        {
            fprintf(receiverFile, "%s ", CC[i]);
        }
        fprintf(receiverFile, "\n");
        fprintf(receiverFile, "%s\n", subject);
        fprintf(receiverFile, "%s\n", msg.strMessage);

        fclose(receiverFile);

        // store in universal messages file
        allMsgs = fopen("ALLMSGS.txt", "a+");
        fprintf(allMsgs, "%s", timestamp);
        fprintf(allMsgs, "Sent by: %s\n", sender);
        fprintf(allMsgs, "Replying to: ");
        fprintf(allMsgs, "%s ", receiver);
        for (i = 0; i<ctr; i++)
        {
            fprintf(allMsgs, "%s ", CC[i]);
        }
        fprintf(allMsgs, "\n");
        fprintf(allMsgs, "Subject: %s\n", subject);
        fprintf(allMsgs, "Message: %s\n", msg.strMessage);
        fclose(allMsgs);
    }

    // send reply to all other users in the "CC: " line
    int k;
    for (i = 0; i<ctr; i++)
    {
        strcpy(fileName, CC[i]);
        strcat(fileName, "Inbox.txt");

        if (checkFileExists(fileName))
        {
            CCFiles[i] = fopen(fileName, "a+");
            fprintf(CCFiles[i], "%s", timestamp);
            fprintf(CCFiles[i], "%s\n", sender);
            fprintf(CCFiles[i], "%s ", receiver);
            
            // fprintf the users in the CC Line except the current user who the msg is being sent to
            for (k = 0; k<ctr; k++)
            {
                if (strcmp(CC[i], CC[k]) != 0) // if not the same
                {
                    fprintf(CCFiles[i], "%s ", CC[k]);
                }
            }

            fprintf(CCFiles[i], "\n");
            fprintf(CCFiles[i], "%s\n", subject);
            fprintf(CCFiles[i], "%s\n", msg.strMessage);
        }
    }

    strcpy(fileName, sender);
    strcat(fileName, "Sent.txt");

    if (checkFileExists(fileName))
    {
        senderFile = fopen(fileName, "a+");
        fprintf(senderFile, "%s", timestamp);
        fprintf(senderFile, "Group Message Reply to: %s %s\n", receiver, CCLine);
        fprintf(senderFile, "Subject: %s\n", subject);
        fprintf(senderFile, "Message: %s\n", msg.strMessage);

        fclose(senderFile);
    }
}

/*
composeMessage is the menu in which users are allowed to choose the type of message they want to send
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param sender - a string containing the username of the sender
@param msg - a messageInfo struct containing the message subject and the message itself
Pre-condition: users and numUsers have been properly initialized, sender is a registered user
*/
void composeMessage(userList users, int numUsers, messageInfo msg, string sender)
{
    int nChoice;

    do
    {
        displayComposeMessage();
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                personalMessage(sender, msg);
                break;
            case 2:
                groupMessage(sender, msg);
                break;
            case 3:
                sendAnnouncement(users, numUsers, msg, sender);
                break;
            case 4:
                displayUserModule();
                break;
            default:
                printf("\nInvalid input, please try again.\n");
                break;
        }
    } while (nChoice != 4);
}

/*
userModule is the menu in which the user can interact with their account and their messages
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param sender - a string containing the username of the sender
@param msg - a messageInfo struct containing the message subject and the message itself
@param announcements - an array of msgDisplay structs in which the announcements are stored
Pre-condition: announcements, users, and numUsers have been properly initialized, sender is a registered user
*/
void userModule(userList users, int numUsers, messageInfo msg, string sender,
msgArray announcements)
{
    msgArray sent, inbox;
    int nChoice, selectedUser;
    int nSent = loadSent(sender, sent);
    int nInbox = loadInbox(sender, inbox);
    int nAnnouncements = loadAnnouncements(announcements);

    do
    {
        displayUserModule();
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                displayComposeMessage();
                composeMessage(users, numUsers, msg, sender);
                break;
            case 2:
                nInbox = loadInbox(sender, inbox);
                displayInbox(inbox, nInbox, sender, msg);
                break;
            case 3:
                nSent = loadSent(sender, sent);
                displaySent(sent, nSent);
                break;
            case 4:
                nAnnouncements = loadAnnouncements(announcements);
                viewAnnouncements(announcements, nAnnouncements);
                break;
            case 5:
                modifyPersonalContents(sender, users, numUsers);
                break;
            case 6:
                modifyAccountSecurity(sender, users, numUsers);
                break;
            case 7:
                modifyPersonalConnections(sender, users, numUsers);
                break;
            case 8:
                displayUserList(users, numUsers, sender);
                scanf("%d", &selectedUser);
                viewUsers(users, numUsers, selectedUser, sender, msg);
                break;
            case 9:
                displayMenu(numUsers);
                break;
            default:
                printf("\nInvalid input, please try again.\n");
                break;
        }
    } while (nChoice != 9);
}

/*
adminModule allows the administrator to perform various tasks, such as managing users and messages,
as well as changing the admin password
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param adminPass - string containing the current admin account password
Pre-condition: admin has successfully logged in with the current password; users and numUsers are
initialized with valid values
*/
void adminModule(userList users, int numUsers, string adminPass)
{
    int nChoice;

    do
    {
        displayAdminModule();
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                adminUsers(users, numUsers);
                break;
            case 2:
                adminMessages(users, numUsers);
                break;
            case 3:
                changeAdminPass(adminPass);
                break;
            case 4:
                displayMenu(numUsers);
                break;
            default:
                printf("\nInvalid input, please try again.\n");
                break;
        }
    } while (nChoice != 4);
}

/*
adminUsers is the menu for the users module of the administrator, in which they can manage the users, 
their details, as well as the security questions
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
Pre-condition: users and numUsers must be initialized with valid values
*/
void adminUsers(userList users, int numUsers)
{
    int nChoice, selectedUser, i;
    FILE *passReqs, *tempFile, *pcFile, *secuQuesFile;
    string strLine, userFile, addQues;

    Questions ques;
    int totalQuestions;
    int bStop = 0;
    char cChoice;

    do
    {
        displayAdminUsersModule();
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                // view users with real name, username, password
                viewUsersAdmin(users, numUsers);
                break;
            case 2:
                // modify user details
                displayListofUsers(users, numUsers);
                scanf("%d", &selectedUser);
                if (selectedUser<numUsers)
                {
                    // display user details and ask for what part the admin wants to modify
                    modifyUser(users, numUsers, selectedUser);
                }
                else if (selectedUser>numUsers)
                {
                    printf("Error! UserID entered does not belong to any existing user...");
                    sleep(1);
                }
                break;
            case 3:
                // refresh user account password
                // display a list of those who forgot their password
                system("cls");
                printf("-------------------- Refresh User Account Password ---------------------\n");
                printf("Password Refresh Requests:\n");
                for (i = 0; i<numUsers; i++)
                {
                    if (users[i].isLocked)
                        printf("[%d] %s\n", i, users[i].userName);
                }
                // display other users
                printf("\nOther Users:\n");
                for (i = 0; i<numUsers; i++)
                {
                    if (users[i].isLocked == 0)
                        printf("[%d] %s\n", i, users[i].userName);
                }
                printf("------------------------------------------------------------------------\n");
                printf("Enter User ID of the user whose password you want to refresh: ");
                scanf("%d", &selectedUser);

                if (selectedUser != -1 && selectedUser<numUsers)
                {
                    // set the user password to "default"
                    strcpy(users[selectedUser].passWord, "default");

                    // unlock user account
                    users[selectedUser].isLocked = 0;

                    // remove username from requests file
                    passReqs = fopen("REFRESHPASSREQS.txt", "rt");
                    tempFile = fopen("temp.txt", "wt");
                    while(fgets(strLine, sizeof(strLine), passReqs) != NULL)
                    {
                        strLine[strlen(strLine) - 1] = '\0';
                        if (strcmp(strLine, users[selectedUser].userName) != 0) // if nde same, write it to the temp file
                            fprintf(tempFile, "%s\n", strLine);
                    }
                    fclose(passReqs);
                    fclose(tempFile);

                    remove("REFRESHPASSREQS.txt");
                    rename("temp.txt", "REFRESHPASSREQS.txt");

                    printf("User password successfully refreshed!");
                    sleep(1);
                    
                }
                else if (selectedUser != -1 && selectedUser>numUsers)
                {
                    printf("Error! UserID entered does not belong to any existing user...");
                    sleep(1);
                }
                // ung selected user, mapapalitan ung password nila into "default"
                break;
            case 4:
                // delete users
                if (numUsers == 0)
                {
                    system("cls");
                    printf("----------------------------- Delete Users -----------------------------\n");
                    printf("%55s", "There are currently no users in the database.\n");
                    printf("------------------------------------------------------------------------\n");
                    printf("\nPress any key to return to ADMIN Users Module. ");

                    getch();
                }
                else
                {
                    system("cls");
                    printf("----------------------------- Delete Users -----------------------------\n");
                    for (i = 0; i<numUsers; i++)
                    {
                        printf("\t[%d] %s\n", users[i].userID, users[i].userName);
                    }
                    printf("------------------------------------------------------------------------\n");
                    printf("Enter UserID of the user you want to delete: ");
                    scanf("%d", &selectedUser);

                    if (selectedUser<numUsers)
                    {
                        // delete the user
                        // change their name to "DELETED USER" (should still show up in messages)
                        strcpy(users[selectedUser].fullName, "DELETED USER");

                        // remove from the PC files of all remaining users
                        for(i = 0; i<numUsers; i++)
                        {
                            if(strcmp(users[i].fullName, "DELETED USER") != 0)
                            {
                                strcpy(userFile, users[i].userName);
                                strcat(userFile, "PC.txt");
                                
                                deleteUserNamefromFile(userFile, users[selectedUser].userName);
                            }
                        }

                        // replace their names in the inbox
                        for (i = 0; i<numUsers; i++)
                        {
                            if(strcmp(users[i].fullName, "DELETED USER") != 0)
                            {
                                strcpy(userFile, users[i].userName);
                                strcat(userFile, "Inbox.txt");
                                replaceSenderLine(userFile, users[selectedUser].userName, "DELETED USER");
                            }
                        }

                        // replace names in all msgs file
                        replaceSenderLine("ALLMSGS.txt", users[selectedUser].userName, "DELETED USER");

                        printf("User successfully deleted from database!");
                        sleep(1);
                        
                    }
                    else if (selectedUser>numUsers)
                    {
                        printf("Error! UserID entered does not belong to any existing user...");
                        sleep(1);
                    }
                }
                break;
            case 5:
                // security questions
                do
                {
                    totalQuestions = loadSecuQues(ques);
                    system("cls");
                    printf("-------------------------- Security Questions --------------------------\n");
                    for (i = 0; i<totalQuestions; i++)
                    {
                        printf("[%d] %s\n", i+1, ques[i]);
                    }
                    printf("------------------------------------------------------------------------\n");
                    printf("[A]dd Question  [R]eturn");
                    cChoice = getch();

                    if (cChoice == 'a' || cChoice == 'A')
                    {
                        printf("\nAdd a NEW Security Question:\n");
                        fflush(stdin);
                        fgets(addQues, sizeof(addQues), stdin);
                        addQues[strlen(addQues) - 1] = '\0';

                        secuQuesFile = fopen("SECUQUES.txt", "a+");
                        fprintf(secuQuesFile, "%s\n", addQues);

                        printf("Security question successfully added to database!");
                        fclose(secuQuesFile);
                        sleep(1);
                    }
                    else if (cChoice == 'r' || cChoice == 'R')
                        bStop = 1;
                    else
                        printf("Invalid input, please try again!");
                } while (!bStop);
                break;
            case 6:
                displayAdminModule();
                break;
            default:
                printf("\nInvalid input, please try again.\n");
                break;
        }
    } while (nChoice != 6);
    
}

/*
deleteUserNamefromFile reads the content of a file line by line, and rewrites all lines that do not
match with the username to be deleted, hence "deleting" the username from the file
@param fileName - string that contains the filename of the file in which the username will be deleted from
@param userName - string that contains the username to be deleted
Pre-condition: file is formatted such that there is only one username per line
*/
void deleteUserNamefromFile(string fileName, string userName)
{
    FILE *input, *temp;
    string strLine;
    char *word;
    int wordLen;

    input = fopen(fileName, "rt");
    temp = fopen("temp.txt", "wt");

    while (fgets(strLine, sizeof(strLine), input) != NULL)
    {
        word = strstr(strLine, userName);
        while (word != NULL)
        {
            wordLen = strlen(userName);
            memmove(word, word + wordLen, strlen(word) - wordLen + 1);
            word = strstr(strLine, userName);
        }
        if (strLine[strlen(strLine) - 1] == '\n')
        {
            strLine[strlen(strLine) - 1] = '\0';
        }

        fputs(strLine, temp);
    }

    fclose(input);
    fclose(temp);

    remove(fileName);
    rename("temp.txt", fileName);
}

/*
displayListofUsers displays the users from the users array with their respective user IDs
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
Pre-condition: users and numUsers have been properly initialized with valid values
*/
void displayListofUsers(userList users, int numUsers)
{
    // view list of users first
    int i;

    if (numUsers == 0)
    {
        system("cls");
        printf("----------------------------- Modify Users -----------------------------\n");
        printf("%55s", "There are currently no users in the database.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to ADMIN Users Module. ");

        getch();
    }
    else
    {
        system("cls");
        printf("----------------------------- Modify Users -----------------------------\n");
        for (i = 0; i<numUsers; i++)
        {
            printf("\t[%d] %s\n", users[i].userID, users[i].userName);
        }
        printf("------------------------------------------------------------------------\n");
        printf("Enter UserID of the user you want to modify: ");
    }
}

/*
displaySelectedUser displays the userID, fullName, username, description, and 
personal connections of the selected user
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param selectedUser - integer referring to the userID of the selected user by the admin
Pre-condition: users and numUsers have been properly initialized with valid values, and admin has inputted a valid userID
*/
void displaySelectedUser(userList users, int numUsers, int selectedUser)
{
    // display the details of the selected user first
    system("cls");
    printf("------------------------- Modify Selected User ------------------------\n");
    printf("User ID: %d\n", users[selectedUser].userID);
    printf("[1] Name: %s\n", users[selectedUser].fullName);
    printf("[2] Username: %s\n", users[selectedUser].userName);
    printf("[3] Description: %s\n\n", users[selectedUser].userDescription);

    string userFile, strLine;
    FILE *pcFile;

    printf("[4] %s's Personal Connections:\n", users[selectedUser].userName);
    strcpy(userFile, users[selectedUser].userName);
    strcat(userFile, "PC.txt");

    pcFile = fopen(userFile, "rt");
    while (fgets(strLine, sizeof(strLine), pcFile) != NULL)
    {
        strLine[strlen(strLine) - 1] = '\0';
        printf("\t%s\n", strLine);
    }
    fclose(pcFile);

    if (users[selectedUser].isLocked)
        printf("Account Status: LOCKED\n");
    else
        printf("Account Status: UNLOCKED\n");

    printf("\nEnter '5' to return to ADMIN Users Module.\n");
    printf("------------------------------------------------------------------------\n");
    printf("Enter user component you wish to modify: ");

}

/*
modifyUser is the menu for the modify user module available in the admin module, it allows the admin
to select from modifying their name, username, description, or personal connections
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param selectedUser - integer referring to the userID of the selected user by the admin
Pre-condition: users and numUsers have been properly initialized with valid values, and admin has inputted a valid userID
*/
void modifyUser(userList users, int numUsers, int selectedUser)
{
    int nChoice;
    string newName, newUserName, newDesc, oldFileName, newFileName;
    char cChoice;

    // for adding and removing personal connections
    string addPC, removePC, userFile, strLine;
    FILE *userPC, *tempFile;
    int nExists = 0, i, isPresent;

    // for changing username
    string user;
    string userFiles[MAX_USERS];
    int j, k;

    do
    {
        displaySelectedUser(users, numUsers, selectedUser);
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                printf("Enter NEW Name for [%d]: ", users[selectedUser].userID);
                fflush(stdin);
                fgets(newName, sizeof(newName), stdin);
                newName[strlen(newName) - 1] = '\0';

                strcpy(users[selectedUser].fullName, newName);
                printf("\nUser's name has been successfully changed!");
                sleep(2);
                break;
            case 2: 
                printf("Enter NEW Username for [%d]: ", users[selectedUser].userID);
                fflush(stdin);
                fgets(newUserName, sizeof(newUserName), stdin);
                newUserName[strlen(newUserName) - 1] = '\0';

                // rename inbox file
                strcpy(oldFileName, users[selectedUser].userName);
                strcat(oldFileName, "Inbox.txt");

                strcpy(newFileName, newUserName);
                strcat(newFileName, "Inbox.txt");

                rename(oldFileName, newFileName);

                // rename sent file
                strcpy(oldFileName, users[selectedUser].userName);
                strcat(oldFileName, "Sent.txt");

                strcpy(newFileName, newUserName);
                strcat(newFileName, "Sent.txt");

                rename(oldFileName, newFileName);

                // rename pc file
                strcpy(oldFileName, users[selectedUser].userName);
                strcat(oldFileName, "PC.txt");

                strcpy(newFileName, newUserName);
                strcat(newFileName, "PC.txt");

                rename(oldFileName, newFileName);

                // add for loop to change all occurences of users[selectedUser].username (old)
                // into newUserName
                // change all occurences in each inbox file
                for (i = 0; i<numUsers; i++)
                {
                    if (i != selectedUser) // when the filename that contains the old username is encountered, it causes and error in processing the next files
                    {
                        strcpy(user, users[i].userName);
                        strcat(user, "Inbox.txt");

                        replaceWordinFile(user, users[selectedUser].userName, newUserName);
                    }
                }

                // change all occurences in each sent file
                for (i = 0; i<numUsers; i++)
                {
                    if (i != selectedUser)
                    {
                        strcpy(user, users[i].userName);
                        strcat(user, "Sent.txt");

                        replaceWordinFile(user, users[selectedUser].userName, newUserName);
                    }
                }

                // change all occurences in each PC file
                for (i = 0; i<numUsers; i++)
                {
                    if (i != selectedUser)
                    {
                        strcpy(user, users[i].userName);
                        strcat(user, "PC.txt");

                        replaceWordinFile(user, users[selectedUser].userName, newUserName);
                    }
                }

                // change all occurences in announcements file
                replaceWordinFile("ANNOUNCEMENTS.txt", users[selectedUser].userName, newUserName);

                // change all occurences in all msgs file
                replaceWordinFile("ALLMSGS.txt", users[selectedUser].userName, newUserName);

                strcpy(users[selectedUser].userName, newUserName);
                printf("\nUser's username has been successfully changed!");
                sleep(2);
                break;
            case 3:
                printf("Enter NEW Description for [%d]: ", users[selectedUser].userID);
                fflush(stdin);
                fgets(newDesc, sizeof(newDesc), stdin);
                newDesc[strlen(newDesc) - 1] = '\0';

                strcpy(users[selectedUser].userDescription, newDesc);
                printf("\nUser's description has been successfully changed!");
                sleep(2);
                break;
            case 4:
                // ask admin whether they want to add or remove a personal connection
                printf("Would you like to [A]dd or [R]emove a personal connection? \n");
                cChoice = getch();

                strcpy(userFile, users[selectedUser].userName);
                strcat(userFile, "PC.txt");
                if (cChoice == 'A' || cChoice == 'a')
                {
                    printf("Enter username to add to %s's personal connections: ", users[selectedUser].userName);
                    fflush(stdin);
                    fgets(addPC, sizeof(addPC), stdin);
                    addPC[strlen(addPC) - 1] = '\0';

                    // check if the username is in the users
                    for (i = 0; i<numUsers; i++)
                    {
                        if (strcmp(addPC, users[i].userName) == 0)
                        {
                            nExists = 1;
                            i = numUsers-1;
                        }
                    }
                    
                    if (checkPersonalConnections(addPC, userFile)) // user is already in personal connections
                    {
                        printf("Error! User is already in %s's personal connections...", users[selectedUser].userName);
                        sleep(1);
                    }
                    else if (nExists && !checkPersonalConnections(addPC, userFile))
                    {
                        userPC = fopen(userFile, "a+");
                        fprintf(userPC, "%s\n", addPC);
                        printf("User successfully added to personal connections!");
                        fclose(userPC);
                    }
                    else
                        printf("Error! The user entered does not exist in the database...");
                }
                // if add, check if the entered user exists in the users array
                // also check if it's already in the user's personal connections

                // if remove, check if it's present in the personal connections
                // then, do the long ass delete process if andun nga

                else if (cChoice == 'R' || cChoice == 'r')
                {
                    printf("Enter username to remove from %s's personal connections: ", users[selectedUser].userName);
                    fflush(stdin);
                    fgets(removePC, sizeof(removePC), stdin);
                    removePC[strlen(removePC) - 1] = '\0';

                    isPresent = checkPersonalConnections(removePC, userFile);

                    if (isPresent) // it exists or user exists ganern
                    {
                        // deleteUserNamefromFile(userFile, removePC);
                        userPC = fopen(userFile, "rt");
                        tempFile = fopen("tempPC.txt", "wt");
                        while(fgets(strLine, sizeof(strLine), userPC) != NULL)
                        {
                            strLine[strlen(strLine) - 1] = '\0';
                            if (strcmp(strLine, removePC) != 0) // if nde same, write it to the temp file
                                fprintf(tempFile, "%s\n", strLine);
                        }
                        fclose(userPC);
                        fclose(tempFile);

                        remove(userFile);
                        rename("tempPC.txt", userFile);

                        printf("User successfully deleted from %s's personal connections!", users[selectedUser].userName);
                    }
                    else
                    {
                        printf("Error! The user you want to delete does not exist in %s's personal connections...", users[selectedUser].userName);
                    }
                }
                else
                    printf("Error! Invalid input");

                sleep(1);
                break;
            case 5:
                displayAdminUsersModule();
                break;
            default:
                printf("Invalid input! Please try again... ");
                break;
        }

    } while (nChoice != 5);
}

/*
encryptPass encrypts a given string (password) by shifting the ASCII values of each character by 3
@param pass - the string containing the password to be encrypted
Pre-condition: pass has to be populated with a valid string
*/
void encryptPass(string pass)
{
    int i;
    for (i = 0; pass[i] != '\0'; i++)
    {
        pass[i] += 3;
    }
}

/*
viewUsersAdmin displays the details of all existing users in the database, along with their personal connections
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
Pre-condition: users and numUsers have been properly initialized with valid values
*/
void viewUsersAdmin(userList users, int numUsers)
{
    int i = 0, bStop = 0;
    char cChoice;
    string userFile, strLine, encryptedPass;
    FILE *pcFile;

    if (numUsers == 0)
    {
        system("cls");
        printf("---------------------------- Existing Users ----------------------------\n");
        printf("%55s", "There are currently no users in the database.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to homescreen. ");

        getch();
    }
    else
    {
        do
        {
            system("cls");
            printf("---------------------------- Existing Users ----------------------------\n");
            printf("Total number of users: %d\n", numUsers);
            printf("\nUser ID: %d\n", users[i].userID);
            printf("Name: %s\n", users[i].fullName);
            printf("Username: %s\n", users[i].userName);
            // copy password to another variable to encrypt, and display the other variable
            strcpy(encryptedPass, users[i].passWord);
            encryptPass(encryptedPass);

            printf("Encrypted Password: %s\n", encryptedPass);
            printf("Decription: %s\n", users[i].userDescription);

            if (users[i].isLocked)
                printf("Account Status: LOCKED\n");
            else
                printf("Account Status: UNLOCKED\n");
            printf("------------------------------------------------------------------------\n\n");

            printf("%s's Personal Connections:\n", users[i].userName);
            strcpy(userFile, users[i].userName);
            strcat(userFile, "PC.txt");

            pcFile = fopen(userFile, "rt");

            while(fgets(strLine, sizeof(strLine), pcFile) != NULL)
            {
                strLine[strlen(strLine) - 1] = '\0';
                printf("%s\n", strLine);
            }
            fclose(pcFile);

            printf("\n[N]ext  [P]rev  [R]eturn");
            cChoice = getch();

            if (cChoice == 'n' || cChoice == 'N')
			{
				if (i < numUsers-1)
					i++;
			}
			else if (cChoice == 'p' || cChoice == 'P')
			{
				if (i > 0)
					i--;
			}
			else if (cChoice == 'r' || cChoice == 'R')
				bStop = 1;
        } while(!bStop);
    }
}

/*
replaceWordinFile replaces all occurences of a given string with a new string in a text file
@param fileName - string containing the filename in which the old string will be replaced with the new one
@param old - old string to be replaced
@param new - string to replace old string with
Pre-condition: all parameters must be valid strings
*/
void replaceWordinFile(string fileName, string old, string new)
{
    string strLine, tempFileName;
    char *match;
    int oldLen = strlen(old), newLen = strlen(new), lenMatch;
    FILE *file, *tempFile;

    strcpy(tempFileName, "temp.txt");

    file = fopen(fileName, "rt");
    tempFile = fopen(tempFileName, "wt");

    if (checkFileExists(fileName))
    {
        while(fgets(strLine, sizeof(strLine), file) != NULL)
        {
            match = strstr(strLine, old);
            while (match != NULL)
            {
                lenMatch = strlen(match);
                *match = '\0'; // replace old word with null character
                fprintf(tempFile, "%s%s", strLine, new); // write modified line to tempFile
                match += oldLen;
                strcpy(strLine, match); // copy rest of the line after old word
                match = strstr(strLine, old);
            }
            fprintf(tempFile, "%s", strLine); // write rest of the line after all matches to tempFile
        }

        fclose(file);
        fclose(tempFile);

        remove(fileName);
        rename(tempFileName, fileName);
    }
}

/*
replaceSenderLine replaces all occurences of the old line with the new line in the file, but only in specific lines of the file
@param fileName - string containing the filename in which the old string will be replaced with the new one
@param old - old string to be replaced
@param new - string to replace old string with
Pre-condition: all parameters must be valid strings
*/
void replaceSenderLine(string fileName, string old, string new)
{
    string strLine, strBuffer;
    FILE *file, *tempFile;
    int oldLen = strlen(old), newLen = strlen(new);
    int lineNum = 0, replaceLine = 0;
    char *match;

    file = fopen(fileName, "rt");
    tempFile = fopen("temp.txt", "wt");

    while (fgets(strBuffer, sizeof(strBuffer), file) != NULL)
    {
        if (lineNum == 1 || (lineNum > 1 && (lineNum - 1) % 5 == 0) || replaceLine)
        {
            match = strstr(strBuffer, old);
            while (match != NULL)
            {
                fwrite(strBuffer, 1, match - strBuffer, tempFile);
                fwrite(new, 1, newLen, tempFile);
                match += oldLen;
                strcpy(strBuffer, match);
                match = strstr(strBuffer, old);
            }
            fwrite(strBuffer, 1, strlen(strBuffer), tempFile);
            replaceLine = 0;
        }
        else
        {
            fwrite(strBuffer, 1, strlen(strBuffer), tempFile);
            replaceLine = lineNum == 1 || (lineNum > 1 && (lineNum - 1) % 5 == 0);
        }
        lineNum++;
    }

    fclose(file);
    fclose(tempFile);

    remove(fileName);
    rename("temp.txt", fileName);
}

/*
forgotPassword allows a user to request a password reset once they have answered their security question correctly
@param users - an array of user structs that contains information about all the users in the system
@param userIndex - integer representing index of the current user
@param currentUser - string containing the username of the current user
Pre-condition: "REFRESHPASSREQS.txt" must exist
*/
void forgotPassword(userList users, int userIndex, string currentUser)
{
    // send request to admin
    // write username to REFRESHPASSREQS.txt
    // lock account

    Questions ques;
    int totalQuestions = loadSecuQues(ques);

    int i, bStop = 0, isPresent;
    string tempAns;
    FILE *reqsFile;
    char cChoice;

    system("cls");
    printf("---------------------- Request for Password Reset ----------------------\n");
    fflush(stdin);
    printf("%s", ques[users[userIndex].secuQuesNo]);
    printf("------------------------------------------------------------------------\n");
    printf("[A]nswer or [R]eturn to Homescreen?\n");

    do
    {
        cChoice = getch();
        if (cChoice == 'a' || cChoice == 'A')
        {
            printf("Type in your answer here: ");
            fgets(tempAns, sizeof(tempAns), stdin);
            tempAns[strlen(tempAns) - 1] = '\0';

            // if tama answer, send the request then lock the account
            // if nde, let the user try again (dapat may option to exit) pero lock the account na din
            if (strcmp(tempAns, users[userIndex].secuQuestion) == 0)
            {
                isPresent = checkPersonalConnections(users[userIndex].userName, "REFRESHPASSREQS.txt");
                if (!isPresent)
                {
                    reqsFile = fopen("REFRESHPASSREQS.txt", "a+");
                    fprintf(reqsFile, "%s\n", users[userIndex].userName);
                    fclose(reqsFile);
                    users[userIndex].isLocked = 1; // lock the account
                    printf("Request to reset password has been successfully sent!\n");
                    sleep(1);

                }
                else
                {
                    users[userIndex].isLocked = 1;
                    printf("Error! You have already sent a request to reset password...\n");
                    sleep(1);
                }
                    
                bStop = 1;
            }
            else
            {
                users[userIndex].isLocked = 1; // lock the account
                printf("Incorrect answer, Try [A]gain or [R]eturn to Homescreen?\n");
            }
        }

        else if (cChoice == 'r' || cChoice == 'R')
            bStop = 1;
    } while (!bStop);
}

/*
loadMessages loads messages from "ALLMSGS.txt" into and array of msgDisplay structs
@param msgs - array of msgDisplay structures in which all the messages from the "ALLMSGS.txt" file are stored
@return nMsgs - the total number of messages loaded
Pre-condition: "ALLMSGS.txt" must exist
*/
int loadMessages(msgArray msgs)
{
    int nMsgs, lineCount = 0, i;
    FILE *allMsgs;
    string strLine;
    char ch;

    allMsgs = fopen("ALLMSGS.txt", "rt");

    if (allMsgs != NULL)
    {
        // reads lines until EOF is encountered
        while ((ch = fgetc(allMsgs)) != EOF)
        {
            if (ch == '\n')
                lineCount++;
        }

        fclose(allMsgs);
    }

    allMsgs = fopen("ALLMSGS.txt", "rt");

    nMsgs = lineCount / 5;

    for (i = 0; i<nMsgs; i++)
    {
        // timestamp
        fgets(strLine, sizeof(strLine), allMsgs);
        strcpy(msgs[i].timestamp, strLine);

        // sender
        fgets(strLine, sizeof(strLine), allMsgs);
        strcpy(msgs[i].sender, strLine);

        // receiver/s
        fgets(strLine, sizeof(strLine), allMsgs);
        strcpy(msgs[i].receiver, strLine);

        // subject
        fgets(strLine, sizeof(strLine), allMsgs);
        strcpy(msgs[i].strSubject, strLine);

        // message
        fgets(strLine, sizeof(strLine), allMsgs);
        strcpy(msgs[i].strMessage, strLine);
    }

    fclose(allMsgs);

    return nMsgs;
}

/*
viewMessages displays the messages loaded in the loadMessages function
@param msgs - an array of msgDisplay structs containing the details for all the messages
@param nMsgs - total number of messages in the array
Pre-condition: msgs and nMsgs have been initialized with valid values
*/
void viewMessages(msgArray msgs, int nMsgs)
{
    int i = 0, j, bStop = 0, hasContent = 0;
    char cChoice;
    string user;
    FILE *userFile;

    // check if there are messages
    if (checkContent("ALLMSGS.txt"))
        hasContent = 1;

    if (!hasContent)
    {
        system("cls");
        printf("----------------------------- All Messages -----------------------------\n");
        printf("%50s", "There are currently no messages in the database.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to user module. ");

        getch();
    }
    else
    {
        do
        {
            system("cls");
            printf("----------------------------- All Messages -----------------------------\n");
            printf("%s\n", msgs[i].timestamp);
            printf("%s\n", msgs[i].sender);
            printf("%s\n", msgs[i].receiver);
            printf("%s\n", msgs[i].strSubject);
            printf("%s\n", msgs[i].strMessage);
            printf("------------------------------------------------------------------------\n");
            printf("\n[N]ext  [P]rev  [R]eturn");
            cChoice = getch();

            if (cChoice == 'n' || cChoice == 'N')
			{
				if (i < nMsgs-1)
					i++;
			}
			else if (cChoice == 'p' || cChoice == 'P')
			{
				if (i > 0)
					i--;
			}
			else if (cChoice == 'r' || cChoice == 'R')
				bStop = 1;
        } while (!bStop);
        
    }
}

/*
isUserNameinLine checks if a username is present in a specific line of a text file
@param fileName - string containing filename of file to be checked
@param numLine - integer representing the number of the line to be checked
@param userName - string containing the username to be checked in the line
@return 1 if username was found, 0 if it was not found, and -1 if an error occurred
Pre-condition: string parameters contain valid strings, and numLine is within the total number of lines in the file
*/
int isUserNameinLine(string fileName, int numLine, string userName)
{
    FILE* fp;
    fp = fopen(fileName, "rt");

    string strLine;
    int curLineNum = 1;

    while (fgets(strLine, sizeof(strLine), fp) != NULL)
    {
        if (curLineNum == numLine)
        {
            // remove newline
            strLine[strlen(strLine) - 1] = '\0';

            // check if word is in line
            if (strstr(strLine, userName) != NULL)
            {
                fclose(fp);
                return 1;
            }
            else
            {
                fclose(fp);
                return 0;
            }
        }
        curLineNum++;
    }

    fclose(fp);
    return -1;
}

/*
adminMessages is the menu in which the administrator can handle all the messages in the database.
administrators can view all the messages, filter them by sender or recipient, and delete messages
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
Pre-condition: users and numUsers have been properly initialized with valid values
*/
void adminMessages(userList users, int numUsers)
{
    int nChoice, nFilter, selectedUser, i, selectedMsg, timestampLine;
    msgArray msgs;
    int nMsgs;
    int nSent, nInbox;

    // for deleting messages
    string userFile;

    do
    {
        displayAdminMessages();
        fflush(stdin);
        scanf("%d", &nChoice);

        switch(nChoice)
        {
            case 1:
                // view all messages
                nMsgs = loadMessages(msgs);
                viewMessages(msgs, nMsgs);
                break;
            case 2:
                // view by filter
                system("cls");
                printf("---------------------------- View by Filter ----------------------------\n");
                printf("\t[1] Filter by Sender\n");
                printf("\t[2] Filter by Recipient\n");
                printf("\t[3] Return to ADMIN Module\n");
                printf("------------------------------------------------------------------------\n");
                printf("\nPlease select an option: ");
                scanf("%d", &nFilter);

                if (nFilter == 1)
                {
                    // filter by sender
                    // allow admin to select user
                    system("cls");
                    printf("--------------------------- Filter by Sender ---------------------------\n");
                    for (i = 0; i<numUsers; i++)
                    {
                        printf("\t[%d] %s\n", users[i].userID, users[i].userName);
                    }
                    printf("------------------------------------------------------------------------\n");
                    printf("Enter UserID to select user: ");
                    scanf("%d", &selectedUser);

                    nSent = loadSent(users[selectedUser].userName, msgs);

                    filterBySender(users, numUsers, msgs, nSent, selectedUser);
                }
                else if (nFilter == 2)
                {
                    // filter by recipient
                    // allow admin to select user
                    system("cls");
                    printf("------------------------- Filter by Recipient --------------------------\n");
                    for (i = 0; i<numUsers; i++)
                    {
                        printf("\t[%d] %s\n", users[i].userID, users[i].userName);
                    }
                    printf("------------------------------------------------------------------------\n");
                    printf("Enter UserID to select user: ");
                    scanf("%d", &selectedUser);

                    nInbox = loadInbox(users[selectedUser].userName, msgs);

                    filterByRecipient(users, numUsers, msgs, nInbox, selectedUser);
                }
                else if (nFilter == 3)
                {
                    displayAdminModule();
                }
                else
                {
                    printf("\nInvalid input, returning to ADMIN Module...\n");
                    sleep(1);
                }
                break;
            case 3:
                // delete message
                // load msgs
                nMsgs = loadMessages(msgs);
                // view the msgs (create a new function that allows to delete)
                selectedMsg = selectMessagetoDelete(msgs, nMsgs);
                // remove newline
                msgs[selectedMsg].timestamp[strlen(msgs[selectedMsg].timestamp) - 1] = '\0';
                
                // get the line in which timestamp of the message shows up
                
                // in all msgs
                timestampLine = findTimestamp("ALLMSGS.txt", msgs[selectedMsg].timestamp);
                // once u get the timestampLine, delete the line itself and the lines below it
                deleteMessageLine("ALLMSGS.txt", timestampLine);
                deleteMessageLine("ALLMSGS.txt", timestampLine);
                deleteMessageLine("ALLMSGS.txt", timestampLine);
                deleteMessageLine("ALLMSGS.txt", timestampLine);
                deleteMessageLine("ALLMSGS.txt", timestampLine);
                
                // in all inbox files
                for (i = 0; i<numUsers; i++)
                {
                    strcpy(userFile, users[i].userName);
                    strcat(userFile, "Inbox.txt");

                    timestampLine = findTimestamp(userFile, msgs[selectedMsg].timestamp);

                    // delete the message lines starting from the timestamp
                    deleteMessageLine(userFile, timestampLine);
                    deleteMessageLine(userFile, timestampLine);
                    deleteMessageLine(userFile, timestampLine);
                    deleteMessageLine(userFile, timestampLine);
                    deleteMessageLine(userFile, timestampLine);
                }

                // in all sent files
                for (i = 0; i<numUsers; i++)
                {
                    strcpy(userFile, users[i].userName);
                    strcat(userFile, "Sent.txt");

                    timestampLine = findTimestamp(userFile, msgs[selectedMsg].timestamp);

                    // delete the message lines starting from the timestamp
                    deleteMessageLine(userFile, timestampLine);
                    deleteMessageLine(userFile, timestampLine);
                    deleteMessageLine(userFile, timestampLine);
                    deleteMessageLine(userFile, timestampLine);
                }
                printf("\nMessage successfully deleted!\n");
                sleep(1);
                break;
            case 4:
                displayAdminModule();
                break;
            default:
                printf("\nInvalid input, please try again.\n");
                break;
        }
    } while (nChoice != 4);

}

/*
deleteMessageLine deletes a specific line from a text file
@param fileName - string containing the filename of the file in which the line will be deleted from
@param nLine - integer representing the line number of the line to be deleted
Pre-condition: nLine must be within the total lines of text in the file
*/
void deleteMessageLine(string fileName, int nLine)
{
    FILE *fp, *temp;
    int currentLine = 1;
    string strLine;

    // open file for reading
    fp = fopen(fileName, "rt");
    temp = fopen("temp.txt", "wt");

    // copy all lines except the line to be deleted
    while (fgets(strLine, sizeof(strLine), fp))
    {
        if (currentLine != nLine)
            fputs(strLine, temp);
        currentLine++;
    }

    fclose(fp);
    fclose(temp);
    
    remove(fileName);
    rename("temp.txt", fileName);
}

/*
findTimestamp takes in a filename and a timestamp from the selected message, and locates
which line number it occurs in inside the file
@param fileName - string containing the filename in which the timestamp will be located
@param timestamp - string containing the timestamp to be located
@return numLine (integer representing the line number in which the timestamp occurs);
-1 if the timestamp doesn't occur in any line in the file
Pre-condition: the line must have the timestamp only as its content
*/
int findTimestamp(string fileName, string timestamp)
{
    FILE *fp;
    fp = fopen(fileName, "rt");

    string strLine;
    int numLine = 0;

    while(fgets(strLine, sizeof(strLine), fp))
    {
        numLine++;
        if(strstr(strLine, timestamp))
        {
            fclose(fp);
            return numLine;
        }
    }
    
    fclose(fp);
    return -1;
}

/*
selectMessagetoDelete displays all the messages in the system and gives the administrator an option to delete
the currently viewed message
@param msgs - array of msgDisplay structs that contain details of all the messages
@param nMsgs - integer representing the total number of messages in the array
@return i (the index of the message to be deleted)
Pre-condition: the "ALLMSGS.txt" file exists
*/
int selectMessagetoDelete(msgArray msgs, int nMsgs)
{
    int i = 0, j, bStop = 0, hasContent = 0;
    char cChoice;
    string user;
    FILE *userFile;

    // check if there are messages
    if (checkContent("ALLMSGS.txt"))
        hasContent = 1;

    // if wala pang messages
    if (!hasContent)
    {
        system("cls");
        printf("----------------------------- All Messages -----------------------------\n");
        printf("%50s", "There are currently no messages in the database.\n");
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to user module. ");

        getch();
        return -1;
    }
    // if meron na
    else
    {
        do
        {
            system("cls");
            printf("----------------------------- All Messages -----------------------------\n");
            printf("%s\n", msgs[i].timestamp);
            printf("%s\n", msgs[i].sender);
            printf("%s\n", msgs[i].receiver);
            printf("%s\n", msgs[i].strSubject);
            printf("%s\n", msgs[i].strMessage);
            printf("------------------------------------------------------------------------\n");
            printf("\n[N]ext  [P]rev  [D]elete  [R]eturn");
            cChoice = getch();

            if (cChoice == 'n' || cChoice == 'N')
			{
				if (i < nMsgs-1)
					i++;
			}
			else if (cChoice == 'p' || cChoice == 'P')
			{
				if (i > 0)
					i--;
			}
            else if(cChoice == 'd' || cChoice == 'D')
            {
                return i;
            }
			else if (cChoice == 'r' || cChoice == 'R')
				bStop = 1;
        } while (!bStop);
        
    }
}

/*
filterbySender displays all the messages sent by the user selected by the administrator
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param selectedUser - integer referring to the userID of the selected user by the admin
@param sent - an array of msgDisplay structs in which the sent messages will be stored
@param nSent - an integer value indicating the number of sent messages in the sent array
Pre-condition: parameters must have been initialized with valid values, administrator has selected
a user that's in the database
*/
void filterBySender(userList users, int numUsers, msgArray sent, int nSent, int selectedUser)
{
    int i = 0, bStop = 0;
    char cChoice;

    if (nSent == 0)
    {
        system("cls");
        printf("--------------------------- Filter by Sender ---------------------------\n");
        printf("%s has currently not sent any messages.\n", users[selectedUser].userName);
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to ADMIN module. ");

        getch();
    }
    else
    {
        do
        {
            system("cls");
            printf("--------------------------- Filter by Sender ---------------------------\n");
            printf("Viewing %s's Sent Messages\n\n", users[selectedUser].userName);

            printf("%s\n", sent[i].timestamp);
            printf("%s\n", sent[i].receiver);
            printf("%s\n", sent[i].strSubject);
            printf("%s\n", sent[i].strMessage);
            printf("------------------------------------------------------------------------\n");
            printf("\n[N]ext  [P]rev  [R]eturn");
            cChoice = getch();

            if (cChoice == 'n' || cChoice == 'N')
			{
				if (i < nSent-1)
					i++;
			}
			else if (cChoice == 'p' || cChoice == 'P')
			{
				if (i > 0)
					i--;
			}
			else if (cChoice == 'r' || cChoice == 'R')
				bStop = 1;
        } while (!bStop);
        
    }
}

/*
filterbyRecipient displays all the messages received by the user selected by the administrator
@param users - an array of user structs that contains information about all the users in the system
@param numUsers - the number of users in the system
@param selectedUser - integer referring to the userID of the selected user by the admin
@param inbox - an array of msgDisplay structs in which the received messages will be stored
@param nInbox - an integer value indicating the number of received messages in the sent array
Pre-condition: parameters must have been initialized with valid values, administrator has selected
a user that's in the database
*/
void filterByRecipient(userList users, int numUsers, msgArray inbox, int nInbox, int selectedUser)
{
    int i = 0, bStop = 0;
    char cChoice;

    if (nInbox == 0)
    {
        system("cls");
        printf("-------------------------- Filter by Recipient -------------------------\n");
        printf("%s has currently not received any messages.\n", users[selectedUser].userName);
        printf("------------------------------------------------------------------------\n");
        printf("\nPress any key to return to ADMIN module. ");

        getch();
    }
    else
    {
        do
        {
            system("cls");
            printf("-------------------------- Filter by Recipient -------------------------\n");
            printf("Viewing %s's Received Messages\n\n", users[selectedUser].userName);

            printf("%s\n", inbox[i].timestamp);
            printf("Sent by: %s\n", inbox[i].sender);
            printf("Subject: %s\n", inbox[i].strSubject);
            printf("Message: %s\n", inbox[i].strMessage);
            printf("------------------------------------------------------------------------\n");
            printf("\n[N]ext  [P]rev  [R]eturn");
            cChoice = getch();

            if (cChoice == 'n' || cChoice == 'N')
			{
				if (i < nInbox-1)
					i++;
			}
			else if (cChoice == 'p' || cChoice == 'P')
			{
				if (i > 0)
					i--;
			}
			else if (cChoice == 'r' || cChoice == 'R')
				bStop = 1;
        } while (!bStop);
        
    }
}

/*
checkContent simply checks if a file already has content
@param fileName - string containing the filename of the file to be checked
@return 1 if the file has content, 0 if not
Pre-condition: None
*/
int checkContent(string fileName)
{
    int contCheck = 0, ch;
    FILE *fp;
    fp = fopen(fileName, "rt");

    if (fp == NULL)
        return 0;

    ch = fgetc(fp);

    if (ch != EOF)
        contCheck = 1;
    
    fclose(fp);

    return contCheck;
}

int main()
{
    userList users;
    loginInfo login;
    messageInfo msg;
    msgArray announcements;
    string adminPass, checkPass;
    int numUsers = 0, nChoice, bQuit = 0, currentUser;

    if (checkFileExists("ANNOUNCEMENTS.txt") == 0)
    {
        FILE *announcementsFile;
        announcementsFile = fopen("ANNOUNCEMENTS.txt", "wt");
        fclose(announcementsFile);
    }

    if (checkFileExists("ALLMSGS.txt") == 0)
    {
        FILE *allMsgs;
        allMsgs = fopen("ALLMSGS.txt", "wt");
        fclose(allMsgs);
    }

    if (checkFileExists("REFRESHPASSREQS.txt"))
    {
        FILE *refreshPass;
        refreshPass = fopen("REFRESHPASSREQS.txt", "wt");
        fclose(refreshPass);
    }
    

    loadUserList(users, &numUsers);

    displayMenu(numUsers);
    do
    {
        fflush(stdin);
        scanf("%d", &nChoice);

        switch (nChoice)
        {
            case 1:
                system("cls");
                currentUser = loginPage(users, &numUsers, login, nChoice);
                if (currentUser != -1)
                {
					displayUserModule();
                    userModule(users, numUsers, msg, users[currentUser].userName,
                    announcements);
                }
                else
                {
                    displayMenu(numUsers);
                }
                break;

            case 2: 
                system("cls");
                addUser(users, &numUsers, nChoice);
                break;

            case 3: 
                system("cls");
                loadAdminPass(adminPass);
                fflush(stdin);
                printf("Enter ADMIN Password: ");
                fgets(checkPass, sizeof(checkPass), stdin);
                checkPass[strlen(checkPass) - 1] = '\0';

                if (strcmp(checkPass, adminPass) == 0)
                {
                    adminModule(users, numUsers, adminPass);
                }
                else
                {
                    printf("Incorrect Password! Type in '5' to return to Homescreen.\n");
                }
                break;

            case 4:
                system("cls");
                printf("------------------------------------------------------------------------\n");
                printf("%46s\n", "Exiting Program...");
                printf("------------------------------------------------------------------------\n");
                sleep(1);
                break;
            
            case 5:
                displayMenu(numUsers);
                break;

            default:
                printf("\nInvalid input, please try again.\n");
                break;
        }
    } while(nChoice != 4);

    saveInfotoFile(users, numUsers);

    return 0;
}
