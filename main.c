int add(int a, int b) {
    int result = a + b;
    return result;
}

int multiply_by_two(int a) {
    int multiplied = add(a,a);
    return multiplied;
}

int main() {
    int five = 5;
    int five_times_two = /* HANDOFF */ multiply_by_two(five);
    int sum = add(five, five_times_two);
    return 0;
}
