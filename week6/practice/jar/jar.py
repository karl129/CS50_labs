class Jar:
    def __init__(self, capacity=12):
        if capacity < 0 or not isinstance(capacity, int):
            raise ValueError("Capacity must be a non-negative integer.")
        self._capacity = capacity
        self._size = 0

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        if self._size + n > self._capacity:
            raise ValueError("No enough spaces.")
        else:
            self._size += n

    def withdraw(self, n):
        if self._size - n < 0:
            raise ValueError("No enough cookies.")
        else:
            self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


if __name__ == "__main__":
    jar = Jar()

    print(str(jar))
    jar.deposit(2)
    print(str(jar))
    jar.deposit(3)
    print(str(jar))

    jar.withdraw(3)
    print(str(jar))
    jar.withdraw(3)
    print(str(jar))
