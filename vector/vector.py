class Vector:
    def __init__(self, x=0.0, y=0.0, z=0.0):
        self.x = x
        self.y = y
        self.z = z

    def __str__(self):
        return f"{self.x},{self.y},{self.z}"

    @staticmethod
    def run_tests():
        v = Vector(x=2, y=3, z=4)
        print(f"v is {v}")


def main():
    Vector.run_tests()


if __name__ == "__main__":
    main()
