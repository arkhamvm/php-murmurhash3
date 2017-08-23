#ifdef HAVE_CONFIG_H
    #include "config.h"
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1600)

    typedef unsigned char uint8_t;
    typedef unsigned int uint32_t;
    typedef unsigned __int64 uint64_t;

    // Other compilers

#else	// defined(_MSC_VER)
    #include <inttypes.h>
    #include <stdint.h>
#endif // !defined(_MSC_VER)


#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_murmurhash3.h"

#include "MurmurHash3.h"

#define MURMURHASH3_OUTPUT_LENGTH	16

#ifdef COMPILE_DL_MURMURHASH3
    ZEND_GET_MODULE(murmurhash3)
    #ifdef ZTS
        ZEND_TSRMLS_CACHE_DEFINE();
    #endif    
#endif

// Convert uint8 to hex representation (2 characters)
void c2h(uint8_t c, char *r)
{
  const char *hex = "0123456789abcdef";
  r[0] = hex[c / 16];
  r[1] = hex[c % 16];
}

PHP_MINFO_FUNCTION(murmurhash3)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "murmurhash3 support", "enabled");
	php_info_print_table_row(2, "extension version", PHP_MURMURHASH3_VERSION);
	php_info_print_table_end();
}

PHP_FUNCTION(murmurhash3)
{
    char *key = NULL;
    size_t key_len;
    unsigned long long seed = 0;
    char output[MURMURHASH3_OUTPUT_LENGTH + 1];
    char result[MURMURHASH3_OUTPUT_LENGTH * 2 + 1];

    // Parse the input parameters
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|l", &key, &key_len, &seed) == FAILURE || key_len < 1) {
        return;
    }
    
    if (!seed) {
        seed = 0;
    }

    // Calculate the hash
    MurmurHash3_x64_128 ( key, key_len, (uint32_t)seed, output );
    output[MURMURHASH3_OUTPUT_LENGTH] = 0;

    // Convert to HEX
    for (int i=0; i<MURMURHASH3_OUTPUT_LENGTH; i++) {
      c2h(output[i], &result[i*2]);
    }
    result[MURMURHASH3_OUTPUT_LENGTH * 2] = 0;

    // Return the result
    RETURN_STRING(result);
}


const zend_function_entry murmurhash3_functions[] = {
	PHP_FE(murmurhash3, NULL)
	PHP_FE_END
};

zend_module_entry murmurhash3_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_MURMURHASH3_EXTNAME,
	murmurhash3_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	PHP_MINFO(murmurhash3),
	PHP_MURMURHASH3_VERSION,
	STANDARD_MODULE_PROPERTIES
};
