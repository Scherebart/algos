def cons(a, b):

  def pair(f):
    return f(a, b)

  return pair


res = cons(3, 6)(lambda a, b: a * b + 5)
print(res)

def car(pair):
  return pair(lambda a, b: a)

def cdr(pair):
  return pair(lambda a, b: b)

pair1 = cons(12, 'domek')
print('first part of the pair', car(pair1))
print('second part of the pair', cdr(pair1))
