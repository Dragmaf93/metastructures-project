#ifndef EXCEPTION_H
#define EXCEPTION_H

#include<QException>
class Exception: public QException{
public:
    void raise()const{throw *this;}
    Exception* clone() {return new Exception(*this);}
};

#endif // EXCEPTION_H
