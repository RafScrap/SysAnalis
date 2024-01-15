import json
import numpy as np

def list_of_reviews_from_json(str, template):
  reviews = json.loads(str)
  reviews_list = [0 for _ in range(len(template))]

  for i in range(len(reviews)):
    if type(reviews[i]) is list:
      for el in reviews[i]:
        reviews_list[template[el]] = i + 1
    else:
      reviews_list[template[reviews[i]]] = i + 1
  
  return reviews_list

def task(*args):
  experts_count = len(args)
  template = dict()
  reviews_count = 0

  for el in json.loads(args[0]):
    if type(el) is list:
      for elem in el:
        template[elem] = reviews_count
        reviews_count += 1
    else:
      template[el] = reviews_count
      reviews_count += 1
      
  matrix = []
  for reviews_str in args:
    matrix.append(list_of_reviews_from_json(reviews_str, template))

  x = matrix
  matrix = []
  for i in range(reviews_count):
    sum = 0
    for j in range(experts_count):
      sum += x[j][i]
    matrix.append(sum)
  matrix = np.matrix(matrix)

  # дисперсия
  D = np.var(matrix) * reviews_count / (reviews_count - 1)
  D_max = experts_count ** 2 * (reviews_count ** 3 - reviews_count) / 12 / (reviews_count - 1)

  return format(D / D_max, ".2f")

A = '["1", ["2", "3"], "4", ["5", "6", "7"], "8", "9", "10"]'
B = '[["1", "2"], ["3", "4", "5"], "6", "7", "9", ["8", "10"]]'
C = '["3", ["1", "4"], "2", "6", ["5", "7", "8"], ["9", "10"]]'

print(task(A, B, C))