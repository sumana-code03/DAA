#include <stdio.h>
struct Data{
    int value;
    int index;
};
int binarysearch(struct Data arr[], int l, int r, int x){
    while (l <= r){
        int mid = (l + r) / 2;
        if (arr[mid].value == x)
            return mid;
        else if (x > arr[mid].value)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}
int main()
{
    struct Data arr[100], temp;
    int n, i, j, x, pos;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i].value);
        arr[i].index = i;
    }
    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - i - 1; j++){
            if(arr[j].value > arr[j + 1].value){
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("After sorting (ascending order): ");
    for(i = 0; i < n; i++)
        printf("%d ", arr[i].value);
    printf("\nEnter searching element: ");
    scanf("%d", &x);
    pos = binarysearch(arr, 0, n - 1, x);
    if(pos != -1){
        i = pos;
        while(i >= 0 && arr[i].value == x){
            printf("Element found at original index :- %d \n", arr[i].index+1);
            i--;
        }
        i = pos + 1;
        while(i < n && arr[i].value == x){
            printf("Element found at original index :- %d \n", arr[i].index+1);
            i++;
        }
    }
    else{
        printf("Element not found");
    }
    return 0;
}
