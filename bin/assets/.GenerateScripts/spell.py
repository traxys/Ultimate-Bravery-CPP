import os
import json

curFold = os.getcwd()

f = []
for (dirpath, dirnames, filenames) in os.walk(curFold+"/../spell"):
	f.extend(dirnames)
	break

spells = {}

for c in f:
	cF = []
	for (dirpath, dirnames, filenames) in os.walk(curFold+"/../spell/"+c):
		cF.extend(filenames)
		break
	spells[c]=cF
	
jSpells = json.dumps(spells,sort_keys=True,indent=4)

fl = open("../spell.json","w")
fl.write(jSpells)
fl.close()

print("Finished generating : spell.py")
