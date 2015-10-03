It is with sad news that I announce that I have no futher plans to develop QTwitchBot, It was a fun ride while it lasted and I may revive the project at a later stage how ever breaking changes to twitch and my lack of time for projects already means that I wish to focus my attention on other projects.
I am on GitHub every day, if you decide to fix this project I will be more than happy to review your code and add merge it with this repository.

Regards - TheOpenDevProject.

QTwitchBot is an opensource Twitch.tv bot that runs on Windows/Mac/Linux

===============================================
	TwitchBot Beta Release V.1.2
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
	[whatNext] = What is the next song playing, sends this out to the stream
	[Riot::getSummonerLevel] = using the Riot Games API get your summoner level
	[Riot::getRankedSummary] = using the Riot Games API get your current division/lp
	[Riot::getWinStreakStatus] = using the Riot Games API, returns if you are on a hot streak(3 win streak)
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
	Theme Engine
	Paint Overlays

Example Script
===================================================================
	!league,Gold IV - Fioras Hord
	!whois,My name is Riot ToxicHawk - I work for Riot Games OCE as a Lead NOC (Which means I fix stuff)
	!time,[GetTime]
	!nextSong,[nextSong]
	!prevSong,[prevSong]
	!isdead,Happy pigeon just did not work out for me sorry guys its gone 4eva
	!daboss,Frozenfury2 is said to be the boss of league
	!streamTimes, I am quite busy but now I have a stream setup at home i should be able to stream a lot more
	!commands,!league !whois !time !nextSong !prevSong !randomNum !isdead !streamTimes
	bye,Good Bye and Thanks for watching
	!hugs, Riot ToxicHawk gives jens a big rioter hug to add to her collection
	!og, Auv2channel was here before anything began. Creator of Toxic himself
	!real, Riot ToxicHawk is so real that chuck norris questions him for advice on how to stay cool
	!faker, Some absolute pleb at League Of Legends who wishes he could be on Toxics mid lane level.
	!aub2, Worst League team ever. Makes me feel like it's in YoloQue.
	!haddaway, What is love oooohhh baby dont hurt me nooo dont hurt me nooooo more
	!goldPlays,Just like bronze only crunchy :)
===================================================================

