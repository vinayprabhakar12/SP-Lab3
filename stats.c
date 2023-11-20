//Vinay Prabhakar
//11-19-2023

//This is a simple program which reads number data from a txt file 
//and computes the mean, median and standard deviation for the data set

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Funciton to sort the array based on values
void sortNum(float *numList, int *numElements){   
    int i, j;
    int swapped;
    float temp;
    for (i = 0; i < *numElements - 1; i++) {
        swapped = 0;
        for (j = 0; j < *numElements - i - 1; j++) {
            if ((numList)[j] > (numList)[j + 1]) {
                temp = (numList)[j];
                (numList)[j] = (numList)[j + 1];
                (numList)[j+1] = temp;
                swapped = 1;
            }
        }
    }
}

//Function to double the capacity of the array
float * doubleArray(float *smallList, int *numElements, int *arraySize){
    float *largeList;
    largeList = (float*)malloc(2 * (*arraySize * sizeof(float)));
    for(int i=0; i<*numElements; i++){
        largeList[i] = smallList[i];
    }
    *arraySize = *arraySize * 2;
    free(smallList);
    return largeList;
}

//Function to calcualte MEAN
double meanArray(float *numArray, int *numElements){
    double mean;
    double sum = 0;
    for(int i=0; i<*numElements; i++){
        sum = sum + numArray[i];
    }
    mean = sum/(*numElements);
    return mean;
}

//Function to calculate the MEDIAN
float medianArray(float *numArray, int *numElements){
    float median;
    if(*numElements%2 == 1){
        median = numArray[(*numElements-1)/2];
    }
    else
        median = (numArray[(*numElements/2)-1] + numArray[(*numElements/2)])/2;
    return median;    
}

//Function to calulate the STANDARD DEVIATION
float stddevArray(float *numArray, int *numElements, double *mean){
    float stddev;
    double sumdev = 0;
    for(int i=0; i<*numElements; i++){
        sumdev = sumdev + pow((numArray[i]-*mean),2);
    }
    stddev = sqrt(sumdev/(*numElements));
    return stddev;
}

//The main function
int main(int argc, char **argv){
    char *filename = argv[1];
    int arraySize = 20;
    int numElements = 0;
    float *numArray;

    numArray = (float*)malloc(arraySize * sizeof(float));

    //Reading the file and storing into an array
    FILE *reads;
    reads = fopen(filename, "r");
    if(reads == NULL){
        printf("Error! Re-run the program with a proper filename\n");
        return -1;
    }
    else{
        while(!feof(reads)){
            fscanf(reads, "%f", &numArray[numElements]);    //Make fscanf end when it reaches an empty line
            numElements++;
            if(numElements==arraySize  && !feof(reads)){
                numArray = doubleArray(numArray, &numElements, &arraySize);
            }
        }
    }

    //Sort the array
    sortNum(numArray, &numElements);
        
    double mean;
    float median, stddev;   

    //Calcualting the MEAN
    mean = meanArray(numArray, &numElements);

    //Calculating the MEDIAN
    median = medianArray(numArray, &numElements);

    //Calculating the STANDARD DEVIATION
    stddev = stddevArray(numArray, &numElements, &mean);

    //Printing the statistics
    printf("\n          DATA STATISTICS\n");
    printf("-------------------------------------\n");
    printf("   Number of elements:%15d\n", numElements);
    printf("                 Mean:%15.3f\n", mean);
    printf("               Median:%15.3f\n", median);
    printf("   Standard Deviation:%15.3f\n", stddev);
    printf("Unused array capacity:%15d\n", (arraySize-numElements));

    //Deallocating the space for the array
    free(numArray);
}