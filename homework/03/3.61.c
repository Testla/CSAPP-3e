long cread_alt(long *xp) {
    long default_value = 0;
    return *(xp ? xp : &default_value);
    // long *p = xp ? xp : &default_value;
    // return *p;

    // Tried both version, only -O1 generated code using conditional move.
    // -Og, -O2 and -O3 all used conditional jump.
}
