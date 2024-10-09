int compare_string(const void *a, const void *b){
    char *s1, *s2;
    s1 = *(char **)a;
    s2 = *(char **)b;

    return strcmp(s1, s2); //use library function to compare
}

//or on one line
int compare_str2(const void *a, const void *b){
    return strcmp(*(char**)a, *(char**)b);
}