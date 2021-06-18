#include <stdio.h>
#include <stdlib.h>

int *sequence = NULL;
int num_tracks;
int sequence_size;

// declare global variables, including dynamic array of integers to store sequence of tracks


/*******************************************/
void parameter() {
    
	// prompt for number of concentric tracks and size of sequence
	printf("Enter the number of concentric tracks: ");
	scanf("%d", &num_tracks);

	printf("Enter size of sequence: ");
	scanf("%d", &sequence_size);
	printf("\n");
	
	// allocate memory for sequence dynamic array
	sequence = (int*) malloc(sequence_size * sizeof(int));
	return;
}


/*******************************************/
void FIFO() {
	// declare local variables
    int num_traversed;
  	// for-loop: prompt for each track in sequence
    printf("\nEnter sequence of tracks to seek:");

	for( int i =0 ; i <= sequence_size -1; i++){
	scanf("%d", &sequence[i]);
	// if track is out of range (<0 or > number of tracks, printe message and return
	 if ((sequence[i] <0 ) || (sequence[i] > num_tracks)){
	     printf("\nOut of range");
	     return;
	 }
	}
	// initilize number of traversed tracks to first track in sequence
    printf("\n Traversed sequence: %d ", sequence[0]);
    num_traversed = sequence[0];
    
	// for loop: 
	for(int i=1; i <= sequence_size-1; i++){
		// update nummber of trversed tracks based on absolute value of difference between adjacent indices in sequence 
		num_traversed += abs(sequence[i] - sequence[i-1]);
		// print traversed sequence	
	    printf("%d ",sequence[i]);
	}
	// print number of traversed tracks 	
    printf("\nThe number of tracks traversed is: %d\n", num_traversed);
    return;
} 
	
	
/*******************************************/
void SSTF() {
	// declare local variables
    int num_traversed;
    int i;
    int *sorted = NULL;
    int total_delay = 0;
    int longest_delay = 0;
    int longest_track = 0;
    int num_track_moved = 0;
    int average_delay = 0;
    int num_moves = 0;
    int j;
    int temp;

    
	// for-loop: prompt for each track in sequence
	printf("Enter sequence of tracks to seek: ");
	
	for( i =0 ; i <= sequence_size -1; i++){
	scanf("%d", &sequence[i]);
	// if track is out of range (<0 or > number of tracks, printe message and return
	  if (sequence[i] <0 || sequence[i] > num_tracks){
	     printf("\nOut of range");
	     return;
	 }
	}
	// allocate memory for sorted sequence dynamic array & initialize to original sequence
	sorted = (int*) malloc(sequence_size * sizeof(int));
	for( i =0 ; i <= sequence_size -1; i++){
	 sorted[i] = sequence[i];   
	}

	// sort elements in increasing order using a sorting algorithm (Selection sort, etc.) ----------------------------------------------------------------------------------------
	for (i = 0; i <sequence_size -1; i++) //only the one with num_porccess-1
	{
		for ( j=i+1; j < sequence_size; j++)
		{
		
			if (sorted[i] > sorted[j])
			{
			temp = sorted[i];
			sorted[i] = sorted[j];
			sorted[j] = temp;
			}//end of if
		}// end for j
	}// end for i

	// for-loop: 
		for( i =0 ; i < sequence_size -1; i++){
            j = i +1;
            
            while ((sequence[i] != sorted[j]) && ( j < sequence_size) )
            j++;
            
            if(j < sequence_size){
		    //printf("Im at line 117");
		    num_moves = j-i;
		    total_delay += num_moves;
		    num_track_moved += 1;
		    }
     
		// calculate delays based on difference between track position in sorted array and original array
	
		// update value of longest delay & associated track if number of moved positions is greater than current longest delay		
		if(num_moves > longest_delay){
		    longest_delay = num_moves;
		    longest_track = sequence[i];
		}
		
	}
	// initilize number of traversed tracks to first track in sequence
	    num_traversed = sorted[0];
	    
        printf("\nTraversed sequence: %d ", sorted[0]);
		for( i =1 ; i <= sequence_size -1; i++){
		   // update nummber of trversed tracks based on difference between adjacent indices in sorted array 
				num_traversed += (sorted[i] - sorted[i-1]);
			// print traversed sequence	
	            printf("%d ",sorted[i]);
		}
	// print number of traversed tracks 
    printf("\nThe number of tracks traversed is: %d\n", num_traversed);

	// calculate and print average_delay
	average_delay = total_delay / num_track_moved;
	
    // print longest delay and associated track
    printf("The average delay of all tracks processed later is: %d\n", average_delay);              
    printf("The longest delay experienced by a track is: %d by track  %d\n\n", longest_delay, longest_track); 
    free(sorted);
	return;
}

/***************************************************************/
void quit() {
/* If the table is not NULL, free the memory */
	
	printf("Quitting");
	if (sequence != NULL) free(sequence);
  return;
}


/***************************************************************/
int main() {

	/* Declare local variables */
	int choice;
	
	/* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
while ( choice != 4)
{
    printf("Batch Scheduling\n");
	printf("--------------------------------\n");
	printf("1) Enter parameters \n");
	printf("2) Schedule disk tracks with FIFO \n");
	printf("3) Schedule disk tracks with SSTF \n");
	printf("4) Quit program and free memory \n\n");
	
	printf("Enter selection: ");
	scanf("%d", &choice);

	
	if (choice == 1)
	{
	   parameter();
	}
	
	else if (choice == 2)
	{
	   FIFO();
	}
	
	else if (choice == 3)
	{
	   SSTF();
	}
	else if (choice == 4)
	{
	   quit();
	}
	
} //end while loop

  return 1;
}


