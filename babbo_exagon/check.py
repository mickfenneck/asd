for i in range(20):
    with open('Dataset/input/input%d.txt' % i) as fin:
        tria = fin.read().split('\n')[1]
        data = [1 if t == 's' else -1 for t in tria]
    
    with open('Dataset/output/output%d.txt' % i) as fout:
        sol = fout.read().split('\n')[1].split(' ')
        solution = [int(x) for x in sol if x]

    sum_b_e, acc = list(), 0
    for t in data:
        acc += t
        sum_b_e.append(acc)

    sum_e_b, acc = list(), 0
    for t in reversed(data):
        acc += t
        sum_e_b.append(acc)

    ind = ['   ^' if i in solution else ' ' for i in range(len(data))]

    fmt = ''.join('{%d:4}' % i for i in range(len(data)))
    print fmt.format(*sum_b_e)
    print fmt.format(*data)
    print fmt.format(*sum_e_b)
    print fmt.format(*ind)
    print
    raw_input()
