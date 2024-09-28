#include <iostream>

int main(void) {
    char str[] = "hello world\n";
    std::cout<<str;
    void* X;
    X=(void*)0;
    int* y = (int*)X;
    std::cout << &y<<"\n";
    return 0;
}