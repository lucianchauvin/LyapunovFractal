from PIL import Image
import math

rez = 2000

im = Image.new(mode="RGB", size=(88, rez))

maxIter = 10**2

aRange = [2,4]
bRange = [2,4]

def lyExp(a,b):
    global maxIter

    r = a
    total = 0
    xn = .5
    for x in range(1, maxIter):
        if xn != .5:
            total += math.log(abs(r*(1-(2*xn))))
        xn = r*xn*(1-xn)
        if r == a:
            r = b
        else:
            r = a

    return (1/maxIter)*total

def getColor(n):
    if n == 0:
        return (0,0,0)
    if n < 0:
        return (int((n*150+255)), int((n*150+255)), 0)
    elif n > 0:
        return (0, 0, int((n*150+255)))

pixles = im.load()  

count = 1
for i in range(1,im.size[1]+1):
    for j in range(1,im.size[0]+1):
        a = (i/im.size[0])*(aRange[1]-aRange[0])+aRange[0]
        b = (j/im.size[1])*(bRange[1]-bRange[0])+bRange[0]
        xp = lyExp(a,b)
        print((count/(im.size[0]*im.size[1]))*100)
        pixles[i-1, im.size[0]+1 - j-1] = getColor(xp)
        count += 1

        
im.save("lyapunov[" + str(aRange[0]) + "," + str(aRange[1]) + "]x[" + str(bRange[0]) + "," + str(bRange[1]) + "]_resolution" + str(rez) + ".png")
im.show()