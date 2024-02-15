void shaker_sort(std::vector<int>& array) {
    int n = array.size();
    bool swapped;

    do {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
         
        if (!swapped) {
            break;
        }

        swapped = false;
        for (int i = n - 2; i >= 0; --i) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}