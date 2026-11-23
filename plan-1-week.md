# Plan 1 tuần – 6.S081 (4–5h/ngày, ~30h)

> Mục tiêu: hiểu Process / VM / Trap / COW / Lock / FS + chạy được xv6 + xong ý chính 6 labs.
> Không đặt mục tiêu full 10 labs 10/10 trong 1 tuần.

## Day 0 – Setup (1h, làm trước Day 1)

- [ ] Cài `qemu-system-misc`, `riscv64-linux-gnu-gcc`, `gdb-multiarch`
- [ ] Clone `xv6-labs-2023`, chạy `make qemu` → gõ được `ls`, `echo hi`
- [ ] Thử `make qemu-gdb` + mở gdb attach để debug
- [ ] Đọc lướt Book Ch.1 (10 trang)

```bash
git clone git://g.csail.mit.edu/xv6-labs-2023 labs/xv6-labs
cd labs/xv6-labs && git checkout util
make qemu
```

Done khi: xv6 boot + thoát bằng `Ctrl-A X`.

---

## Day 1 – Overview + xv6 + Lab util (4.5h)

**Học (1.5h):**
- [ ] Book Ch.1 + Ch.2: OS org, isolation, `fork/exec/wait/exit`
- [ ] Lecture 1 + 2 (x1.5 speed): intro + syscall overview
- [ ] Đọc code: `kernel/proc.c`, `user/sh.c`

**Code (2.5h):**
- [ ] Lab util: `sleep, pingpong, primes, find, xargs`
- [ ] Code để vào `labs/lab-util/`

**Ôn (0.5h):**
- [ ] Viết `notes/Day1.md`: giải thích `fork() -> exec() -> wait()` đi qua hàm nào?

Tự check: shell `sh.c` fork rồi exec như thế nào? FD 0/1/2 là gì? pipe hoạt động sao?

---

## Day 2 – Syscall + Page Table (5h)

**Học (1.5h):**
- [ ] Book Ch.3 + Ch.4: VM, 3-level page table, `satp`, `PTE_R/W/X/U/V`, `TRAMPOLINE`
- [ ] Lecture Pagetables
- [ ] Đọc code: `kernel/vm.c` (`walk`, `mappages`, `copyin/copyout`), `kernel/memlayout.h`

**Code (3h):**
- [ ] Lab syscall: `trace`, `sysinfo`
- [ ] Lab pgtbl: `print pgtbl` (`vmprint`), đọc hiểu `copyin` speedup

**Ôn (0.5h):**
- [ ] Viết `notes/Day2.md`: vẽ VA → PA walk, tại sao user pointer phải qua `copyin`?

Tự check: `TRAPFRAME` nằm ở đâu? `copyout` fail khi nào?

---

## Day 3 – Trap + Scheduling (4h)

**Học (1.5h):**
- [ ] Book Ch.5: trap, `uservec/usertrap/kerneltrap/userret`, timer, `alarm`
- [ ] Lecture Traps + Scheduling: context switch, `swtch`, round-robin
- [ ] Đọc code: `kernel/trap.c`, `kernel/trampoline.S`

**Code (2.5h):**
- [ ] Lab traps: `backtrace`, `alarm`

**Ôn:**
- [ ] Vẽ đường đi 1 syscall: `ecall → uservec → usertrap → syscall → userret → sret`
- [ ] Vẽ đường đi 1 timer interrupt

Done khi: giải thích được `sret` quay về user mode kiểu gì.

---

## Day 4 – COW Fork (5h, khó nhất)

**Học (1.5h):**
- [ ] Book Ch.6: `fork`, `uvmcopy`, lazy allocation, COW
- [ ] Lecture Copy-on-write
- [ ] Đọc code: `kernel/vm.c:uvmcopy`, `kernel/trap.c` page-fault path

**Code (3h):**
- [ ] Lab cow full: refcount (`kalloc.c`), mark PTE read-only + `PTE_COW`, fault handler copy

**Ôn:**
- [ ] Viết `notes/Day4.md`: khi nào tăng/giảm refcount? Khi nào thực sự copy? Leak xảy ra ở đâu?

Đây là lab đáng tiền nhất, đừng skip.

---

## Day 5 – Concurrency + Lock (4h)

**Học (1.5h):**
- [ ] Book Ch.7: `spinlock`, `sleeplock`, `sleep/wakeup`, `acquire/release`, `push_off/pop_off`
- [ ] Lecture Locking + Thread switching
- [ ] Đọc code: `kernel/spinlock.c`, `kernel/sleeplock.c`, `kernel/bio.c`

**Code (2.5h):**
- [ ] Lab lock: `kalloc` + `bcache`
- [ ] Lab thread `uthread switch` nếu còn giờ

**Ôn:**
- [ ] Tại sao phải giữ lock khi `sleep`? `spinlock` vs `sleeplock`? Deadlock trong `bcache` fix bằng gì (lock ordering / hashing)?

---

## Day 6 – File System (5h)

**Học (1.5h):**
- [ ] Book Ch.8 + Ch.10: inode, direct/indirect block, logging, crash recovery
- [ ] Lecture FS
- [ ] Đọc code: `kernel/fs.c`, `kernel/log.c`, `kernel/file.h`

**Code (3h):**
- [ ] Lab fs: `large file`, `symlink`

**Ôn:**
- [ ] symlink lưu path ở đâu? large file thêm mấy level? `log_write/commit/begin_op/end_op` chống crash kiểu gì?

---

## Day 7 – Tổng ôn (3–4h)

- [ ] 1h: Vẽ 1 tờ A4: Boot → Syscall → VM → Trap → Sched → Lock → FS
- [ ] 1.5h: Làm lại chỗ fail trong 6 ngày, đọc lại `vmprint / backtrace / cow` không nhìn doc
- [ ] 1h: Trả lời miệng, ghi âm hoặc viết vào `notes/Day7.md`:
  1. fork vs thread?
  2. pagetable để làm gì?
  3. COW tiết kiệm gì, tốn gì?
  4. FS chống crash kiểu gì?
  5. spinlock hoạt động sao?

Bỏ qua tuần này (để tuần 2 nếu cần full điểm): lab net, mmap, multithreading.
