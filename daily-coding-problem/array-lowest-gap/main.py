def lowestGap(low):

  def solve(array):
    for i in range(0, len(array)):
      value = array[i]
      array[i] = None
      while value != None and value - low < len(array) and value >= low:
        nextValue = array[value - low]
        array[value - low] = value
        value = nextValue

    for i in range(0, len(array)):
      if (array[i] == None):
        return i + low

  return solve


solution = lowestGap(4)
array = [2, 7, 3, 9, 5]
res = solution(array)
print(array)
print(res)