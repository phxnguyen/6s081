# MIT 6.S081 – Operating System Engineering

> Learn in public – 1-week sprint: 4–5h/ngày, vừa lý thuyết vừa labs xv6.
> Background: C khá + Linux.

**Link gốc:**
- Schedule (2023): https://pdos.csail.mit.edu/6.828/2023/schedule.html
- xv6 book (RISC-V rev3): https://pdos.csail.mit.edu/6.S081/2023/xv6/book-riscv-rev3.pdf
- Labs: https://pdos.csail.mit.edu/6.828/2023/labs/util.html (đổi `util` → `syscall`, `pgtbl`, `traps`, `cow`, `lock`, `fs`...)
- Code: `git clone git://g.csail.mit.edu/xv6-labs-2023`

## Tiến độ 1 tuần

- [ ] Day 0 – Setup: toolchain + `make qemu` chạy được
- [ ] Day 1 – Overview + xv6 + Lab util
- [ ] Day 2 – Syscall + Page Table + Lab syscall/pgtbl
- [ ] Day 3 – Trap + Scheduling + Lab traps
- [ ] Day 4 – COW Fork + Lab cow
- [ ] Day 5 – Concurrency + Lock + Lab lock/thread
- [ ] Day 6 – File System + Lab fs
- [ ] Day 7 – Tổng ôn + vẽ lại toàn bộ flow

Chi tiết từng ngày: xem [`plan-1-week.md`](./plan-1-week.md)

## Cấu trúc repo

```
6s081/
├── README.md
├── plan-1-week.md
├── notes/   – ghi chép từng ngày (Day1.md, Day2.md...)
├── labs/    – code xv6 labs (mỗi lab 1 folder)
└── TIL/     – cái gì hay thì ghi 5 dòng
```

## Luật

1. Mỗi ngày 1 commit, dù chưa xong: `docs(day2): pgtbl - hiểu copyin/copyout`
2. Kẹt lab >1h → đọc hint/solution, ghi lại ý chính, đi tiếp. Đừng cố 100/100 trong 1 tuần.
3. Cuối ngày update checkbox ở trên + viết 5 dòng tổng kết vào `notes/`.
