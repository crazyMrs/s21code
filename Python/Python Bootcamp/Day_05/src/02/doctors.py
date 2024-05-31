import threading
import time
import random

class Doctors(threading.Thread):
    def __init__(self, id, left_screwdriver, right_screwdriver):
        super().__init__()
        self.id = id
        self.left_screwdriver = left_screwdriver
        self.right_screwdriver = right_screwdriver

    def run(self):
        while True:
            time.sleep(random.uniform(0.1, 0.5))

            self.left_screwdriver.lock.acquire()
            acquired = self.right_screwdriver.lock.acquire(False)

            if acquired:
                try:
                    print(f"Doctor {self.id}: BLAST!")
                    time.sleep(1)
                finally:
                    self.right_screwdriver.lock.release()
                    self.left_screwdriver.lock.release()
                break
            else:
                self.left_screwdriver.lock.release()
                time.sleep(random.uniform(0.1, 0.5))


class Screwdriver():
    def __init__(self):
        self.lock = threading.Lock()


def main():
    doctors = []
    screwdrivers = [Screwdriver() for _ in range(5)]

    for i in range(5):
        doctors.append(Doctors(i+9, screwdrivers[i], screwdrivers[(i+1)%5]))
    
    for doctor in doctors:
        doctor.start()

    for doctor in doctors:
        doctor.join()


if __name__ == '__main__':
    main()
