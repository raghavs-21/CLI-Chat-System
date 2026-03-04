#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
void regis(void);
void login(int*);
void chatpage(char*);
void viewchats(char*);
void newchats(char*);
void sendmesg(char*);
void searchchat(char*, char*);
void typedmesg(char*, char*);
bool user_exists(char*);
void remove_n(char*);
void add_n(char*);
void existing_username(char*);
void check_password(char*);
void setstatus(char*);
void seestatus();
const char * newchat="newchats.txt";
const char * userdata="USER_DATA.txt";
const char * chats="CHATS.txt";
const char * temp="temp.txt";
const char * status="status.txt";
int wct;
int* wctptr = &wct;

void enterloop() {
	char inp = 'a';
	while ((inp != 'e') && (inp != 'E')) {
		//asking user to register, login or exit
		printf("To Register/Sign up, Enter \'R\' \n");
		printf("Already Registered? Enter \'L\' TO LOGIN \n");
		printf("To Exit, Enter \'E\' \n\n");
		scanf(" %c", &inp);
		switch (inp) {
			//if r or R then calls regis function
		case 'R':
			regis();
			break;
		case 'r':
			regis();
			break;

			//if l or L then calls login function
		case 'L':
			login(&wct);
			break;
		case 'l':
			login(&wct);
			break;

			//if e or E then exits 
		case 'E':
			printf("\n                                 THANK YOU FOR USING YOUR CHAT APP!!! HAVE A WONDERFUL DAY :) \n**\n");
			return;
		case 'e':
			printf("\n                                 THANK YOU FOR USING YOUR CHAT APP!!! HAVE A WONDERFUL DAY :) \n**\n");
			return;
		default://if input is invalid
			printf("Please enter valid input :( \n");

		}
	}
	return;
}

