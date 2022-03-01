# Tetris_V2
In order to run this project the JUCE library files need to be accessible.
You can either copy the whole folder to the project (not reccomended)
Or you can create a symbolic link to your JUCE library folder.

e.g ln -s /Users/some-user/JUCE/ /Users/some-user/dev/Tetris_V2/JUCE/Users/tom-harvey/dev/backup_2/README.md

If you don't have JUCE, it can be installed from the following link:

https://juce.com/get-juce/download

This project is built using CMake. To build an xcode project do the following in the Tetris_V2 folder.

mkdir xcode
cd xcode
cmake -G Xcode ..

Otherwise use your IDE of choice.


