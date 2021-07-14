# bomblab

    gdb bomb
    (gdb) b main
    ...
    (gdb) layout asm
    (gdb) layout regs

We quickly encounter the first unknown function `initialize_bomb`.

## initialize_bomb

    (gdb) layout asm
    (gdb) layout regs

By reading the assembly, we know it's like:

    0x4013a2 initialize_bomb
        signal(2(SIGINT), 0x4012a0(signal_handler))

    0x4012a0 signal_handler
        puts(0x4024c0)  // So you think you can stop the bomb with ctrl-c, do you?
        sleep(3)
        printf(0x402582, 1)  // Well...
        fflush(stdout)
        sleep(1)
        puts(0x40258a)  // OK. :-)
        exit(0x10)

`man signal` and `man 7 signal` says the call of `signal` sets `signal_handler` as the handler of `SIGINT`.

What is at `0x4024c0`? It's not shown in gdb.

    objdump -t bomb

The only symbol that is close is

    00000000004024b0 l     O .rodata        0000000000000010              array.3449

According to `man objdump`, the first column is the symbol's address, `l` means local, `O` means object, the symbol is in setion `.rodata`, `0000000000000010` is alignment or size (I can't tell), `array.3449` is symbol name.

    objdump -j .rodata -d ./bomb

The string is quite long. Starting from `0x4024c0` and up to the first null ('\0') is

    So you think you can stop the bomb with ctrl-c, do you?

And several strings follows

    Curses, you've found the secret phase!
    But finding it and solving it are quite different...
    Congratulations! You've defused the bomb!
    Well...
    OK. :-)
    Invalid phase%s.
    BOOM!!!
    The bomb has blown up.
    %d %d %d %d %d %d
    Error: Premature EOF on stdin
    GRADE_BOMB
    Error: Input line too long
    %d %d %s
    DrEvil
    greatwhite.ics.cs.cmu.edu
    angelshark.ics.cs.cmu.edu
    makoshark.ics.cs.cmu.edu
    (Some error messages)

It says I've found the secret phase, but I have no idea how to even enter the phase...

I guess I should not trust the function names and go through the whole program.

The three domains resolve to 128.2.220.{10,11,18}, but TCP port 80 seems not open. Visiting 128.2.220.9 302 redirects to <https://aladdin1.inf.cs.cmu.edu/>.

The other symbol in .rodata is `_IO_stdin_used`, some strings that may be useful are:

    Border relations with Canada have never been better.
    Wow! You've defused the secret stage!
    flyers

## read_line

    0x40149e read_line
        // The condition and handling of input too long is weird.
        // It will include cases that length is 0x4f.
        // And though it writes mysterious constant, the branch will exit.
        result = skip();
        if (result) {
            if (infile == stdin) {
                puts(0x4025d5);  // Error: Premature EOF on stdin
                exit(0x8);
            } else { // 0x4014d5
                if (!getenv($0x4025f3)) {  // GRADE_BOMB
                    exit(0);
                } else { // 0x4014ee
                    infile = stdin;
                    if (!skip()) {
                        puts($0x4025d5);  // Error: Premature EOF on stdin
                        exit(0);
                    }
                }
            }
        }
        // 0x40151f
        // https://stackoverflow.com/a/26818873
        char input_strings(0x603780)[][80];
        if (strlen(input_strings[num_input_strings]) > 0x4e) {
            puts(0x4025fe);  // Error: Input line too long
            num_input_strings += 1;
            input_strings[num_input_strings] = 0x636e7572742a2a2a;
            input_strings[num_input_strings] + 8 = 0x2a2a2a64657461;
            // "cnurt******deta" in ASCII
            explode_bomb();
        }
        // 0x40159a
        input_strings[num_input_strings] + len - 1 = '\0';
        num_input_strings += 1;
        return input_strings[num_input_strings - 1];

    0x4013f9 skip
        // Return the first non-blank line, or NULL if error occurred.
        do {
            result = fgets(input_strings[num_input_strings], 80, infile);
            if (!result) break;
        } while (blank_line(result));
        return result;

    0x4013bc blank_line(char *str)
        // Return if none of character in str is printable.
        while (*str) {
            // https://stackoverflow.com/questions/37702434/ctype-b-loc-what-is-its-purpose
            if (!isprint(*str)) {
                return 0;
            }
            str += 1;
        }
        return 1;

    0x40143a explode_bomb
        puts(0x4025a3);  // BOOM!!!
        puts(0x4025ac);  // The bomb has blown up.
        exit(8);

