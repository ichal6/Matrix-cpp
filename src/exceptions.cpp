#include <iostream>

class IncorrectSizeException: public exception 
{
    public:
        virtual const char* what() const throw(){
            return "Incorrect size";
        }
};

class FailureOpenFileException: public exception
{
    public:
        virtual const char* what() const throw(){
            return "Cannot open a file";
        }
};

class IndexOutOfBoundsException: public exception
{
    public:
        virtual const char* what() const throw(){
            return "Index is not contain to matrix";
        }    
};

class FailureStreamException: public exception
{
    public:
        virtual const char* what() const throw(){
            return "Stream is  damaged";
        }    
};