int main() {
	//change color
	printf("\033[0;31m");
	//prints welcome 
	for (int i = 0; i < 120; i++) {
		printf("*");
	}
	printf("\033[1;33m");
	printf("\n                                       WELCOME TO YOUR CHAT                                        \a \n");
	printf("\033[0;31m");
	for (int i = 0; i < 120; i++) {
		printf("*");
	}
	printf("\033[1;33m");
	printf("\n\n");
	*wctptr = 0;
	//input for register,signup,delete,exit

	enterloop();

	return 0;
}
void regis(void) {     //function to register as new user using username and password
	FILE* fptr;
	fptr = fopen(userdata, "a");//opening file "USER_DATA.txt" using file pointer in append mode
	if (fptr == NULL) {                                                 //checking if file-open is successful
		printf("Error opening file.\n");
		return;
	}
	char u_name[100] = { '\0' };
	char u_password[20] = { '\0' };
	printf(" ENTER USERNAME : (Press B to go back to main menu)");
	getchar();
	fgets(u_name, 100, stdin);                                          //getting input for username from user
	remove_n(u_name);
	if (strcmp(u_name, "B") == 0 || strcmp(u_name, "b") == 0) {
		fclose(fptr);
		return; // Exit to main menu
	}
	while (user_exists(u_name)) {
		printf("USERNAME IS ALREADY TAKEN !!! PLEASE ENTER DIFFERENT USERNAME !!\n");
		printf(" ENTER USERNAME : ");
		fgets(u_name, 100, stdin);                                          //getting input for username from user
		remove_n(u_name);
		if (strcmp(u_name, "B") == 0 || strcmp(u_name, "b") == 0) {
			fclose(fptr);
			return; // Exit to main menu
		}
	}
	add_n(u_name);
	fwrite(u_name, sizeof(char), strlen(u_name), fptr);
	printf(" ENTER PASSWORD : ");
	fgets(u_password, 20, stdin);                              //getting input for password from user
	check_password(u_password);
	fwrite(u_password, sizeof(char), strlen(u_password), fptr);            //appending username and password data to file
	fclose(fptr);
	printf("\nREGISTERED SUCCESSFULLY\n\n");
	system("cls");
	return;
}
void login(int* wctptr) //function to login using username and password
{
	FILE* fptr;
	fptr = fopen(userdata, "r");	//opening file "USER_DATA.txt" in read mode using file pointer
	if (fptr == NULL) {										//checking if file is opened properly
		printf("Error opening file.\n");
		return;
	}
	char u_name[100] = { '\0' };
	char u_password[20] = { '\0' };
	char user_read[100] = { '\0' };
	char pswd_read[20] = { '\0' };
	printf(" ENTER USERNAME : (Press B to go back to main menu): ");
	getchar();
	fgets(u_name, 100, stdin);								//getting input for username from user
	remove_n(u_name);
	if (strcmp(u_name, "B") == 0 || strcmp(u_name, "b") == 0) {
		fclose(fptr);
		return; // Exit to main menu
	}
	int wc = 0;
	while (!user_exists(u_name)) {
		if (wc == 5) {
			printf("INCORRECT USERNAME ENTERED FIVE TIMES !!! PLEASE TRY AGAIN!!\n\n");
			fclose(fptr);
			return;
		}
		printf("USER NOT REGISTERED OR USERNAME IS INCORRECT !! TRY AGAIN !! \n\nENTER USERNAME (Press B to go back to main menu): ");
		fgets(u_name, 100, stdin);
		remove_n(u_name);
		if (strcmp(u_name, "B") == 0 || strcmp(u_name, "b") == 0) {
			fclose(fptr);
			return; // Exit to main menu
		}
		wc++;
	}
	while (!feof(fptr)) {
		fgets(user_read, 100, fptr);
		fgets(pswd_read, 20, fptr);
		remove_n(user_read);
		remove_n(pswd_read);
		if (strcmp(u_name, user_read) == 0) break;
	}
	printf("ENTER PASSWORD : ");
	fgets(u_password, 20, stdin);							//getting input for password from user
	wc = 0;
	remove_n(u_password);
	while (strcmp(u_password, pswd_read) != 0) {
		wc++;
		if (wc == 5) {
			printf("INCORRECT PASSWORD ENTERED 5 TIMES !! PLEASE TRY AGAIN LATER !!\n\n");
			return;
		}
		printf("PASSWORD IS INCORRECT !! PLEASE TRY AGAIN !!\nENTER PASSWORD : ");
		fgets(u_password, 20, stdin);
		remove_n(u_password);
	}
	system("cls");
	for (int i = 0; i < 80; i++) printf("*");
	printf("\n\n         LOGGED IN SUCCESSFULLY!!      \n\n  HELLO %s !   What would you like to do? \n\n", u_name);
	fclose(fptr);
	chatpage(u_name);
	return;
}
void chatpage(char* u_name)									//function called after successful log in   
{
	char inpcp = '\0';

	while ((inpcp != 'l') && (inpcp != 'L')) {
		char* serchwrd = (char*)malloc(sizeof(char) * 50);
		printf("TO VIEW ALL CHATS, Enter \'V\' \n\n");
		printf("TO VIEW NEW MESSAGE(S), Enter \'N\' \n\n");
		printf("TO SEND A NEW MESSAGE, Enter \'S\' \n\n");
		printf("TO FIND A PARTICULAR MESSAGE IN A CHAT, Enter \'F\' \n\n");
		printf("TO SET STATUS, Enter \'G\' \n\n");
		printf("TO VIEW STATUS, Enter \'A\' \n\n");
		printf("TO LOG OUT, Enter \'L\' \n\n");
		printf("---------------------------------------------PRINTING USERS---------------------------------------------");
		existing_username(u_name);
		scanf(" %c", &inpcp);
		switch (inpcp) {
			//if v or V then calls viewchats function
		case 'V':
			viewchats(u_name);
			break;
		case 'v':
			viewchats(u_name);
			break;
			//if s or S then calls sendmesg function
		case 'S':
			sendmesg(u_name);
			break;
		case 's':
			sendmesg(u_name);
			break;
			//if l or L then calls logout function
		case 'L':
			system("cls");
			printf("\nLOGGING OUT..............\nSUCCESSFULLY LOGGED OUT\n\n");
			break;
		case 'l':
			system("cls");
			printf("\nLOGGING OUT..............\nSUCCESSFULLY LOGGED OUT\n\n");
			break;
		case 'N':
			newchats(u_name);
			break;
		case 'n':
			newchats(u_name);
			break;
			//if e or E then exits 
		case 'f':
			printf("Enter the word/sentence to be searched :\n");
			getchar();
			fgets(serchwrd, 50, stdin);
			remove_n(serchwrd);
			searchchat(u_name, serchwrd);
			break;
		case 'F':
			getchar();
			printf("Enter the word/sentence to be searched :\n");
			fgets(serchwrd, 50, stdin);
			searchchat(u_name, serchwrd);
			//printf("\n                                 THANK YOU FOR USING YOUR CHAT APP!!! HAVE A WONDERFUL DAY :) \n*\n");
			break;
		case 'g':
			setstatus(u_name);
			break;
		case 'G':
			setstatus(u_name);
			break;
		case 'A':
			seestatus();
			break;
		case 'a':
			seestatus();
			break;
		default:
			printf("Please enter valid input :( \n");
			break;
		}
	}
}
void viewchats(char* u_name) {
	FILE* fptrch;
	fptrch = fopen(chats, "r+");
	if (fptrch == NULL) {
		printf("Error opening file.\n");
		return;
	}
	char rcvr[100];
	printf("WHOSE CHATS WOULD YOU LIKE TO VIEW?\nENTER USERNAME: ");
	getchar();
	fgets(rcvr, 100, stdin);
	remove_n(rcvr);
	remove_n(u_name);
	rewind(fptrch);
	while (!user_exists(rcvr)) {
		printf("USER NOT REGISTERED !! \nPLEASE ENTER VALID USERNAME : ");
		fgets(rcvr, 100, stdin);
		remove_n(rcvr);
	}
	//printf("%s", rcvr);
	bool flag = false;

	while (!feof(fptrch)) {
		char s[100] = { '\0' };
		char r[100] = { '\0' };
		char msg[200] = { '\0' };
		fgets(s, sizeof(s), fptrch); //gets sender username
		fgets(r, sizeof(r), fptrch); //gets receiver username
		fgets(msg, sizeof(msg), fptrch);  //gets message
		remove_n(s);//remove newline at end of 's' if present
		remove_n(r);//remove newline at end of 'r' if present
		remove_n(msg);//remove newline at end of 'msg' if present
		if ((strcmp(s, u_name) == 0) && (strcmp(r, rcvr) == 0)) {
			printf("You: %s\n", msg);
			flag = true;
		}
		if ((strcmp(r, u_name) == 0) && (strcmp(s, rcvr) == 0)) {
			printf("%s:  %s\n", s, msg);
			flag = true;
		}
		//printf("%s %s", rcvr,u_name);
	}
	if (flag == false) printf("\n NO MESSAGES FOUND WITH THE ENTERED USER!! \n\n");
	fclose(fptrch);
}
void sendmesg(char* u_name)									//function to send messages
{
	FILE* fptrch;//file pointer of chathistory
	fptrch = fopen(chats, "a+");
	FILE* fptrd;//file pointer of user data
	fptrd = fopen(userdata, "r");
	char which_user[100] = { '\0' };//variable for sending to which user
	char uf[100] = { '\0' }; // variable for username match 
	char mesg[200] = { '\0' };//variable for storing message
	printf("Who do you want to text ?\n");
	getchar();
	fgets(which_user, 100, stdin);
	remove_n(which_user);
	while (!user_exists(which_user)) {
		printf("USER NOT REGISTERED !! \nPLEASE ENTER VALID USERNAME : ");
		fgets(which_user, 100, stdin);
		remove_n(which_user);
	}
	while (!feof(fptrd)) {
		fgets(uf, 100, fptrd);
		remove_n(uf);
		if (strcmp(uf, which_user) == 0) {
			typedmesg(u_name, which_user);
			break;//function called when user inputs valid receiver username
			//sreturn;
		}
	}
	rewind(fptrd);
	rewind(fptrch);
	fclose(fptrd);
	fclose(fptrch);
	return;
}
void typedmesg(char* u_name, char* which_user) {
	FILE* fptrch; // For chat history
	FILE* fptrnc; // For new chats (optional if needed)

	fptrch = fopen(chats, "a+");
	fptrnc = fopen(newchat, "a+");

	if (fptrch == NULL || fptrnc == NULL) {
		printf("Error opening file.\n");
		return;
	}

	char ch[200] = { '\0' };
	printf("\nType your message here, [TO EXIT,  ENTER TWICE] :)\n");
	fgets(ch, 200, stdin); 
	add_n(u_name);         
	add_n(which_user);     

	while (ch[0] != '\n') { 
		add_n(ch);          
		fwrite(u_name, sizeof(char), strlen(u_name), fptrch); // Write sender to CHAT_HISTORY
		fwrite(which_user, sizeof(char), strlen(which_user), fptrch); // Write receiver to CHAT_HISTORY
		fwrite(ch, sizeof(char), strlen(ch), fptrch); // Write message to CHAT_HISTORY

		// Also add the same to newchats.txt if required
		fwrite(u_name, sizeof(char), strlen(u_name), fptrnc);
		fwrite(which_user, sizeof(char), strlen(which_user), fptrnc);
		fwrite(ch, sizeof(char), strlen(ch), fptrnc);

		printf("\nType your message here, [TO EXIT,  ENTER TWICE] :)\n");
		fgets(ch, 200, stdin);
	}
	fflush(fptrch);
	fflush(fptrnc);
	printf("\nSending .......... \n\nSUCCESSFULLY SENT MESSAGE(S) \n");

	fclose(fptrch);
	fclose(fptrnc);
	return;
}

