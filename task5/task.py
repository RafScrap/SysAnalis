import numpy as np
import json

def makeMatrix(data: list) -> np.array:
    setVisited = set()
    M = list()
    number = makeArrSize(data)

    for item in data:
        if (type(item) != list):
            setVisited.add(int(item))
            row = makeRow(setVisited, number)
            M.append({'num': int(item), 'row': row})
        else:
            for subItem in item:
                setVisited.add(int(subItem))
            for subItem in item:
                row = makeRow(setVisited, number)
                M.append({'num': int(subItem), 'row': row})

    M.sort(key = (lambda x: x['num']))
    rowResult = [item['row'] for item in M]

    return np.array(rowResult)

def makeRow(setVisited: set, number : int) -> np.array:
    row = []
    for k in range(number):
        row.append(1 if k + 1 in setVisited else 0)
    return np.array(row)

def makeArrSize(data) -> int:
    number = 0
    for elem in data:
        if isinstance(elem, list):
            number += len(elem)
        else:
            number += 1
    return number 

def isStringType(string1, string2) -> bool:
    if (type(string1) == list) or (type(string2) == list):
        return True

    string1 = json.loads(string1)
    string2 = json.loads(string2)
    res = True
    for elem in string1:
        if (type(elem) != list):
            res = res and (type(elem) == str)
        else:
            for subelem in elem:
                res = res and (type(subelem) == str)
    for elem in string2:
        if (type(elem) != list):
            res = res and (type(elem) == str)
        else:
            for subelem in elem:
                res = res and (type(subelem) == str)
    return res

def makeArr(data) -> list:
    if (type(data) != list):
        data = json.loads(data)
    arr = []
    i = 1
    for item in data:
        if isinstance(item, list):
            for l2 in item:
                arr.append((l2, i, 1, item))
                i += 1
        else:
            arr.append((item, i, 0, []))
            i += 1
    return arr 

def S(strA, strB, isStr) -> list:
    strA = eval(strA)
    M_A = makeMatrix(strA)
    strB = eval(strB)    
    M_B = makeMatrix(strB)

    M_AB = M_A * M_B
    M_AB_T = M_A.T * M_B.T
    parameter = M_AB | M_AB_T 

    result = []
    temp = []
    for i in range(parameter.shape[0]):
        item = []
        for k in range(parameter.shape[0]): #range(i):
            if parameter[i][k] == 0:
                if isStr:
                    item.append(str(k + 1))
                else:
                    item.append(k + 1)

        if len(item) > 0:
            if isStr:
                item.append(str(i + 1))
            else:
                item.append(i + 1)
            temp.append([item, 0])

    for arr in temp:
        if arr[1] == 0:
            res = arr[0]
            arr[1] = 1
            for arr2 in temp:
                if arr2[1] == 0:
                    m = list(set(res) & set(arr2[0]))
                    if len(m) > 0:
                        arr2[1] = 1
                        res = list(set(res) | set(arr2[0]))
            result.append(res)
    return result



def makeArr2(data) -> list:
    if (type(data) != list):
        data = json.loads(data)
    res = []
    for item in data:
        if isinstance(item, list):
            for l2 in item:
                res.append(l2)
        else:
            res.append(item)
    return res 

def itIsUsed(items, arr) -> bool:
    for elem in items:
        if elem in arr:
            return True
    return False

def getSforItem(value, Sab) -> list:
    for item in Sab:
        if value in item:
            return item
    return []

def func(s1, s2, isStr) -> list:
    S_AB = S(s1, s2, isStr)
    AL = makeArr(s1)
    BL = makeArr(s2)
    SL2 = makeArr2(S_AB)

    usedArr = []
    n = len(AL)
    x = []
    for i in range(n):
        if (not (AL[i][0] in SL2)) and (not (AL[i][0] in x)) and (AL[i][2] == 0):
            x.append(AL[i][0])
        if (not (BL[i][0] in SL2)) and (not (BL[i][0] in x)) and (BL[i][2] == 0):
            x.append(BL[i][0])

    resL = []
    for i in range(n):
        isAddA = False
        if (AL[i][2] == 0) and (AL[i][0] in x) and (not itIsUsed([AL[i][0]], usedArr)):
            resL.append(AL[i][0])
            usedArr.append(AL[i][0])
            isAddA = True

        isAddB = False
        if (BL[i][2] == 0) and (BL[i][0] in x) and (not itIsUsed([BL[i][0]], usedArr)):
            resL.append(BL[i][0])
            usedArr.append(BL[i][0])
            isAddB = True

        if (not itIsUsed([AL[i][0]], usedArr)) and (not isAddA):
            S_item = getSforItem(AL[i][0], S_AB)
            if (len(S_item) > 0):
                    for item in S_item:
                        usedArr.append(item)
                    resL.append(S_item)

        if (not itIsUsed([BL[i][0]], usedArr)) and (not isAddB):
            S_item = getSforItem(BL[i][0], S_AB)
            if (len(S_item) > 0):
                    for item in S_item:
                        usedArr.append(item)
                    resL.append(S_item)

        if (not isAddA) and (not isAddB):
            L = list(set(AL[i][3]) & set(BL[i][3]))
            L2 = []
            for item in L:
                if (not (item in SL2)) and (not (item in x)) and (not itIsUsed([item], usedArr)):
                    L2.append(item)
            if len(L2) == 1:
                if not itIsUsed([L2[0]], usedArr):
                    resL.append(L2[0])
                    usedArr.append(L2[0])
            elif len(L2) > 1:
                resL.append(L2)
                for item in L2:
                    usedArr.append(item)
        elif (not isAddA):
            L = AL[i][3]
            L2 = []
            for item in L:
                if (not (item in SL2)) and (not (item in x)) and (not itIsUsed([item], usedArr)):
                    L2.append(item)
            if len(L2) == 1:
                if not itIsUsed([L2[0]], usedArr):
                    resL.append(L2[0])
                    usedArr.append(L2[0])
            elif len(L2) > 1:
                resL.append(L2)
                for item in L2:
                    usedArr.append(item)
        elif (not isAddB):
            L = BL[i][3]
            L2 = []
            for item in L:
                if (not (item in SL2)) and (not (item in x)) and (not itIsUsed([item], usedArr)):
                    L2.append(item)
            if len(L2) == 1:
                if not itIsUsed([L2[0]], usedArr):
                    resL.append(L2[0])
                    usedArr.append(L2[0])
            elif len(L2) > 1:
                resL.append(L2)
                for item in L2:
                    usedArr.append(item)
        
    return resL

def task(s1, s2) -> list:
    return func(s1, s2, isStringType(s1, s2))

def main():
    s1 = '[1,[2,3],4,[5,6,7],8,9,10]'
    s2 = '[[1,2],[3,4,5],6,7,9,[8,10]]'
    s3 = '[3,[1,4],2,6,[5,7,8],[9,10]]'

    print(task(s1, s2))
    #print(task(s2, s3))
    #print(task(s1, s3))


if __name__ == "__main__":
    main()