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
    ERROR_UNINITIALIZED = 3,
    ERROR_NOT_IMPLEMENTED = 4,
};



#define CHECK_LABEL_CODE(expr, label, code)  do { if (!(expr)) { err = (code); goto label; } } while (0)
#define CHECK_LABEL(expr, label) CHECK_LABEL_CODE(expr, label, ERORR_INVALID)
#define CHECK_CODE(expr, code) CHECK_LABEL_CODE(expr, cleanup, code)

#define CHECK(expr) CHECK_CODE(expr, ERROR_INVALID)

#define IS_SUCCESS(expr) ((expr) == SUCCESS)
#define IS_FAILED(expr) (!IS_SUCCESS(expr))


#define CHECK_AND_RETHROW_LABEL(error, label) do {err = error; CHECK_LABEL_CODE(IS_SUCCESS(err), label, err);} while(0)
#define CHECK_AND_RETHROW(error) CHECK_AND_RETHROW_LABEL(error, cleanup)



#define CHECK_FAILED_LABEL_CODE(label, code) CHECK_LABEL_CODE(0, label, code)
#define CHECK_FAILED_LABEL(label) CHECK_LABEL(0, label)
#define CHECK_FAILED_CODE(code) CHECK_CODE(0, code)
#define CHECK_FAILED() CHECK(0)







#endif //OSDEV_EXCEPTIONS_H
