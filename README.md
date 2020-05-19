# C-8QueenRiddle-Processes-2-versions

This project is implemented by Processes in two versions:

  version 1:

    The main process will check correctness of the testing solution (standard chess board).
    A valid chess board to check consists of only "Q","." and whitespace characters.
    A valid solutin for the test consists of exactly 1 Queen in each row/column and at most 1 Queen at the diagonals.
    The main process will create 4 processes.
    Each child will call the principal and enter the program that does the appropriate test (row, column or half of the diagonal test).
    The main process will be using a pipe system to communicate with his children.
    The process will create a pipeline in front of each child who will pass the inputs (there may be more than one input file) and use       another pipeline to get the children's results from the tests they did.
    The files that the children will run will read the input from the standard input and write the output to the standard output.
    We will use the dup2 command to direct the child process side of each pipe to his standard input and standard output.
    
 version 2:
    
    The main process will check correctness of the testing solution (standard chess board).
    A valid chess board to check consists of only "Q","." and whitespace characters.
    A valid solutin for the test consists of exactly 1 Queen in each row/column and at most 1 Queen at the diagonals.
    The main process will create 4 processes.
    The main process will be communicating with the children using shared memory for him and his children.
    The main process will use the mmap system call to create the shared memory area.
    The call to mmap will be done before calls to fork so that the processes receive the mapping as well.
    The status array is an array into which the four children will write their test results.
    Each child writes only to the designated entrance, so no need for synchronization between the children and themselves.
    There is synchronization between the parent process and the child: The parent process needs to know when the children have completed     the test by being able to print the output and transmit to the children the next input, if any;
    The children need to know when the next input was received and when the inputs ended.
    Each process is allowed to make waiting busy (as directed by the question).
    
