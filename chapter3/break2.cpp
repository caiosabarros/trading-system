#include <cstdio>
#include <cstdint>

// This attribute forces GCC to treat this function as a separate black box
__attribute__((noinline))
void flip_sign_bit(uint64_t* ui_ptr) {
    // the pointer received is assigned a value that is now negative
    *ui_ptr |= 0x8000000000000000;
}

int main() {
    // double is created and saved as a var in the CPU register.
    double x = 102398213810;
    // another var is created in the CPU register
    const auto origin_x = x;

    // since a pointer to x is created, x also goes to RAM.
    // the below C-type casting is an unsafe, compiler-trusted line
    // C-type casting of the pointer, not the variable.
    auto x_as_ui = (uint64_t *)&x;
    // x_as_ui does not go to RAM, but it goes to a fn
    flip_sign_bit(x_as_ui);

    // when x is read, it grabs the value from register
    printf("origin_x:%0.2f x:%0.2f\n", origin_x, x);
}
