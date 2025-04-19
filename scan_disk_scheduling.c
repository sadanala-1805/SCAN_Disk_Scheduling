#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n, int ascending) {
    for(int i = 0; i < n-1; ++i) {
        for(int j = 0; j < n-i-1; ++j) {
            if ((ascending && arr[j] > arr[j+1]) || (!ascending && arr[j] < arr[j+1])) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, i, head, direction, disk_size;
    int total_seek_time = 0;

    printf("Enter the number of disk I/O requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter the disk I/O request sequence: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size (number of cylinders): ");
    scanf("%d", &disk_size);

    printf("Enter initial direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    int left[n], right[n];
    int l = 0, r = 0;

    for(i = 0; i < n; i++) {
        if(requests[i] < head)
            left[l++] = requests[i];
        else
            right[r++] = requests[i];
    }

    sort(left, l, 0);
    sort(right, r, 1);

    printf("\nSeek Sequence: %d ", head);

    if(direction == 0) {
        for(i = l-1; i >= 0; i--) {
            total_seek_time += abs(head - left[i]);
            head = left[i];
            printf("-> %d ", head);
        }
        if (l > 0) {
            total_seek_time += head;
            head = 0;
        }
        for(i = 0; i < r; i++) {
            total_seek_time += abs(head - right[i]);
            head = right[i];
            printf("-> %d ", head);
        }
    }
    else {
        for(i = 0; i < r; i++) {
            total_seek_time += abs(head - right[i]);
            head = right[i];
            printf("-> %d ", head);
        }
        if (r > 0) {
            total_seek_time += (disk_size - 1 - head);
            head = disk_size - 1;
        }
        for(i = l-1; i >= 0; i--) {
            total_seek_time += abs(head - left[i]);
            head = left[i];
            printf("-> %d ", head);
        }
    }

    printf("\n\nTotal Seek Time = %d\n", total_seek_time);
    return 0;
}