## phase_1

Now we finally come to defuse phase 1... Luckily it's quite short.

    0x400ee0 phase_1(char *input)
        if (strings_not_equal(input, 0x402400)) {  // Border relations with Canada have never been better.
            explode_bomb();
        }

    0x401338 strings_not_equal(char *a, char *b)
        if (string_length(a) != string_length(b)) {
            return 1;
        }
        if (!*a) {
            return 0;
        }
        if (*a != *b) {
            return 1;
        }
        while (*a) {
            if (*a != *b) {
                return 1;
            }
            a += 1;
            b += 1;
        }
        return 0;

    0x40131b string_length
        same as strlen

Simply input "Border relations with Canada have never been better.".

## phase_defused

    0x4015c4 phase_defused
        // stack protection at rsp + 0x68
        if (num_input_strings == 6) {
            if (sscanf(input_strings[3], "%d %d %s", rsp + 0x8, rsp + 0xc, rsp + 0x10) == 3) {
                if (strings_not_equal(rsp + 0x10, "DrEvil") == 0) {
                    puts(0x4024f8);  // Curses, you've found the secret phase!
                    puts(0x402520);  // But finding it and solving it are quite different...
                    secret_phase();
                }
            }
            // 0x401635
            puts(0x402558);  // Congratulations! You've defused the bomb!
        }

## phase_2

    0x400efc phase_2(char *input)
        read_six_numbers(input, rsp)
        // The following code requires the sequence starting from rsp
        // be 1, 2, 4, 8, 16, 32
        if (*(int *)rsp != 1) {
            explode_bomb();
        }
        rbx = rsp + 0x4;
        rbp = rsp + 0x18;
        do {
            if (*(rbx - 4) * 2 != *rbx) {
                explode_bomb();
            }
            rbx += 4;
        } while (rbx != rbp);

    0x40145c read_six_numbers(char *input, void *old_rsp)
        // Reads 6 number from input into destination.
        if (sscanf(input, "%d %d %d %d %d %d", old_rsp, old_rsp + 4, old_rsp + 8, old_rsp + 0xc, old_rsp + 0x10, old_rsp + 0x14) <= 6) {
            explode_bomb();
        }

Input "1 2 4 8 16 32".

## phase_3

    0x400f43 phase_3(char *input)
        int a(rsp + 8), b(rsp + 0xc);
        if (sscanf(input, "%d %d", &a, &b) <= 1) {
            explode_bomb();
        }
        // Switch construct
        if (a > 7) {
            explode_bomb();
        }
        // jmpq   *0x402470(,%rax,8)
        // 0x400f7c, 0x400fb9, 0x400f83, 0x400f8a, 0x400f91, 0x400f98, 0x400f9f, 0x400fa6
        if (b != eax) {
            explode_bomb();
        }

Seems we can select any one from eight options.\
Input "0 207".

## phase_4

    0x40100c phase_4(char *input)
        unsigned a(rsp + 8), b(rsp + 0xc);
        if (sscanf(input, "%d %d", &a, &b) != 2 || a > 0xe) {
            explode_bomb();
        }
        if (func4(a, 0, 0xe) || b) {
            explode_bomb();
        }

    0x400fce func4(int a, int b, int c)
        // A quite complicated recursive function.
        int d(eax) = c - b;
        int e(ecx) = (unsigned)d >> 31;
        d = (d + e) >> e;
        e = d + b;
        if (e > a) {
            d = func4(a, b, e - 1) * 2;
        } else {  // 0x400ff2
            if ((unsigned)e < a) {
                d = func4(a, e + 1, c) * 2 + 1;
            }
        }

* a <= 0xe
* func4(a, 0, 0xe) == 0
* b == 0

Considering the range of a, we can just trial and error. Luckily 0 is OK.

Input "0 0".

