//TODO
//
//  ctrl + c => code should not be terminated it should print new prompt
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
//
//
//      //before the whole code
// 
//  }
