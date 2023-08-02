#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int *arr;
int sz = 0;

void *thread1(void *arg)
{
	int tests[20]; //up to 20 test scores can be entered
	int score, nread, i; //integer that holds a score value, the number of bytes read, loop counter
	char buffer[BUFSIZ];
	printf("Enter a test score. Ctrl+D if no more scores\n");
	while(sz < 20 && (nread = read(0, &buffer, BUFSIZ)) > 0)
	{
		sscanf(buffer, "%d", &score); //scan for a keyboard entry
		tests[sz] = score;
		sz++; //size of the array increases with every keyboard entry
		printf("Enter a test score. Ctrl+D if no more scores\n");
	}
	arr = (int*)malloc(sz*sizeof(int)); //allocates memory for the entries in the array
	for(i = 0; i<sz; i++)
		arr[i] = tests[i]; //fills the array with the keyboard entries

	pthread_exit(NULL);
}

void *thread2(void *arg)
{
	//calculate average and median scores in the array
	int sum = 0;
	for(int i = 0; i < sz; i++)
		sum += arr[i];
	
	float avg = sum/(float)sz;
	printf("Average score is: %.2f\n", avg);

	float med;
	//find the median value
	int *temp = (int*) malloc(sz*sizeof(int));
	for(int i = 0; i<sz; i++)
		temp[i] = arr[i]; //fill the temporary array with the same scores from the score array
	//sort the array before finding the median val
	for(int i = 0; i < sz; i++)
	{
		for(int j = i+1; j < sz; j++)
		{
			if(temp[j] < temp[i]) //compare elements and swap if the compared elem is less than
			{
				int t = temp[i];
				temp[i] = temp[j];
				temp[j] = t;
			}
		}
	}

	if(sz%2 == 0) //if an even number of elements, find the average of the middle nums
		med = (float)(temp[(sz / 2) - 1] + temp[(sz / 2)])/2;
	else //the odd number is median
		med = (float)(temp[(sz / 2)]);

	printf("Median score is: %.2f\n", med);

	free(temp);
	pthread_exit(NULL);
}

void *thread3(void *arg)
{
	//find the min and max scores in the array
	int min = arr[0], max = 0;
	for(int i = 0; i < sz; i++)
	{
		if(min > arr[i])
			min = arr[i];
		if(max < arr[i])
			max = arr[i];
	}
	printf("Minimum value: %d\n", min);
	printf("Maximum value: %d\n", max);
	pthread_exit(NULL);
}

void *thread4(void *arg)
{
	//resets the buffer
	for(int i = 0; i < sz; i++)
	{
		arr[i] = 0;
		printf("%d ", arr[i]); //print each number with a space proceeding it
	}
	printf("\n");
	pthread_exit(NULL);
}

int main()
{
	//Make an array of threads to hold each thread (for sake of simplicity)
	pthread_t t1, t2, t3, t4;

	int ret; //return code
	void *wait; //for use in pthread_join

	if((ret = pthread_create(&t1, NULL, thread1, NULL)) != 0) //create the first thread
	{
		perror("return code error from pthread_create()");
		exit(1);
	}
	if((ret = pthread_join(t1, &wait)) != 0) //wait until the first thread finishes before running threads 2 and 3
	{
		perror("return code error from pthread_join()");
		exit(1);
	}
	if((ret = pthread_create(&t2, NULL, thread2, NULL)) != 0) //create threads 2 and 3 to run concurrently
	{
		perror("return code error from pthread_create()");
                exit(1);
	}
	if((ret = pthread_create(&t3, NULL, thread3, NULL)) != 0)
	{
		perror("return code error from pthread_create()");
                exit(1);
	}
	//wait until threads 2 and 3 finish before running thread 4
	if((ret = pthread_join(t2, &wait)) != 0)
	{
		perror("return code error from pthread_join()");
                exit(1);
	}
	if((ret = pthread_join(t3, &wait)) != 0)
	{
		perror("return code error from pthread_join()");
                exit(1);
	}
	if((ret = pthread_create(&t4, NULL, thread4, NULL)) != 0) //create thread 4
	{
		perror("return code error from pthread_create()");
                exit(1);
	}
	
	pthread_exit(NULL); //exit the main thread
	free(arr); //free the allocated memory for the array
	return 0;
}
