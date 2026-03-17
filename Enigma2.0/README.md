# Enigma2.0
The code for electronic replica implemented using the raspberry pi pico for educational purposes.


Notes along the way:  
July 13, 2025
- Today, I tried to configure the CMake to work for all of the files. Now I do not have to change much there forwards.
I had a severe problem when the linux OS compiler interefered the pico's ARM compiler, and it got worse when the vivado's compiler got detected. FIX: I added a line in flash.sh to use ARM's compiler to compile the pico's code.
- After that I realised that I had added git only in enigma 2.0 but in reality i needed was whole directory as there were build files that needed to be outside the source files. So, I moved the git one step up.


August 3, 2025  
So I have now added the encryption functions and some other functions, but it's not working well, because of some minor issues. Some steps to take for the issues I encountered:
- Need to clear the buffer at the start of the program.
- After input is read, (both at the main menu and the encrypt/decrypt steps), the program should echo the input, so still have to implement that.
- Major issue is that the program only works once, after that I have to unplug, plug the baord again, I have yet to search the solution.
- One major TODO: To add some decorations in the terminal, and write clear steps to compile the program to help anyone following the repository.

March 16, 2026
After a break from the project, I was finally able to fix the input reading error. Now the code is fully functional. Next steps could be adding decorations to make the terminal more interactive and make the program more abstract to the user. Future work might also adding hardware based control.