## phase_5

    0x401062 phase_5(char *input)
        if (string_length(input) != 6) {
            explode_bomb();
        }
        rax = 0
        do {
            *(char *)rsp = *(input + rax);
            *(char *)(rsp + rax + 0x10) = *(char *)(0x4024b0 + (*(long *)rsp & 0xf));
            rax += 1;
        } while (rax != 6);
        *(char *)(rsp + 0x16) = 0;
        // 0x40245e is "flyers"
        if (strings_not_equal(rsp + 10, 0x40245e)) {
            explode_bomb();
        }

Look for the closest character to get "flyers" at 0x4024b0,\
offsets are 9, 0xf, 0xe, 5, 6, 7.\
These should be the lowest 4 bits of characters of input.\
We use the start of lowercase characters.

Input "ionefg".

## phase_6

    0x4010f4 phase_6(char *input)
        int a(rsp)[6];
        read_six_numbers(input, a);

        // 0x401114
        for (int i(r12d) = 0, int *p(r13) = a; ; ++p) {
            if ((unsigned)(*p - 1) > 5) {
                explode_bomb();
            }
            if (++i == 6)
                break;
            // 0x401132
            for (j(ebx) = i; j <= 5; ++j) {
                if (a[j] == *p) {
                    explode_bomb();
                }
            }
        }
        // Requires a be permutation of [1, 2, 3, 4, 5, 6].

        // 0x401153
        for (int i = 0; i != 6; ++i) {
            a[i] = 7 - a[i];
        }

        // 0x40116f

        // First pass of 0x40116f
        esi = 0
        jmp +163
        +130
        do {
            rdx = *(rdx + 8);
            eax += 1;
        } while (ecx != eax);
        jmp +148;
        +143 edx = 0x6032d0;
        +148
        *(rsp + rsi * 2 + 0x20) = rdx
        rsi += 4;
        if (rsi == 0x18)
            break;
        +163 if (*(int *)(rsp + rsi) <= 1) jmp +143;
        eax = 1;
        edx = 0x6032d0;
        jmp +130;

        // Second pass of 0x40116f
        for (esi = 0; esi != 0x18; esi += 4) {
            edx = 0x6032d0;
            if ((ecx = *(int *)(rsp + rsi)) > 1) {
                eax = 1;
                do {
                    rdx = *(rdx + 8);
                    eax += 1;
                } while (ecx != eax);
            }
            *(rsp + rsi * 2 + 0x20) = rdx;
        }

    (gdb) x/12gx 0x6032d0
    0x6032d0 <node1>:       0x000000010000014c      0x00000000006032e0
    0x6032e0 <node2>:       0x00000002000000a8      0x00000000006032f0
    0x6032f0 <node3>:       0x000000030000039c      0x0000000000603300
    0x603300 <node4>:       0x00000004000002b3      0x0000000000603310
    0x603310 <node5>:       0x00000005000001dd      0x0000000000603320
    0x603320 <node6>:       0x00000006000001bb      0x0000000000000000

        // Third pass of 0x40116f
        node *b(rsp + 0x20)[6];
        for (int i = 0; i != 6; ++i) {
            b[i] = 0x6032d0 + (a[i] - 1) * 0x10;  // b[i] = &node<a[i]>
        }

        typedef struct {
            int x;
            int index;
            node *next;
        } node;

        // 0x4011ab
        node *p = b[0];
        for (int i = 1; i != 6; ++i) {
            b[i - 1]->next = b[i];
        }
        b[5]->next = 0;

        // 0x4011da
        for (int i(ebp) = 5; i; --i) {
            if (p->x < p->next->x) {
                explode_bomb();
            }
            p = p->next;
        }
        // Traverse the linked list, the x must be in non-increasing order.
        // So the order should be 3 4 5 6 1 2, which are 7 - input[i].

Input "4 3 2 1 6 5".

## secret_phase

