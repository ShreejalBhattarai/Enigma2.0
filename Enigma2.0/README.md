# Enigma2.0
The code for electronic replica implemented using the raspberry pi pico for educational purposes.


Notes along the way:
July 13
- Today, I tried to configure the CMake to work for all of the files. Now I do not have to change much there forwards.
I had a severe problem when the linux OS compiler interefered the pico's ARM compiler, and it got worse when the vivado's compiler got detected. FIX: I added a line in flash.sh to use ARM's compiler to compile the pico's code.
- After that I realised that I had added git only in enigma 2.0 but in reality i needed was whole directory as there were build files that needed to be outside the source files. So, I moved the git one step up.