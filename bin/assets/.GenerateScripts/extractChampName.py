import json

champ = open("../championIcon.json")
champJSON = json.load(champ)
champ.close()

champName = open("../championName.json","w")
champName.write(json.dumps(sorted(champJSON),indent=4))
champName.close()

