from threading import Thread, Semaphore, current_thread
import time
import random

queue = []
MAX_NUM = 20  # max limit of the queue

sem = Semaphore()  # intitializing semaphore


class ProducerThread(Thread):
    def run(self):
        nums = range(5)  # [0 1 2 3 4]
        global queue

        while True:
            sem.acquire()  # wait operation to stop consuming
            if len(queue) == MAX_NUM:

                print("List is full, producer will wait")
                sem.release()
                print("Space in queue, Consumer notified the producer")

            else:
                num = random.choice(nums)
                queue.append(num)  # added any random number from 0 to 4 to the list
                print(current_thread().name, "Produced", num)
                sem.release()  # signal operation to allow consumer to consume data

            time.sleep(random.random())  # to allow program to run a bit slower


class ConsumerThread(Thread):
    def run(self):
        global queue

        while True:
            sem.acquire()  # wait operation to stop producing
            if not queue:
                print("List is empty, consumer waiting")
                sem.release()
                print("Producer added something to queue and notified the consumer")

            else:
                num = queue.pop(0)

                print(current_thread().name, "Consumed", num)
                sem.release()  # signal operation to allow producer to produce

            time.sleep(random.random())


def main():
    ProducerThread().start()  # start producer thread
    ConsumerThread().start()  # start consumer thread
    ProducerThread().start()  # start producer thread
    ConsumerThread().start()  # start consumer thread
    ProducerThread().start()  # start producer thread
    ConsumerThread().start()  # start consumer thread
    ProducerThread().start()  # start producer thread
    ConsumerThread().start()  # start consumer thread
    ProducerThread().start()  # start producer thread
    ConsumerThread().start()  # start consumer thread
    ProducerThread().start()  # start producer thread
    ConsumerThread().start()  # start consumer thread
    ProducerThread().start()  # start producer thread
    ConsumerThread().start()  # start consumer thread


if __name__ == "__main__":
    main()
