//      Leaky Memory
//
//    When allocating memory it is important to clean up after yourself. C and C++ do not
//    have any kind of garbage collection. What this means is that allocated memory that is
//    never used again will not be available. It will also not be de-allocated by your program
//    automatically.
//
//    This does not cause a problem if you allocate memory in the main life span of the
//    program. It does cause a problem if allocating memory in function and classes.
//
//    Below is example that shows the order with which memory is allocated. It also demonstrates
//    the care that needs to be taken when de-allocating memory.
//
//

#include <iostream>
#include <string>

//==============================================================================
/** A Class that does not deals with memory correctly*/
class LeakyString
{
public:
    //==========================================================================
    /** Constructor*/
    LeakyString(const char *charPtr)
    {
        const size_t sizeOfText = strlen (charPtr);
        text = new char[sizeOfText]; // Dynamically allocate the correct amount of memory.
        
        if(text) // If the allocation succeeds, copy the initialization string.
            strcpy (text, charPtr);
    };
    /** Destructor*/
    ~LeakyString() // destructor does nothing
    {
        std::cout << "I am the LeakyString destructor" << '\n' << '\n';
        //  delete[] text; // when commented out, this class will leak memory
    };
    //==========================================================================
    char    *text;
    //==========================================================================
};

//==============================================================================

class String : public LeakyString
{
public:
    String(const char *charPtr) : LeakyString(charPtr){};
    ~String()
    {
        std::cout << "I am the String destructor\n";
        delete[] text; // deletes the allocated memory
    };
};

//==============================================================================

void memoryLeak()
{
    LeakyString str("I am Leaking Memory!!!");
    std::cout << str.text << '\n'; // print str text
}

void possibleMemoryFailure()
{
    String str("Uncomment Line 38 and this line causes an error");
    std::cout << str.text << '\n'; // print str text
}

//==============================================================================

int main()
{
    memoryLeak();
    possibleMemoryFailure();
    
    String str("I am dealing with memory correctly");
    std::cout << str.text << '\n'; // print str text
    
    return EXIT_SUCCESS;
}