void remove_n(char* str) {
	if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
}
void add_n(char* str) {
	if (str[strlen(str) - 1] != '\n') strcat(str, "\n");
}
bool user_exists(char* u_name) {
	char user[100];
	char pswd[20];
	FILE* fptr;
	fptr = fopen(userdata, "r");
	while (!feof(fptr)) {
		fgets(user, 100, fptr);
		remove_n(user);
		if (strcmp(u_name, user) == 0) {
			return true;
		}
		fgets(pswd, 20, fptr);
	}
	return false;
}
void check_password(char* u_password) {
	while (1) {
		int flaga = 0, flagd = 0, flags = 0;
		if (strlen(u_password) < 8) {
			printf("Too short password. Please reenter the password to greater than equal to 8 characters");
		}
		else {
			for (int i = 0; u_password[i] != '\0'; i++) {
				if (isalpha(u_password[i])) flaga = 1;
				else if (isdigit(u_password[i])) flagd = 1;
				else if (!isalnum(u_password[i])) flags = 1;
			}
			if (!flaga) {
				printf("Password must contain at least one letter.\n");
			}
			if (!flagd) {
				printf("Password must contain at least one number.\n");
			}
			if (!flags) {
				printf("Password must contain at least one special character.\n");
			}
			if (flaga && flagd && flags) {
				printf("Password valid\n");
				return;
			}
		}
		printf("\nPlease re-enter your password: ");
		scanf("%99s", u_password);
	}
}
void newchats(char* u_name) {
	FILE* fptrnc, * fptrch, * ftemp;
	fptrnc = fopen(newchat, "r");
	fptrch = fopen(chats, "a");
	ftemp = fopen(temp, "w+");
	getchar();
	while (!feof(fptrnc)) {
		char s[100] = { '\0' };
		char r[100] = { '\0' };
		char msg[200] = { '\0' };
		fgets(s, sizeof(s), fptrnc); //gets sender username
		fgets(r, sizeof(r), fptrnc); //gets receiver username
		fgets(msg, sizeof(msg), fptrnc);  //gets message
		remove_n(s);//remove newline at end of 's' if present
		remove_n(r);//remove newline at end of 'r' if present
		remove_n(msg);//remove newline at end of 'msg' if present

		if (strcmp(r, u_name) == 0) {
			printf("%s:  %s\n", s, msg);
			add_n(s);
			add_n(r);
			add_n(msg);
			fwrite(s, sizeof(char), strlen(s), fptrch);					//writes sender username in file
			fwrite(r, sizeof(char), strlen(r), fptrch);			//writes receiver username in file
			fwrite(msg, sizeof(char), strlen(msg), fptrch);							//writes message into file
		}
		else {
			add_n(s);
			add_n(r);
			add_n(msg);
			fwrite(s, sizeof(char), strlen(s), ftemp);					//writes sender username in file
			fwrite(r, sizeof(char), strlen(r), ftemp);			//writes receiver username in file
			fwrite(msg, sizeof(char), strlen(msg), ftemp);							//writes message into file
		}
	}
	rewind(ftemp);
	fclose(fptrnc);
	fptrnc = fopen(newchat, "w");
	while (!feof(ftemp)) {
		char s[100] = { '\0' };
		char r[100] = { '\0' };
		char msg[200] = { '\0' };
		fgets(s, sizeof(s), ftemp); //gets sender username
		fgets(r, sizeof(r), ftemp); //gets receiver username
		fgets(msg, sizeof(msg), ftemp);  //gets message
		/*remove_n(s);//remove newline at end of 's' if present
		remove_n(r);//remove newline at end of 'r' if present
		remove_n(msg);//remove newline at end of 'msg' if present
		add_n(s);
		add_n(r);
		add_n(msg);
		*/
		fwrite(s, sizeof(char), strlen(s), fptrnc);					//writes sender username in file
		fwrite(r, sizeof(char), strlen(r), fptrnc);			//writes receiver username in file
		fwrite(msg, sizeof(char), strlen(msg), fptrnc);
	}
	fclose(fptrnc);
	fclose(ftemp);
	remove("temp.txt");
	return;
}
void existing_username(char* user) {
	FILE* fptr;
	fptr = fopen(userdata, "r");	//opening file "USER_DATA.txt" in read mode using file pointer
	if (fptr == NULL) {										//checking if file is opened properly
		printf("Error opening file.\n");
		return;
	}
	char u_name[100] = { '\0' };
	char password[100] = { '\0' };
	//getchar();
	//getting input for username from user
	printf("\nEXISTING USERS :\n");
	int i = 1;
	while (!feof(fptr)) {
		fgets(u_name, 100, fptr);
		fgets(password, 100, fptr);
		remove_n(u_name);
		if (feof(fptr)) break;
		if (strcmp(u_name, user) != 0) {
			printf("USER %d : %s\n", i, u_name);
			i++;
		}
	}
}

