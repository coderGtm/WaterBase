import waterbase as wb

db = wb.WaterBase("db1")

db.SaveText ( "quote", "Talk is cheap. Show me the code." )
db.SaveBoolean ( "Python is awesome", True )
db.SaveNumber ( "num_var", 345 )

print(db.LoadBoolean ( "Python is awesome", False ))
print(db.LoadNumber ( "num_var", 9 ))
print(db.LoadText( "quote", "Quote not found!" ))