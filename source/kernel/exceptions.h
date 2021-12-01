//
// Created by omri on 01/12/2021.
//

#ifndef OSDEV_EXCEPTIONS_H
#define OSDEV_EXCEPTIONS_H

typedef int error_t;
enum error {
    SUCCESS = 0,
    ERROR_INVALID = 1,
    ERROR_NULL_DEREF = 2,
    ERROR_UNINITIALIZED =3
};



#define CHECK_AND_RETHROW_LABEL(error, label) do {if ((error) != SUCCESS) goto label;} while(0)
#define CHECK_AND_RETHROW(error) CHECK_AND_RETHROW_LABEL(error, cleanup)

#define CHECK_LABEL_CODE(expr, label, code)  do { if (!(expr)) { err = (code); goto label; } } while (0)
#define CHECK_LABEL(expr, label) CHECK_LABEL_CODE(expr, label, ERORR_INVALID)
#define CHECK_CODE(expr, code) CHECK_LABEL_CODE(expr, cleanup, code)

#define CHECK(expr) CHECK_CODE(expr, ERROR_INVALID)




#endif //OSDEV_EXCEPTIONS_H
