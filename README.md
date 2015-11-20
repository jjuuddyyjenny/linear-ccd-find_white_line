# linear-ccd-find_white_line
int find_white_line() {
		
    int targetNumber = 10;
    int arrayLength = 128;
    int sortedArray[128];
    //int sortedArray[100]; 
    //Only make it 
    for (int h = 0; h < 128; ++h) {
        sortedArray[h] = linear_ccd_buffer1[h];
    }
    
    int swap;

    for (int i = 0; i < arrayLength; ++i) {
        for (int j = 0; j < arrayLength - i - 1; ++j) {
            if (sortedArray[j] < sortedArray[j+1]) {
                swap = sortedArray[j];
                sortedArray[j] = sortedArray[j+1];
                sortedArray[j+1] = swap;
            }
        }
    }

    int xvalues[targetNumber];
    int index = 0;
    int target = sortedArray[targetNumber];
    for (int i = 0; i < arrayLength; ++i) {
        if (linear_ccd_buffer1[i] > target) {
            xvalues[index] = i;
            index +=1;
        }
    }
    int averagex = 0;
    int sum = 0;
    for(int i = 0; i < targetNumber; i++) {
        sum += xvalues[i];
    }
		if(target>110)
		{
    averagex = sum/targetNumber;

    return averagex;
		}
		else
		{return 64 ;}
}
