  .text
mov $0, %eax
loop:
  cmpl $10, %eax
  je end
  add $1, %eax
  jmp loop
end:
