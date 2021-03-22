int binsearch(int low, int high, int tar, int array[])
{
    int i, mid;
    while(low <= high)
    {
        mid = low + (high - low) / 2;
        if(array[mid] > tar)
        {
            high = mid - 1;
        }
        else if(array[mid] < tar)
        {
            low = mid + 1;
        }
        else
        {
            break;
        }
    }
    if (array[mid] != tar)
    {
        return -1;
    }
    return mid;
}
