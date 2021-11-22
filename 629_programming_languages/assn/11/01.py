from threading import Thread, Lock, current_thread
from time import sleep

status, count, lock = 1, 1, Lock()


def fun1():
    global count, status
    while 1:
        with lock:
            print(current_thread().name, "lock acquired")  # line 10
            count += 1
            status = count
            print(current_thread().name, "updated status= %d" % (status))
            sleep(0.5)


def fun2():
    global count, status
    while 1:
        with lock:
            print(current_thread().name, "lock acquired")  # line 22
            count += 1
            status = count
            print(current_thread().name, "updated status= %d" % (status))
            sleep(0.5)


if __name__ == "__main__":
    f1 = Thread(target=fun1)
    f2 = Thread(target=fun2)
    f1.start()
    f2.start()
