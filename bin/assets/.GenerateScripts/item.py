import os
import json

curFold = os.getcwd()

f = []
for (dirpath, dirnames, filenames) in os.walk(curFold+"/../item/"):
	f.extend(filenames)
	break
	
b = []
for (dirpath, dirnames, filenames) in os.walk(curFold+"/../item/Boots"):
	b.extend(filenames)
	break
	
e = []
for (dirpath, dirnames, filenames) in os.walk(curFold+"/../item/Elixir"):
	e.extend(filenames)
	break
	
items = {}
items["core"] = f
items["boots"] = b
items["elixir"] = e

jItems = json.dumps(items,sort_keys=True,indent=4)

fl = open("../item.json","w")
fl.write(jItems)
fl.close()

print("Finished generating : item.py")


