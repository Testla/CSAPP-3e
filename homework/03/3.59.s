// (2 ^ 64 * xh + xl) * (2 ^ 64 * yh + yl)
// 2 ^ 128 * xh * yh + 2 ^ 64 * (xh * yl + xl * yh) + xl * yl
// Because only the lower 128 bit will be kept, 2 ^ 128 * xh * yh can be eliminated.
// 2 ^ 64 * (xh * yl + xl * yh) + xl * yl

store_prod:
movq %rdx, %rax
cqto // Sign-extend y to rdx, rax
movq %rsi, %rcx
sarq $63, %rcx // Calculate xh at rcx.
imulq %rax, %rcx // xh * yl
imulq %rsi, %rdx // xl * yh
addq %rdx, %rcx // xh * yl + xl * yh
mulq %rsi // xl * yl
addq %rcx, %rdx // Add (xh * yl + xl * yh) to higher 64 bits.
movq %rax, (%rdi)
movq %rdx, 8(%rdi)
ret

