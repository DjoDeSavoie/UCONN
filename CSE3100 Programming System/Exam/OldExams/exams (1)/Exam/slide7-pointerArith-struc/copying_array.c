// using array indexing
void copy_array(int source[], int target[], int n){
    for(int i = 0; i<n; i++){
        target[i] = source[i];
    }
}

//using pointers
void copy_array1(int source[], int target[], int n){
    for(int i = 0 ;i < n; i++){
        *target++ = *source++;
    }
}