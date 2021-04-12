# batteryMemoryNotifier
## Problem Statement
Design an application - Like a module - which will give warning msg when power or memory goes down.
## Design
The information regarding power and memory are retrieved from proc and sys directory(in root directory).</br>
A C code is implemented(in linux) to manipulate these info and display relevant Notifications.</br>
The code is converted into an executable file under a diffrent name and its run command "./<file_name> &" is added to the first line of "/home/<user_name>/.bashrc" file, so that the progress executes during the operating system's startup.</br> 
The '&' after file name in run command makes the process run in background
<h3>Explanation Video 1:</h3>
https://drive.google.com/file/d/1Y49eaB7Q849CShsUqwtudZbPdtdsbwFs/view?usp=sharing
<h3>Explanation Video 2:</h3>
https://drive.google.com/file/d/1ubZQX5Fh7drmiCMCFct8rV3iyB7A6VJF/view?usp=sharing
