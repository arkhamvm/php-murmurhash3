# PHP7 MurmurHash3

*MurmurHash* is an algorithm desiged by Austin Appleby.

## Changes
1. Add PHP 7 support.
2. Seed parameter can be omitted.

## Install

```bash
phpize
./configure --enable-murmurhash3
make
sudo make install
```


Create `murmurhash3.ini` in lib dir (for php 7.1: `/etc/php/7.1/mods-available/`):
```
extension=murmurhash3.so
```

Finally enable it in PHP:
```bash
sudo phpenmod murmurhash3
```

## Usage

```php
// Example
echo murmurhash3('anystring');      // default seed usage
echo murmurhash3('anystring', 123); // specific seed usage

// Some locale strings
echo murmurhash3('№АаЯя');

// Example from @maksimf
echo murmurhash3('豥붢㦖徱阵儹㜀耄巅簏罚撦');
echo murmurhash3('豥붢㦖徱阵儹㜀耄巅簏罚撦', 1096928849);
``` 