void searchchat(char* u_name, char* word) {
	FILE* fptr;
	fptr = fopen(chats, "r");
	if (fptr == NULL) {
		printf("Error opening file.\n");
		return;
	}
	char* s = (char*)malloc(sizeof(char) * 50);
	fgets(s, 50, fptr);
	char* r = (char*)malloc(sizeof(char) * 50);
	fgets(r, 50, fptr);
	char* sw = (char*)malloc(sizeof(char) * 100);
	fgets(sw, 100, fptr);
	bool fl = false;
	while (!feof(fptr)) {
		remove_n(s);
		remove_n(sw);
		if (strstr(sw, word)) {
			printf(" SEARCH SUCCESSFUL !!! \n  ---------------PRINTING----------------- \n");
			printf("%s: %s\n\n", s, sw);
			fl = true;
		}
		fgets(s, 50, fptr);
		fgets(r, 50, fptr);
		fgets(sw, 100, fptr);
	}
	if (!fl) printf("--------------ENTERED WORD NOT FOUND--------------\n");
}

void setstatus(char* u_name) {
	FILE* fptrss;
	fptrss = fopen(status, "a+");
	if (fptrss == NULL) {
		printf("Error opening file.\n");
		return;
	}
	char status[100] = { '\0' };
	printf(" Enter your status  ");
	getchar();
	fgets(status, 100, stdin);                                          //getting input for username from user
	add_n(status);
	add_n(u_name);
	fwrite(u_name, sizeof(char), strlen(u_name), fptrss);
	fwrite(status, sizeof(char), strlen(status), fptrss);     //appending username and password data to file
	fclose(fptrss);
	system("cls");
	return;
}

void seestatus() {
	FILE* fptrs;
	fptrs = fopen(status, "r");
	if (fptrs == NULL) {
		printf("Error opening file.\n");
		return;
	}
	char otheruser[100] = { '\0' };
	printf(" Enter whose status you want to see  ");
	getchar();
	fgets(otheruser, 100, stdin);
	remove_n(otheruser);
	char reqs[100]={ '\0' };
	bool flag = false;

	while (!feof(fptrs)) {
		char s[100] = { '\0' };
		char msg[200] = { '\0' };
		fgets(s, sizeof(s), fptrs); //gets sender username
		fgets(msg, sizeof(msg), fptrs);  //gets message
		remove_n(s);//remove newline at end of 's' if present
		remove_n(msg);//remove newline at end of 'msg' if present
		if (strcmp(s, otheruser) == 0) {
			strcpy(reqs,msg);
			flag = true;
		}
	}
	if (flag == true) printf("%s\n", reqs);
	if (flag == false) printf("\n NO STATUS AVAILABLE \n\n");
	fclose(fptrs);

}
