//TODO: SIGNAL PART
//
//  ctrl + c => code should not be terminated it should print new prompt
//
//NOTE: the thing is prompt and input string array should be global else 
//       you cannot access it on siganl_handler function 
//
//ERROR : use waitpid(pid,&status,WUNTRACED); idk where to put it 
//
//  siganl_handler( signum ) {
//
//      if ( collected siganal is SIGINT ) {
//
//          print(prompt);
//          
//      } else if ( collected signal is Ctrl+z ) {
//              
//              print(prompt);
//      } 
//
//  }
//      
//  inside scaninput() {
//
//      signal(SIGINT,siganl_handler);
//
//      signal(SIGTSTP,siganl_handler); // for ctrl + z
//
//      //before the whole code
// 
//  }
