//test_wait.cpp
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
  pid_t pid;		//process id
  char *message;
  int n;
  int exit_code;

  cout << "fork program starting\n";
  pid = fork();
  switch ( pid ) {
  case -1:
    cout << "Fork failure!\n";
    return 1;
  case 0:
    message = "This is the child\n";
    n = 5;
    exit_code = 9;
    break;
  default:
    message = "This is the parent\n";
    n = 3;
    exit_code = 0;
    break;
  }
  for ( int i = 0; i < n; ++i ) {
    cout << message;
    sleep ( 1 );
  }


  
  //waiting for the  child to finish
  if ( pid != 0 ) {		//parent 
  	cout << "I am the child with process id: "<< getpid()<< endl;
	cout <<"My parent has the procress is: "<< getppid()<< endl;
	int grand_parent = getppid();
	int parent = fork(); // create another child
        if (parent == 0) // this is the grand_child
		{
			cout <<"I am the grand child with process id: "<<getpid()<<", And my parent was: " << getppid() << endl<< ", And my grand parent was: "<< grand_parent << endl;
			cout << endl;
		}
    int stat_val;
    pid_t child_pid;

    child_pid = wait ( &stat_val );	//wait for the child to finish
    cout << "Child finished: PID = " << child_pid << endl;
    if ( WIFEXITED ( stat_val ) )
 		cout << "child exited with code " << WEXITSTATUS ( stat_val ) << endl;
    else
		cout << "child terminated abnormally!" << endl;
  }
  exit ( exit_code ); 
   
}

