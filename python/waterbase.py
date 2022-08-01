class WaterBase:
    def __init__(self,dbName):
        self.seperator = ":"
        self.fname = dbName+".wb"
        f = open(self.fname,"a+")
        f.close()

    def write(self,valType,name,val):
        lines = []
        wrote = False
        with open(self.fname,"r") as file:
            for line in file:
                lines.append(line)
                tokens = line.split(":")
                if (tokens.pop(0) == valType):
                    keyLen = int(tokens.pop(0))
                    valLen = int(tokens.pop(0))
                    dataString = self.seperator.join(tokens)
                    key = dataString[:keyLen]
                    if name == key:
                        lines[-1] = valType + self.seperator + str(keyLen) + self.seperator + str(valLen) + self.seperator + name + self.seperator + val
                        wrote = True
        if wrote == False:
            lines.append(valType + self.seperator + str(len(name)) + self.seperator + str(len(val)) + self.seperator + name + self.seperator + val)

        with open(self.fname,"w") as newFile:
            newFile.writelines(s+"\n" for s in lines)

    def read(self,valType,name,defaultVal):
        val = defaultVal
        with open(self.fname,"r") as file:
            for line in file:
                tokens = line.split(":")
                if (tokens.pop(0) == valType):
                    keyLen = int(tokens.pop(0))
                    valLen = int(tokens.pop(0))
                    dataString = self.seperator.join(tokens)
                    key = dataString[:keyLen]
                    if name == key:
                        val = dataString[keyLen+1:]
        return val

    def SaveBoolean(self,name,val):
        self.write("B",name,str(int(val)))
    def SaveNumber(self,name,val):
        self.write("N",name,str(int(val)))
    def SaveText(self,name,val):
        self.write("S",name,str(val))

    def LoadBoolean(self,name,defaultVal):
        entry = self.read("B",name,str(defaultVal))
        return entry != "0"
    def LoadNumber(self,name,defaultVal):
        entry = self.read("N",name,str(defaultVal))
        return int(entry)
    def LoadText(self,name,defaultVal):
        entry = self.read("S",name,str(defaultVal))
        return entry


db = WaterBase("db1")

db.SaveText ( "pushpa dialogue", "jhukega nai sala" )
db.SaveBoolean ( "cpp is awesome", True )
db.SaveNumber ( "num_var", 345 )

print(db.LoadBoolean ( "cpp is awesome", False ))
print(db.LoadNumber ( "num_var", 9 ))
print(db.LoadText( "pushpa dialogue", "hi" ))