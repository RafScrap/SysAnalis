import json
import numpy as np

def arrFromJson(string, t):
  revs = json.loads(string)
  arrRevs = [0 for _ in range(len(t))]

  for k in range(len(revs)):
    if type(revs[k]) is list:
      for item in revs[k]:
        arrRevs[t[item]] = k + 1
    else:
      arrRevs[t[revs[k]]] = k + 1
  
  return arrRevs

def task(*args):
  exps_number = len(args)
  dictTemp = dict()
  revs_number = 0

  for item in json.loads(args[0]):
    if type(item) is list:
      for k in item:
        dictTemp[k] = revs_number
        revs_number += 1
    else:
      dictTemp[item] = revs_number
      revs_number += 1
      
  M = []
  for revs_string in args:
    M.append(arrFromJson(revs_string, dictTemp))

  x = M
  M = []
  for k in range(revs_number):
    amount = 0
    for h in range(exps_number):
      amount += x[h][k]
    M.append(amount)
  M = np.matrix(M)

  twelve = 12
  revs_number_1 = revs_number - 1
  Disp = np.var(M) * revs_number / revs_number_1
  Disp_MAX = exps_number ** 2 * (revs_number ** 3 - revs_number) / twelve / revs_number_1

  return format(Disp / Disp_MAX, ".2f")

M1 = '["1", ["2", "3"], "4", ["5", "6", "7"], "8", "9", "10"]'
M2 = '[["1", "2"], ["3", "4", "5"], "6", "7", "9", ["8", "10"]]'
M3 = '["3", ["1", "4"], "2", "6", ["5", "7", "8"], ["9", "10"]]'

print(task(M1, M2, M3))