According to `phase_defused`, append " DrEvil" to phase_4 to enter secret_phase.

    0x401242 secret_phase
        long l = strtol(readline(), 0, 0xa);
        if (l - 1 > 0x3e8) {
            explode_bomb();
        }
        if (fun7(0x6030f0, l) != 2) {
            explode_bomb();
        }
        puts(0x402438);  // Wow! You've defused the secret stage!
        phase_defused();

    (gdb) x/60gx 0x6030f0
    0x6030f0 <n1>:  0x0000000000000024      0x0000000000603110
    0x603100 <n1+16>:       0x0000000000603130      0x0000000000000000
    0x603110 <n21>: 0x0000000000000008      0x0000000000603190
    0x603120 <n21+16>:      0x0000000000603150      0x0000000000000000
    0x603130 <n22>: 0x0000000000000032      0x0000000000603170
    0x603140 <n22+16>:      0x00000000006031b0      0x0000000000000000
    0x603150 <n32>: 0x0000000000000016      0x0000000000603270
    0x603160 <n32+16>:      0x0000000000603230      0x0000000000000000
    0x603170 <n33>: 0x000000000000002d      0x00000000006031d0
    0x603180 <n33+16>:      0x0000000000603290      0x0000000000000000
    0x603190 <n31>: 0x0000000000000006      0x00000000006031f0
    0x6031a0 <n31+16>:      0x0000000000603250      0x0000000000000000
    0x6031b0 <n34>: 0x000000000000006b      0x0000000000603210
    0x6031c0 <n34+16>:      0x00000000006032b0      0x0000000000000000
    0x6031d0 <n45>: 0x0000000000000028      0x0000000000000000
    0x6031e0 <n45+16>:      0x0000000000000000      0x0000000000000000
    0x6031f0 <n41>: 0x0000000000000001      0x0000000000000000
    0x603200 <n41+16>:      0x0000000000000000      0x0000000000000000
    0x603210 <n47>: 0x0000000000000063      0x0000000000000000
    0x603220 <n47+16>:      0x0000000000000000      0x0000000000000000
    0x603230 <n44>: 0x0000000000000023      0x0000000000000000
    0x603240 <n44+16>:      0x0000000000000000      0x0000000000000000
    0x603250 <n42>: 0x0000000000000007      0x0000000000000000
    0x603260 <n42+16>:      0x0000000000000000      0x0000000000000000
    0x603270 <n43>: 0x0000000000000014      0x0000000000000000
    0x603280 <n43+16>:      0x0000000000000000      0x0000000000000000
    0x603290 <n46>: 0x000000000000002f      0x0000000000000000
    0x6032a0 <n46+16>:      0x0000000000000000      0x0000000000000000
    0x6032b0 <n48>: 0x00000000000003e9      0x0000000000000000
    0x6032c0 <n48+16>:      0x0000000000000000      0x0000000000000000

    // n1  0x24  n21 n22
    // n21 0x08  n31 n32
    // n22 0x32  n33 n34
    // n31 0x06  n41 n42
    // n32 0x16  n43 n44
    // n33 0x2d  n45 n46
    // n34 0x6b  n47 n48
    // n41 0x01  0   0
    // n42 0x07  0   0
    // n43 0x14  0   0
    // n44 0x23  0   0
    // n45 0x28  0   0
    // n46 0x2f  0   0
    // n47 0x63  0   0
    // n48 0x3e9 0   0

    0x401204 fun7(void *p, long l)
        if (!p) {
            return 0xffffffff;
        }
        if (*p > l) {
            return fun7(*(p + 8), l) * 2;
        } else if (*p == l) {
            return 0;
        else {
            return fun7(*(p + 0x10), l) * 2 + 1;
        }

First, we should avoid entering the first branch (!p), otherwise the return value will be negative.\
So at the final call we should enter the (\*p == l) branch, returning 0.\
To obtain 2 as final result, we need to hit (optionally)(\*p > l), then else(\*p < l) and finally (\*p > l).\
If no (\*p > l) immediately after (\*p == l), at n3x it's ==, n2x < and n1 >.\
Then 0x24 > l, enters n21, 0x08 < l, enters n32, 0x16 == l.\
If there is one (\*p > l) after (\*p == l), at n4x it's ==, n3x >, n2x < and n1 >.\
Then 0x24 > l, enters n21, 0x08 < l, enters n32, 0x16 > l, enters n43, 0x14 == l.

Input "22" or "20".
