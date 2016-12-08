#include <iostream>
#include <string>

#include "playlist.h"
#include "doublylinkedlist.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

/**
 * Process a playlist command.
 *
 * Gets an entire line from std::cin, extracts the first word as the command,
 * and calls the appropriate processing function. Invalid commands are
 * ignored.
 */
void Playlist::processCommand() 
{
	string inputLine, inputString;
	getline(cin, inputLine);
	inputString = inputLine.substr(0, inputLine.find(' '));
	inputLine.erase(0,inputString.length()+1);
	if (inputString == "appendSong")
	{	   
	  dll.append(inputLine);
	}
	
	else if (inputString == "insertBefore")
	   dll.insertBefore(inputLine);
	else if (inputString == "insertAfter")
	   dll.insertAfter(inputLine);
	else if (inputString == "gotoFirstSong")
	   dll.begin();
	else if (inputString == "gotoLastSong")
	   dll.end();
	else if (inputString == "playCurrent")
	{	 
	  cout << endl << "playing current: ";	
	  if (dll.empty() == false) 
		{
		  dll.getData();
		}	
	}
	else if (inputString == "removeSong")
	   dll.remove(inputLine);
	else if (inputString == "gotoSong")
	  dll.find(inputLine);
	else if (inputString == "nextSong")
	   dll.next();
	else if (inputString == "prevSong")
	   dll.prev();
	else if (inputString == "playForward")
	  { 
	  	cout << endl << "playing forward: " << endl;
		if (dll.empty() == false)
		
		do
		{     
			dll.getData();
		         
		} while(dll.next());
 	   
	  }
	else if (inputString == "playReverse")
	  { 
	  	cout << endl << "playing reverse: " << endl;
		if (dll.empty() == false)
		do
		{
			dll.getData();
		}while(dll.prev());
 	   
	  }
}


/**
 * The Playlist main loop will process command lines until eof.
 */  
void Playlist::mainLoop() {
   while (!cin.eof()) 
	processCommand();         // process all commands
}

/**
 * The main entry point for the program.
 */
int main()
{
   Playlist myPlaylist;
   myPlaylist.mainLoop();
   return 0;
}

