  .text
  mov $30, %eax
func:
  cmp $3, %eax
  je out
  sub $1, %eax
  call func
out:
