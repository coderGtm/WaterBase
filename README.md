# WaterBase

WaterBase is a storage utility created for easy saving and access of persistent key-value data. Boolean, Numeric and String data types can easily be stored and retreived accross multiple app starts in a simple one-liner manner.

# Usage
WaterBase currently supports C++ and Python 3. Although work is underway for other languages. _(Feel free to contribute)_

## Python 3

Download the [waterbase.py](python/waterbase.py) file and place it in your project directory.
Import the module as follows:

`import waterbase as wb`

Then, create an object of WaterBase in the following manner:

`db = wb.WaterBase("db1")`

where "db1" is the database name.
If specified name does not exist, a new database will be created.

To Save values to WaterBase DB, use
```
db.SaveText ( "quote", "Talk is cheap. Show me the code." )
db.SaveBoolean ( "Python is awesome", True )
db.SaveNumber ( "num_var", 345 )
```
To get stored values, simply use
```
print(db.LoadBoolean ( "Python is awesome", False ))
print(db.LoadNumber ( "num_var", 9 ))
print(db.LoadText( "quote", "Quote not found!" ))
```
_As simple as that!_


Refer to [example.py](python/example.py) for the whole programme.


## C++
Download the [waterbase.h](cpp/waterbase.h) header file and include it in your main programme
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
db.SaveText ( "a quote", "Talk is cheap. Show me the code." );
db.SaveBoolean ( "cpp is awesome", true );
db.SaveNumber ( "num_var", 345 );
```
  
  
To load saved data, use **Load* (var_name, default value)** <-- _default value is used if variable not found in database_
```
cout << db.LoadBoolean ( "cpp is awesome", false ) << endl;
cout << db.LoadNumber ( "num_var 2", 9 ) << endl;
cout << db.LoadText( "a quote", "Quote not found" ) << endl;
```

Refer to [example.cpp](cpp/example.cpp) for the whole programme.
