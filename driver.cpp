#ifndef IOSTREAM
    #define IOSTREAM
    #include <iostream>
#endif
#ifndef WATERBASE
    #define WATERBASE
    #include "waterBase.h"
#endif


using namespace std;

int main() {
    WaterBase db;
    
    //Save* (var_name, value);
    db.SaveText ( "pushpa dialogue", "jhukega nai sala" );
    db.SaveBoolean ( "cpp is awesome", true );
    db.SaveNumber ( "num_var", 345 );
  
  
    //Load* (var_name, default value) <-- default value is used if variable not found in database
    cout << db.LoadBoolean ( "cpp is awesome", false ) << endl;
    cout << db.LoadNumber ( "num_var 2", 9 ) << endl;
    cout << db.LoadText( "pushpa dialogue", "hi" ) << endl;
}
