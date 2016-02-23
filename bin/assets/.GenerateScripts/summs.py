import os
import json

curFold = os.getcwd()

f = []
for (dirpath, dirnames, filenames) in os.walk(curFold+"../summs/"):
	f.extend(filenames)
	break

jSumms = json.dumps(f,sort_keys=True,indent=4)

fl = open("../summs.json","w")
fl.write(jSumms)
fl.close()

print(jSumms)
