import os
import json

curFold = os.getcwd()

f = []
for (dirpath, dirnames, filenames) in os.walk(curFold+"/../champion/"):
	f.extend(filenames)
	break

champions = {}

for c in f:
	name = ""
	for l in c:
		if l == "_":
			break
		else:
			name+=l
	champions[name]=c

jChamps = json.dumps(champions,sort_keys=True,indent=4)

fl = open("../championIcon.json","w")
fl.write(jChamps)
fl.close()

print("Finished generating championIcon.json")
