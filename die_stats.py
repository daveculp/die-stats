import random
from datetime import datetime
import pygame

#function to return "old school" D&D stats for 6 ability scores
#die_type = number of sides
#num_rolls = number of times to roll dice
#drop_lowest = if True will drop the lowest dice roll
#returns the six numbers generated as a list ordered from lowest to highest
def get_stats(die_type,num_rolls, drop_lowest = True):
    stats = []
    for i in range(6):
        dice = [ random.randint(1,die_type) for x in range(num_rolls)] 
        dice.sort()
        if drop_lowest:
            dice.pop(0)
        stats.append(sum(dice))
    return stats

random.seed(datetime.now().timestamp())

count = 0
total = 0
running = True
totals = [0,0,0,0,0,0,0] # Keeps track of the total number charaters with this number of 18s (0-6)
while (count < 20_000_000_000):
    
    stats = get_stats(6,4, True)
    #print(stats)
    #print (stats.count(18))
    totals [stats.count(18)]+=1
    count+=1
    if count%100_000 == 0:
        print(f"{count:,}")

print (f"\nTotal number of characters generated {count:,}")
for i in range(7):
    print (f"Total number of characters with {i} 18's: {totals[i]:,}. ",end="" )
    if totals[i] > 0:
        print(f"Ratio is 1 in {count/totals[i]:,} or { (totals[i]/count)*100}%")
    else:
        print("")
          
print (totals) 


