QTwitchBot is an opensource Twitch.tv bot that runs on Windows/Mac/Linux

===============================================
	TwitchBot Alpha Release V.1
	Please Give Feedback On GitHub
===============================================

TwitchBot Language (TBL)
===========================

TwitchBot has support for a scripting language called TBL and reads TBS files (TwitchBot Script)

Simply create a new file and name it anything.tbs

Inside the file you can create commands that users can use in your stream and the response the bot will send

the format looks like this

!command,response
!anothercommand,response

[Specials]
The TBL has support for special commands that call a function in the program in this release these are

[getTime] = Gets YOUR current system time
[randomNumber] = Generates a random number from 1 - 1000
[nextSong] = Plays next song in loaded playlist
[prevSong] = Plays previous song in loaded playlist

A special command is created like so...

!command,[special]

Where the !command can be anything you wish and the [special] is the command to be run

You may view the commands that were loaded into your script on the left hand side of the bot
==================================================================
General Features
==================================================================
Ban/Unban users from the GUI
Set Slow Mode/ Un-set it from the GUI
Send an announcement to the stream from the GUI
Clear Stream Chat
Add Moderator / Remove Moderator

View the live feed of the stream from the bot (Requires Flash)
View the chat feed as seen on Twitch.tv (Broken)
