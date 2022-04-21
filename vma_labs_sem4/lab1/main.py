from pylab import *

def f(x):
    return x * x * cos(x) - x * sin(x)

def df(x):
    return x * cos(x) - sin(x) * (x * x + 1)

x1 = 0.5
x2 = 2
step = 0.01

f2 = (f(x2) - f(x1)) / (x2 - x1)
f3 = (f2 - df(x1)) / (x2 - x1)
f4 = (df(x2) - f2) / (x2 - x1)
f5 = (f4 - f3) / (x2 - x1)

def p(x):
    return f(x1) + df(x1) * (x - x1) + f3 * (x - x1) ** 2 + f5 * (x - x1) ** 2 * (x - x2)

fx = arange(x1, x2 + step, step)
fy = f(fx)
py = p(fx)

plot(fx, fy, label='exact')
plot(fx, py, label='approximation', ls='--')
legend()
show()

print("f(0.75) =", f(0.75))
print("p(0.75) =", p(0.75))
print("remainder =", abs(f(0.75) - p(0.75)))
