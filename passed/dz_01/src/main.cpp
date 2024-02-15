void findSubstring(const string& fileContent, const string& substring, const string& outputFilePath,
    size_t shift, mutex& mtx, vector<condition_variable>& cVars, size_t index) {

    auto startTime = chrono::high_resolution_clock::now(); // (1)

    size_t substringLength = substring.length(); // (2)
    vector<size_t> positions; // (3)
    for (size_t i = 0; i < fileContent.length(); ++i) { // (4)
        if (fileContent.substr(i, substringLength) == substring) {  // (5)
            positions.push_back(i + shift);  // (6)
        }
    }
    {
        lock_guard<mutex> lock(mtx);  // (7)
        ofstream outputFile(outputFilePath, ios::app);  // (8)
        for (size_t pos : positions) {  // (9)
            outputFile << pos << "\n";  // (10)
        }
        cVars[index].notify_one();  // (11)
    }

    auto endTime = chrono::high_resolution_clock::now();  // (12)
    auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();  // (13)
}