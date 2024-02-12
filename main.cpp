#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>
using namespace std;

// You must design and implement the ArrayVector class below:
// arraryVector class to have functions that emulates std::vector

template <typename Elem>
class ArrayVector {
private:
    Elem* array; //pointer to an array of elements of type Elem
    size_t n;
    size_t capacity;
    const size_t initial_capacity = 10;

    //well need to adjust the size of the array each time an element is added
    void resize(size_t newCapacity) {
        Elem* newArray = new Elem[newCapacity]; //creating the new array

        //if N < n
        if(newCapacity < n) {
            n = newCapacity;
        }

        for (size_t i=0; i<n; i++){ //insert elements from the old array to the new array
            newArray[i] = array[i];
        }

        //expanding the array if N > n
        for(size_t i=n; i<newCapacity; i++) {
            newArray[i] = Elem(); //null state
        }
        delete[] array; //to delete the old array
        array = newArray;
        capacity = newCapacity;
    }




public:
    // constructor https://www.geeksforgeeks.org/how-to-initialize-array-of-objects-with-parameterized-constructors-in-c/
    ArrayVector(int i) {
        array = new Elem[initial_capacity];
        n=0;
        capacity=initial_capacity;
    }

    //deconstructor https://cplusplus.com/forum/beginner/30903/
    ~ArrayVector() {
        delete[] array;
    }

    //function reserve ; to manually mange the array's capacity https://www.educative.io/answers/how-to-regrow-and-shrink-a-1d-array-in-cpp
    void reserve(size_t newCapacity) {
        if(newCapacity <= capacity){
            cout << "requested capacity is less than or equal to current capacity of " << array[capacity]<< endl;
            return; //if the requested capacity is less or equal to the current capacity of the array do nothing
        }
        Elem* newArray = new Elem[newCapacity]; //creating the new array
        for (size_t i=0; i<n; i++){ //insert elements from the old array to the new array
            newArray[i] = array[i];
        }
        delete[] array; //to delete the old array
        array = newArray;
        capacity = newCapacity;


    }

    //function to insert an element at the back of the array
    void push_back(const Elem& value) {
        if (n==capacity) { //checks if the vector is full https://cplusplus.com/doc/tutorial/operators/
            resize(capacity == 0 ? initial_capacity:capacity*2); //boolean  operator ? gives out conditions ; if capacity is 0, set it to the intial capacity value, if not, double the array's capacity
        }
        array[n++] = value; //increments n and places the new value at that index
    }
    //accessing elements by index
    Elem& at(size_t index) {
        if (index <= n) {
            return array[index];
        }else {
            throw std::out_of_range("Index out of range"); //error check if users ask to check beyond arrays index
        }
    }

    //function to insert an element at a specific postion in the array
    void insert(size_t index, const Elem& value ){
        //error checking
        if(index > n) {
            throw out_of_range("index out of range");
        }
        //resize the array if needed
        if (n == capacity) {
            resize(capacity==0 ? initial_capacity : capacity *2);
        }
        //https://www.geeksforgeeks.org/how-to-insert-an-element-at-a-specific-position-in-an-array-in-c/
        //shifting elements to the right
        for (size_t i = n; i >= index; i--) {
            array[i] = array[i-1];
        }

        array[index - 1] = value;

        n++;
    }

    //function to remove an element from a specific postion (index) in the array
    void erase(size_t index) {
        //error check
        if (index > n) {
            throw std::out_of_range("index out of range");
        }
        for (size_t i = index - 1; i < n-1; i++) {
            array[i] = array[i+1];
        }
        n--;

        cout << endl;

    }
    //checking if the array is empty
    bool ifEmpty() {
        return n==0;
    }
    [[nodiscard]] size_t size() const {
        return n;
    }



};

struct node_t {
    int id;
    float balance;

};
void print_vector(ArrayVector<node_t>& nodes) {
    // Access and print elements in ArrayVector
    cout << "Printing the elements of the vector:" << endl;
    for (int i = 0; i < nodes.size(); ++i) {
        cout << "[ " << to_string(i) << " ]. ID: " << nodes.at(i).id << ", Balance $" << nodes.at(i).balance << endl;
    }
    cout << endl;
}
#define num_records 5

int main() {
    try {
        // Initialize random seed
        srand(static_cast<unsigned int>(time(0)));

        ArrayVector<node_t> nodes(num_records);

        // Populate the ArrayVector with 2x more values to test correct resizing
        for (int i = 0; i < 2 * num_records; ++i) {
            node_t new_node;
            new_node.id = 10000 + rand() % 10001;
            new_node.balance = (static_cast<double>(rand()) / RAND_MAX) * 10000;
            nodes.push_back(new_node);
        }
        // Access and print elements in ArrayVector
        print_vector(nodes);
        std::cout << "Erasing nodes at index 5 and 3 and inserting new node at index 1." << std::endl;
        // Try your code with tests below!
        nodes.erase(5);
        nodes.erase(3);

        node_t new_node;
        new_node.id = 1;
        new_node.balance = 10;
        nodes.insert(1, new_node);

        // Access and print elements in ArrayVector
        print_vector(nodes);

        // Example of out_of_range access
        // std::cout << "Trying to access an out-of-range element:" << std::endl;
        // std::cout << nodes.at(100).balance << std::endl; // This must throw an exception

        // Example of out_of_range access
        // std::cout << "Trying to insert an out-of-range element:" << std::endl;
        // nodes.insert(100, new_node); // This must throw an exception
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Out of range error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        // Generic catch block for other exceptions
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }
    catch (...) {
        // Catch-all for non-standard exceptions
        std::cerr << "Unknown exception caught" << std::endl;
    }
        return 0;
}


