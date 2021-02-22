x = [0, 0, 0, 0, 1, 1, 0, 1]
y = [0, 0, 0, 0, 0, 0, 1, 1]

def add(a, b):

    total_sum = len(a) * [0]
    cout = 0
    for i in range(len(total_sum) - 1, -1, -1):
        total_sum[i] = a[i] + b[i] + cout
        if total_sum[i] == 2:
            cout = 1
            total_sum[i] = 0
        elif total_sum[i] == 3:
            cout = 1
            total_sum[i] = 1
        else:
            cout = 0

    return total_sum

def inv(i):

    return 0 if i else 1

def comp(a):

    ones_comp = len(a) * [0]
    for i in range(len(ones_comp)):
        ones_comp[i] = inv(a[i])

    return add(ones_comp, [0] * (len(a) - 1) + [1])

def rshift(a):

    return [0] + a[:-1]

def lshift(a):

    return a[1:] + [0]

def mult(a, b):

    product = (len(a) * 2) * [0]
    product[len(a):] = b
    print(product)
    for i in range(len(a)):
        if product[-1]:
            product[:len(a)] = add(product[:len(a)], a)
        product = rshift(product)
        print(i + 1, product)

def div(a, b):

    remainder = (len(a) * 2) * [0]
    remainder[len(a):] = a
    print(remainder)
    for i in range(len(a)):
        remainder = lshift(remainder)
        print(i + 1, "a", remainder)
        remainder[:len(a)] = add(remainder[:len(a)], comp(b))
        print(i + 1, "b", remainder)
        if remainder[0]:
            remainder[:len(a)] = add(remainder[:len(a)], b)
        else:
            remainder[-1] = inv(remainder[-1])
        print(i + 1, "c", remainder)


if __name__ == '__main__':
    print(x)
    print(y)
    print("multinh ")
    # print(comp(y))
    # print(add(x, comp(y)))

    print(div(x, y))
