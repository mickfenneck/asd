from os import system

system('cp a.out /tmp/a.out')
for i in range(20):
    filein = 'input%d.txt' % i
    
    print 'test', i
    system('cp Dataset/input/%s /tmp/input.txt' % filein)
    system('cd /tmp && /tmp/a.out')
    system('cat Dataset/output/output%d.txt' % i)
    print '---'

