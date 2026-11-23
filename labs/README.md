# Labs

Mỗi lab 1 folder, clone từ `xv6-labs-2023` ra hoặc copy file đã làm vào.

```
labs/
├── lab-util/    – sleep, pingpong, primes, find, xargs
├── lab-syscall/ – trace, sysinfo
├── lab-pgtbl/   – vmprint
├── lab-traps/   – backtrace, alarm
├── lab-cow/     – copy-on-write
├── lab-lock/    – kalloc, bcache
└── lab-fs/      – large file, symlink
```

Gợi ý: giữ nguyên repo xv6 riêng, chỉ copy diff vào đây để log learn-in-public cho nhẹ.
`git diff > ../../labs/lab-cow/cow.patch`
