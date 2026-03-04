# C-CLI-Chat-System(Group Project)
Robust command-line-interface(CLI) application built from scratch in C. Implements core programming concepts including file handling and string manipulation.This project was developed as a collaborative group effort for the course Introduction to Computer Science in the 1st Semester.
## Features:
### Identity and Security:
**Registration and Authentication:** 
* Cross-references user input with stored file records, granting session access only upon successful validation.
* Passwords must meet a complexity threshold (Minimum 8 characters, including $\ge 1$ letter, $\ge 1$ digit, and $\ge 1$ special character).
### Messaging & Data Handling:
**Messaging Pipeline:** Enables authenticated users to transmit data to specific recipients, updating the chat history.
**View History:** Scans the chat history to filter and display dialogues relevant to the logged-in user.
**Search Functionality:** Implements a keyword search algorithm to parse message strings and return matching historical data.
### Modularity: 
Each feature and function has been implemented using separate functions for clear understanding and error correction.
## Technical Details:
* **Language:** C
* **Libraries:** `stdio.h`, `stdlib.h`, `string.h`, `conio.h`
* **Interface:** Command-line menu-based navigation
* **File Handling:** Used File-I/O for user and chat details
  
## Project Structure
* `USER_DATA.txt`: Stores user credentials.
* `CHATS.txt`: The primary database for message history.
* `status.txt`: Stores user-defined status updates.
  
## User Interface (CLI) 
The application uses a menu-driven interface. Users navigate by entering character commands: R, L, V, N, S, F, G
## Group Project: 
This was a collaborative group project. 
1. Jaineel Chetan Vora (B24CM1080) - 20%
2. Om Gupta (B24BB1022) - 20%
3. Anirudh Balaji (B24ES1026) - 30%
4. Raghav Srinivasan (B24EE1060) - 30%
