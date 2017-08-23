#ifndef PHP_MURMURHASH3_H
    #define PHP_MURMURHASH3_H

    extern zend_module_entry murmurhash3_module_entry;
    #define phpext_murmurhash3_ptr &murmurhash3_module_entry

    #define PHP_MURMURHASH3_VERSION "0.2"
    #define PHP_MURMURHASH3_EXTNAME "murmurhash3"

    #ifdef PHP_WIN32
        #   define PHP_MURMURHASH3_API __declspec(dllexport)
    #elif defined(__GNUC__) && __GNUC__ >= 4
        #   define PHP_MURMURHASH3_API __attribute__ ((visibility("default")))
    #else
        #   define PHP_MURMURHASH3_API
    #endif

    #ifdef ZTS
        #include "TSRM.h"
    #endif


    #ifdef ZTS
        #define MURMURHASH3_G(v) ZEND_TSRMG(murmurhash3_globals_id, zend_murmurhash3_globals *, v)
        #ifdef COMPILE_DL_MURMURHASH3
            ZEND_TSRMLS_CACHE_EXTERN();
        #endif
    #else
        #define MURMURHASH3_G(v) (murmurhash3_globals.v)
    #endif
#endif  /* PHP_MURMURHASH3_H */
