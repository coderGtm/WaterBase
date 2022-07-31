# WaterBase

WaterBase is a storage utility created for easy saving and access of persistent key-value data. Boolean, Numeric and String data types can easily be stored and retreived accross multiple app starts in a simple one-liner manner.

# Usage
WaterBase currently supports C++ language only. Although work is underway for other languages. _(Feel free to contribute)_
## C++
Download the `WaterBase.h` header file and include it in your main programme
```
#ifndef WATERBASE
    #define WATERBASE
    #include "WaterBase.h"
#endif
```
or simply
```
#include WaterBase.h
```

Then create an object of `WaterBase` class.
```
WaterBase db;
```

You can then easily use WaterBase `db` object to save and load your persistent data.

For saving data, use **Save* (var_name, value);**
```
db.SaveText ( "pushpa dialogue", "jhukega nai sala" );
db.SaveBoolean ( "cpp is awesome", true );
db.SaveNumber ( "num_var", 345 );
```
  
  
To load saved data, use **Load* (var_name, default value)** <-- _default value is used if variable not found in database_
```
cout << db.LoadBoolean ( "cpp is awesome", false ) << endl;
cout << db.LoadNumber ( "num_var 2", 9 ) << endl;
cout << db.LoadText( "pushpa dialogue", "hi" ) << endl;
```

Refer to [driver.cpp](driver.cpp) for the whole programme.
