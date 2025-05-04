  Niv Ramati  322566332 
  Nofar Sages 212780324
  
  Notes :
  
  1. Mario can kill a barrel only while moving and if it is within a distance of 1 or 2.
	link - https://mama.mta.ac.il/mod/forum/discuss.php?d=3638#p4602
  
  2.If a barrel is spawned on a '=' floor, it is automatically assigned a diff_x = 1 (movement to the right).
  
  3.If Mario or a barrel falls without landing on a floor, they die.
	  
  4.If a barrel reaches the screen's boundary, it simply dies and is removed from the game.
  
  5.The diff_x value for the ghost effect is set to 1 (movement to the right)
  
  6.If there is a mismatch between the expected result file and the actual result in the game, the error message will appear at the end of the specific screen's run, and the game will stop.
  
  7.If a step file is missing for a specific screen, an error message will be displayed, and the game will stop.
  
  8.If a result file is missing for a specific screen, the game will run that screen, and at the end, an error message will be displayed indicating that the result file is missing for the corresponding screen.
  
  9.If the screen is faulty, the user will be given the option to move to the next screen even during the loading state.